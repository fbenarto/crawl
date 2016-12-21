//#include "AppHdr.h"

#include "mon-cast.h"

#include <algorithm>
#include <cmath>
#include <unordered_set>

#include "act-iter.h"
#include "areas.h"
#include "bloodspatter.h"
#include "branch.h"
#include "cloud.h"
#include "colour.h"
#include "coordit.h"
#include "database.h"
#include "delay.h"
#include "directn.h"
#include "english.h"
#include "env.h"
#include "evoke.h"
#include "exclude.h"
#include "fight.h"
#include "fprop.h"
#include "godpassive.h"
#include "items.h"
#include "libutil.h"
#include "losglobal.h"
#include "mapmark.h"
#include "message.h"
#include "misc.h"
#include "mon-act.h"
#include "mon-behv.h"
#include "mon-book.h"
#include "mon-clone.h"
#include "mon-death.h"
#include "mon-gear.h"
#include "mon-pathfind.h"
#include "mon-pick.h"
#include "mon-place.h"
#include "mon-project.h"
#include "mon-speak.h"
#include "mon-tentacle.h"
#include "mutation.h"
#include "player-stats.h"
#include "random.h"
#include "religion.h"
#include "shout.h"
#include "showsymb.h"
#include "spl-clouds.h"
#include "spl-damage.h"
#include "spl-goditem.h"
#include "spl-monench.h"
#include "spl-selfench.h"
#include "spl-summoning.h"
#include "spl-transloc.h"
#include "spl-util.h"
#include "spl-zap.h" // spell_to_zap
#include "state.h"
#include "stepdown.h"
#include "stringutil.h"
#include "target.h"
#include "teleport.h"
#include "terrain.h"
#ifdef USE_TILE
#include "tiledef-dngn.h"
#endif
#include "timed_effects.h"
#include "traps.h"
#include "travel.h"
#include "view.h"
#include "viewchar.h"
#include "xom.h"

static const int MIN_DREAM_SUCCESS_POWER = 25;

static void _sheep_message(int num_sheep, int sleep_pow, actor& foe)
{
    string message;

    // Determine messaging based on sleep strength.
    if (sleep_pow >= 125)
        message = "You are overwhelmed by glittering dream dust!";
    else if (sleep_pow >= 75)
        message = "The dream sheep are wreathed in dream dust.";
    else if (sleep_pow >= MIN_DREAM_SUCCESS_POWER)
    {
        message = make_stringf("The dream sheep shake%s wool and sparkle%s.",
                               num_sheep == 1 ? "s its" : " their",
                               num_sheep == 1 ? "s": "");
    }
    else // if sleep fails
    {
        message = make_stringf("The dream sheep ruffle%s wool and motes of "
                               "dream dust sparkle, to no effect.",
                               num_sheep == 1 ? "s its" : " their");
    }

    if (!foe.is_player()) // Messaging for non-player targets
    {
        const char* pluralize = num_sheep == 1 ? "s": "";
        const string foe_name = foe.name(DESC_THE);
        if (you.see_cell(foe.pos()) && sleep_pow)
        {
            mprf(foe.as_monster()->friendly() ? MSGCH_FRIEND_SPELL
                                              : MSGCH_MONSTER_SPELL,
                 "As the sheep sparkle%s and sway%s, %s falls asleep.",
                 pluralize,
                 pluralize,
                 foe_name.c_str());
        }
        else // if dust strength failure for non-player
        {
            mprf(foe.as_monster()->friendly() ? MSGCH_FRIEND_SPELL
                                              : MSGCH_MONSTER_SPELL,
                 "The dream sheep attempt%s to lull %s to sleep.",
                 pluralize,
                 foe_name.c_str());
            mprf("%s is unaffected.", foe_name.c_str());
        }
    }
    else
    {
        mprf(MSGCH_MONSTER_SPELL, "%s%s", message.c_str(),
             sleep_pow ? " You feel drowsy..." : "");
    }
}

static void _dream_sheep_sleep(monster& mons, actor& foe)
{
    // Shepherd the dream sheep.
    int num_sheep = 0;
    for (monster_near_iterator mi(foe.pos(), LOS_NO_TRANS); mi; ++mi)
        if (mi->type == MONS_DREAM_SHEEP)
            num_sheep++;

    // The correlation between amount of sheep and duration of
    // sleep is randomised, but bounds are 5 to 20 turns of sleep.
    // More dream sheep are both more likely to succeed and to have a
    // stronger effect. Too-weak attempts get blanked.
    // Special note: a single sheep has a 1 in 25 chance to succeed.
    int sleep_pow = min(150, random2(num_sheep * 25) + 1);
    if (sleep_pow < MIN_DREAM_SUCCESS_POWER)
        sleep_pow = 0;

    // Communicate with the player.
    _sheep_message(num_sheep, sleep_pow, foe);

    // Put the player to sleep.
    if (sleep_pow)
        foe.put_to_sleep(&mons, sleep_pow, false);
}

void mons_cast(monster* mons, bolt pbolt, spell_type spell_cast,
               mon_spell_slot_flags slot_flags, bool do_noise)
{
    // check sputtercast state for e.g. orb spiders. assumption: all
    // sputtercasting monsters have one charge status and use it for all of
    // their spells.
    if (max_mons_charge(mons->type) > 0 && !_spell_charged(mons))
        return;

    setup_mons_cast(mons, pbolt, spell_cast);

    const unsigned int flags = get_spell_flags(spell_cast);
    actor* const foe = mons->get_foe();
    const mons_spell_logic* logic = map_find(spell_to_logic, spell_cast);
    const mon_spell_slot slot = {spell_cast, 0, slot_flags};

    int sumcount = 0;
    int sumcount2;
    int duration = 0;

    dprf("Mon #%d casts %s (#%d)",
         mons->mindex(), spell_title(spell_cast), spell_cast);
    ASSERT(!(flags & SPFLAG_TESTING));
    // Targeted spells need a valid target.
    // Wizard-mode cast monster spells may target the boundary (shift-dir).
    ASSERT(map_bounds(pbolt.target) || !(flags & SPFLAG_TARGETING_MASK));

    // Maybe cast abjuration instead of certain summoning spells.
    if (mons->can_see(you) && _mons_will_abjure(mons, spell_cast))
    {
        if (do_noise)
        {
            pbolt.range = 0;
            pbolt.glyph = 0;
            mons_cast_noise(mons, pbolt, SPELL_ABJURATION, MON_SPELL_NO_FLAGS);
        }
        _monster_abjuration(mons, true);
        return;
    }

    if (do_noise)
        mons_cast_noise(mons, pbolt, spell_cast, slot_flags);

    if (logic && logic->cast)
    {
        logic->cast(*mons, slot, pbolt);
        return;
    }

    const god_type god = _find_god(*mons, slot_flags);
    const int splpow = _mons_spellpower(spell_cast, *mons);

    switch (spell_cast)
    {
    default:
        break;

    case SPELL_DREAM_DUST:
        _dream_sheep_sleep(*mons, *foe);
        return;
    }
}
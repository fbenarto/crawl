#include "AppHdr.h"

#include "mon-death.h"

#include "act-iter.h"
#include "areas.h"
#include "arena.h"
#include "artefact.h"
#include "art-enum.h"
#include "attitude-change.h"
#include "bloodspatter.h"
#include "butcher.h"
#include "cloud.h"
#include "cluautil.h"
#include "colour.h"
#include "coordit.h"
#include "dactions.h"
#include "database.h"
#include "delay.h"
#include "describe.h"
#include "dgn-overview.h"
#include "english.h"
#include "env.h"
#include "fineff.h"
#include "food.h"
#include "godabil.h"
#include "godblessing.h"
#include "godcompanions.h"
#include "godconduct.h"
#include "godpassive.h" // passive_t::bless_followers, share_exp, convert_orcs
#include "hints.h"
#include "hiscores.h"
#include "itemname.h"
#include "itemprop.h"
#include "items.h"
#include "kills.h"
#include "libutil.h"
#include "mapdef.h"
#include "mapmark.h"
#include "message.h"
#include "mon-abil.h"
#include "mon-behv.h"
#include "mon-gear.h"
#include "mon-place.h"
#include "mon-poly.h"
#include "mon-speak.h"
#include "mon-tentacle.h"
#include "mutation.h"
#include "nearby-danger.h"
#include "notes.h"
#include "output.h"
#include "religion.h"
#include "rot.h"
#include "spl-damage.h"
#include "spl-goditem.h"
#include "spl-miscast.h"
#include "spl-summoning.h"
#include "sprint.h" // SPRINT_MULTIPLIER
#include "state.h"
#include "stepdown.h"
#include "stringutil.h"
#include "target.h"
#include "terrain.h"
#include "timed_effects.h"
#include "traps.h"
#include "unwind.h"
#include "viewchar.h"
#include "view.h"

static int _calc_monster_experience(monster* victim, killer_type killer,
                                    int killer_index)
{
    const int experience = exper_value(*victim);

    if (!experience || !MON_KILL(killer) || invalid_monster_index(killer_index))
        return 0;

    monster* mon = &menv[killer_index];
    if (!mon->alive() || !mons_gives_xp(*victim, *mon))
        return 0;

    return experience;
}

static void _give_monster_experience(int experience, int killer_index)
{
    if (experience <= 0 || invalid_monster_index(killer_index))
        return;

    monster* mon = &menv[killer_index];
    if (!mon->alive())
        return;

    if (mon->gain_exp(experience))
    {
        if (!have_passive(passive_t::bless_followers) || !one_chance_in(3))
            return;

        // Randomly bless the follower who gained experience.
        if (random2(you.piety) >= piety_breakpoint(2))
            bless_follower(mon);
    }
}

static void _beogh_spread_experience(int exp)
{
    int total_hd = 0;

    for (monster_near_iterator mi(&you); mi; ++mi)
    {
        if (is_orcish_follower(**mi))
            total_hd += mi->get_experience_level();
    }

    if (total_hd <= 0)
        return;

    for (monster_near_iterator mi(&you); mi; ++mi)
        if (is_orcish_follower(**mi))
        {
            _give_monster_experience(exp * mi->get_experience_level() / total_hd,
                                         mi->mindex());
        }
}

static int _calc_player_experience(const monster* mons)
{
    int experience = exper_value(*mons);
    if (!experience)
        return 0;

    const bool already_got_half_xp = testbits(mons->flags, MF_PACIFIED);
    const int half_xp = (experience + 1) / 2;

    if (!mons->damage_total)
    {
        mprf(MSGCH_WARN, "Error, exp for monster with no damage: %s",
             mons->name(DESC_PLAIN, true).c_str());
        return 0;
    }

    experience = (experience * mons->damage_friendly / mons->damage_total
                  + 1) / 2;
    ASSERT(mons->damage_friendly <= 2 * mons->damage_total);

    // Note: This doesn't happen currently since monsters with
    //       MF_PACIFIED have always gone through pacification,
    //       hence also have MF_WAS_NEUTRAL. [rob]
    if (already_got_half_xp)
    {
        experience -= half_xp;
        if (experience < 0)
            experience = 0;
    }

    return experience;
}

static void _give_player_experience(int experience, killer_type killer,
                                    bool pet_kill, bool was_visible)
{
    if (experience <= 0 || crawl_state.game_is_arena())
        return;

    unsigned int exp_gain = 0;
    gain_exp(experience, &exp_gain);

    kill_category kc =
            (killer == KILL_YOU || killer == KILL_YOU_MISSILE) ? KC_YOU :
            (pet_kill)                                         ? KC_FRIENDLY :
                                                                 KC_OTHER;
    PlaceInfo& curr_PlaceInfo = you.get_place_info();
    PlaceInfo  delta;

    delta.mon_kill_num[kc]++;
    delta.mon_kill_exp += exp_gain;

    you.global_info += delta;
    you.global_info.assert_validity();

    curr_PlaceInfo += delta;
    curr_PlaceInfo.assert_validity();

    // Give a message for monsters dying out of sight.
    if (exp_gain > 0 && !was_visible)
        mpr("You feel a bit more experienced.");

    if (kc == KC_YOU && have_passive(passive_t::share_exp))
        _beogh_spread_experience(experience / 2);
}

static void _give_experience(int player_exp, int monster_exp,
                             killer_type killer, int killer_index,
                             bool pet_kill, bool was_visible)
{
    _give_player_experience(player_exp, killer, pet_kill, was_visible);
    _give_monster_experience(monster_exp, killer_index);
}
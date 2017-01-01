#ifndef EXPERIENCE_H
#define EXPERIENCE_H

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

class Experience
{
    public:

    static int _calc_monster_experience(monster* victim, killer_type killer,
                                        int killer_index);

    static void _give_monster_experience(int experience, int killer_index);

    static void _beogh_spread_experience(int exp);

    static int _calc_player_experience(const monster* mons);

    static void _give_player_experience(int experience, killer_type killer,
                                        bool pet_kill, bool was_visible);

    static void _give_experience(int player_exp, int monster_exp,
                                 killer_type killer, int killer_index,
                                 bool pet_kill, bool was_visible);
};

#endif
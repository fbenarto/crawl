#include "AppHdr.h"

#include "hiscores.h"

#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <memory>
#ifndef TARGET_COMPILER_VC
#include <unistd.h>
#endif

#include "branch.h"
#include "chardump.h"
#include "cio.h"
#include "dungeon.h"
#include "end.h"
#include "english.h"
#include "files.h"
#include "initfile.h"
#include "itemprop.h"
#include "items.h"
#include "jobs.h"
//#include "kills.h"
//#include "libutil.h"
#include "menu.h"
#include "misc.h"
//#include "mon-util.h"
//#include "options.h"
//#include "ouch.h"
#include "place.h"
#include "religion.h"
#include "skills.h"
#include "state.h"
#include "status.h"
#include "stringutil.h"
#ifdef USE_TILE
 #include "tilepick.h"
#endif
#ifdef USE_TILE_LOCAL
 #include "tilereg-crt.h"
#endif
#include "unwind.h"
#include "version.h"

class Score
{
    public:

    static int _award_modified_experience()
    {
        int xp = you.experience;
        int result = 0;

        if (xp <= 250000)
            return xp * 7 / 10;

        result += 250000 * 7 / 10;
        xp -= 250000;

        if (xp <= 750000)
        {
            result += xp * 4 / 10;
            return result;
        }

        result += 750000 * 4 / 10;
        xp -= 750000;

        if (xp <= 2000000)
        {
            result += xp * 2 / 10;
            return result;
        }

        result += 2000000 * 2 / 10;
        xp -= 2000000;

        result += xp / 10;

        return result;
    }

    static void calculate_score(int points, int num_runes, int num_diff_runes, int death_type)
    {
        // sprint games could overflow a 32 bit value
        uint64_t pt = points + _award_modified_experience();
        num_runes      = runes_in_pack();
        num_diff_runes = num_runes;

        // There's no point in rewarding lugging artefacts. Thus, no points
        // for the value of the inventory. -- 1KB
        if (death_type == KILLED_BY_WINNING)
        {
            pt += 250000; // the Orb
            pt += num_runes * 2000 + 4000;
            pt += ((uint64_t)250000) * 25000 * num_runes * num_runes
                / (1+you.num_turns);
        }
        pt += num_runes * 10000;
        pt += num_runes * (num_runes + 2) * 1000;

        points = pt;
    }
};
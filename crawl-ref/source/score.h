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
#include <iostream>

bool newscoredebug;

static int _award_modified_experience()
{
    int xp = you.experience;
    int result = 0;

    if (xp <= 250000)
    {
        cout << "Method 1 Jalan";
        newscoredebug = true;
        return xp * 7 / 10;
    }

    result += 250000 * 7 / 10;
    xp -= 250000;

    if (xp <= 750000)
    {
        result += xp * 4 / 10;
        cout << "Method 2 Jalan";
        newscoredebug = true;
        return result;
    }

    result += 750000 * 4 / 10;
    xp -= 750000;

    if (xp <= 2000000)
    {
        result += xp * 2 / 10;
        cout << "Method 3 Jalan";
        newscoredebug = true;
        return result;
    }

    result += 2000000 * 2 / 10;
    xp -= 2000000;

    result += xp / 10;
    cout << "Method 4 Jalan";
    newscoredebug = true;

    return result;
}
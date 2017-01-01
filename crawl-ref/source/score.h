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

    static int _award_modified_experience();

    static void calculate_score(int points, int num_runes, int num_diff_runes, int death_type);
};
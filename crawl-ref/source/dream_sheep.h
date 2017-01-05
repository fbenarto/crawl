#ifndef DREAM_SHEEP_H
#define DREAM_SHEEP_H

#include "AppHdr.h"

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

class Dream_Sheep
{
	public:

	static const bool mini = false;

	static const int MIN_DREAM_SUCCESS_POWER;

	static void _sheep_message(int num_sheep, int sleep_pow, actor& foe);

	static void _dream_sheep_sleep(monster& mons, actor& foe);
};

#endif
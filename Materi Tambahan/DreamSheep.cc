class DreamSheep implements MonsterCreation
{
	public addData()
	{
		#define DUMMY(id, glyph, colour, name, tile) \
		{ \
		    (id), (glyph), (colour), (name), \
		    M_CANT_SPAWN, \
		    MR_NO_FLAGS, \
		    10, (id), (id), MH_NONLIVING, 10, \
		    { AT_NO_ATK, AT_NO_ATK, AT_NO_ATK, AT_NO_ATK }, \
		    0, 0, \
		    0, 0, MST_NO_SPELLS, CE_CLEAN, S_SILENT, \
		    I_BRAINLESS, HT_LAND, 0, DEFAULT_ENERGY, \
		    MONUSE_NOTHING, SIZE_MEDIUM, MON_SHAPE_MISC, \
		    {(tile)}, TILE_ERROR \
		},

		{
			MONS_DREAM_SHEEP, 'Y', CYAN, "dream sheep",
		    M_WARM_BLOOD | M_HERD,
		    MR_NO_FLAGS,
		    10, MONS_SHEEP, MONS_DREAM_SHEEP, MH_NATURAL, 30,
		    { {AT_BITE, AF_PLAIN, 13}, AT_NO_ATK, AT_NO_ATK, AT_NO_ATK },
		    9, 220,
		    2, 10, MST_DREAM_SHEEP, CE_CLEAN, S_BLEAT,
		    I_ANIMAL, HT_LAND, 10, DEFAULT_ENERGY,
		    MONUSE_NOTHING, SIZE_MEDIUM, MON_SHAPE_QUADRUPED_TAILLESS,
		    {TILEP_MONS_DREAM_SHEEP}, TILE_CORPSE_DREAM_SHEEP
		}
	}

	public addSpells()
	{
		if (!target || !target->alive())
	        return;

	    // Shepherd the dream sheep
	    vector<monster*> dream_herd;
	    for (monster_near_iterator mi(target->pos(), LOS_NO_TRANS); mi; ++mi)
	    {
	        if (mi->type == MONS_DREAM_SHEEP)
	            dream_herd.push_back(*mi);
	    }
	    const int num_sheep = dream_herd.size();
	    dprf("Dream herd size: %d", num_sheep);

	    // Sleep duration depends on how many dream sheep are available to combine
	    // their strength. The correlation between amount of sheep and duration of
	    // sleep is randomised somewhat, but has a minimum of 5 turns and max of 20.
	    // More dream sheep are both more likely to succeed and more likely to have
	    // a stronger effect.
	    int sleep_pow = min(150, random2(num_sheep * 25) + 1);
	    if (sleep_pow < 25)
	        sleep_pow = 0; // Weak attempts should not succeed.
	                       // Single sheep have a 1 in 25 chance to sleep.

	    // Communicate to the player.
	    _sheep_message(num_sheep, sleep_pow, target);

	    // This takes the results generated above and applies a sleep duration and
	    // sleep immunity duration (if player).
	    // Sleep duration is 5 to 20 turns, depending on strength.
	    // Immunity is 4 to 8 turns regardless of duration of sleep.
	    if (sleep_pow)
	    {
	        target->put_to_sleep(mons, sleep_pow, false);
	        if (target->is_player())
	            you.set_duration(DUR_SLEEP_IMMUNITY, random_range(4, 8));
	    }
	}

	public addAbilities()
	{
		actor *foe = mons->get_foe();
        if (!mons_is_confused(mons) && !mons_is_fleeing(mons)
            && !is_sanctuary(mons->pos()) && !is_sanctuary(foe->pos())
            && foe && foe->can_sleep() && !foe->asleep()
            && one_chance_in(5))
        {
            _dream_sheep_sleep(mons, foe);
            used = true;
        }
	}

	public addBehaviors()
	{
		
	}

	public addSpawns()
	{
		
	}
}
class MonsterCreation
{
	//Responsibility 1
	/*
		Spells
	*/
	public addSpells()
	{
		
	}

	//Responsibility 2
	/*
		Abilities
	*/
	public addAbilities()
	{
		
	}

	//Responsibility 3
	/*
		Behaviors
	*/
	public addBehaviors()
	{
		
	}

	//Responsibility 4
	/*
		Spawns
	*/
	public addSpawns()
	{
		
	}
}

class Spells implements MonsterCreation
{
	MonsterCreation.addSpells()
	{
		//Monster 1
		monster dragon
		spell fire
		spell incinerate
		spell destroy
		
		add(dragon, fire)
		add(dragon, incinerate)
		add(dragon, incinerate)

		//Monster 2
		monster serpent
		spell petrify
		spell curse
		spell poison
		
		add(serpent, petrify)
		add(serpent, curse)
		add(serpent, poison)

		//Monster n
		monster newMonster
		spell newCurse1
		spell newCurse2
		spell newCurse3
		
		add(newMonster, newCurse1)
		add(newMonster, newCurse2)
		add(newMonster, newCurse3)
	}
}

class Abilities implements MonsterCreation
{
	MonsterCreation.addAbilities()
	{
		//Monster 1
		monster dragon
		ability stoneSkin
		ability flying
		ability magic
		
		add(dragon, stoneSkin)
		add(dragon, flying)
		add(dragon, magic)

		//Monster 2
		monster serpent
		ability swimming
		ability poisonImmunity
		ability magicResist
		
		add(serpent, swimming)
		add(serpent, poisonImmunity)
		add(serpent, magicResist)

		//Monster n
		monster newMonster
		ability newAbility1
		ability newAbility2
		ability newAbility3
		
		add(newMonster, newAbility1)
		add(newMonster, newAbility2)
		add(newMonster, newAbility3)
	}
}

class Behaviors implements MonsterCreation
{
	MonsterCreation.addBehaviors()
	{
		//Monster 1
		monster dragon
		player player
		
		if(dragon sees player)
		{
			dragon.kill(player)
			dragon.useSpell(fire)
		}

		//Monster 2
		monster serpent
		player player
		
		if(serpent sees player)
		{
			serpent.pursue(player)
			serpent.useSpell(poison)
		}

		//Monster n
		monster newMonster
		player player
		
		if(newMonster sees player)
		{
			newMonster.runAwayFrom(player)
		}
	}
}

class Spawn implements MonsterCreation
{
	MonsterCreation.addSpawns()
	{
		//Monster 1
		monster dragon
		level dungeon5
		coordinate here
		
		spawnLocation(dragon, dungeon5, here)

		//Monster 2
		monster serpent
		level dungeon7
		coordinate there
		
		spawnLocation(serpent, dungeon7, there)

		//Monster n
		monster newMonster
		level dungeon1
		coordinate center
		
		spawnLocation(newMonster, dungeon1, center)
	}
}
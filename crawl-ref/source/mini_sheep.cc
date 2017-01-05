#include "mini_sheep.h"

const int Mini_Sheep::MIN_DREAM_SUCCESS_POWER = 25;

void Mini_Sheep::_sheep_message(int num_sheep, int sleep_pow, actor& foe)
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

void Mini_Sheep::_dream_sheep_sleep(monster& mons, actor& foe)
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
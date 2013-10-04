//
//  Enemy.cpp
//  game
//
//  Created by Christopher Harris on 9/27/13.
//
//

#include "Enemy.h"

#include "Square.h"

#include <math.h>

using namespace Zeni;
using namespace std;

void Enemy::render(const String &texture, const Zeni::Color &filter) const
{
    Game_Object::render(texture, filter);
}

void Enemy::doLogic(float timestep, Game_Object* player)
{
	seen_last_frame = square->isVisible();

    Game_Object::doLogic(timestep, player);

	if(square->isVisible()) last_seen_timer.stop();
	else last_seen_timer.start();

    
    Point2f playerPos = player->getRealPosition();
    Point2f selfPos = getRealPosition();
    setTheta(atan2(playerPos.x - selfPos.x, playerPos.y - selfPos.y) - Global::pi_over_two);
}

void Enemy::check_and_play_sound_seen(const Zeni::String& name)
{
	if(last_seen_timer.seconds() >= seen_threshold)
	{
		play_sound(name);
		last_seen_timer.reset();
		seen_threshold = random_generator.rand_lt(5) + 5;  //5 - 9
	}
}

void Enemy::check_and_play_sound_move(const Zeni::String& name)
{
	if(movement_sound_timer.seconds() >= heard_threshold)
	{
		play_sound(name);
		movement_sound_timer.reset();
		heard_threshold = random_generator.rand_lt(5) + 5;  //5 -9
	}
}
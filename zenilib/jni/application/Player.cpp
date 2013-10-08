//
//  Player.cpp
//  game
//
//  Created by Christopher Harris on 9/25/13.
//
//

#include "Player.h"

using namespace Zeni;
using namespace std;

void Player::render() const
{
    Game_Object::render("player");
}

void Player::doLogic(float timestep, Game_Object* player)
{
	bool wasMoving = isMoving();
    Game_Object::doLogic(timestep, player);

	if(!wasMoving && isMoving())
	{
		play_sound("foot_step");
	}
}
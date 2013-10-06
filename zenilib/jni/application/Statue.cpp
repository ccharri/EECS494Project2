//
//  Statue.cpp
//  game
//
//  Created by Christopher Harris on 9/27/13.
//
//

#include "Statue.h"

#include <math.h>

#include "Square.h"

using namespace Zeni;
using namespace std;

void Statue::render() const
{
    if(!square) return;
    
    if(getSquare()->isVisible())
        Enemy::render("statue");
}

void Statue::doLogic(float timestep, Game_Object* player)
{
    if(!square) return;
    
	bool seen = seen_last_frame;

    if(!square->isVisible())
        Enemy::doLogic(timestep, player);
    else
        seen_last_frame = square->isVisible();

	if(isMoving() && !square->isVisible())
	{
		check_and_play_sound_move("stone_slide");
	}

	bool should_play_visibility_sound = !seen && square->isVisible();
	float distance_from_player = Vector2f(player->getRealPosition() - getRealPosition()).magnitude();

	if(!should_play_visibility_sound) return;

	if(distance_from_player <= (1.5 * SQUARE_SIZE.x))
	{
		check_and_play_sound_seen("close_scare");
	}
	else if(distance_from_player <= (3 * SQUARE_SIZE.x))
	{
		check_and_play_sound_seen("medium_scare");
	}
	else 
	{
		check_and_play_sound_seen("far_scare");
	}
}
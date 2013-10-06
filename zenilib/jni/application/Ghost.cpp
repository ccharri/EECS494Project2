//
//  Ghost.cpp
//  game
//
//  Created by Christopher Harris on 9/27/13.
//
//

#include "Ghost.h"

#include <math.h>

#include "cheats.h"
#include "Square.h"

using namespace Zeni;
using namespace std;

void Ghost::render() const
{
    if(!square) return;
    
    if(see_all || !getSquare()->isVisible())
        Enemy::render("ghost");
}

void Ghost::doLogic(float timestep, Game_Object* player)
{
    if(!square) return;
    
    if(always_use_enemy_logic || !getSquare()->isVisible())
        Enemy::doLogic(timestep, player);
}

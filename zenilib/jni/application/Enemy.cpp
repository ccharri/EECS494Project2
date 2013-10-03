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
    Game_Object::doLogic(timestep, player);
    
    Point2f playerPos = player->getRealPosition();
    Point2f selfPos = getRealPosition();
    setTheta(atan2(playerPos.x - selfPos.x, playerPos.y - selfPos.y) - Global::pi_over_two);
}
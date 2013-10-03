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
    if(getSquare()->isVisible())
        Enemy::render("statue");
}

void Statue::doLogic(float timestep, Game_Object* player)
{
    if(!getSquare()->isVisible())
        Enemy::doLogic(timestep, player);
}
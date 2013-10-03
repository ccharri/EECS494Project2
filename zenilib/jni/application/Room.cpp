//
//  Room.cpp
//  game
//
//  Created by Christopher Harris on 9/23/13.
//
//

#include "Room.h"

#include <algorithm>
#include <math.h>
#include <zenilib.h>

#include "Player.h"

using namespace Zeni;
using namespace std;

void Room::removeObject(Game_Object* object_)
{
    auto it = find(objects.begin(), objects.end(), object_);

    if(it != objects.end()) objects.erase(it);
}

void Room::render(Player* player) const
{
    for(vector<Square*> vector : squares)
    {
        for(Square* square : vector)
        {
            square->render(player);
        }
    }
    
    for(Game_Object* object : objects)
    {
        object->render();
    }
}



void Room::doLogic(float timestep, Player* player)
{
    for(vector<Square*> vector : squares)
    {
        for(Square* square : vector)
        {
            square->doLogic(timestep);

            Point2f squarePos = square->getRealPosition();
            Point2f playerPos = player->getRealPosition();
            
            
            //TODO: Fix Left-facing Rotation Rendering
            
            float distance = abs(Vector2f(squarePos - playerPos).magnitude());
            float playerAngle = -player->getTheta();
            while(playerAngle > M_PI) playerAngle -= 2*M_PI;
            while(playerAngle < -M_PI) playerAngle += 2*M_PI;
            float arc = player->getLightArc();
            float angleMin = playerAngle - arc/2.;
            float angleMax = playerAngle + arc/2.;
            float angle = atan2((squarePos.y - playerPos.y),(squarePos.x - playerPos.x));
            bool inAngle = (angle >= angleMin) && (angle <= angleMax);
            
            if((player->isLightOn()) && !(square == player->getSquare()) && ((distance <= (player->getLightDist() * player->getSquare()->getSize().x)) && (inAngle)))
            {
                square->setVisible(true);
            }
            else {
                square->setVisible(false);
            }
        }
    }
    
    for(Game_Object* object : objects)
    {
        object->doLogic(timestep, player);
    }
}
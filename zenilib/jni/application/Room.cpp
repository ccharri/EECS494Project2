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
#include "Enemy.h"
#include "Door.h"

#include "cheats.h"

using namespace Zeni;
using namespace std;

Point2f Room::getRealPosition() const
{
	return Point2f(position.x * size.x * squares[0][0]->getSize().x, position.y * size.y * squares[0][0]->getSize().y);
}

void Room::removeObject(Game_Object* object_)
{
    auto it = find(objects.begin(), objects.end(), object_);

    if(it != objects.end()) objects.erase(it);
}

void Room::randomizeEnemies()
{
	for(Game_Object* object : objects)
	{
		Enemy* enemy = dynamic_cast<Enemy*>(object);

		if(!enemy) continue;

		bool locationFound = false;

		while(!locationFound)
		{
			int x = random_generator.rand_lt(getSize().x);
			int y = random_generator.rand_lt(getSize().y);

			Square* square = squares[x][y];
			if(!square->isPathable()) continue;
			if(dynamic_cast<Door*>(square)) continue;

			Square* oldsquare = enemy->getSquare();
			oldsquare->removeObject(enemy);
			square->addObject(enemy);
			enemy->setSquare(square);
			enemy->stopMovement();
			locationFound = true;
		}
	}
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
            
            if(see_all ||( (player->isLightOn()) && !(square == player->getSquare()) && ((distance <= (player->getLightDist() * player->getSquare()->getSize().x)) && (inAngle))))
            {
                square->setVisible(true);
            }
            else {
                square->setVisible(false);
            }
        }
    }
    
	for_each(objects.begin(), objects.end(), [&](Game_Object* object)
	{
		object->doLogic(timestep, player);
	});
}

Door* Room::addDoorNorth() 
{
	Vector2f location = Vector2f((int)((getSize().x -1) /2.), 0);

	if(hasDoorNorth) return static_cast<Door*>(squares[location.x][location.y]);

	Door* newDoor = new Door(location);
	Square* oldSquare = squares[location.x][location.y];
	newDoor->replaceConnections(oldSquare);
	delete squares[location.x][location.y];
	squares[location.x][location.y] = newDoor;
	newDoor->setRoom(this);
	hasDoorNorth = true;
	return newDoor;
}

Door* Room::addDoorEast() 
{
	Vector2f location = Vector2f((int)(getSize().x-1.), (int)((getSize().y -1) /2.));

	if(hasDoorEast) return static_cast<Door*>(squares[location.x][location.y]);

	Door* newDoor = new Door(location);
	Square* oldSquare = squares[location.x][location.y];
	newDoor->replaceConnections(oldSquare);
	delete squares[location.x][location.y];
	squares[location.x][location.y] = newDoor;
	newDoor->setRoom(this);
	hasDoorEast = true;
	return newDoor;
}

Door* Room::addDoorSouth() 
{
	Vector2f location = Vector2f((int)((getSize().x -1) /2.), (int)(getSize().y - 1));

	if(hasDoorSouth) return static_cast<Door*>(squares[location.x][location.y]);

	Door* newDoor = new Door(location);
	Square* oldSquare = squares[location.x][location.y];
	newDoor->replaceConnections(oldSquare);
	delete squares[location.x][location.y];
	squares[location.x][location.y] = newDoor;
	newDoor->setRoom(this);
	hasDoorSouth = true;
	return newDoor;
}

Door* Room::addDoorWest() 
{
	Vector2f location = Vector2f(0, (int)(getSize().y -1) /2.);

	if(hasDoorWest) return static_cast<Door*>(squares[location.x][location.y]);

	Door* newDoor = new Door(location);
	Square* oldSquare = squares[location.x][location.y];
	newDoor->replaceConnections(oldSquare);
	delete squares[location.x][location.y];
	squares[location.x][location.y] = newDoor;
	newDoor->setRoom(this);
	hasDoorWest = true;
	return newDoor;
}
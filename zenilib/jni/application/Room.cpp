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
#include "Ghost.h"
#include "Statue.h"
#include "Door.h"

#include "cheats.h"

using namespace Zeni;
using namespace std;

Room::Room(const Zeni::Point2f& position_, const Zeni::Vector2f& size_) : random_generator(Zeni::Random()), position(position_), size(size_), hasDoorNorth(false), hasDoorEast(false), hasDoorSouth(false), hasDoorWest(false)
{
};

Point2f Room::getRealPosition() const
{
	return Point2f(position.x * size.x * SQUARE_SIZE.x, position.y * size.y * SQUARE_SIZE.y);
}

void Room::removeObject(Game_Object* object_)
{
    auto it = find(objects.begin(), objects.end(), object_);

    if(it != objects.end()) objects.erase(it);
}

void Room::randomizeEnemies(Player* player_)
{
	for_each(objects.begin(), objects.end(), [&](Game_Object* object){
        if(object == player_ || !object || !object->isEnemy()) return;
        
		bool locationFound = false;
        
		while(!locationFound)
		{
			int x = random_generator.rand_lt(getSize().x);
			int y = random_generator.rand_lt(getSize().y);
            
			Square* square = squares[x][y];
			if(!square->isPathable()) continue;
            if(Vector2f(player_->getRealPosition() - square->getRealPosition()).magnitude() < 4*SQUARE_SIZE.x) continue;
            
			Square* oldsquare = object->getSquare();
			if(oldsquare)
			{
				oldsquare->removeObject(object);
			}
			square->addObject(object);
			object->setSquare(square);
			object->stopMovement();
			locationFound = true;
		}
    });
}

void Room::render(Player* player) const
{
	for_each(squares.begin(), squares.end(), [&](vector<Square*> column) {
		for_each(column.begin(), column.end(), [&](Square* square) {
            square->render(player);
        });
    });
    
	for_each(objects.begin(), objects.end(), [&](Game_Object* object){
        if(!object->getSquare()) return;
           
        object->render();
    });
}



void Room::doLogic(float timestep, Player* player)
{
	for_each(squares.begin(), squares.end(), [&](vector<Square*> column) {
		for_each(column.begin(), column.end(), [&](Square* square) {
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
            
            bool inAngle = false;
            
            if(angleMin <= -Global::pi)
            {
                inAngle = (angle <= angleMax) || (angle >= (angleMin += 2*Global::pi));
            }
            else if (angleMax >= Global::pi)
            {
                inAngle = (angle >= angleMin) || (angle <= (angleMax -= 2*Global::pi));
            }
            else
            {
                inAngle = (angle >= angleMin) && (angle <= angleMax);
            }
            
            if(see_all ||( (player->isLightOn()) && !(square == player->getSquare()) && ((distance <= (player->getLightDist() * player->getSquare()->getSize().x)) && (inAngle))))
            {
                square->setVisible(true);
            }
            else {
                square->setVisible(false);
            }
        });
    });
    
	for_each(objects.begin(), objects.end(), [&](Game_Object* object)
	{
        if(!object->getSquare()) return;
        
		object->doLogic(timestep, player);
	});
}

Door* Room::addDoorNorth() 
{
	Vector2f location = Vector2f((int)((getSize().x -1) /2.), 0);

	if(hasDoorNorth) return static_cast<Door*>(squares[location.x][location.y]);

	Door* newDoor = new Door(this, location, -Global::pi_over_two);
	Square* oldSquare = squares[location.x][location.y];
	newDoor->replaceConnections(oldSquare);
	delete oldSquare;
	squares[location.x][location.y] = newDoor;
	hasDoorNorth = true;
	return newDoor;
}

Door* Room::addDoorEast() 
{
	Vector2f location = Vector2f((int)(getSize().x-1.), (int)((getSize().y -1) /2.));

	if(hasDoorEast) return static_cast<Door*>(squares[location.x][location.y]);

	Door* newDoor = new Door(this, location, 0);
	Square* oldSquare = squares[location.x][location.y];
	newDoor->replaceConnections(oldSquare);
	delete oldSquare;
	squares[location.x][location.y] = newDoor;
	hasDoorEast = true;
	return newDoor;
}

Door* Room::addDoorSouth() 
{
	Vector2f location = Vector2f((int)((getSize().x -1) /2.), (int)(getSize().y - 1));

	if(hasDoorSouth) return static_cast<Door*>(squares[location.x][location.y]);

	Door* newDoor = new Door(this, location, Global::pi_over_two);
	Square* oldSquare = squares[location.x][location.y];
	newDoor->replaceConnections(oldSquare);
	delete oldSquare;
	squares[location.x][location.y] = newDoor;
	hasDoorSouth = true;
	return newDoor;
}

Door* Room::addDoorWest() 
{
	Vector2f location = Vector2f(0, (int)(getSize().y -1) /2.);

	if(hasDoorWest) return static_cast<Door*>(squares[location.x][location.y]);

	Door* newDoor = new Door(this, location, Global::pi);
	Square* oldSquare = squares[location.x][location.y];
	newDoor->replaceConnections(oldSquare);
	delete oldSquare;
	squares[location.x][location.y] = newDoor;
	hasDoorWest = true;
	return newDoor;
}

Enemy* Room::randomEnemy()
{
	int random = random_generator.rand_lt(100);

	if((random >= 0) && (random < 70))
	{
		return new Statue(Point2f(0,0));
	}
	else if ((random >= 70) && (random < 100))
	{
		return new Ghost(Point2f(0,0));
	}
	else
	{
		assert((random >= 0) && (random < 100));
        return nullptr;
	}
}

void Room::createEnemies()
{
    int random = random_generator.rand_lt(100);
    
	if((random >= 0)  && (random < 15))
	{
        Enemy* enemy1 = randomEnemy();
        squares[0][0]->addObject(enemy1);
        enemy1->setSquare(squares[0][0]);
		addObject(enemy1);
        Enemy* enemy2 = randomEnemy();
        squares[0][0]->addObject(enemy2);
        enemy2->setSquare(squares[0][0]);
		addObject(enemy2);
	}
	else if((random >= 15)  && (random < 80))
	{
        Enemy* enemy1 = randomEnemy();
        squares[0][0]->addObject(enemy1);
        enemy1->setSquare(squares[0][0]);
		addObject(enemy1);
	}
	else if((random >= 80)  && (random < 100))
	{
		//Relax, you're safe!
	}
	else {
		assert ((random >= 0) && (random < 100));
	}
}
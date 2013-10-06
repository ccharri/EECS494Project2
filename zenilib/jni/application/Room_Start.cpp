//
//  Room_Start.cpp
//  game
//
//  Created by Christopher Harris on 9/26/13.
//
//

#include "Room_Start.h"

#include "Player.h"
#include "StartSquare.h"

using namespace std;
using namespace Zeni;

Room_Start::Room_Start(const Point2f position_, const Vector2f size_)
	: Room_Square(position_, size_), player(new Player(Point2f((size_.x -1 /2.), (size_.y -1/2.))))
{
    for(Game_Object* object : objects)
    {
        removeObject(object);
        object->getSquare()->removeObject(object);
        delete object;
    }
    
    Point2f location = Point2f((size_.x-1)/2., (size_.y-1)/2.);
	Square* playerSquare = squares[location.x][location.y];
    Square_Start* startSquare = new Square_Start(this, location);
	startSquare->replaceConnections(playerSquare);
	delete playerSquare;
	squares[location.x][location.y] = startSquare;
	player->setSquare(startSquare);
	startSquare->addObject(player);
	addObject(player);
}
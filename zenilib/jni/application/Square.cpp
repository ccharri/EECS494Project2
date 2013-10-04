//
//  Square.cpp
//  game
//
//  Created by Christopher Harris on 9/23/13.
//
//

#include "Square.h"

#include "Room.h"
#include "Player.h"

#include "cheats.h"

using namespace Zeni;
using namespace std;

Zeni::Point2f Square::getRealPosition() const
{
    Point2f roomPos = room->getRealPosition();
    return Point2f(roomPos.x + (position.x * size.x), roomPos.y + (position.y * size.y));
}

void Square::removeObject(Game_Object* object_)
{
    auto it = find(objects.begin(), objects.end(), object_);
    
    if(it != objects.end()) objects.erase(it);
}

void Square::render(Player* player) const
{
    if(!isVisible()) return;
    
    Point2f startPos = getRealPosition();
    Point2f endPos = Point2f(startPos.x + size.x, startPos.y + size.y);
    
    String texture = pathable ? "brick" : "wall";
    
    Point2f playerPos = player->getRealPosition();
    float alpha = see_all ? 1 : 1.2- (Vector2f(playerPos.x - startPos.x, playerPos.y - startPos.y).magnitude() / (player->getLightDist() * size.x));
    Color fadeout = Color(alpha, 1, 1, 1);
    
    render_image(
         texture, // which texture to use
         startPos, // upper-left corner
         endPos, // lower-right corner
         theta, // rotation in radians
         1.0f, // scaling factor
         startPos + 0.5f * size, // point to rotate & scale about
         false, // whether or not to horizontally flip the texture
         fadeout); // what Color to "paint" the texture
    
}

void Square::doLogic(float timestep)
{
}

void Square::replaceConnections(Square* square_)
{
	setNorth(square_->getNorth());
	if(north) north->setSouth(this);
	setSouth(square_->getSouth());
	if(south) south->setNorth(this);
	setEast(square_->getEast());
	if(east) east->setWest(this);
	setWest(square_->getWest());
	if(west) west->setEast(this);
}

bool Square::isPathable() const
{
    if(!pathable) return false;
    
    for(Game_Object* object : objects)
    {
        if(!object->isPathable()) return false;
    }
    
    return true;
}
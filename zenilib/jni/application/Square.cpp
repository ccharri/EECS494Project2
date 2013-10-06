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

Square::Square(Room* room_, const Point2f position_, const Vector2f size_, float theta_, bool pathable_) : position(position_), size(size_), theta(theta_), room(room_), north(nullptr), south(nullptr), east(nullptr), west(nullptr), pathable(pathable_), visible(false)
{
    Point2f roomPos = room->getRealPosition();
	Point2f startPos = Point2f(roomPos.x + (position_.x * size_.x), roomPos.y + (position_.y * size_.y));
	Point2f endPos = Point2f(startPos.x + size.x, startPos.y + size.y);

	Vertex2f_Texture ul(startPos, Point2f(0.f,0.f));
	Vertex2f_Texture ll(Point2f(startPos.x, endPos.y), Point2f(0.f, 1.f));
	Vertex2f_Texture lr(endPos, Point2f(1.f,1.f));
	Vertex2f_Texture ur(Point2f(endPos.x, startPos.y), Point2f(1.f, 0.));
	Material stone_mat("brick");

	stone = Quadrilateral<Vertex2f_Texture>(ul, ll, lr, ur);
	stone.fax_Material(&stone_mat);

	Material wall_mat("wall");
	wall = Quadrilateral<Vertex2f_Texture>(ul, ll, lr, ur);
	wall.fax_Material(&wall_mat);
}

Zeni::Point2f Square::getRealPosition() const
{
    if(!room) return Point2f(0,0);
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
    if(!visible && !see_all) return;
    if((!north || !north->pathable) &&
       (!east || !east->pathable) &&
       (!south || !south->pathable) &&
       (!west || !west->pathable))
        return;
    
    Point2f startPos = getRealPosition();
    Point2f endPos = Point2f(startPos.x + size.x, startPos.y + size.y);
    
    //String texture = pathable ? "brick" : "wall";
    
    Point2f playerPos = player->getRealPosition();
    float alpha = see_all ? 0.0 : (Vector2f(playerPos.x - startPos.x, playerPos.y - startPos.y).magnitude() / (player->getLightDist() * size.x) - .2);
    Color fadeout = Color(alpha, 0, 0, 0);

	Vertex2f_Color ul(startPos, fadeout);
	Vertex2f_Color ll(Point2f(startPos.x, endPos.y), fadeout);
	Vertex2f_Color lr(endPos, fadeout);
	Vertex2f_Color ur(Point2f(endPos.x, startPos.y), fadeout);

	Quadrilateral<Vertex2f_Color> fade(ul, ll, lr, ur);
    
    //render_image(
    //     texture, // which texture to use
    //     startPos, // upper-left corner
    //     endPos, // lower-right corner
    //     theta, // rotation in radians
    //     1.0f, // scaling factor
    //     startPos + 0.5f * size, // point to rotate & scale about
    //     false, // whether or not to horizontally flip the texture
    //     fadeout); // what Color to "paint" the texture
    
	if(pathable)
	{
		get_Video().render(stone);
	}
	else 
	{
		get_Video().render(wall);
	}

	get_Video().render(fade);
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
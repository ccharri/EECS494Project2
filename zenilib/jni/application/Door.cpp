//
//  Door.cpp
//  game
//
//  Created by Christopher Harris on 10/2/13.
//
//

#include "Door.h"

#include "cheats.h"
#include "Player.h"
#include "Room.h"

using namespace Zeni;
using namespace std;

Point2f rotatePointAroundPoint(Point2f point, Point2f center, float theta)
{
    float s = sin(theta);
    float c = cos(theta);
    
    Point2f translatedPoint = point - center;
    
    Point2f rotatedPoint = Point2f(translatedPoint.x * c - translatedPoint.y * s, translatedPoint.x * s + translatedPoint.y * c);
    
    return rotatedPoint + center;
}

Door::Door(Room* room_, const Zeni::Point2f position_, float theta_, const Zeni::Vector2f size_) :  Square(room_, position_, size_, 0, true), theta(theta_)
{
    Point2f roomPos = getRoom()->getRealPosition();
    Vector2f size = getSize();
	Point2f startPos = Point2f((roomPos.x + (position_.x * size_.x)),
                               (roomPos.y + (position_.y * size_.y)));
	Point2f endPos = Point2f(startPos.x + size.x,
                             startPos.y + size.y);
    
    Point2f centerPos = startPos + .5 * size_;

    Point2f ulp = rotatePointAroundPoint(startPos, centerPos, theta);
    Point2f llp = rotatePointAroundPoint(Point2f(startPos.x, endPos.y), centerPos, theta);
    Point2f lrp = rotatePointAroundPoint(endPos, centerPos, theta);
    Point2f urp = rotatePointAroundPoint(Point2f(endPos.x, startPos.y), centerPos, theta);
    
	Vertex2f_Texture ul(ulp, Point2f(0.f,0.f));
	Vertex2f_Texture ll(llp, Point2f(0.f, 1.f));
	Vertex2f_Texture lr(lrp, Point2f(1.f,1.f));
	Vertex2f_Texture ur(urp, Point2f(1.f, 0.f));
    
	Material door_mat("door");
    
	door = Quadrilateral<Vertex2f_Texture>(ul, ll, lr, ur);
	door.fax_Material(&door_mat);
}

void Door::render(Player* player_) const
{
    if(!isVisible() && !see_all && (player_->getSquare() != this)) return;
    
    Point2f startPos = getRealPosition();
    Vector2f size = getSize();
    Point2f endPos = Point2f(startPos.x + size.x, startPos.y + size.y);
    
    Point2f playerPos = player_->getRealPosition();
    float alpha = see_all || player_->getSquare() == this ? 0.0 : (Vector2f(playerPos.x - startPos.x, playerPos.y - startPos.y).magnitude() / (player_->getLightDist() * size.x) - .2);
    Color fadeout = Color(alpha, 0, 0, 0);
    
	Vertex2f_Color ul(startPos, fadeout);
	Vertex2f_Color ll(Point2f(startPos.x, endPos.y), fadeout);
	Vertex2f_Color lr(endPos, fadeout);
	Vertex2f_Color ur(Point2f(endPos.x, startPos.y), fadeout);
    
	Quadrilateral<Vertex2f_Color> fade(ul, ll, lr, ur);
    
	get_Video().render(door);
    
	get_Video().render(fade);
}
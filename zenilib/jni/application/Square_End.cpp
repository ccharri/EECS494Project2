//
//  Square_End.cpp
//  game
//
//  Created by Christopher Harris on 10/6/13.
//
//

#include "Square_End.h"

#include "Room.h"
#include "Player.h"

using namespace Zeni;
using namespace std;

Square_End::Square_End(Room* room_, const Zeni::Point2f position_, const Zeni::Vector2f size_) : Square(room_, position_, size_, true)
{
    Point2f roomPos = getRoom()->getRealPosition();
    Vector2f size = getSize();
	Point2f startPos = Point2f(roomPos.x + (position_.x * size_.x), roomPos.y + (position_.y * size_.y));
	Point2f endPos = Point2f(startPos.x + size.x, startPos.y + size.y);
    
	Vertex2f_Texture ul(startPos, Point2f(0.f,0.f));
	Vertex2f_Texture ll(Point2f(startPos.x, endPos.y), Point2f(0.f, 1.f));
	Vertex2f_Texture lr(endPos, Point2f(1.f,1.f));
	Vertex2f_Texture ur(Point2f(endPos.x, startPos.y), Point2f(1.f, 0.));
    
    Material stone_mat("brick");
	stone = Quadrilateral<Vertex2f_Texture>(ul, ll, lr, ur);
	stone.fax_Material(&stone_mat);
    
    ul = Vertex2f_Texture (startPos - Point2f(0, 32), Point2f(0.f,0.f));
    ll =  Vertex2f_Texture (Point2f(startPos.x, endPos.y), Point2f(0.f, 1.f));
    lr =  Vertex2f_Texture (endPos, Point2f(1.f,1.f));
    ur =  Vertex2f_Texture (Point2f(endPos.x, startPos.y - 32), Point2f(1.f, 0.));
    
    Material ladder_mat("ladder_tall");
	ladder = Quadrilateral<Vertex2f_Texture>(ul, ll, lr, ur);
	ladder.fax_Material(&ladder_mat);
    
    Material light_mat("light_beams_tall");
	light = Quadrilateral<Vertex2f_Texture>(ul, ll, lr, ur);
	light.fax_Material(&light_mat);
}

void Square_End::render(Player* player) const
{
    get_Video().render(stone);
    get_Video().render(ladder);
    get_Video().render(light);
    //    get_Video().render(hole);
}
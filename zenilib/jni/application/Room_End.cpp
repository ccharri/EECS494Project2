//
//  Room_End.cpp
//  game
//
//  Created by Christopher Harris on 10/6/13.
//
//

#include "Room_End.h"

#include "Square.h"
#include "Square_End.h"
#include "Player.h"

using namespace std;
using namespace Zeni;

Room_End::Room_End(const Point2f position_, const Vector2f size_)
: Room_Hall(position_, size_)
{
    Point2f location = Point2f((size_.x-1)/2., (size_.y-1)/2.);
	Square* endSquare_old = squares[location.x][location.y];
    Square_End* endSquare_new = new Square_End(this, location);
	endSquare_new->replaceConnections(endSquare_old);
	delete endSquare_old;
	squares[location.x][location.y] = endSquare_new;
}
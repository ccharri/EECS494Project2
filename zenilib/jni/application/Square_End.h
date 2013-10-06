//
//  Square_End.h
//  game
//
//  Created by Christopher Harris on 10/6/13.
//
//

#ifndef __game__Square_End__
#define __game__Square_End__

#include <iostream>

#include <zenilib.h>

#include "Square.h"

class Room;
class Player;

class Square_End : public Square
{
public:
    Square_End(Room* room_, const Zeni::Point2f position_, const Zeni::Vector2f size_ = SQUARE_SIZE);
    
    virtual void render(Player* player) const;
private:
    Zeni::Quadrilateral<Zeni::Vertex2f_Texture> stone;
    Zeni::Quadrilateral<Zeni::Vertex2f_Texture> light;
    Zeni::Quadrilateral<Zeni::Vertex2f_Texture> ladder;
};

#endif /* defined(__game__Square_End__) */

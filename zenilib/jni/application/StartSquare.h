//
//  StartSquare.h
//  game
//
//  Created by Christopher Harris on 10/6/13.
//
//

#ifndef __game__StartSquare__
#define __game__StartSquare__

#include <iostream>
#include <zenilib.h>

#include "Square.h"

class Room;

class Square_Start : public Square
{
public:
    Square_Start(Room* room_, const Zeni::Point2f position_, const Zeni::Vector2f size_ = SQUARE_SIZE);
    
    virtual void render(Player* player) const;
private:
    Zeni::Quadrilateral<Zeni::Vertex2f_Texture> stone;
    Zeni::Quadrilateral<Zeni::Vertex2f_Texture> light;
    Zeni::Quadrilateral<Zeni::Vertex2f_Texture> hole;
};

#endif /* defined(__game__StartSquare__) */

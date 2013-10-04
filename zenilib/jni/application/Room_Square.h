//
//  Room_Square.h
//  game
//
//  Created by Christopher Harris on 9/26/13.
//
//

#ifndef __game__Room_Square__
#define __game__Room_Square__

#include <iostream>
#include <zenilib.h>

#include "Square.h"
#include "Door.h"
#include "Room.h"

class Room_Square : public Room
{
public:
    Room_Square(const Zeni::Point2f position_, const Zeni::Vector2f size_);
    
    virtual ~Room_Square() {};
};

#endif /* defined(__game__Room_Square__) */

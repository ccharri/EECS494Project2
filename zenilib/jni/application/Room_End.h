//
//  Room_End.h
//  game
//
//  Created by Christopher Harris on 10/6/13.
//
//

#ifndef __game__Room_End__
#define __game__Room_End__

#include <iostream>

#include <zenilib.h>

#include "Room_Hall.h"

class Room_End : public Room_Hall
{
public:
    Room_End(const Zeni::Point2f position_, const Zeni::Vector2f size_);
    
    virtual ~Room_End() {};
};

#endif /* defined(__game__Room_End__) */

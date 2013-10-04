//
//  Room_Square_Filled.h
//  game
//
//  Created by Christopher Harris on 9/26/13.
//
//

#ifndef __game__Room_Square_Filled__
#define __game__Room_Square_Filled__

#include <iostream>
#include <zenilib.h>

#include "Square.h"
#include "Door.h"
#include "Room.h"

using namespace Zeni;
using namespace std;

class Room_Square_Filled : public Room
{
public:
	Room_Square_Filled(const Zeni::Point2f position_, const Zeni::Vector2f size_);

	virtual ~Room_Square_Filled() {};
};

#endif /* defined(__game__Room_Square_Filled__) */

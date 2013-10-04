//
//  Room_Start.h
//  game
//
//  Created by Christopher Harris on 9/26/13.
//
//

#ifndef __game__Room_Start__
#define __game__Room_Start__

#include <iostream>
#include <zenilib.h>

#include "Room_Square.h"

class Player;

class Room_Start : public Room_Square
{
public:
	Room_Start(const Zeni::Point2f position_, const Zeni::Vector2f size_);

	inline Player* getPlayer() const {return player;};

	virtual ~Room_Start() {};
private:
	Player* player;
};

#endif /* defined(__game__Room_Start__) */

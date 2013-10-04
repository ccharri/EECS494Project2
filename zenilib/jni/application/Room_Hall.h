
#ifndef __game__Room_Hall__
#define __game__Room_Hall__

#include <zenilib.h>

#include "Room.h"

class Room_Hall : public Room
{
public:
	Room_Hall(const Zeni::Point2f position_, const Zeni::Vector2f size_);

	virtual ~Room_Hall() {};

private:
	Door* addDoorNorth();
	Door* addDoorEast();
	Door* addDoorSouth();
	Door* addDoorWest();
};

#endif

#include "Room_Manager.h"

#include <algorithm>

#include "Door.h"
#include "Room.h"
#include "Room_Square.h"
#include "Room_Square_Filled.h"
#include "Room_Hall.h"
#include "Room_Start.h"

using namespace Zeni;
using namespace std;

bool inRange(int x, int min, int max);

Room_Manager::Room_Manager(const int min_rooms_, const float min_distance_) : random_generator(Random())
{
	bool isValidMap = false;

	Vector2f roomSize = Vector2f(9,9);

	Room_Start* start = new Room_Start(Point2f(0,0), roomSize);
	rooms.push_back(start);

	while((rooms.size() < min_rooms_) && !isValidMap)
	{
		generateRoom(roomSize);

		if(rooms.size() >= min_rooms_) //See if a valid end location exists
		{
			isValidMap = findAndCreateEndRoom(roomSize, min_distance_);
		}
	}
}

Room_Manager::~Room_Manager()
{
	for(Room* room : rooms)
	{
		delete room;
	}
}

Room* Room_Manager::roomAtPosition(const Zeni::Vector2f& position_)
{
	auto it = find_if(rooms.begin(), rooms.end(), [&](Room* room){
		Point2f pos = room->getPosition();
		return (pos.x == position_.x) && (pos.y == position_.y);
	});	

	if(it != rooms.end()) return *it;

	return nullptr;
}

Player* Room_Manager::getPlayer()
{
	for(Room* room : rooms)
	{
		Room_Start* start = dynamic_cast<Room_Start*>(room);
		if(start)
		{
			return start->getPlayer();
		}
		else continue;
	}

	return nullptr;
}

void Room_Manager::linkRooms(Room* newRoom, Room* existingRoom, int dir)
{
	Door* newDoor;
	Door* existingDoor;

	switch(dir)
	{
	case 0: //North
		newDoor = newRoom->addDoorSouth();
		existingDoor = existingRoom->addDoorNorth();
		newDoor->setSouth(existingDoor);
		existingDoor->setNorth(newDoor);
		newDoor->setConnection(existingDoor->getRoom());
		existingDoor->setConnection(newDoor->getRoom());
		break;
	case 1: //East
		newDoor = newRoom->addDoorWest();
		existingDoor = existingRoom->addDoorEast();
		newDoor->setWest(existingDoor);
		existingDoor->setEast(newDoor);
		newDoor->setConnection(existingDoor->getRoom());
		existingDoor->setConnection(newDoor->getRoom());
		break;
	case 2: //South
		newDoor = newRoom->addDoorNorth();
		existingDoor = existingRoom->addDoorSouth();
		existingDoor->setSouth(newDoor);
		newDoor->setNorth(existingDoor);
		existingDoor->setConnection(newDoor->getRoom());
		newDoor->setConnection(existingDoor->getRoom());
		break;
	case 3: //West
		existingDoor = existingRoom->addDoorWest();
		newDoor = newRoom->addDoorEast();
		existingDoor->setWest(newDoor);
		newDoor->setEast(existingDoor);
		existingDoor->setConnection(newDoor->getRoom());
		newDoor->setConnection(existingDoor->getRoom());
		break;
	}
}

Room* Room_Manager::randomRoom(Zeni::Point2f position_, Zeni::Vector2f size_)
{
	int random = random_generator.rand_lt(100);

	if(inRange(random, 0, 25))
	{
		return new Room_Square(position_, size_);
	}
	else if (inRange(random, 25, 50))
	{
		return new Room_Square_Filled(position_, size_);
	}
	else if(inRange(random, 50, 75))
	{
		return new Room_Hall(position_, size_);
	}
	else if(inRange(random, 75, 100))
	{
		//Placeholder for new rooms

		//For right now, roll again!
		return randomRoom(position_, size_);
	}
	else {
		assert(inRange(random, 0, 100));
        return nullptr;
	}
}

void Room_Manager::generateRoom(Vector2f size_)
{
	int roomloc = random_generator.rand_lt(rooms.size());
	int dir = random_generator.rand_lt(4);

	Room* room = rooms[roomloc];
	Point2f pos = room->getPosition();
	Point2f newPos;
	Room* newRoom;

	switch (dir)
	{
		case 0: //North
			{
				newPos = Point2f(pos.x, pos.y -1);
				if(roomAtPosition(newPos)) return;
				if(!room->canAddDoorNorth()) return;
				break;
			}
		case 1: //East
			{
				newPos = Point2f(pos.x +1, pos.y);
				if(roomAtPosition(newPos)) return;
				if(!room->canAddDoorEast()) return;
				break;
			}
		case 2: //South
		{
			newPos = Point2f(pos.x, pos.y + 1);
			if(roomAtPosition(newPos)) return;
			if(!room->canAddDoorSouth()) return;
			break;
		}
		case 3: //West
		{
			newPos = Point2f(pos.x -1, pos.y);
			if(roomAtPosition(newPos)) return;
			if(!room->canAddDoorWest()) return;
			break;
		}
	}

	newRoom = randomRoom(newPos, size_);
	linkRooms(newRoom, room, dir);
	rooms.push_back(newRoom);
    
    Point2f checkPos;
    
    for(int dir = 0; dir < 4; ++dir)
    {
        Room* linkRoom;
        bool link;
        
        switch(dir)
        {
            case 0: //North
			{
				checkPos = Point2f(newPos.x, newPos.y -1);
				if(!(linkRoom = roomAtPosition(checkPos))) continue;
				if(!newRoom->canAddDoorNorth()) continue;
                if(!linkRoom->canAddDoorSouth()) continue;
                
                if((link = random_generator.rand_lt(3) == 0))
                {
                    linkRooms(linkRoom, newRoom, dir);
                }
                
				break;
			}
            case 1: //East
			{
				checkPos = Point2f(newPos.x +1, newPos.y);
				if(!(linkRoom = roomAtPosition(checkPos))) continue;
				if(!newRoom->canAddDoorEast()) continue;
                if(!linkRoom->canAddDoorWest()) continue;
                
                if((link = random_generator.rand_lt(3) == 0))
                {
                    linkRooms(linkRoom, newRoom, dir);
                }
                
				break;
			}
            case 2: //South
            {
                checkPos = Point2f(newPos.x, newPos.y + 1);
				if(!(linkRoom = roomAtPosition(checkPos))) continue;
                if(!newRoom->canAddDoorSouth()) continue;
                if(!linkRoom->canAddDoorNorth()) continue;
                
                if((link = random_generator.rand_lt(3) == 0))
                {
                    linkRooms(linkRoom, newRoom, dir);
                }
                
                break;
            }
            case 3: //West
            {
                checkPos = Point2f(newPos.x -1, newPos.y);
				if(!(linkRoom = roomAtPosition(checkPos))) continue;
                if(!newRoom->canAddDoorWest()) continue;
                if(!linkRoom->canAddDoorEast()) continue;
                
                if((link = random_generator.rand_lt(3) == 0))
                {
                    linkRooms(linkRoom, newRoom, dir);
                }
                
                break;
            }
        }
    }
}

bool Room_Manager::findAndCreateEndRoom(Zeni::Vector2f size_, float min_distance_)
{
	Vector2f endloc;
	bool validPlacement = false;
	Point2f newPos;
	int dir;

	for(Room* room :rooms)
	{
		Vector2f pos = room->getPosition();

		for(int i = 0; (i < 4) && !validPlacement; ++i)
		{
			switch(i)
			{
			case 0:
				newPos = Point2f(pos.x, pos.y -1); //north
				if(room->canAddDoorNorth() && (!roomAtPosition(newPos) && (Vector2f(newPos - pos).magnitude() >= min_distance_)))
				{
					validPlacement = true;
					dir = i;
				}
				break;
			case 1:
				newPos = Point2f(pos.x +1, pos.y); //east
				if(room->canAddDoorEast() && (!roomAtPosition(newPos) && (Vector2f(newPos - pos).magnitude() >= min_distance_)))
				{
					validPlacement = true;
					dir = i;
				}
				break;
			case 2:
				newPos = Point2f(pos.x, pos.y +1); //south
				if(room->canAddDoorSouth() && (!roomAtPosition(newPos) && (Vector2f(newPos - pos).magnitude() >= min_distance_)))
				{
					validPlacement = true;
					dir = i;
				}
				break;
			case 3:
				newPos = Point2f(pos.x -1, pos.y); //west
				if(room->canAddDoorWest() && (!roomAtPosition(newPos) && (Vector2f(newPos - pos).magnitude() >= min_distance_)))
				{
					validPlacement = true;
					dir = i;
				}
				break;
			}

		}
		if(validPlacement)
		{
			/*	Room* finalRoom = new Room_End(newPos, size_);
			linkRooms(finalRoom, room, dir);
			rooms.push_back(finalRoom);*/
			return true;
		}
	}

	return false;
}

bool inRange(int x, int min, int max)
{
	return ((x >= min) && (x < max));
}


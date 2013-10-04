//
//  Room_Manager.h
//  game
//
//  Created by Christopher Harris on 9/26/13.
//
//

#ifndef __game__Room_Manager__
#define __game__Room_Manager__

#include <iostream>
#include <vector>
#include <zenilib.h>

class Room;
class Player;

class Room_Manager
{
public:
	Room_Manager(const int min_rooms_, const float min_distance_);

	virtual const inline std::vector<Room*>& getRooms() const {return rooms;};
	virtual Room* roomAtPosition(const Zeni::Vector2f& position_);
	virtual Player* getPlayer();

	virtual ~Room_Manager();
private:
	Zeni::Random random_generator;

	std::vector<Room*> rooms;
	
	void linkRooms(Room* newRoom, Room* existingRoom, int dir);
	Room* randomRoom(Zeni::Point2f position_, Zeni::Vector2f size_);

	void generateRoom(Zeni::Vector2f size_);
	bool findAndCreateEndRoom(Zeni::Vector2f size_, float min_distance_);
};

#endif /* defined(__game__Room_Start__) */

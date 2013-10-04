//
//  Room.h
//  game
//
//  Created by Christopher Harris on 9/23/13.
//
//

#ifndef __game__Room__
#define __game__Room__

#include <zenilib.h>
#include <iostream>
#include <vector>

#include "Square.h"
#include "Door.h"

class Game_Object;
class Player;

class Room
{
public:
    Room(const Zeni::Point2f& position_, const Zeni::Vector2f& size_) : random_generator(Zeni::Random()), position(position_), size(size_), hasDoorNorth(false), hasDoorEast(false), hasDoorSouth(false), hasDoorWest(false)
    {};
    
    virtual inline const Zeni::Point2f& getPosition() const {return position;};
    virtual inline const Zeni::Vector2f& getSize() const {return size;};
    
    virtual inline bool containsObject(Game_Object* object_) const {return find(objects.begin(), objects.end(), object_) != objects.end();};
    virtual inline void addObject(Game_Object* object_) {objects.push_back(object_);};
    virtual inline const std::vector<Game_Object*>& getObjects() const {return objects;};
    virtual void removeObject(Game_Object* object_);

	virtual void randomizeEnemies();
    
    virtual inline const std::vector<std::vector<Square*> >& getSquares() const {return squares;};
    virtual inline const std::vector<Door*>& getDoors() const {return doors;};
    
    virtual void render(Player* player) const;
    virtual void doLogic(float timestep, Player* player);
    
    virtual ~Room() {
        for(std::vector<Square*> vector : squares)
        {
            for(Square* square : vector)
            {
                delete square;
            }
        }
    };

	virtual Door* addDoorNorth();
	virtual Door* addDoorEast();
	virtual Door* addDoorSouth();
	virtual Door* addDoorWest();
    
protected:
	Zeni::Random random_generator;

    void setSquares(const std::vector<std::vector<Square*> >& squares_) {squares = squares_;};
    inline void addDoor(Door* door_) {doors.push_back(door_);};

	std::vector<std::vector<Square*> > squares;

	virtual bool canAddDoorNorth() {return !hasDoorNorth;};
	virtual bool canAddDoorEast() {return !hasDoorEast;};
	virtual bool canAddDoorSouth() {return !hasDoorSouth;};
	virtual bool canAddDoorWest() {return !hasDoorWest;};
	//virtual Door* addDoorNorth() {return nullptr;};
	//virtual Door* addDoorEast() {return nullptr;};
	//virtual Door* addDoorSouth() {return nullptr;};
	//virtual Door* addDoorWest() {return nullptr;};

	bool hasDoorNorth;
	bool hasDoorEast;
	bool hasDoorSouth;
	bool hasDoorWest;
    
private:
    Zeni::Point2f position;
    Zeni::Vector2f size;
    std::vector<Game_Object*> objects;
    std::vector<Door*> doors;
};

#endif /* defined(__game__Room__) */

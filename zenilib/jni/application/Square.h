//
//  Square.h
//  game
//
//  Created by Christopher Harris on 9/23/13.
//
//

#ifndef __game__Square__
#define __game__Square__

#include <iostream>
#include <vector>
#include <algorithm>
#include <zenilib.h>

#include "Game_Object.h"

class Room;
class Player;

class Square
{
public:
    Square(const Zeni::Point2f position_, const Zeni::Vector2f size_ = Zeni::Vector2f(32, 32), bool pathable_ = true) : position(position_), size(size_), north(nullptr), south(nullptr), east(nullptr), west(nullptr), pathable(pathable_), visible(false) {};
    
    inline const Zeni::Point2f& getPosition() const {return position;};
    Zeni::Point2f getRealPosition() const;
    inline const Zeni::Vector2f& getSize() const {return size;};
    
    inline Room* getRoom() const {return room;};
    inline void setRoom(Room* room_) {room = room_;};
    
    inline Square* getNorth() const {return north;};
    inline Square* getSouth() const {return south;};
    inline Square* getEast() const {return east;};
    inline Square* getWest() const {return west;};
    
    inline void setNorth(Square* north_) {north = north_;};
    inline void setSouth(Square* south_) {south = south_;};
    inline void setEast(Square* east_) {east = east_;};
    inline void setWest(Square* west_) {west = west_;};
    
    bool isPathable() const;
    inline bool isVisible() const {return visible;};
    
    inline void setPathable(bool pathable_) {pathable = pathable_;};
    inline void setVisible(bool visible_) {visible = visible_;};
    
    inline void addObject(Game_Object* object_) {objects.push_back(object_);};
    inline bool containsObject(Game_Object* object_) const {return std::find(objects.begin(), objects.end(), object_) != objects.end();};
    void removeObject(Game_Object* object_);
    inline void clearObjects() {objects.clear();};
    inline const std::vector<Game_Object*>& getObjects() const {return objects;};
    
    virtual void render(Player* player) const;
    virtual void doLogic(float timestep);
    
    virtual ~Square() {};
    
private:
    //Position is integer (x, y) and is based on local coordinates inside the containing room
    //
    Zeni::Point2f position;
    Zeni::Vector2f size;
    
    Room* room;
    
    Square* north;
    Square* south;
    Square* east;
    Square* west;
    
    //Can a unit walk into this square?
    bool pathable;
    
    //Should this square render?
    bool visible;
    
    //List of all game objects in this square
    std::vector<Game_Object*> objects;
};

#endif /* defined(__game__Square__) */

//
//  Door.h
//  game
//
//  Created by Christopher Harris on 10/2/13.
//
//

#ifndef __game__Door__
#define __game__Door__

#include <iostream>

#include "Square.h"

class Room;

class Door : public Square
{
public:
    Door(const Zeni::Point2f position_, const Zeni::Vector2f size_ = Zeni::Vector2f(32, 32)) :  Square(position_, size_, true) {};
    
    inline Room* getConnection() const {return connection;};
    inline void setConnection(Room* connection_) {connection = connection_;};
    
private:
    Room* connection;
};

#endif /* defined(__game__Door__) */

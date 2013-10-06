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
#include <zenilib.h>

#include "Square.h"

class Player;
class Room;

class Door : public Square
{
public:
    Door(Room* room_, const Zeni::Point2f position_, float theta_ = 0, const Zeni::Vector2f size_ = SQUARE_SIZE);
    
    inline Room* getConnection() const {return connection;};
    inline void setConnection(Room* connection_) {connection = connection_;};
    
    void render(Player* player_) const;
    
private:
    Room* connection;
    
    float theta;
    
    Zeni::Quadrilateral<Zeni::Vertex2f_Texture> door;
};

#endif /* defined(__game__Door__) */

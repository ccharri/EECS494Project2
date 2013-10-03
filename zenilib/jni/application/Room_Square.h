//
//  Room_Square.h
//  game
//
//  Created by Christopher Harris on 9/26/13.
//
//

#ifndef __game__Room_Square__
#define __game__Room_Square__

#include <iostream>
#include <zenilib.h>

#include "Square.h"
#include "Door.h"
#include "Room.h"

using namespace Zeni;
using namespace std;

class Room_Square : public Room
{
public:
    Room_Square(const Zeni::Point2f position_, const Zeni::Vector2f size_)
    : Room(position_, size_)
    {
        vector<vector<Square*> > squares;
        
        //Row for each column
        for(int x = 0; x < (int)size_.x; ++x)
        {
            vector<Square*> column;
            
            for(int y = 0; y < (int)size_.y; ++y)
            {
                Square* square = new Square(Point2f(x,y));
                square->setRoom(this);
                
                //Fill in left
                if(x) {
                    Square* west = squares[x-1][y];
                    west->setEast(square);
                    square->setWest(west);
                    
                    if(x == (size_.x -1))
                    {
                        square->setPathable(false);
                        
                        if(y == (int)(size_.y / 2.))
                        {
                            delete square;
                            Door* door = new Door(Point2f(x,y));
                            door->setRoom(this);
                            west->setEast(door);
                            door->setWest(west);
                            addDoor(door);
                        }
                    }
                }
                else {
                    square->setPathable(false);
                    
                    if(y == (int)(size_.y / 2.))
                    {
                        delete square;
                        Door* door = new Door(Point2f(x,y));
                        door->setRoom(this);
                        addDoor(door);
                    }
                }
                //Fill in top
                if(y)
                {
                    Square* north = column[y-1];
                    north->setSouth(square);
                    square->setNorth(north);
                    
                    if(y == (size_.y -1))
                    {
                        square->setPathable(false);
                        
                        if(x == (int)(size_.x / 2.))
                        {
                            delete square;
                            Door* door = new Door(Point2f(x,y));
                            door->setRoom(this);
                            north->setSouth(door);
                            door->setNorth(north);
                            addDoor(door);
                        }
                    }
                }
                else {
                    square->setPathable(false);
                    
                    if(x == (int)(size_.x / 2.))
                    {
                        delete square;
                        Door* door = new Door(Point2f(x,y));
                        door->setRoom(this);
                        addDoor(door);
                    }
                }
                
                
                column.insert(column.end(), square);
            }
            
            squares.insert(squares.end(), column);
        }
        
        setSquares(squares);
    };
    
    virtual ~Room_Square() {};
    
private:
    
};

#endif /* defined(__game__Room_Square__) */

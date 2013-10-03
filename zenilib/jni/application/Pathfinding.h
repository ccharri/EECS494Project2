//
//  Pathfinding.h
//  game
//
//  Created by Christopher Harris on 9/26/13.
//
//

#ifndef __game__Pathfinding__
#define __game__Pathfinding__

#include <iostream>
#include <vector>

class Square;

std::vector<Square*> AStar(Square* start_, Square* destination_);

#endif /* defined(__game__Pathfinding__) */

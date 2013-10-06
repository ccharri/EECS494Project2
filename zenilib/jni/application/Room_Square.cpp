//
//  Room_Square.cpp
//  game
//
//  Created by Christopher Harris on 9/26/13.
//
//

#include "Room_Square.h"

using namespace std;
using namespace Zeni;

Room_Square::Room_Square(const Point2f position_, const Vector2f size_)
	: Room(position_, size_)
{
	vector<vector<Square*> > squares;

	//Row for each column
	for(int x = 0; x < (int)size_.x; ++x)
	{
		vector<Square*> column;

		for(int y = 0; y < (int)size_.y; ++y)
		{
			Square* square = new Square(this, Point2f(x,y));

			//Fill in left
			if(x) {
				Square* west = squares[x-1][y];
				west->setEast(square);
				square->setWest(west);

				if(x == (size_.x -1))
				{
					square->setPathable(false);
				}
			}
			else {
				square->setPathable(false);
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
				}
			}
			else {
				square->setPathable(false);
			}


			column.insert(column.end(), square);
		}

		squares.insert(squares.end(), column);
	}

	setSquares(squares);
    
    Room::createEnemies();
};


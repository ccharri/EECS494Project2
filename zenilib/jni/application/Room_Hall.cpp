
#include "Room_Hall.h"

#include "Room.h"

using namespace std;
using namespace Zeni;

Room_Hall::Room_Hall(const Point2f position_, const Vector2f size_)
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

				if(!(( x >= ((size_.x - 1)/2.) - 1) && ( x <= ((size_.x - 1)/2.) + 1)))
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

				if(!((y >= ((size_.y - 1)/2.) - 1) && ( y <= ((size_.y - 1)/2.) + 1)))
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
};

Door* Room_Hall::addDoorNorth() 
{
	Vector2f location = Vector2f((int)((getSize().x -1) /2.), 0);

	if(hasDoorNorth) return static_cast<Door*>(squares[location.x][location.y]);

	for(vector<Square*> column : squares)
	{
		for(Square* square : column)
		{
			Point2f pos = square->getPosition();

			if((pos.y == 0) || (pos.y > ((getSize().y-1)/2.))) continue;

			if((pos.x >= (((getSize().x-1)/2.) -1)) && (pos.x <= (((getSize().x-1)/2.) +1)))
			{
				square->setPathable(true);
			}
		}
	}

	return Room::addDoorNorth();
}

Door* Room_Hall::addDoorEast() 
{
	Vector2f location = Vector2f((int)(getSize().x-1.), (int)((getSize().y -1) /2.));

	if(hasDoorEast) return static_cast<Door*>(squares[location.x][location.y]);

	for(vector<Square*> column : squares)
	{
		for(Square* square : column)
		{
			Point2f pos = square->getPosition();

			if((pos.x == (getSize().x-1)) || (pos.x < (((getSize().x-1)/2.) + 1))) continue;

			if((pos.y >= (((getSize().y-1)/2.) -1)) && (pos.y <= (((getSize().y-1)/2.) +1)))
			{
				square->setPathable(true);
			}
		}
	}

	return Room::addDoorEast();
}

Door* Room_Hall::addDoorSouth() 
{
	Vector2f location = Vector2f((int)((getSize().x -1) /2.), (int)(getSize().y - 1));

	if(hasDoorSouth) return static_cast<Door*>(squares[location.x][location.y]);

	for(vector<Square*> column : squares)
	{
		for(Square* square : column)
		{
			Point2f pos = square->getPosition();

			if((pos.y == (getSize().y-1)) || (pos.y < ((getSize().y+1)/2.))) continue;

			if((pos.x >= (((getSize().x-1)/2.) -1)) && (pos.x <= (((getSize().x-1)/2.) +1)))
			{
				square->setPathable(true);
			}
		}
	}

	return Room::addDoorSouth();
}

Door* Room_Hall::addDoorWest() 
{
	Vector2f location = Vector2f(0, (int)(getSize().y -1) /2.);

	if(hasDoorWest) return static_cast<Door*>(squares[location.x][location.y]);

	for(vector<Square*> column : squares)
	{
		for(Square* square : column)
		{
			Point2f pos = square->getPosition();

			if((pos.x == 0) || (pos.x > ((getSize().x-1)/2.))) continue;

			if((pos.y >= (((getSize().y-1)/2.) -1)) && (pos.y <= (((getSize().y-1)/2.) +1)))
			{
				square->setPathable(true);
			}
		}
	}

	return Room::addDoorWest();
}

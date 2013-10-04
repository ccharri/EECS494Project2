//
//  Game_Object.cpp
//  game
//
//  Created by Christopher Harris on 9/23/13.
//
//

#include "Game_Object.h"

#include "Square.h"
#include "Room.h"

using namespace Zeni;
using namespace std;

bool Game_Object::collide(const Game_Object &rhs) const {
    
    const Vector2f dist_vec = getRealPosition() - rhs.getRealPosition() +
    
    0.5f * (m_size - rhs.m_size);
    
    const float dist2 = dist_vec * dist_vec;
    
    const float radius_sum = .5 * m_size.x + .5 * rhs.getSize().x;
    
    return dist2 < radius_sum * radius_sum;
    
}

Point2f Game_Object::getRealPosition() const
{
    if(!square) return Point2f();
    Point2f squarePos = square->getRealPosition();
    return Point2f(squarePos.x + m_position.x, squarePos.y + m_position.y);
}

void Game_Object::doLogic(float timestep, Game_Object* player)
{
    //Get new path to object
    
    doMovement(timestep);
}

void Game_Object::doMovement(float timestep)
{
    //If can accept move commands, do so
    if(canMove())                           //Start movement
    {
        //No where to go
        if(!path.size())
        {
            stopMovement();
            return;
        }
        
        destination = path.front();
        setMoving(true);
        setMoveable(false);
        
        if(!destination)                        //If invalid destination
        {
            stopMovement();
            return;
        }
        if(!(destination -> isPathable()))      //If destination is not pathable
        {
            stopMovement();
            return;
        }
        
        //Claim the square we're moving into
        square->removeObject(this);
        destination->addObject(this);
        
        if(destination->getRoom() != square->getRoom())
        {
            square->getRoom()->removeObject(this);
            destination->getRoom()->addObject(this);
        }
        
        Point2f destinationPos = destination -> getRealPosition();
        Point2f ownSquarePos = square->getRealPosition();
        Point2f ownPos = ownSquarePos;
        
        m_position = ownPos - destinationPos;
        
        square = destination;
        path.erase(path.begin());
        
    }

    //If moving, do so
    if(isMoving())
    {
        Point2f ownSquarePos = square->getRealPosition();
        Point2f ownPos = getRealPosition();
        
        float distance_x = ownSquarePos.x - ownPos.x;
        float distance_y = ownSquarePos.y - ownPos.y;
        Vector2f distance = Vector2f(distance_x, distance_y);
        Vector2f direction = distance.normalized();
        
        if(distance.magnitude() < (m_speed * timestep)) {
            //We have arrived
            
            m_position = Vector2f(0, 0);

            destination = nullptr;
            setMoveable(true);
            setMoving(false);
        }
        else {
            //Move closer
            
            m_position = m_position + (direction * (m_speed * timestep));
        }
    }
}

void Game_Object::stopMovement()
{
    m_position = Vector2f(0, 0);
    path.clear();
    destination = nullptr;
    setMoveable(true);
    setMoving(false);
}

void Game_Object::render(const String &texture, const Color &filter) const {
    
    // Use a helper defined in Zeni/EZ2D.h
    
    Point2f startPos = getRealPosition();
    Point2f endPos = startPos + m_size;
    
    render_image(
       texture, // which texture to use
       startPos, // upper-left corner
       endPos, // lower-right corner
       m_theta, // rotation in radians
       1.0f, // scaling factor
       startPos + 0.5f * m_size, // point to rotate & scale about
       false, // whether or not to horizontally flip the texture
       filter); // what Color to "paint" the texture
    
}
//
//  Ghost.h
//  game
//
//  Created by Christopher Harris on 9/27/13.
//
//

#ifndef __game__Ghost__
#define __game__Ghost__

#include <iostream>
#include <zenilib.h>

#include "Enemy.h"

class Ghost : public Enemy
{
public:
    Ghost(const Zeni::Point2f &position_,
           const Zeni::Vector2f &size_ = Zeni::Vector2f(32, 32),
           const float &theta_ = 0.0f,
           const float &speed_ = 20.0f) : Enemy(position_, size_, theta_, speed_, true)
    {};
    
    virtual void render() const;
    virtual void doLogic(float timestep, Game_Object* player);
    
    ~Ghost() {};
private:
    
};

#endif /* defined(__game__Ghost__) */

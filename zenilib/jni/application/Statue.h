//
//  Statue.h
//  game
//
//  Created by Christopher Harris on 9/27/13.
//
//

#ifndef __game__Statue__
#define __game__Statue__

#include <iostream>
#include "Enemy.h"

class Statue : public Enemy
{
public:
    Statue(const Zeni::Point2f &position_,
           const Zeni::Vector2f &size_ = Zeni::Vector2f(32, 32),
           const float &theta_ = 0.0f,
           const float &speed_ = 20.0f) : Enemy(position_, size_, theta_, speed_, false)
    {};
    
    virtual void render() const;
    virtual void doLogic(float timestep, Game_Object* player);
    
    ~Statue() {};
private:
    
};

#endif /* defined(__game__Statue__) */

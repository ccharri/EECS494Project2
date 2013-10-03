//
//  Enemy.h
//  game
//
//  Created by Christopher Harris on 9/27/13.
//
//

#ifndef __game__Enemy__
#define __game__Enemy__

#include <iostream>

#include "Game_Object.h"

class Enemy : public Game_Object
{
public:
    Enemy(const Zeni::Point2f &position_,
           const Zeni::Vector2f &size_ = Zeni::Vector2f(32, 32),
           const float &theta_ = 0.0f,
           const float &speed_ = 0.0f,
           const bool &pathable_ = false) : Game_Object(position_, size_, theta_, speed_, pathable_)
    {};
    
    virtual void doLogic(float timestep, Game_Object* player);
    
    ~Enemy() {};
    
protected:
    void render(const Zeni::String &texture, const Zeni::Color &filter = Zeni::Color()) const;
private:
    
};

#endif /* defined(__game__Enemy__) */

//
//  Player.h
//  game
//
//  Created by Christopher Harris on 9/25/13.
//
//

#ifndef __game__Player__
#define __game__Player__

#include <iostream>
#include <zenilib.h>

#include "Game_Object.h"

class Player : public Game_Object
{
public:
    Player(const Zeni::Point2f &position_,
           const Zeni::Vector2f &size_ = Zeni::Vector2f(32, 32),
           const float &theta_ = 0.0f,
           const float &speed_ = 70.0f) : Game_Object(position_, size_, theta_, speed_, true),
                                            light_arc(45 * (M_PI/180)), light_dist(4), light_on(true)
    {};
    
    inline float getLightArc() const {return light_arc;};
    inline float getLightDist() const {return light_dist;};
    inline bool isLightOn() const {return light_on;};
    
    inline void setLightArc(float arc_) {light_arc = arc_;};
    inline void setLightDist(float dist_) {light_dist = dist_;};
    inline void setLightOn(bool on_) {light_on = on_;};
    
    virtual void render() const;
    virtual void doLogic(float timestep, Game_Object* player);
    
    ~Player() {};
private:
    float light_arc;
    float light_dist;
    bool light_on;
};

#endif /* defined(__game__Player__) */

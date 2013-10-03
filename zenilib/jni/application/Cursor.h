//
//  Cursor.h
//  game
//
//  Created by Christopher Harris on 9/27/13.
//
//

#ifndef __game__Cursor__
#define __game__Cursor__

#include <iostream>
#include <zenilib.h>

class Cursor
{
public:
    Cursor() : m_position(Zeni::Point2f()), m_size(Zeni::Vector2f(8,8)), m_theta(0) {};
    
    void render() const;
    
    inline void setPosition(Zeni::Point2f position_) {m_position = position_;};
    inline void setTheta(float theta_) {m_theta = theta_;};
    
    inline Zeni::Point2f getPosition() const {return m_position;};
    inline float getTheta() const {return m_theta;};
    inline Zeni::Vector2f getSize() const {return m_size;};
    
private:
    Zeni::Point2f m_position;
    Zeni::Vector2f m_size;
    float m_theta;
};


#endif /* defined(__game__Cursor__) */

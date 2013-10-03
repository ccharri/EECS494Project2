//
//  Game_Object.h
//  game
//
//  Created by Christopher Harris on 9/23/13.
//
//

#ifndef __game__Game_Object__
#define __game__Game_Object__

#include <zenilib.h>
#include <iostream>

class Square;

class Game_Object {
public:
    Game_Object(const Zeni::Point2f &position_,
                const Zeni::Vector2f &size_,
                const float &theta_ = 0.0f,
                const float &speed_ = 0.0f,
                const bool &pathable_ = false)
    : m_position(position_),
    m_size(size_),
    m_theta(theta_),
    m_speed(speed_),
    square(nullptr),
    destination(nullptr),
    pathable(pathable_),
    moving(false),
    moveable(true)
    {
    };
    
    virtual inline const Zeni::Point2f& getPosition() const {return m_position;};
    virtual Zeni::Point2f getRealPosition() const;
    virtual float getTheta() const {return m_theta;};
    virtual void setTheta(float theta_) {m_theta = theta_;};
    
    virtual Zeni::Vector2f getSize() const {return m_size;};
    
    virtual inline const std::vector<Square*>& getPath() {return path;};
    //This will only be 1 square long in the case of player
    virtual inline void setPath(std::vector<Square*> path_) {path = path_;};
    
    virtual inline Square* getSquare() const {return square;};
    virtual inline void setSquare(Square* square_) {square = square_;};
    
    virtual inline const bool isPathable() const {return pathable;};
    virtual inline void setPathable(bool pathable_) {pathable = pathable_;};
    
    virtual inline const bool isMoving() const {return moving;};
    virtual inline void setMoving(bool moving_) {moving = moving_;};
    
    virtual inline const bool canMove() const {return moveable;};
    virtual inline void setMoveable(bool moveable_) {moveable = moveable_;};
    
    virtual bool collide(const Game_Object &rhs) const;
    
    virtual void render() const = 0;
    virtual void doLogic(float timestep, Game_Object* player);
    
    // If you might delete base class pointers, you need a virtual destructor.
    virtual ~Game_Object() {}
    
protected:
    
    virtual void render(const Zeni::String &texture, const Zeni::Color &filter = Zeni::Color()) const;
    
    //Pixel offset from containing Square
    Zeni::Point2f m_position; // Upper left corner
    
    Zeni::Vector2f m_size; // (width, height)
    float m_theta;
    float m_speed;
    
    Square* square;
    Square* destination;
    std::vector<Square*> path;
    
    bool pathable;
    bool moving;
    bool moveable;
    
    void doMovement(float timestep);
    void stopMovement();
};

#endif /* defined(__game__Game_Object__) */

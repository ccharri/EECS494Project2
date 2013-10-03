//
//  Play_State.cpp
//  game
//
//  Created by Christopher Harris on 9/25/13.
//
//

#include "Play_State.h"

#include <math.h>

#include "Room.h"
#include "Room_Square.h"

using namespace Zeni;
using namespace std;

Play_State::Play_State() :  m_time_passed(0.0), screenSize(Point2f(800, 600.0f)), player(Player(Point2f(0, 0))), enemy_Statue_1(Statue(Point2f(4,4))), enemy_Ghost_1(Ghost(Point2f(6,6))),  cursor(Cursor()), m_north(false), m_south(false), m_west(false), m_east(false)
{
    set_pausable(true);
    
    Room* testRoom =new Room_Square(Vector2f(), Vector2f(10, 10));
    testRoom->addObject(&player);
    testRoom->addObject(&enemy_Statue_1);
    testRoom->addObject(&enemy_Ghost_1);
    const vector< vector<Square*> >& squares = testRoom->getSquares();
    
    for(vector<Square*> vector : squares)
    {
        for(Square* square : vector)
        {
            if((square->getPosition().x == 1) && (square->getPosition().y == 1))
            {
                square->addObject(&player);
                player.setSquare(square);
            }
            
            if((square->getPosition().x == 4) && (square->getPosition().y == 4))
            {
                square->addObject(&enemy_Statue_1);
                enemy_Statue_1.setSquare(square);
            }
            
            if((square->getPosition().x == 6) && (square->getPosition().y == 6))
            {
                square->addObject(&enemy_Ghost_1);
                enemy_Ghost_1.setSquare(square);
            }
        }
    }
    
    rooms.push_back(testRoom);
    
    Room* playerRoom = player.getSquare()->getRoom();
    
    vector<Game_Object*> roomObjects = playerRoom->getObjects();
    
    for(Game_Object* object : roomObjects)
    {
        if(dynamic_cast<Enemy*>(object))
        {
            object->setPath(AStar(object->getSquare(), player.getSquare()));
        }
    }
    
    m_end_timer.stop();
}

Play_State::~Play_State()
{
    for(Room* room : rooms)
    {
        delete room;
    }
}

void Play_State::on_push() {
//    get_Window().mouse_grab(true);
    get_Window().mouse_hide(true);
    m_chrono.start();
    //get_Game().joy_mouse.enabled = false;
}

void Play_State::on_pop() {
//    get_Window().mouse_grab(false);
    get_Window().mouse_hide(false);
    m_chrono.stop();
    //get_Game().joy_mouse.enabled = true;
}

void Play_State::on_key(const SDL_KeyboardEvent &event) {
    switch(event.keysym.sym) {
        case SDLK_w:
            m_north = event.type == SDL_KEYDOWN;
            m_west = false;
            m_south = false;
            m_east = false;
            break;
            
        case SDLK_a:
            m_west = event.type == SDL_KEYDOWN;
            m_north = false;
            m_south = false;
            m_east = false;
            break;
            
        case SDLK_s:
            m_south = event.type == SDL_KEYDOWN;
            m_west = false;
            m_north = false;
            m_east = false;
            break;
            
        case SDLK_d:
            m_east = event.type == SDL_KEYDOWN;
            m_west = false;
            m_south = false;
            m_north = false;
            break;
            
        default:
            m_east = false;
            m_west = false;
            m_south = false;
            m_north = false;
            Gamestate_Base::on_key(event); // Let Gamestate_Base handle it
            break;
            
    }
}

void Play_State::on_mouse_motion(const SDL_MouseMotionEvent &event)
{
    Point2f world_coordinate = m_projector.unproject(Point2f(event.x, event.y));
    Point2f playerPos = player.getRealPosition();
    Vector2f playerSize = player.getSize();
    float theta = atan2(world_coordinate.x - playerPos.x - .5*playerSize.x, world_coordinate.y - playerPos.y - .5*playerSize.y) - M_PI_2;
    player.setTheta(theta);
    cursor.setPosition(world_coordinate - .5 * cursor.getSize());
    cursor.setTheta(theta);
}

void Play_State::render()
{
    get_Video().set_2d(make_pair(player.getRealPosition() - .5*screenSize, player.getRealPosition() + .5* screenSize), true);
    
    player.getSquare()->getRoom()->render(&player);
    
    cursor.render();
}

void Play_State::perform_logic() {
    const float time_passed = m_chrono.seconds();
    const float time_step = time_passed - m_time_passed;
    m_time_passed = time_passed;
    
    m_projector = Projector2D(make_pair(player.getRealPosition() - .5 * screenSize, player.getRealPosition() + .5 * screenSize), get_Video().get_viewport());
    
    
    const vector<Game_Object*>& roomObjects = player.getSquare()->getRoom()->getObjects();
    
    for(Game_Object* object : roomObjects)
    {
        if(dynamic_cast<Enemy*>(object))
        {
            if(object->collide(player))
            {
                end_game(true);
            }
        }
    }
    
    if(m_end_timer.is_running())
    {
        if(m_end_timer.seconds() > 3.0f)
        {
            get_Game().pop_state();
        }
        else
        {
            return;
        }
    }
    
    
    do_player_movement(time_step);
    
    Square* playerSquare = player.getSquare();
    
    player.getSquare()->getRoom()->doLogic(time_step, &player);
    
    Square* newPlayerSquare = player.getSquare();
    
    if(playerSquare != newPlayerSquare)
    {
//        Room* playerRoom = player.getSquare()->getRoom();
//        
//        vector<Game_Object*> roomObjects = playerRoom->getObjects();
//        
        for(Game_Object* object : roomObjects)
        {
            if(dynamic_cast<Enemy*>(object))
            {
                object->setPath(AStar(object->getSquare(), player.getSquare()));
            }
        }
    }
}

void Play_State::do_player_movement(float time_step)
{
    //Deal with player movement
    vector<Square*> path = player.getPath();
    
    if(player.canMove())
    {
        if(m_north)
        {
            path.push_back(player.getSquare()->getNorth());
        }
        else if (m_south)
        {
            path.push_back(player.getSquare()->getSouth());
        }
        else if(m_west)
        {
            path.push_back(player.getSquare()->getWest());
        }
        else if (m_east)
        {
            path.push_back(player.getSquare()->getEast());
        }
        else
        {
            //Do nothing
        }
        
        player.setPath(path);
    }
}

void Play_State::end_game(bool loss)
{
    m_chrono.stop();
    
    m_end_timer.start();
}
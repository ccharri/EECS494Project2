//
//  Play_State.h
//  game
//
//  Created by Christopher Harris on 9/25/13.
//
//

#ifndef __game__Play_State__
#define __game__Play_State__

#include <iostream>
#include <zenilib.h>
#include <vector>

#include "Cursor.h"
#include "Player.h"
#include "Statue.h"
#include "Ghost.h"
#include "Pathfinding.h"
#include "cheats.h"

class Room_Manager;
class Room;

class Play_State : public Zeni::Gamestate_Base {
    Play_State(const Play_State &);
    Play_State operator=(const Play_State &);
    
public:
    Play_State();
    ~Play_State();
    
private:
    Zeni::Chronometer<Zeni::Time> m_chrono;
    float m_time_passed;
    
    Zeni::Chronometer<Zeni::Time> m_end_timer;
    
    Zeni::Projector2D m_projector;
    
    Zeni::Point2f screenSize;
    
    void perform_logic();
    
    void on_push();
    void on_pop();
    void on_key(const SDL_KeyboardEvent &event);
    void render();
    void on_mouse_motion(const SDL_MouseMotionEvent &event);
    
    void do_player_movement(float time_step);
    void end_game(bool loss);
    
    std::vector<Room*> rooms;
    
    Player* player;
    
    Cursor cursor;

	Room_Manager* room_manager;
    
    bool m_north;
    bool m_south;
    bool m_west;
    bool m_east;
};

#endif /* defined(__game__Play_State__) */

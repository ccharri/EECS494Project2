//
//  End_Gamestate.h
//  game
//
//  Created by Christopher Harris on 10/7/13.
//
//

#ifndef __game__End_Gamestate__
#define __game__End_Gamestate__

#include <iostream>
#include <zenilib.h>

class End_Gamestate : public Zeni::Widget_Gamestate
{
public:
    End_Gamestate(const Zeni::String& text_, float displaytime_, const std::pair<Zeni::Point2f, Zeni::Point2f> &virtual_window_, const bool &fix_aspect_ratio_ = true);
    
    void render();
    void perform_logic();
private:
    Zeni::String text;
    float displaytime;
    Zeni::Chronometer<Zeni::Time> displayTimer;
};

#endif /* defined(__game__End_Gamestate__) */

//
//  Setup_Gamestate.h
//  game
//
//  Created by Christopher Harris on 10/7/13.
//
//

#ifndef __game__Setup_Gamestate__
#define __game__Setup_Gamestate__

#include <iostream>
#include <zenilib.h>

class Setup_Gamestate : public Zeni::Widget_Gamestate
{
public:
    Setup_Gamestate(const Zeni::String& text_, float displaytime_, const std::pair<Zeni::Point2f, Zeni::Point2f> &virtual_window_, const bool &fix_aspect_ratio_ = true);

    void render();
    void perform_logic();
private:
    
};

#endif /* defined(__game__Setup_Gamestate__) */

//
//  End_Gamestate.cpp
//  game
//
//  Created by Christopher Harris on 10/7/13.
//
//

#include "End_Gamestate.h"

using namespace Zeni;
using namespace std;

End_Gamestate::End_Gamestate(const Zeni::String& text_, float displaytime_, const std::pair<Zeni::Point2f, Zeni::Point2f> &virtual_window_, const bool &fix_aspect_ratio_) : Widget_Gamestate(virtual_window_, fix_aspect_ratio_), text(text_), displaytime(displaytime_)
{
    displayTimer.start();
}

void End_Gamestate::render()
{
    Widget_Gamestate::render();
    
    Zeni::Font &fr = get_Fonts()["title"];
    
    fr.render_text(
                   text,
                   Point2f(400.0f, 300.0f -.5f * fr.get_text_height()),
                   get_Colors()["title_text"],
                   ZENI_CENTER);
}

void End_Gamestate::perform_logic()
{
    Widget_Gamestate::perform_logic();
    
    if(displayTimer.seconds() >= displaytime)
    {
        get_Game().pop_state();
    }
}
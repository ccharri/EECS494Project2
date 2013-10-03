//
//  Cursor.cpp
//  game
//
//  Created by Christopher Harris on 9/27/13.
//
//

#include "Cursor.h"

void Cursor::render() const
{
    Zeni::render_image(
     "cursor", // which texture to use
     m_position, // upper-left corner
     m_position + m_size, // lower-right corner
     m_theta, // rotation in radians
     1.0f, // scaling factor
     m_position + 0.5f * m_size, // point to rotate & scale about
     false, // whether or not to horizontally flip the texture
     Zeni::Color()); // what Color to "paint" the texture
}
/*
 * ========================================================================
 *
 *       Filename:  Color.cpp
 *
 *    Description:  Color class implementation 
 *
 *        Version:  1.0
 *        Created:  26/01/22 00:56:25
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * =========================================================================
 */
//////////////////////////
// Headers
/////////////////////////
#include "Color.hpp"
#include <algorithm>
#include <cstdint>

namespace xwc
{
    ////////////////////////////
    // Static member data
    ////////////////////////////
    const Color Color::Black (0,0,0);
    const Color Color::White (255,255,255);
    const Color Color::Red (255,0,0);
    const Color Color::Green (0,255,0);
    const Color Color::Blue (0,0,255);
    const Color Color::Yellow (255,255,0);
    const Color Color::Magenta (255,0,255);
    const Color Color::Cyan (0,255,255);
    const Color Color::Transparent (0,0,0,0);
} // end of namespace xwc
/*--------------------------Eof Color.cpp----------------------*/

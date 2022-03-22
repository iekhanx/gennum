/*
 * ==========================================================================
 *
 *       Filename:  Glyph.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  18/01/22 00:42:19
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
#ifndef _GLYPH_HPP_
#define _GLYPH_HPP_

/////////////////////
// Headers
/////////////////////
#include "Rect.hpp"

namespace xwc
{
    class Glyph
    {
        public:

            ///////////////////////
            // \brief Default constructor
            //////////////////////
            Glyph () : advance (0) {}

            /////////////////////
            // Member data
            /////////////////////
            float       advance;    //< Offset to move horizontal next char
            int         lsbDelta;   //< Left offset after forced auto hint.
            int         rsbDelta;   //< Right offset after forced auto hint
            FloatRect   bounds;     //< Bounding rectangles of the glyph
            IntRect     textureRect;//< Texture coordinate of glyph
    };  // end of class Glyph
} // end of namespace xwc
#endif
/* -------------------------- Eof Glyph.hpp ------------------------*/
/// \class xwc::Glyph
/// \ingroup graphics
///
/// A glyph is the visual representation of a character.
///
/// The xwc::Glyph structure provides the information needed
/// to handle the glyph:
/// \li its coordinates in the font's texture
/// \li its bounding rectangle
/// \li the offset to apply to get the starting position of the next glyph
///
/// \see xwc::Font
///
////////////////////////////////////////////////////////////

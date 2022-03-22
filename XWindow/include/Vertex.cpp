/*
 * ========================================================================
 *
 *       Filename:  Vertex.cpp
 *
 *    Description:  Vertex class implementation
 *
 *        Version:  1.0
 *        Created:  26/01/22 11:04:21
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * =========================================================================
 */
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Vertex.hpp"


namespace xwc
{
////////////////////////////////////////////////////////////
Vertex::Vertex() :
position (0, 0),
color    (255, 255, 255),
texCoords(0, 0)
{
}


////////////////////////////////////////////////////////////
Vertex::Vertex(const Vector2f& thePosition) :
position (thePosition),
color    (255, 255, 255),
texCoords(0, 0)
{
}


////////////////////////////////////////////////////////////
Vertex::Vertex(const Vector2f& thePosition, const Color& theColor) :
position (thePosition),
color    (theColor),
texCoords(0, 0)
{
}


////////////////////////////////////////////////////////////
Vertex::Vertex(const Vector2f& thePosition, const Vector2f& theTexCoords) :
position (thePosition),
color    (255, 255, 255),
texCoords(theTexCoords)
{
}


////////////////////////////////////////////////////////////
Vertex::Vertex(const Vector2f& thePosition, const Color& theColor, const Vector2f& theTexCoords) :
position (thePosition),
color    (theColor),
texCoords(theTexCoords)
{
}

} // namespace xwc


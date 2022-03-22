/*
 * ==========================================================================
 *
 *       Filename:  Vertex.hpp
 *
 *    Description:  Vertex class defintions 
 *
 *        Version:  1.0
 *        Created:  26/01/22 10:43:29
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
#ifndef _VERTEXT_HPP_
#define _VERTEXT_HPP_

///////////////////////////////////
// Headers
////////////////////////////////////
#include "Color.hpp"
#include <cstdint>

namespace xwc
{
    class Vertex
    {
        ///////////////////
        // \brief Default Constructor
        //////////////////
        Vertex ();

        //////////////
        // \brief Construct the vertex from its position
        //////////////
        Vertex (const Vector2f& thePosition);

        /////////////
        // \brief Construct vertex from pos n color
        ////////////
        Vertex (const Vector2f& thePosition, const Color& theColor);

        ////////////
        // \brief Construct vertex from pos, coord
        ////////////
        Vertex (const Vector2f& thePosition, const Vector2f& theTexCoords);

        ////////////
        // \brief Construct the vertex pos, color, coord
        // \param the position
        // \param theColor,
        // \param theTexCoord
        ///////////
        Vertex (const Vector2f& thePosition, const Color& theColor, 
                const Vector2f& theTexCoords);

        /////////////
        // Member Data
        /////////////
        Vector2f     position;      //< 2D position
        Color        color;         //< Color of vertex
        Vector2f     texCoords;     //< Coordinates of vertex
    };
} // end of namespace xwc
#endif
/*--------------------- Eof Vertex.hpp----------------------*/
////////////////////////////////////////////////////////////
/// \class xwc::Vertex
/// \ingroup graphics
///
/// A vertex is an improved point. It has a position and other
/// extra attributes that will be used for drawing: in SFML,
/// vertices also have a color and a pair of texture coordinates.
///
/// The vertex is the building block of drawing. Everything which
/// is visible on screen is made of vertices. They are grouped
/// as 2D primitives (lines, triangles, ...), and these primitives
/// are grouped to create even more complex 2D entities such as
/// sprites, texts, etc.
///
/// If you use the graphical entities of SFML (sprite, text, shape)
/// you won't have to deal with vertices directly. But if you want
/// to define your own 2D entities, such as tiled maps or particle
/// systems, using vertices will allow you to get maximum performances.
///
/// Example:
/// \code
/// // define a 100x100 square, red, with a 10x10 texture mapped on it
/// xwc::Vertex vertices[] =
/// {
///     xwc::Vertex(xwc::Vector2f(  0,   0), xwc::Color::Red, 
///                                     xwc::Vector2f( 0,  0)),
///     xwc::Vertex(xwc::Vector2f(  0, 100), xwc::Color::Red, 
///                                     xwc::Vector2f( 0, 10)),
///     xwc::Vertex(xwc::Vector2f(100, 100), xwc::Color::Red, 
///                                      xwc::Vector2f(10, 10)),
///     xwc::Vertex(xwc::Vector2f(  0,   0), xwc::Color::Red, 
///                                     xwc::Vector2f( 0,  0)),
///     xwc::Vertex(xwc::Vector2f(100, 100), xwc::Color::Red, 
///                                     xwc::Vector2f(10, 10)),
///     xwc::Vertex(xwc::Vector2f(100,   0), xwc::Color::Red, 
///                                     xwc::Vector2f(10,  0))
/// };
///
/// // draw it
/// window.draw(vertices, 6, xwc::Triangles);
/// \endcode
///
/// Note: although texture coordinates are supposed to be an integer
/// amount of pixels, their type is float because of some buggy graphics
/// drivers that are not able to process integer coordinates correctly.
///
/// \see xwc::VertexArray
///
////////////////////////////////////////////////////////////


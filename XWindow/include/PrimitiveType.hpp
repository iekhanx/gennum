/*
 * ==========================================================================
 *
 *       Filename:  PrimitiveType.hpp
 *
 *    Description:  PrimitiveType class declaration 
 *
 *        Version:  1.0
 *        Created:  27/01/22 15:02:37
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
#ifndef _PRIMITIVETYPE_HPP
#define _PRIMITIVETYPE_HPP

namespace xwc
{
////////////////////////////////////////////////////////////
/// \ingroup graphics
/// \brief Types of primitives that a xwc::VertexArray can render
///
/// Points and lines have no area, therefore their thickness
/// will always be 1 pixel, regardless the current tranxwcorm
/// and view.
///
////////////////////////////////////////////////////////////
enum PrimitiveType
{
    Points,        //!< List of individual points
    Lines,         //!< List of individual lines
    LineStrip,     //!< List of connected lines, a point uses the 
                   //!< previous point to form a line
    Triangles,     //!< List of individual triangles
    TriangleStrip, //!< List of connected triangles, a point uses 
                   //!< the two previous points to form a triangle
    TriangleFan    //!< List of connected triangles, a point uses the 
                   //!< common center and the previous point to form a triangle
};

} // namespace xwc


#endif // _PRIMITIVETYPE_HPP

/*
 * ==========================================================================
 *
 *       Filename:  Rect.hpp
 *
 *    Description: Rect class declaration 
 *
 *        Version:  1.0
 *        Created:  18/01/22 00:56:02
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
#ifndef _RECT_HPP_
#define _RECT_HPP_

/////////////////////////
// Headers
////////////////////////
#include "Vector2.hpp"
#include <algorithm>

namespace xwc
{
    //////////////////////////
    // \brief Utility class for manipulating 2D axis algined rectangles
    //////////////////////////
    template <typename T>
    class Rect
    {
        public:
            
            ////////////////////
            // \brief Default Constructor
            // Create empty rectangle Rect (0,0,0,0)
            ///////////////////
            Rect ();

            ///////////////////
            // \brief Construct the rectangle for its coord
            // \param rectLeft
            // \param rectTop
            // \param rectWidth
            // \param rectHeight
            ////////////////////
            Rect (T rectLeft, T rectTop, T rectWidth, T rectHeight);

            ///////////////////
            // \brief Construct the rectangle from position and size
            // \param pos
            // \param size
            //////////////////
            Rect (const Vector2<T>& position, const Vector2<T>& size);

            /////////////////
            // \brief Construct the rectangle from another type of rectangle
            // \param rectangle to convert
            /////////////////
            template <typename U>
            explicit Rect (const Rect<U>& rectangle);

            //////////////////
            // \brief Check if a point is inside the rectangle's area
            // \param x X coord point to test
            // \param y Y coord point to test
            // \return True if the point is inside
            /////////////////
            bool contains (T x, T y) const;

            ////////////////////
            // \brief  Check if a point is inside the rectangle's area
            // \param poit to test
            // \return True if the point is inside
            /////////////////
            bool contains (const Vector2<T>& point) const;

            ////////////////////
            // \brief Check the intersection between two rectangle
            // \param rectangle to test
            // \return True if rectangle overlap
            /////////////////////
            bool intersects (const Rect<T>& rectangle) const;

            /////////////////////
            // \brief Check intersection beween the two rectangles
            // \param rectangle
            // \param intersection
            // \return true if rectangles overlap
            /////////////////////
            bool intersects (const Rect<T>& rectangle, 
                             Rect<T>& intersection) const;

            ///////////////////
            // \brief Get the position of rectangle top-left
            // \return position of rectangle
            ///////////////////
            Vector2<T> getPosition () const;

            /////////////////////
            // \brief Get the size of the rectangle
            // \return Size of rectangle
            ////////////////////
            Vector2 <T> getSize () const;

            /////////////////////
            // Member data
            /////////////////////
            T left;         //< Left coordinates of rectangle
            T top;          //< Top coord
            T width;        //< Width
            T height;       //< Height
    };

    /////////////////////////////////////
    // \relates Rect
    // \brief Overload of binary operator ==
    // \param left Left operand 
    // \param right Right operand
    // \return True if left is equal to right
    /////////////////////////////////////
    template <typename T>
    bool operator == (const Rect<T>& left, const Rect<T>& right);

    ///////////////////////////
    // \relates Rect
    // \brief Overload of binary operator !=
    // \param left Left operand
    // \param right 
    // \return True if left is not equal to right
    //////////////////////////
    template <typename T>
    bool operator != (const Rect<T>& left, const Rect<T>& right);

#include "Rect.inl"

    // Create type alias for the most common types
    using IntRect = Rect<int>;
    using FloatRect = Rect<float>;
} // end of namespace xwc
#endif
/* -------------------- Eof Rect.hpp -----------------------*/
////////////////////////////////////////////////////////////
/// \class xwc::Rect
/// \ingroup graphics
///
/// A rectangle is defined by its top-left corner and its size.
/// It is a very simple class defined for convenience, so
/// its member variables (left, top, width and height) are public
/// and can be accessed directly, just like the vector classes
/// (Vector2 and Vector3).
///
/// To keep things simple, xwc::Rect doesn't define
/// functions to emulate the properties that are not directly
/// members (such as right, bottom, center, etc.), it rather
/// only provides intersection functions.
///
/// xwc::Rect uses the usual rules for its boundaries:
/// \li The left and top edges are included in the rectangle's area
/// \li The right (left + width) and bottom (top + height) edges are excluded from the rectangle's area
///
/// This means that xwc::IntRect(0, 0, 1, 1) and xwc::IntRect(1, 1, 1, 1)
/// don't intersect.
///
/// xwc::Rect is a template and may be used with any numeric type, but
/// for simplicity type aliases for the instantiations used by SFML are given:
/// \li xwc::Rect<int> is xwc::IntRect
/// \li xwc::Rect<float> is xwc::FloatRect
///
/// So that you don't have to care about the template syntax.
///
/// Usage example:
/// \code
/// // Define a rectangle, located at (0, 0) with a size of 20x5
/// xwc::IntRect r1(0, 0, 20, 5);
///
/// // Define another rectangle, located at (4, 2) with a size of 18x10
/// xwc::Vector2i position(4, 2);
/// xwc::Vector2i size(18, 10);
/// xwc::IntRect r2(position, size);
///
/// // Test intersections with the point (3, 1)
/// bool b1 = r1.contains(3, 1); // true
/// bool b2 = r2.contains(3, 1); // false
///
/// // Test the intersection between r1 and r2
/// xwc::IntRect result;
/// bool b3 = r1.intersects(r2, result); // true
/// // result == (4, 2, 16, 3)
/// \endcode
///
////////////////////////////////////////////////////////////

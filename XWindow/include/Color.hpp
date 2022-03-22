/*
 * ==========================================================================
 *
 *       Filename:  color.hpp
 *
 *    Description:  color class declaration
 *
 *        Version:  1.0
 *        Created:  22/01/22 14:36:20
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
#ifndef _COLOR_HPP_
#define _COLOR_HPP_

//////////////////////////
// Headers
//////////////////////////
#include <cstdint>

namespace xwc
{
    class Color
    {
    public:

        ///////////////////
        // \brief Default constructor
        //////////////////
        constexpr Color ();

        ////////////////
        // \brief construct the color fro its RGBA components
        // \param red components 255
        // \param green  "       255
        // \param blue   "       255
        // \param alpha  "       255
        //////////////
        constexpr Color (uint8_t red, uint8_t green, 
                         uint8_t blue, uint8_t alpha = 255);

        /////////////////
        // \brief Retrive the color as 32-bit  unsigned interger
        // \return Color represent as 32-bit interger
        ////////////////
        constexpr explicit Color (uint32_t color);

        ///////////////
        // \brief  Contruct the color 
        // \return Color represent as 32-bit unsigned integer
        ///////////////
        constexpr uint32_t toInteger () const;

        /////////////////
        // Static Member data 
        ////////////////
        static const Color  Black;          //< predefined color Black
        static const Color  White;          //< White predefined color
        static const Color  Red;            //< Red     "
        static const Color  Green;          //< Green   "
        static const Color  Blue;           //< Blue    "
        static const Color  Yellow;         //< Yellow  "
        static const Color  Magenta;        //< Magenta "
        static const Color  Cyan;           //< Cyan    "
        static const Color  Transparent;    //< Transparent (black) predefined

        ////////////////////////
        // Member data
        ///////////////////////
        uint8_t  r;      //< red component
        uint8_t  g;      //< green
        uint8_t  b;      //< blue
        uint8_t  a;      //< alpha
    };

    //////////////////////
    // \relates Color
    // \brief Overload the == operator
    // This operator compares two color are equal?
    // \param left operand
    // \param right operand
    // \return True if equals
    //////////////////////
    [[nodiscard]] constexpr bool operator == (const Color& left, 
                                              const Color& right);

    /////////////////////
    // \relate Color
    // \brief operator compares two colors not equals
    // \param left
    // \param right
    // \return true if not equals
    ///////////////////
    [[nodiscard]] constexpr bool operator != (const Color& left, 
                                              const Color& right);

    ///////////////////
    // \brief overload binary + operator
    // \param left 
    // \param right
    // \return  result a + b
    /////////////////
    [[nodiscard]] constexpr Color operator + (const Color& left, 
                                             const Color& right);

    /////////////////////
    // \brief Overload the binar - operator
    // \param left 
    // \param right
    // \return true if l - r
    [[nodiscard]] constexpr Color operator - (const Color& left, 
                                               const Color& right);

    //////////////////
    // \brief Overload binary * operator
    // \param left
    // \param right
    // \return  Result \a left * \a right
    /////////////////
    [[nodiscard]] constexpr Color operator * (const Color& left, 
                                              const Color& right);

    //////////////////
    // \brief Overload binary += operator
    // \param left
    // \param right
    // \return true if succeed
    //////////////////
    constexpr Color& operator += (Color& left, Color& right);

    /////////////////
    // \brief Overload binary -= operator
    // \param left
    // \param right
    // \return true
    ////////////////
    constexpr Color& operator -= (Color& left, const Color& right);

    /////////////////
    // \brief Overload the binary *= operator
    // \param left
    // \param right
    // \return Reference to left
    /////////////////
    constexpr Color& operator *= (Color& left, const Color& right);

#include "Color.inl"

}  // end of namespace xwc 
#endif   // _COLOR_HPP_
/* --------------------Eof Color.hpp ----------------------*/
///////////////////////////////////////////////////////////
/// \class xwc::Color
/// \ingroup graphics
///
/// xwc::Color is a simple color class composed of 4 components:
/// \li Red
/// \li Green
/// \li Blue
/// \li Alpha (opacity)
///
/// Each component is a public member, an unsigned integer in
/// the range [0, 255]. Thus, colors can be constructed and
/// manipulated very easily:
///
/// \code
/// xwc::Color color(255, 0, 0); // red
/// color.r = 0;                // make it black
/// color.b = 128;              // make it dark blue
/// \endcode
///
/// The fourth component of colors, named "alpha", represents
/// the opacity of the color. A color with an alpha value of
/// 255 will be fully opaque, while an alpha value of 0 will
/// make a color fully transparent, whatever the value of the
/// other components is.
///
/// The most common colors are already defined as static variables:
/// \code
/// xwc::Color black       = xwc::Color::Black;
/// xwc::Color white       = xwc::Color::White;
/// xwc::Color red         = xwc::Color::Red;
/// xwc::Color green       = xwc::Color::Green;
/// xwc::Color blue        = xwc::Color::Blue;
/// xwc::Color yellow      = xwc::Color::Yellow;
/// xwc::Color magenta     = xwc::Color::Magenta;
/// xwc::Color cyan        = xwc::Color::Cyan;
/// xwc::Color transparent = xwc::Color::Transparent;
/// \endcode
///
/// Colors can also be added and modulated (multiplied) using the
/// overloaded operators + and *.
///
////////////////////////////////////////////////////////////


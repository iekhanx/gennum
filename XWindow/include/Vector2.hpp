/*
 * ==========================================================================
 *
 *       Filename:  Vector2.hpp
 *
 *    Description:  Class vector2 declaration  
 *
 *        Version:  1.0
 *        Created:  10/01/22 19:28:32
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
#ifndef __VECTOR2_HPP__
#define __VECTOR2_HPP__

namespace xwc
{
    ////////////////////////////////////////////
    // \brief Utility template class for manipulating  2 dimension vectors
    ////////////////////////////////////////////
    template <typename T>
        class Vector2
        {
            public:
                /////////////////////////////////
                //\brief Default constructor
                //
                // Create a Vector2 (0, 0)
                // /////////////////////////////
                constexpr Vector2 ();

                ////////////////////////////////
                // \brief Construct the vector from its coordinates
                //
                // \param X X coordinate
                // \param Y Y coordinate
                ////////////////////////////////
                constexpr Vector2 (T X, T Y);

                ///////////////////////////////
                // \brief Construct vector from another type of vector
                //
                //This constructor doesn't replace the copy conpy constructor
                //it called only when U != T.
                //
                // \param vector Vector to convert
                template <typename U>
                constexpr explicit Vector2 (const Vector2<U>& vector);

                ///////////////////////////////
                // member data
                //////////////////////////////
                T x;        //!<X coordinate of the vector
                T y;        //!<Y coordinate of the vector
        };
    ///////////////////////////////////////////
    // \relates Vector2
    // \brief Overload of unary operator -
    //
    // \param right Vector to negate
    //
    // \return Memberwise opposite of the vector
    //////////////////////////////////////////
    template <typename T>
    [[nodiscard]] constexpr Vector2<T> operator -(const Vector2<T>& right);

    /////////////////////////////////////////
    // \relates Vector2
    // \brief Overload of binary operator +=
    //
    // This operator performs a memberwise addtion of both vectors
    // and assigns the result to \a left
    //
    // \parm left  Left operand (a vector)
    // \parm right Right operand (a vector)
    //
    // \return Reference to \a left
    ///////////////////////////////////////
    template <typename T>
    constexpr Vector2<T>& operator +=(Vector2<T>& left, 
                                            const Vector2<T>& right);

    ///////////////////////////////////////
    // \relates Vector2 
    // \brief Overloadd of Binary operator +
    //
    // \param left  Left operator (a vector)
    // \param right Right operator (a vector)
    //
    // \return Memberwise addition of borth vectors
    ////////////////////////////////////////
    template <typename T>
    [[nodiscard]] constexpr Vector2<T> operator +(const Vector2<T>& left,
                                                  const Vector2<T>& right);
    ///////////////////////////////////////
    // \relates Vector2
    // \brief Overload of binary operator -
    //
    // \param left  Left operand 
    // \param right Right operand
    //////////////////////////////////////
    template <typename T>
    [[nodiscard]] constexpr Vector2<T> operator -(const Vector2<T>& left,
                                                  const Vector2<T>& right);

    ///////////////////////////////////////
    // \relates Vector2
    // \brief Overload of binary operator *
    //
    // \param left  Left operand
    // \param right Right operand
    //
    // \return Member multiplication by a right
    /////////////////////////////////////
    template <typename T>
    [[nodiscard]] constexpr Vector2<T> operator *(const Vector2<T>& left,
                                                  T right);

    /////////////////////////////////////
    // \relates Vector2
    // \brief Overload of binary operator
    //
    // \param left
    // \param right
    //
    // \return Member multiplication by left
    /////////////////////////////////////
    template <typename T>
    [[nodiscard]] constexpr Vector2<T> operator *(T left, 
                                                const Vector2<T>& right);

    ///////////////////////////////////////
    // \relates Vector2
    // \brief Overload of binary operator *=
    //
    // This operator perform a memberwise multiplication by \a right
    // and assign the result to \a left
    //
    // \param left  Left
    // \param right Right
    //
    // \return Reference to \a left
    //////////////////////////////////////
    template <typename T>
    constexpr Vector2<T>& operator *=(Vector2<T>& left, T right);

    /////////////////////////////////////
    // \relates Vector2
    // \brief Overload of binary operator /
    //
    // \param left Left operand
    // \param right Right operand
    //
    // \return Memberwise division by \a right
    ////////////////////////////////////
    template <typename T>
    [[nodiscard]] constexpr Vector2<T> operator /(const Vector2<T>& left,
                                                    T right);

    ///////////////////////////////////
    // \relates Vector2
    // \brief Overload of binary operator /=
    //
    // This operator perform a member division by \a right
    // and assign the result to \a left
    //
    // \param left  Left
    // \param right Right
    //
    // \return Reference to \a left
    ///////////////////////////////////
    template <typename T>
    constexpr Vector2<T>& operator /=(Vector2<T>& left, T right);

    ///////////////////////////////////
    // \relates Vector2
    // \brief Overload of binary operator  ==
    //
    // This operator compare strict equality between two vectors
    //
    // \param left   Left
    // \param right  Right 
    //
    // \return True if \a left is equal to \a right
    ////////////////////////////////////
    template <typename T>
    [[nodiscard]] constexpr bool operator ==(const Vector2<T>& left,
                                             const Vector2<T>& right);

    /////////////////////////////////////
    // \relates Vector2
    // \brief Overload of binary operator !=
    //
    // This operator complare strict difference between two vectors
    //
    // \param left   Left
    // \param right  Right
    //
    // \return True if \a left is not equal to \a right
    ////////////////////////////////////
    template <typename T>
    [[nodiscard]] constexpr bool operator !=(const Vector2<T>& left,
                                            const Vector2<T>& right);

    
    #include "Vector2.inl"

    // define most common types
    using Vector2i = Vector2<int>;
    using Vector2u = Vector2<unsigned int>;
    using Vector2f = Vector2<float>;
}   // End of namespace xwc

#endif   /* --- Eof Vector2.hpp --- */

////////////////////////////////////////////////////////////
/// \class xwc::Vector2
/// \ingroup system
///
/// xwc::Vector2 is a simple class that defines a mathematical
/// vector with two coordinates (x and y). It can be used to
/// represent anything that has two dimensions: a size, a point,
/// a velocity, etc.
///
/// The template parameter T is the type of the coordinates. It
/// can be any type that supports arithmetic operations (+, -, /, *)
/// and comparisons (==, !=), for example int or float.
///
/// You generally don't have to care about the templated form (xwc::Vector2<T>),
/// the most common specializations have special type aliases:
/// \li xwc::Vector2<float> is xwc::Vector2f
/// \li xwc::Vector2<int> is xwc::Vector2i
/// \li xwc::Vector2<unsigned int> is xwc::Vector2u
///
/// The xwc::Vector2 class has a small and simple interface, 
/// its x and y members
/// can be accessed directly (there are no accessors like setX(), getX()) and it
/// contains no mathematical function like dot product, cross product, 
/// length, etc.
///
/// Usage example:
/// \code
/// xwc::Vector2f v1(16.5f, 24.f);
/// v1.x = 18.2f;
/// float y = v1.y;
///
/// xwc::Vector2f v2 = v1 * 5.f;
/// xwc::Vector2f v3;
/// v3 = v1 + v2;
///
/// bool different = (v2 != v3);
/// \endcode
///
/// Note: for 3-dimensional vectors, see xwc::Vector3.
///
////////////////////////////////////////////////////////////

/*
 * ==========================================================================
 *
 *       Filename:  Vector3.hpp
 *
 *    Description:  Vector3 class declarations  
 *
 *        Version:  1.0
 *        Created:  26/01/22 12:27:19
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
#ifndef _VECTOR3_HPP_
#define _VECTOR3_HPP_

//////////////////////////
// Headers
//////////////////////////

namespace xwc
{
    ////////////////
    // \brief Utility template class for manipulating 3 dimesion vectors
    ///////////////
    template <typename T>
    class Vector3
    {
        /////////////////
        // \brief Default constructor
        /////////////////
        constexpr Vector3 ();

        /////////////////
        // \brief Construct the vector from its coordinates
        ////////////////
        constexpr Vector3 (T X, T Y, T Z);

        //////////////
        // \brief Construct vector from another type of Vector
        /////////////
        template <typename U>
        constexpr explicit Vector3 (const Vector3<U>& vector);

        //////////////////
        // Member Data
        /////////////////
        T x;    //< X coordinates of vector
        T y;    //< Y coordinates of vector
        T z;    //< Z coordinates of vector
    };
////////////////////////////////////////////////////////////
/// \relates Vector3
/// \brief Overload of unary operator -
///
/// \param left Vector to negate
///
/// \return Memberwise opposite of the vector
///
////////////////////////////////////////////////////////////
template <typename T>
[[nodiscard]] constexpr Vector3<T> operator -(const Vector3<T>& left);

////////////////////////////////////////////////////////////
/// \relates Vector3
/// \brief Overload of binary operator +=
///
/// This operator performs a memberwise addition of both vectors,
/// and assigns the result to \a left.
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a vector)
///
/// \return Reference to \a left
///
////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector3<T>& operator +=(Vector3<T>& left, const Vector3<T>& right);

////////////////////////////////////////////////////////////
/// \relates Vector3
/// \brief Overload of binary operator -=
///
/// This operator performs a memberwise subtraction of both vectors,
/// and assigns the result to \a left.
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a vector)
///
/// \return Reference to \a left
///
////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector3<T>& operator -=(Vector3<T>& left, const Vector3<T>& right);

////////////////////////////////////////////////////////////
/// \relates Vector3
/// \brief Overload of binary operator +
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a vector)
///
/// \return Memberwise addition of both vectors
///
////////////////////////////////////////////////////////////
template <typename T>
[[nodiscard]] constexpr Vector3<T> operator +(const Vector3<T>& left, const Vector3<T>& right);

////////////////////////////////////////////////////////////
/// \relates Vector3
/// \brief Overload of binary operator -
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a vector)
///
/// \return Memberwise subtraction of both vectors
///
////////////////////////////////////////////////////////////
template <typename T>
[[nodiscard]] constexpr Vector3<T> operator -(const Vector3<T>& left, const Vector3<T>& right);

////////////////////////////////////////////////////////////
/// \relates Vector3
/// \brief Overload of binary operator *
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a scalar value)
///
/// \return Memberwise multiplication by \a right
///
////////////////////////////////////////////////////////////
template <typename T>
[[nodiscard]] constexpr Vector3<T> operator *(const Vector3<T>& left, T right);

////////////////////////////////////////////////////////////
/// \relates Vector3
/// \brief Overload of binary operator *
///
/// \param left  Left operand (a scalar value)
/// \param right Right operand (a vector)
///
/// \return Memberwise multiplication by \a left
///
////////////////////////////////////////////////////////////
template <typename T>
[[nodiscard]] constexpr Vector3<T> operator *(T left, const Vector3<T>& right);

////////////////////////////////////////////////////////////
/// \relates Vector3
/// \brief Overload of binary operator *=
///
/// This operator performs a memberwise multiplication by \a right,
/// and assigns the result to \a left.
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a scalar value)
///
/// \return Reference to \a left
///
////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector3<T>& operator *=(Vector3<T>& left, T right);

////////////////////////////////////////////////////////////
/// \relates Vector3
/// \brief Overload of binary operator /
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a scalar value)
///
/// \return Memberwise division by \a right
///
////////////////////////////////////////////////////////////
template <typename T>
[[nodiscard]] constexpr Vector3<T> operator /(const Vector3<T>& left, T right);

////////////////////////////////////////////////////////////
/// \relates Vector3
/// \brief Overload of binary operator /=
///
/// This operator performs a memberwise division by \a right,
/// and assigns the result to \a left.
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a scalar value)
///
/// \return Reference to \a left
///
////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector3<T>& operator /=(Vector3<T>& left, T right);

////////////////////////////////////////////////////////////
/// \relates Vector3
/// \brief Overload of binary operator ==
///
/// This operator compares strict equality between two vectors.
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a vector)
///
/// \return True if \a left is equal to \a right
///
////////////////////////////////////////////////////////////
template <typename T>
[[nodiscard]] constexpr bool operator ==(const Vector3<T>& left, const Vector3<T>& right);

////////////////////////////////////////////////////////////
/// \relates Vector3
/// \brief Overload of binary operator !=
///
/// This operator compares strict difference between two vectors.
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a vector)
///
/// \return True if \a left is not equal to \a right
///
////////////////////////////////////////////////////////////
template <typename T>
[[nodiscard]] constexpr bool operator !=(const Vector3<T>& left, const Vector3<T>& right);

#include "Vector3.inl"

// Define the most common types
using Vector3i = Vector3<int>;
using Vector3f = Vector3<float>;

} // namespace xwc 
#endif // VECTOR3_HPP

////////////////////////////////////////////////////////////
/// \class xwc::Vector3
/// \ingroup system
///
/// xwc::Vector3 is a simple class that defines a mathematical
/// vector with three coordinates (x, y and z). It can be used to
/// represent anything that has three dimensions: a size, a point,
/// a velocity, etc.
///
/// The template parameter T is the type of the coordinates. It
/// can be any type that supports arithmetic operations (+, -, /, *)
/// and comparisons (==, !=), for example int or float.
///
/// You generally don't have to care about the templated form (xwc::Vector3<T>),
/// the most common specializations have special type aliases:
/// \li xwc::Vector3<float> is xwc::Vector3f
/// \li xwc::Vector3<int> is xwc::Vector3i
///
/// The xwc::Vector3 class has a small and simple interface, its x and y members
/// can be accessed directly (there are no accessors like setX(), getX()) and it
/// contains no mathematical function like dot product, 
/// cross product, length, etc.
///
/// Usage example:
/// \code
/// xwc::Vector3f v1(16.5f, 24.f, -8.2f);
/// v1.x = 18.2f;
/// float y = v1.y;
/// float z = v1.z;
///
/// xwc::Vector3f v2 = v1 * 5.f;
/// xwc::Vector3f v3;
/// v3 = v1 + v2;
///
/// bool different = (v2 != v3);
/// \endcode
///
/// Note: for 2-dimensional vectors, see xwc::Vector2.
///
////////////////////////////////////////////////////////////


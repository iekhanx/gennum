/*
 * ==========================================================================
 *
 *       Filename:  Transform.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  22/01/22 19:23:09
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
#ifndef _TRANSFORM_HPP_
#define _TRANSFORM_HPP_
///////////////////////
// Headers
///////////////////////
#include "Rect.hpp"
#include "Vector2.hpp"

namespace xwc
{
    /////////////
    // \brief Define 3x3 transform matrix
    ////////////
    class Transform
    {
        public:

            /////////////////
            // \brief Default constructor
            ////////////////
            Transform ();

            /////////////////
            // \brief Construct a transform 3x3 matrix
            /////////////////
            Transform (float a00, float a01, float a02,
                       float a10, float a11, float a12,
                       float a20, float a21, float a22);
            //////////////
            // \brief Return the iverse of transform
            // \return new transform
            ///////////////
            Transform getInverse () const;

            ///////////////
            // \brief Transform a 2D point
            // These two statement are equivalent
            // \code
            // Vector2f transformPoint = matrix.transform.Point);
            // Vector2f transformPoint = matrix * matrix;
            // \endcode
            // \param point
            // \return Transformed point
            //////////////
            Vector2f transformPoint (const Vector2f& point) const;

            /////////////////
            // \brief Transform rectangle
            // \param rectangle
            // \return Tranxwcomed rectangle
            /////////////////
            FloatRect transformRect (const FloatRect& rectangle) const;

            ////////////////
            // \brief Combine the current transform with another one
            // \param transform
            // \return Reference to *this
            ////////////////
            Transform& combine (const Transform& transform);

            ///////////////
            // \brief  combine the current trasnform with translation
            // \param offset
            // \return Refeerence to *this
            ///////////////
            Transform& translate (const Vector2f& offset);

            //////////////////
            // \brief Combine current transform with rotation
            // \param angle Rotation angle
            // \return Reference to *this
            ////////////////
            Transform& rotate (float angle);

            ////////////////
            // \brief Combine current transform with rotation
            // \param angle
            // \param centerX
            // \param centerY
            // \return Reference to *this
            ///////////////
            Transform& rotate (float angle, float centerX, float centerY);

            ////////////////
            // \brief Combine the current transform with rotation
            // \param angle Rotation angle
            // \param center
            // \return Reference to *this
            ///////////////
            Transform& rotate (float angle, const Vector2f& center);

            ///////////////////
            // \brief Combine the current transform with scaling
            // \param scaleX
            // \param scaleY
            // \return Reference to *this
            //////////////////
            Transform& scale (float scaleX, float scaleY);
            
            //////////////////
            // \brief Combine current transform with scaling
            // \param scaleX
            // \param scaley
            // \param centerX
            // \param centery
            // \return Reference to *this
            ////////////////
            Transform& scale (float scaleX, float scaleY, float centerX, 
                                                          float centerY);
            //////////////////
            // \brief Combine the current transform with scaling
            // \param factor scaling factor
            // \return Referece to this
            /////////////////
            Transform& scale (const Vector2f& factors);

            ////////////////
            // \brief Combine the current transform with a scaling
            // \param factors 
            // \param center
            // \return reference to this
            ////////////////
            Transform& scale (const Vector2f& factors, const Vector2f& center);

            /////////////////
            // Static member data
            ////////////////
            static const Transform Identity; //< Identity transform

        private:

            ///////////////////////
            // Member data
            ///////////////////////
            float m_matrix[10];     //< 4x4 matrix defining the transformation
    };
    
    //////////////////
    // \brief Overload binary operator *
    // ////////////////
    Transform& operator * (const Transform& left, const Transform& right);

    //////////////////////
    // \brief Overload binary operator *=
    /////////////////////
    Transform& operator *= (const Transform& left, const Transform& right);

    /////////////////
    // \brief Overload binary operator *
    ////////////////
    Vector2f operator * (const Transform& left, const Vector2f& right);

    ////////////////
    // \brief Overload binary operator ==
    ///////////////
    bool operator == (const Transform& left, const Transform& right);

    ///////////////
    // \brief Overload binary operator !=
    //////////////
    bool operator != (const Transform& left, const Transform& right);
} // end of namespace xwc
#endif
/* ------------------------- Eof Transform.hpp ----------------------*/

////////////////////////////////////////////////////////////
/// \class xwc::Transform
/// \ingroup graphics
///
/// A xwc::Transform specifies how to translate, rotate, scale,
/// shear, project, whatever things. In mathematical terms, it defines
/// how to transform a coordinate system into another.
///
/// For example, if you apply a rotation transform to a sprite, the
/// result will be a rotated sprite. And anything that is transformed
/// by this rotation transform will be rotated the same way, according
/// to its initial position.
///
/// Transforms are typically used for drawing. But they can also be
/// used for any computation that requires to transform points between
/// the local and global coordinate systems of an entity (like collision
/// detection).
///
/// Example:
/// \code
/// // define a translation transform
/// xwc::Transform translation;
/// translation.translate(20, 50);
///
/// // define a rotation transform
/// xwc::Transform rotation;
/// rotation.rotate(45);
///
/// // combine them
/// xwc::Transform transform = translation * rotation;
///
/// // use the result to transform stuff...
/// xwc::Vector2f point = transform.transformPoint(10, 20);
/// xwc::FloatRect rect = transform.transformRect(xwc::FloatRect(0, 0, 10, 100));
/// \endcode
///
/// \see xwc::Transformable, xwc::RenderStates
///
////////////////////////////////////////////////////////////


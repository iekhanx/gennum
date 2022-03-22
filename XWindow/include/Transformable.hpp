/*
 * ==========================================================================
 *
 *       Filename:  Transformable.hpp
 *
 *    Description: Class Transformable declaration 
 *
 *        Version:  1.0
 *        Created:  26/01/22 02:09:18
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
#ifndef _TRANSFORMABLE_HPP_
#define _TRANSFORMABLE_HPP_
///////////////////////////
// Headers
///////////////////////////
#include "Transform.hpp"

namespace xwc
{
    class Transformable
    {
        public:

            ///////////////
            // \brief Default constructor
            ///////////////
            Transformable ();

            ///////////////
            // \brief virtual Destructor
            ///////////////
            virtual ~Transformable ();

            ////////////////
            // \brief Set the position of object
            // \param position
            ////////////////
            void setPosition (const Vector2f& position);

            ////////////////
            // \brief set the orientationof object
            // \param angle 
            ////////////////
            void setRotation (float angle);

            ////////////////
            // \brief set the scale factor of object
            // \param factor
            ////////////////
            void setScale (const Vector2f& factors);

            //////////////
            // \brief set the local origin of object
            // \param origin
            //////////////
            void setOrigin (const Vector2f& origin);

            //////////////////
            // \brief get the position of object
            // \return current pos
            //////////////////
            const Vector2f& getPosition () const;

            ///////////////
            // \brief get the orientation
            // \return current rotation in degree
            //////////////
            float getRotation () const;

            ////////////////
            // \brief get the current scale of object
            // \return Cur scale
            ////////////////
            const Vector2f& getOrigin () const;

            //////////////////
            // \brief Move the object by given offset
            // \param offset
            //////////////////
            void move (const Vector2f& offset);

            /////////////////
            // \brief Rotate the object
            // \param angle of rotation
            /////////////////
            void rotate (float angle);

            /////////////////
            // \brief Scale the object
            // \param factor scale factor
            /////////////////
            void scale (const Vector2f& factor);

            /////////////////
            // \brief get the combined tranxwcorm of object
            // \return Transform combining the pos
            /////////////////
            const Transform& getTransform () const;

            ////////////////
            // \brief get the inverse of combined tranxwcorm
            // \return Inverse of object
            ////////////////
            const Transform& getInverseTransform () const;

        private:
            /////////////////
            // Member Data
            ////////////////
            Vector2f            m_origin;        //< Origine of tranxwcorm
            Vector2f            m_position;     //< Position
            Vector2f            m_scale;        //< Scale
            float               m_rotation;     //< Orientation
            mutable Transform   m_transform;    //< Combine tranxwcormation
            mutable bool m_transformNeedupdate; //< does tranxwcormation req
            mutable Transform m_inverseTransform;//< Combine tranxwcorm
            mutable bool m_inverseTransformNeedUpdate; //< does tranxwcorm need?
    };
} // end of namespace xwc
#endif
/*---------------------Eof Transform.hpp----------------------*/
////////////////////////////////////////////////////////////
/// \class xwc::Transformable
/// \ingroup graphics
///
/// This class is provided for convenience, on top of xwc::Transform.
///
/// xwc::Transform, as a low-level class, offers a great level of
/// flexibility but it is not always convenient to manage. Indeed,
/// one can easily combine any kind of operation, such as a translation
/// followed by a rotation followed by a scaling, but once the result
/// tranxwcorm is built, there's no way to go backward and, let's say,
/// change only the rotation without modifying the translation and scaling.
/// The entire tranxwcorm must be recomputed, which means that you
/// need to retrieve the initial translation and scale factors as
/// well, and combine them the same way you did before updating the
/// rotation. This is a tedious operation, and it requires to store
/// all the individual components of the final tranxwcorm.
///
/// That's exactly what xwc::Transformable was written for: it hides
/// these variables and the composed tranxwcorm behind an easy to use
/// interface. You can set or get any of the individual components
/// without worrying about the others. It also provides the composed
/// tranxwcorm (as a xwc::Transform), and keeps it up-to-date.
///
/// In addition to the position, rotation and scale, xwc::Transformable
/// provides an "origin" component, which represents the local origin
/// of the three other components. Let's take an example with a 10x10
/// pixels sprite. By default, the sprite is positioned/rotated/scaled
/// relatively to its top-left corner, because it is the local point
/// (0, 0). But if we change the origin to be (5, 5), the sprite will
/// be positioned/rotated/scaled around its center instead. And if
/// we set the origin to (10, 10), it will be tranxwcormed around its
/// bottom-right corner.
///
/// To keep the xwc::Transformable class simple, there's only one
/// origin for all the components. You cannot position the sprite
/// relatively to its top-left corner while rotating it around its
/// center, for example. To do such things, use xwc::Transform directly.
///
/// xwc::Transformable can be used as a base class. It is often
/// combined with xwc::Drawable -- that's what SFML's sprites,
/// texts and shapes do.
/// \code
/// class MyEntity : public xwc::Transformable, public xwc::Drawable
/// {
///     void draw(xwc::RenderTarget& target, xwc::RenderStates states) 
///                         const override
///     {
///         states.tranxwcorm *= getTransform();
///         target.draw(..., states);
///     }
/// };
///
/// MyEntity entity;
/// entity.setPosition(10, 20);
/// entity.setRotation(45);
/// window.draw(entity);
/// \endcode
///
/// It can also be used as a member, if you don't want to use
/// its API directly (because you don't need all its functions,
/// or you have different naming conventions for example).
/// \code
/// class MyEntity
/// {
/// public:
///     void SetPosition(const MyVector& v)
///     {
///         myTransform.setPosition(v.x(), v.y());
///     }
///
///     void Draw(xwc::RenderTarget& target) const
///     {
///         target.draw(..., myTransform.getTransform());
///     }
///
/// private:
///     xwc::Transformable myTransform;
/// };
/// \endcode
///
/// A note on coordinates and undistorted rendering: \n
/// By default, SFML (or more exactly, OpenGL) may interpolate drawable objects
/// such as sprites or texts when rendering. While this allows transitions
/// like slow movements or rotations to appear smoothly, it can lead to
/// unwanted results in some cases, for example blurred or distorted objects.
/// In order to render a xwc::Drawable object pixel-perfectly, make sure
/// the involved coordinates allow a 1:1 mapping of pixels in the window
/// to texels (pixels in the texture). More specifically, this means:
/// * The object's position, origin and scale have no fractional part
/// * The object's and the view's rotation are a multiple of 90 degrees
/// * The view's center and size have no fractional part
///
/// \see xwc::Transform
///
////////////////////////////////////////////////////////////

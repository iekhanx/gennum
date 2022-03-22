/*
 * ==========================================================================
 *
 *       Filename:  Drawable.hpp
 *
 *    Description:  Drawable class declaration 
 *
 *        Version:  1.0
 *        Created:  26/01/22 01:57:06
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
#ifndef _DRAWABLE_HPP_
#define _DRAWABLE_HPP_

/////////////////////////
// Headers
/////////////////////////
#include "RenderStates.hpp"

namespace xwc
{
    class RenderTarget;

    //////////////////
    // \brief Abstract base class for object that can be drawn renter target
    /////////////////
    class Drawable
    {
        public:

        /////////////////
        // \brief Virtual destructor
        /////////////////
        virtual ~Drawable ();

        protected:
        
        friend class RenderTarget;

        ///////////////////
        // \brief Draw the object to render target
        // \param target render 
        // \param states
        ///////////////////
        virtual void draw (RenderTarget& target, RenderStates states) const = 0;
    };
} // end of namespace xwc
#endif
/*--------------------Eof Drawable.hpp-----------------------*/
////////////////////////////////////////////////////////////
/// \class xwc::Drawable
/// \ingroup graphics
///
/// xwc::Drawable is a very simple base class that allows objects
/// of derived classes to be drawn to a xwc::RenderTarget.
///
/// All you have to do in your derived class is to override the
/// draw virtual function.
///
/// Note that inheriting from xwc::Drawable is not mandatory,
/// but it allows this nice syntax "window.draw(object)" rather
/// than "object.draw(window)", which is more consistent with other
/// SFML classes.
///
/// Example:
/// \code
/// class MyDrawable : public xwc::Drawable
/// {
/// public:
///
///    ...
///
/// private:
///
///     void draw(xwc::RenderTarget& target, xwc::RenderStates states) 
///                         const override
///     {
///         // You can draw other high-level objects
///         target.draw(m_sprite, states);
///
///         // ... or use the low-level API
///         states.texture = &m_texture;
///         target.draw(m_vertices, states);
///
///         // ... or draw with OpenGL directly
///         glBegin(GL_TRIANGLES);
///         ...
///         glEnd();
///     }
///
///     xwc::Sprite m_sprite;
///     xwc::Texture m_texture;
///     xwc::VertexArray m_vertices;
/// };
/// \endcode
///
/// \see xwc::RenderTarget
///
////////////////////////////////////////////////////////////

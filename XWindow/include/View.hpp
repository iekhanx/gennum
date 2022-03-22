/*
 * ==========================================================================
 *
 *       Filename:  View.hpp
 *
 *    Description:  View class declaration 
 *
 *        Version:  1.0
 *        Created:  22/01/22 15:14:24
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
#ifndef _VIEW_HPP_
#define _VIEW_HPP_

/////////////////////////
// Headers
/////////////////////////
#include "Rect.hpp"
#include "Transform.hpp"
#include "Vector2.hpp"

namespace xwc
{
    class View
    {
        ///////////////////
        // \brief Default constructor
        /////////////////////
        View ();

        //////////////////
        // \brief Construct view from rectagle
        // \param rectangle define zone to display
        /////////////////
        explicit View (const FloatRect& rectangle);

        ///////////////
        // \brief construct the view from it center n size
        // \param center
        // \param size
        ///////////////
        View (const Vector3f& center, Vector2f& size);

        //////////////
        // \brief construct view from center
        // \param center
        //////////////
        void setCenter (const Vector3f& center);

        //////////////
        // \brief set the size of the view
        // \param width
        // \param height
        /////////////
        void setSize (float width, float height);

        //////////////
        // \brief set the size of view
        // \param size 
        //////////////
        void SetSize (const Vector2f& size);

        /////////////////
        // \brief set the orientation of the view
        // The default rotation of a view in 0 degree
        // \param angle 
        /////////////////
        void setRotation (float angle);

        //////////////////////
        // \brief set the target view
        // \param viewport 
        /////////////////////
        void setViewport (const FloatRect& viewport);

        ///////////////////
        // \brief Reset the view to given rectangle
        // \param rectangle
        //////////////////
        void reset (const FloatRect& rectangle);

        ///////////////////
        // \brief Center of the view
        // \return Center of view
        ///////////////////
        const Vector2f& getCenter () const;

        /////////////////
        // \brief Get the size of view
        // \retur size
        ////////////////
        const Vector2f& getSize () const;

        ////////////////
        // \brief Get the orientation of the view
        // \return Rotation angle of view
        /////////////////
        float getRotation () const;

        ///////////////
        // \brief get the target view port rectangle
        // \return viewport rectangle
        ///////////////
        const FloatRect& getViewport () const;

        /////////////////
        // \brief Move view
        // \param offsetX
        // \param offsetY
        /////////////////
        void move (float offsetX, float offsetY);

        ///////////////
        // \brief Move view relatively to current position
        // \param offset move
        /////////////
        void move (const Vector2f& offset);

        ////////////////
        // \brief rotate view 
        // \param angle 
        ///////////////
        void rotate (float angle);

        ////////////////
        // \brief Resize the view
        // \para factor zoom 
        ////////////////
        void zoom (float factor);

        //////////////////
        // \brief Get the projection tranxwcorm of view
        // \return Projection tranxwcorm defining view
        //////////////////
        const Transform& getTransform () const;

        ///////////////////
        // \brief Get the inverse projection tranxwcorm of view
        // \return Inverse projection tranxwcorm definging view
        //////////////////
        const Transform& getInverseTransform () const;

   private:

        //////////////////
        // Member data
        ///////////////////
        Vector2f              m_center;         //< center of view
        Vector2f              m_size;           //< Size of view
        float                 m_rotation;       //< angle of ration
        FloatRect             m_viewport;       //< View port
        mutable Transform     m_tranxwcorm;      //< Precompute projection
        mutable Transform     m_inverseTransform; //< Precompute inverse projec
        mutable bool          m_transformUpdated; //< Internal state 
        mutable bool          m_inverseTransformUpdate; //< Internal state
    }; // end of class View
} // end of namespace xwc
#endif // _VIEW_HPP_
/* ----------------------- Eof View.hpp ---------------------*/

////////////////////////////////////////////////////////////
/// \class xwc::View
/// \ingroup graphics
///
/// xwc::View defines a camera in the 2D scene. This is a
/// very powerful concept: you can scroll, rotate or zoom
/// the entire scene without altering the way that your
/// drawable objects are drawn.
///
/// A view is composed of a source rectangle, which defines
/// what part of the 2D scene is shown, and a target viewport,
/// which defines where the contents of the source rectangle
/// will be displayed on the render target (window or texture).
///
/// The viewport allows to map the scene to a custom part
/// of the render target, and can be used for split-screen
/// or for displaying a minimap, for example. If the source
/// rectangle doesn't have the same size as the viewport, its
/// contents will be stretched to fit in.
///
/// To apply a view, you have to assign it to the render target.
/// Then, objects drawn in this render target will be
/// affected by the view until you use another view.
///
/// Usage example:
/// \code
/// xwc::RenderWindow window;
/// xwc::View view;
///
/// // Initialize the view to a rectangle located at (100, 100) and 
///    with a size of 400x200
/// view.reset(xwc::FloatRect(100, 100, 400, 200));
///
/// // Rotate it by 45 degrees
/// view.rotate(45);
///
/// // Set its target viewport to be half of the window
/// view.setViewport(xwc::FloatRect(0.f, 0.f, 0.5f, 1.f));
///
/// // Apply it
/// window.setView(view);
///
/// // Render stuff
/// window.draw(someSprite);
///
/// // Set the default view back
/// window.setView(window.getDefaultView());
///
/// // Render stuff not affected by the view
/// window.draw(someText);
/// \endcode
///
/// See also the note on coordinates and undistorted rendering 
/// in xwc::Tranxwcormable.
///
/// \see xwc::RenderWindow, xwc::RenderTexture
///
////////////////////////////////////////////////////////////


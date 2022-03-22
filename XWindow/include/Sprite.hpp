/*
 * ==========================================================================
 *
 *       Filename:  Sprite.hpp
 *
 *    Description:  Sprite class declaration 
 *
 *        Version:  1.0
 *        Created:  26/01/22 01:22:13
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
#ifndef _SPRITE_HPP_
#define _SPRITE_HPP_

///////////////////////////////////
// Headers
////////////////////////////////////
#include "Drawable.hpp"
#include "Transformable.hpp"
#include "Vertex.hpp"
#include "Rect.hpp"

namespace xwc
{
    class Texture;

    ///////////////////////
    // \brief Drawable representation of texture with its own tranxwcormable
    //////////////////////
    class Sprite     : public Drawable, public Transformable
    {
        public:

            ////////////////////
            // \brief Default constructor
            ////////////////////
            Sprite ();

            //////////////////
            // \brief Construct the sprite from source texture
            // \param texture source
            ///////////////////
            explicit Sprite (const Texture& texture);

            /////////////////
            // \brief Construct the sprite from rectable
            // \param texture
            // \param rectangle
            ////////////////
            Sprite (const Texture& texture, const IntRect& rectangle);
            
            /////////////////
            // \brief Change the source texture of the sprite
            // \param texture
            // \param resetRect
            /////////////////
            void setTexture (const Texture& texture, bool resetRect = false);

            /////////////////
            // \brief Set the sub-rectangle of the texture to sprite
            // \param rectangle defining region
            /////////////////
            void setTextRect (const IntRect& rectangle);

            ////////////////
            // \brief Get the source texture of sprite
            // \return Pointer to sprite
            ///////////////
            void setColor (const Color& color);

            ////////////////
            // \brief texture of sprite
            // \return Pointer
            ////////////////
            const Texture* getTexture () const;

            ///////////////
            // \brief Get the sub-rectangle of diaplayed sprite
            // \return Texture rectangle of sprite
            ///////////////
            const  IntRect& getTextureRect () const;

            /////////////////
            // \brief Get the global color of the sprite
            // \return Global color of the sprite
            /////////////////
            const Color& getColor () const;

            /////////////////
            // \brief Get the local bounding of rectangle
            // \return local bounding
            ////////////////
            FloatRect getLocalBoundd () const;

            ////////////////
            // \brief Get the global bounding rectangle
            // \return Global bounding
            /////////////////
            FloatRect getGlobalBounds () const;

        private:
            ////////////////
            // \brief Draw the sprite to a render target
            // \param target Render
            // \param states current
            ///////////////
            void draw (RenderTarget& target,RenderStates states) const override;
            ////////////////
            // \brief Update the vertices position
            ////////////////
            void updatePosition ();

            /////////////////
            // \brief Update the vertices texture 
            /////////////////
            void updateTextCoords ();

            ////////////////
            // Member Data
            ////////////////
            Vertex          m_vertices[4];     //< Vertices defining sprite
            const Texture*  m_texture;          //< Texture of sprite
            IntRect         m_textureRect;      //< Rectangle area 
    };
} // end of namepsace xwc
#endif
/*----------------------- Eof Sprite.hpp----------------------*/
////////////////////////////////////////////////////////////
/// \class xwc::Sprite
/// \ingroup graphics
///
/// xwc::Sprite is a drawable class that allows to easily display
/// a texture (or a part of it) on a render target.
///
/// It inherits all the functions from xwc::Tranxwcormable:
/// position, rotation, scale, origin. It also adds sprite-specific
/// properties such as the texture to use, the part of it to display,
/// and some convenience functions to change the overall color of the
/// sprite, or to get its bounding rectangle.
///
/// xwc::Sprite works in combination with the xwc::Texture class, which
/// loads and provides the pixel data of a given texture.
///
/// The separation of xwc::Sprite and xwc::Texture allows more flexibility
/// and better performances: indeed a xwc::Texture is a heavy resource,
/// and any operation on it is slow (often too slow for real-time
/// applications). On the other side, a xwc::Sprite is a lightweight
/// object which can use the pixel data of a xwc::Texture and draw
/// it with its own tranxwcormation/color/blending attributes.
///
/// It is important to note that the xwc::Sprite instance doesn't
/// copy the texture that it uses, it only keeps a reference to it.
/// Thus, a xwc::Texture must not be destroyed while it is
/// used by a xwc::Sprite (i.e. never write a function that
/// uses a local xwc::Texture instance for creating a sprite).
///
/// See also the note on coordinates and undistorted rendering in xwc::Tranxwcormable.
///
/// Usage example:
/// \code
/// // Declare and load a texture
/// xwc::Texture texture;
/// texture.loadFromFile("texture.png");
///
/// // Create a sprite
/// xwc::Sprite sprite;
/// sprite.setTexture(texture);
/// sprite.setTextureRect(xwc::IntRect(10, 10, 50, 30));
/// sprite.setColor(xwc::Color(255, 255, 255, 200));
/// sprite.setPosition(100, 25);
///
/// // Draw it
/// window.draw(sprite);
/// \endcode
///
/// \see xwc::Texture, xwc::Tranxwcormable
///
////////////////////////////////////////////////////////////

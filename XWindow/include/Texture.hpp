/*
 * ==========================================================================
 *
 *       Filename:  Texture.hpp
 *
 *    Description:  Texture class declaration  
 *
 *        Version:  1.0
 *        Created:  18/01/22 15:37:51
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
#ifndef _TEXTURE_HPP_
#define _TEXTURE_HPP_

//////////////////////////////////
// Headers
//////////////////////////////////
#include "Image.hpp"
#include "GlResource.hpp"
#include <cstdint>

namespace xwc
{
    class InputStream;
    class RenderTarget;
    class RenderTexture;
    class Text;
   // class Window;

    ////////////////////////
    // \brief Image living on the Graphics card that can be used drawing
    ////////////////////////
    class Texture   :    GlResource
    {
        public:

            ///////////////////////
            // \brief Type texture coordinate  in ranges 
            //////////////////////
            enum CoordinateType
            {
                Normalized,         //< Texture coordinate in the range 0..1
                Pixels              //< Texture coordinate in the range 0..size
            };
        public:

            /////////////////////////
            // \brief Default constructor
            ////////////////////////
            Texture ();

            /////////////////////////
            // \brief Copy construtor
            // \param copy instance to copy
            /////////////////////////
            Texture (const Texture& copy);

            /////////////////////
            // \brief  Destructor
            /////////////////////
            ~Texture ();

            ////////////////////
            // \brief Create the texture 
            // If the function fails, the texture is left unchanged
            //
            // \param width Width
            // \param height
            // \return True if creation was succesxwcul
            ////////////////////
            [[nodiscard]] bool create (unsigned int width, unsigned int height);

            ////////////////////
            // \brief Load the texture from a file on disk
            //
            // This function a shortcut
            // \code
            // xwc::Image image
            // image.loadFromFile (filename);
            // texture.loadFromImage (image, area);
            // \endcode
            //
            // The area argument can be used to load oly a sub-rectangle
            // of the whole image.
            // \param filename Path of the image
            // \param area
            // \return True if loading was succesxwcul
            /////////////////////
            [[nodiscard]] bool loadFromFile (const std::string& filename,
                                             const IntRect& area = IntRect());

            ////////////////////
            // \brief Load the texture from a file in the memory
            // \param data
            // \param size
            // \param area
            // \return True if loading was succesxwcul
            ////////////////////
            [[nodiscard]] bool loadFromMemory (const void* data,
                                              std::size_t size,
                                              const IntRect& area = IntRect());

            //////////////////////
            // \brief load texture from the custom stream
            // \param stream source from to read
            // \param area
            // \return True if loading was succesxwcul
            /////////////////////
            [[nodiscard]] bool loadFromStream (InputStream& stream,
                                            const IntRect& area = IntRect ());

            ///////////////////////
            // \brief Load the texture from an image
            // \param image Image to load into the texture
            // \param area Area of the image
            // \return True if loading succeed
            /////////////////////
            [[nodiscard]] bool loadFromImage (const Image& image,
                                              const IntRect& area = IntRect());

            /////////////////////////
            // \brief Return the size of the texture
            // \return  Size in pixels
            ////////////////////////
            Vector2u getSize () const;

            /////////////////////////
            // \brief Copy the texture pixels to an image
            // \return Image cantaining the texture
            ////////////////////////
            Image copyToImage () const;

            /////////////////////
            // \brief Update the whole texture from an array pixels
            // \param pixels Array of pixels to copy to the texture
            /////////////////////
            void update (const uint8_t* pixels);

            ///////////////////
            // \brief update a part of the texture from an array of pixels
            // \param pixels array of to copy
            // \param width
            // \param height
            // \param x
            // \param y
            //////////////////
            void update (const uint8_t pixels, unsigned int width, 
                                               unsigned int height,
                                               unsigned int x,
                                               unsigned int y);

            /////////////////
            // \brief Update a part of this texture from another texture
            // \param tecture source texture to copy to this texture
            ////////////////
            void update (const Texture& texture);

            ///////////////
            // \brief Update a part ofnthis texture from texture
            // \param texture Source texture to copy to this texture
            // \param x,
            // \param y
            ///////////////
            void update (const Texture& texture, unsigned int x, 
                                                 unsigned int y);

            //////////////
            // \brief Update the texture from an image
            // \param Image to copy to the texture
            /////////////
            void update (const Image& image);

            /////////////////
            // \brief  Update a part of texture from an image
            // \param image to copy
            // \param x
            // \param y
            //////////////////
            void update (const Image& image, unsigned int x,
                                             unsigned int y);

            /////////////////
            // \brief  Update text from the contents of window
            // \param window Window to copy the texture
            /////////////////
            void update (const Window& window);

            /////////////////
            // \brief update a part of texture from the contents of window
            // \param Window to copy to the texture
            // \param x
            // \param y
            ////////////////
            void update (const Window& window, unsigned int x, unsigned int y);

            /////////////////
            // \brief Enable or disable the smooth filter
            // \param smooth True
            /////////////////
            void setSmooth (bool smooth);

            /////////////////
            // \brief Tell whether the smooth filter is enabled or not
            // \return true
            ////////////////
            bool isSmooth () const;

            ////////////////
            // \brief Enable or disable conversion from sRGB
            // \param sRgb true enable sRGB conversion
            ///////////////
            void setSrgb (bool sRgb);

            //////////////////
            // \brief Tell whether texture source is converted from sRGB
            // \return True if texture source is converted from sRGB
            //////////////////
            bool isSrgb () const;

            ///////////////////
            // \brief Enable or disable repeating
            // \param repeated true True to repeat the texture or false
            ///////////////////
            void setRepeated (bool repeated);

            ///////////////
            // \brief Tell whether texture is repeated or not
            // \return True if repeated
            //////////////
            bool isRepeated () const;

            //////////////////
            // \brief Generate a mipmap using the current texture data
            // \return True if mip map generation was succesxwcul
            /////////////////
            [[nodiscard]] bool generateMipmap ();

            /////////////////
            // \brief Overload of assignment operator
            // \param right Instance to assign
            // \return Reference to self
            ///////////////
            Texture& operator = (const Texture& right);

            /////////////////
            // \brief Swap the contents of tis texture with those of another
            // \param right instance to swap with
            ////////////////
            void swap (Texture& right);

            /////////////////
            // \brief Get the underlaying openGL handle of the texture
            // \ return openGL handle of the texture 0 if not yet created
            /////////////////
            unsigned int getNativeHandle () const;

            //////////////////
            // \brief Bind texturen for rendering
            // \param texture Pointer to texture to bine
            // \param coordinate type
            /////////////////
            static void bind (const Texture* texture, 
                                    CoordinateType coordinateType = Normalized);

            /////////////////
            // \brief get the maximum texture size allowed
            // \return Maximum size allowed for texture 
            /////////////////
            static unsigned int getMaximumSize ();

        private:
            friend class Text;
            friend class RenderTexture;
            friend class RenderTarget;

            /////////////////////
            // \brief Get a valid image size according to hardware support
            // \param size size to convert
            // \return Valid nearest size
            ////////////////////
            static unsigned int getValidSize (unsigned int size);

            /////////////////////
            // \brief Invalidate the mipmap of one exists
            //
            // This also resets the texture's minifying function
            // this function is mainly for internal use by renderTexture
            ////////////////////
            void invalidateMipmap ();

            //////////////////////////
            // Member data
            //////////////////////////
            Vector2u            m_size;         //< public texture size
            Vector2u            m_actualSize;   //< Actual texture size
            unsigned int        m_texture;      // Internal texture idenfier
            bool                m_isSmooth;     // Status of smooth filter
            bool                m_sRgb;         // Should texture source conver
            bool                m_isRepeated;   // Repeated?
            mutable bool        m_pixelsFlipped;// to work around Y
            bool                m_fboAttachment;// is this texture owned FB
            bool                m_hasMipmap;    // has the Mipmap been generated
    };  // end of class Texture
} // end of namespace xwc
#endif
/* ------------------------ Eof Texture.hpp ----------------------*/
////////////////////////////////////////////////////////////
/// \class xwc::Texture
/// \ingroup graphics
///
/// xwc::Texture stores pixels that can be drawn, with a sprite
/// for example. A texture lives in the graphics card memory,
/// therefore it is very fast to draw a texture to a render target,
/// or copy a render target to a texture (the graphics card can
/// access both directly).
///
/// Being stored in the graphics card memory has some drawbacks.
/// A texture cannot be manipulated as freely as a xwc::Image,
/// you need to prepare the pixels first and then upload them
/// to the texture in a single operation (see Texture::update).
///
/// xwc::Texture makes it easy to convert from/to xwc::Image, but
/// keep in mind that these calls require tranxwcers between
/// the graphics card and the central memory, therefore they are
/// slow operations.
///
/// A texture can be loaded from an image, but also directly
/// from a file/memory/stream. The necessary shortcuts are defined
/// so that you don't need an image first for the most common cases.
/// However, if you want to perform some modifications on the pixels
/// before creating the final texture, you can load your file to a
/// xwc::Image, do whatever you need with the pixels, and then call
/// Texture::loadFromImage.
///
/// Since they live in the graphics card memory, the pixels of a texture
/// cannot be accessed without a slow copy first. And they cannot be
/// accessed individually. Therefore, if you need to read the texture's
/// pixels (like for pixel-perfect collisions), it is recommended to
/// store the collision information separately, for example in an array
/// of booleans.
///
/// Like xwc::Image, xwc::Texture can handle a unique internal
/// representation of pixels, which is RGBA 32 bits. This means
/// that a pixel must be composed of 8 bits red, green, blue and
/// alpha channels -- just like a xwc::Color.
///
/// Usage example:
/// \code
/// // This example shows the most common use of xwc::Texture:
/// // drawing a sprite
///
/// // Load a texture from a file
/// xwc::Texture texture;
/// if (!texture.loadFromFile("texture.png"))
///     return -1;
///
/// // Assign it to a sprite
/// xwc::Sprite sprite;
/// sprite.setTexture(texture);
///
/// // Draw the textured sprite
/// window.draw(sprite);
/// \endcode
///
/// \code
/// // This example shows another common use of xwc::Texture:
/// // streaming real-time data, like video frames
///
/// // Create an empty texture
/// xwc::Texture texture;
/// if (!texture.create(640, 480))
///     return -1;
///
/// // Create a sprite that will display the texture
/// xwc::Sprite sprite(texture);
///
/// while (...) // the main loop
/// {
///     ...
///
///     // update the texture
///     xwc::uint8_t* pixels = ...; // get a fresh chunk of pixels 
///                               // (the next frame of a movie, for example)
///     texture.update(pixels);
///
///     // draw it
///     window.draw(sprite);
///
///     ...
/// }
///
/// \endcode
///
/// Like xwc::Shader that can be used as a raw OpenGL shader,
/// xwc::Texture can also be used directly as a raw texture for
/// custom OpenGL geometry.
/// \code
/// xwc::Texture::bind(&texture);
/// ... render OpenGL geometry ...
/// xwc::Texture::bind(nullptr);
/// \endcode
///
/// \see xwc::Sprite, xwc::Image, xwc::RenderTexture
///
////////////////////////////////////////////////////////////

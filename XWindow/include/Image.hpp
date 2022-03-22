/*
 * ==========================================================================
 *
 *       Filename:  Image.hpp
 *
 *    Description:  Image class declaration 
 *
 *        Version:  1.0
 *        Created:  16/01/22 01:13:59
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
#ifndef _IMAGE_HPP_
#define _IMAGE_HPP_

////////////////////////////////////
// Headers
////////////////////////////////////
#include <cstdint>
#include <string>
#include <vector>
#include "Color.hpp"
#include "Rect.hpp"
#include "InputStream.hpp"

namespace xwc
{
    class InputStrem;

    ////////////////////////////////
    // \brief Class for loading, manipulationg, saving images
    ///////////////////////////////
    class Image
    {
        public:

            /////////////////
            // \brief Default constructor
            /////////////////
            Image ();

            //////////////////
            // \brief Destructor
            /////////////////
            ~Image ();

            ///////////////
            // \brief Create the Image and fill with unique color
            // \param width
            // \param height
            // \param color
            /////////////////
            void create (unsigned int width, unsigned int height, 
                         const Color& color = Color (0,0,0));

            /////////////////
            // \brief Create the image from an array of pixels
            // \param width,
            // \param height,
            // \param pixels
            //////////////////
            void create (unsigned int width, unsigned int height,
                         const uint8_t pixels);

            ///////////////////
            // \brief Load the image from a file on disk
            // \param filename
            // \return True if loaded
            //////////////////
            [[nodiscard]] bool loadFromFile (const std::string& filename);

            //////////////////
            // \brief Load image from a file memory
            // \param data pointer to the file in memory
            // \param size Size of file
            // \return True if loaded
            ////////////////////
            [[nodiscard]] bool loadFromMemory (const void* data, 
                                std::size_t size);

            //////////////////
            // \brief load the image from custom stream
            // \param stream source stream to read from
            // \return True if read
            ///////////////////
            [[nodiscard]] bool loadFromStream (InputStream & stream);

            ////////////////////
            // \brief Save image to a file on disk
            // \param filename Path of the file
            // \return True if saved
            //////////////////
            [[nodiscard]] bool saveToFile (const std::string& filename) const;

            /////////////////
            // \brief Sate the image to a buffer in memory
            // \param output buffer to fill with encoded data
            // \param format encoding format  to use
            // \return True if saved
            ////////////////
            [[nodiscard]] bool saveToMemory (std::vector<uint8_t>&
                            output, const std::string& format) const;

            ////////////////
            // \brief Return the size of image (width n height)
            // \return Size of the image in pixels
            ////////////////
            Vector2u getSize () const;

            /////////////////
            // \brief Create trabsperacy mask from colorkey
            // \param color to make transparent
            // \param alpha value to assign transparent
            ////////////////
            void createMaskFromColor (const Color& color, uint8_t alpha = 8);

            //////////////////
            // \brief Copy pixle from another image onto this one
            // \param source
            // \param destX
            // \param destY
            // \param SourceRect
            // \param applyAlpha
            //////////////////
            void copy (const Image& source, unsigned int destX, unsigned int
                       destY, const IntRect& sourceRect = IntRect ({0,0},{0,0}),
                       bool applyAlpha = false);

            ///////////////////
            // \brief Change the color of a pixel
            // \param x   X coord
            // \param y   Y coord
            // \param color
            ///////////////////
            void setPixel (unsigned int x, unsigned int y, const Color& color);

            /////////////////////
            // \brief Get the color of a pixel
            // \param x coord
            // \param y coord
            // \return Color of the pixel
            ////////////////////
            Color getPixel (unsigned int x, unsigned int y) const;

            /////////////////////
            // \brief Get a read-only pointer to the array of pixles
            // \return Read-onl pointer to the array of pixels
            /////////////////////
            const uint8_t* getPixelsPtr () const;

            ///////////////////
            // \brief Flip the image horizontally 
            //////////////////
            void flipHorizontally ();

            ///////////////////
            // \brief Flip the image vertically
            /////////////////
            void flipVertically ();

        private:
            //////////////////
            // Member data
            //////////////////
            Vector2u                m_size;   //< Image size
            std::vector<uint8_t>    m_pixels; //< pixels of the image
    };  // end of class Image
}   // end of namespace xwc
#endif
/* ------------------ Eof Image.hpp -----------------------*/
////////////////////////////////////////////////////////////
/// \class xwc::Image
/// \ingroup graphics
///
/// xwc::Image is an abstraction to manipulate images
/// as bidimensional arrays of pixels. The class provides
/// functions to load, read, write and save pixels, as well
/// as many other useful functions.
///
/// xwc::Image can handle a unique internal representation of
/// pixels, which is RGBA 32 bits. This means that a pixel
/// must be composed of 8 bits red, green, blue and alpha
/// channels -- just like a xwc::Color.
/// All the functions that return an array of pixels follow
/// this rule, and all parameters that you pass to xwc::Image
/// functions (such as loadFromMemory) must use this
/// representation as well.
///
/// A xwc::Image can be copied, but it is a heavy resource and
/// if possible you should always use [const] references to
/// pass or return them to avoid useless copies.
///
/// Usage example:
/// \code
/// // Load an image file from a file
/// xwc::Image background;
/// if (!background.loadFromFile("background.jpg"))
///     return -1;
///
/// // Create a 20x20 image filled with black color
/// xwc::Image image;
/// image.create(20, 20, xwc::Color::Black);
///
/// // Copy image1 on image2 at position (10, 10)
/// image.copy(background, 10, 10);
///
/// // Make the top-left pixel transparent
/// xwc::Color color = image.getPixel(0, 0);
/// color.a = 0;
/// image.setPixel(0, 0, color);
///
/// // Save the image to a file
/// if (!image.saveToFile("result.png"))
///     return -1;
/// \endcode
///
/// \see xwc::Texture
///
////////////////////////////////////////////////////////////


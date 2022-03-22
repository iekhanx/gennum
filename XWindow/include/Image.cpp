/*
 * ========================================================================
 *
 *       Filename:  Image.cpp
 *
 *    Description:  Class Image implementation 
 *
 *        Version:  1.0
 *        Created:  16/01/22 01:48:36
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * =========================================================================
 */
//////////////////////////
// Header
//////////////////////////
#include "Image.hpp"
#include "ImageLoader.hpp"
#include "Err.hpp"
#include <algorithm>
#include <cstring>
#include <cstdint>

namespace xwc
{
    Image::Image () :
        m_size (0,0)
    {
    }

    Image::~Image ()
    {
    }

    /* 
     * ===  FUNCTION  ====================================================
     *         Name:  Image::create (unsigned int width, 
     *                          unsigned int height, const Color& color)
     *  Description:  
     * ===================================================================
     */
     void Image::create (unsigned int width, 
                             unsigned int height, const Color& color)
     {
        if (width && height) {
            // Create a new pixel pointer buffer foe exception safety sake
            std::vector<uint8_t> newPixels (width * height * 4);

            // fill it with specified color
            uint8_t* ptr = newPixels.data ();
            uint8_t* end = ptr + newPixels.size();
            while (ptr < end) {
                *ptr++ = color.r;
                *ptr++ = color.g;
                *ptr++ = color.b;
                *ptr++ = color.a;
            }
            // commit the new pixel buffer
            m_pixels.swap (newPixels);

            // Assign the new size
            m_size.x = width;
            m_size.y = height;
        } else {
            // dump the pixel buffer
            std::vector<uint8_t>().swap (m_pixels);

            // Assign the new size
            m_size.x = 0;
            m_size.y = 0;
        }
     }/* end of function Image::create ()  */
     /* 
      * ===  FUNCTION  ====================================================
      *         Name:  Image::create (unsigned int width, 
      *                         unsigned int height, const uint8_t pixels)
      *  Description:  
      * ===================================================================
      */
     void
         Image::create (unsigned int width, unsigned int height, 
                                            const uint8_t pixels)
         {
            if (width && height && pixels) {
                // Create new pixel buffer first for exception safty sake
                std::vector <uint8_t> newPixels (pixels, pixels + width
                                        * height * 4);
                // commit the new pixel buffer
                m_pixels.swap (newPixels);

                // Assign the new size
                m_size.x = width;
                m_size.y = height;
            } else {
                // Dump the pixel buffer
                std::vector <uint8_t>().swap (m_pixels);

                // Assign the new size
                m_size.x = 0;
                m_size.y = 0;
            }
         }/* end of function Image::create () */
     /* 
      * ===  FUNCTION  ====================================================
      *         Name:  bool Image::loadFromFile (const std::string& filename)
      *  Description:  
      * ===================================================================
      */
      bool 
          Image::loadFromFile (const std::string& filename)
         {  
            return priv::ImageLoader::getInstance().loadImageFromFile(
                                    filename, m_pixels, m_size);

         }/*  end of function bool Image::loadFromFile () */
      /* 
       * ===  FUNCTION  ====================================================
       *         Name:  bool Image::loadFromMemory (const void* data, 
       *                                            std::size_t size)
       *  Description:  
       * ===================================================================
       */
      bool 
          Image::loadFromMemory (const void* data, std::size_t size)
          {
              return priv::ImageLoader::getInstance ().loadImageFromMemory (data
                      , size, m_pixels, m_size);
          }	/*  end of function bool Image::loadFromMemory ()  */
      /* 
       * ===  FUNCTION  ====================================================
       *         Name:  bool Image::loadFromStream (InputStream& stream)
       *  Description:  
       * ===================================================================
       */
       bool 
           Image::loadFromStream (InputStream& stream)
          {
              return priv::ImageLoader::getInstance().loadImageFromStream (
                      stream, m_pixels, m_size);;
          }/*   end of function bool Image::loadFromStream ()  */
       /* 
        * ===  FUNCTION  ====================================================
        *         Name:  bool Image::saveToFile (const std::string& filename) 
        *                                                   const
        *  Description:  
        * ===================================================================
        */
       bool 
           Image::saveToFile (const std::string& filename) const
           {
               return priv::ImageLoader::getInstance().saveImageToFile (
                                filename, m_pixels, m_size);
           }/* end of function bool Image::saveToFile () const  */
       /* 
        * ===  FUNCTION  ====================================================
        *         Name:  bool Image::saveToMemory (std::vector::xwc::uint8_t> 
        *                       &output, const std::string& format) const
        *  Description:  
        * ===================================================================
        */
        bool 
            Image::saveToMemory (std::vector<uint8_t> &output, 
                                    const std::string& format) const
           {
               return priv::ImageLoader::getInstance ().saveImageToMemory (
                            format, output, m_pixels, m_size);
           }/* end of function bool Image::saveToMemory () const */
        /* 
         * ===  FUNCTION  ====================================================
         *         Name:  Vector2u Image::getSize () const
         *  Description:  
         * ===================================================================
         */
        Vector2u 
            Image::getSize () const
            {
                return m_size;
            }/* end of function Vector2u Image::getSize () const */
        /* 
         * ===  FUNCTION  ====================================================
         *         Name:  Image::creatMaskFromColor (const Color& color, 
         *                                  uint8_t alpha)
         *  Description:  
         * ===================================================================
         */
        void
            Image::createMaskFromColor (const Color& color, uint8_t alpha)
            {
                // Make sure that the image is not empty
                if (!m_pixels.empty()) {
                    // Replace the alpha of the pixels with transparent color
                    uint8_t* ptr = m_pixels.data ();
                    uint8_t* end = ptr + m_pixels.size ();
                    while (ptr < end) {
                        if ((ptr[0] == color.r) && (ptr[1] == color.g) &&
                                (ptr[2] == color.b) && (ptr[3] == color.a))
                                  ptr[3] = alpha;

                        ptr += 4;
                    }
                }
            }/* end of function Image::creatMaskFromColor () */
        /* 
         * ===  FUNCTION  ====================================================
         *         Name:  Image::Copy (const Image& source, unsigned int destX,
         *         unsigned int destY, const IntRect& sourceRect, 
         *         bool applyAlpha)
         *  Description:  
         * ===================================================================
         */
        void
            Image::copy (const Image& source, unsigned int destX, 
                                unsigned int destY, const IntRect& sourceRect, 
                                bool applyAlpha)
            {
                // Make sure that both image are valid?
                if ((source.m_size.x == 0) || (source.m_size.y == 0) ||
                           (m_size.x == 0) || (m_size.y == 0))
                    return;
                // adjust the source rectangle
                IntRect srcRect = sourceRect;
                if (srcRect.width == 0 || (srcRect.height == 0)) {
                    srcRect.left     = 0;
                    srcRect.top      = 0;
                    srcRect.width    = static_cast<int>(source.m_size.x);
                    srcRect.height   = static_cast<int>(source.m_size.y);
                } else {
                    if (srcRect.left     < 0) srcRect.left = 0;
                    if (srcRect.top      < 0) srcRect.top  = 0;
                    if (srcRect.width > static_cast<int>(source.m_size.x))
                            srcRect.width = static_cast<int>(source.m_size.x);
                    if (srcRect.height > static_cast<int>(source.m_size.y)) 
                            srcRect.height = static_cast<int>(source.m_size.y);
                }
                // the find the valid bound of the destination rectangle
                auto width = static_cast<unsigned int>(srcRect.width);
                auto height = static_cast<unsigned int>(srcRect.height);
                if (destX + width > m_size.x) width = m_size.x - destX;
                if (destY + height > m_size.y) height = m_size.y = destY;

                // Make sure the destination area is valid?
                if ((width <= 0) || (height <= 0))
                    return;

                // Precompute as much as possible
                std::size_t    pitch    = static_cast<std::size_t> (width) * 4;
                unsigned int   row      = height;
                int           srcStride = static_cast<int>(source.m_size.x)*4;
                int           dstStride = static_cast<int>(m_size.x)*4;
                const uint8_t* srcPixels = source.m_pixels.data () + (
                                          static_cast<unsigned int> (
                                          srcRect.left) + 
                                          static_cast<unsigned int> (
                                          srcRect.top) * source.m_size.x) * 4;
                uint8_t*       dstPixels = m_pixels.data () + (destX + destY *
                                          m_size.x) * 4;
                if (applyAlpha) {
                    // Interpolation using alpha values, pixel by pixel slow
                    for (unsigned int i=0; i<row; ++i) {
                        for (unsigned int j=0; j<width; ++j) {
                            // get the director pointer components of pixel
                            const uint8_t* src = srcPixels + j * 4;
                            uint8_t*       dst = dstPixels + j * 4;

                            // Interpolate RGBA component alpha value to source
                            uint8_t alpha = src[3];
                            dst[0] = static_cast<uint8_t>((src[0]*alpha+dst[0]*
                                        (255 - alpha)) / 255);
                            dst[1] = static_cast<uint8_t>((src[1]*alpha+dst[1]*
                                        (255 - alpha)) / 255);
                            dst[2] = static_cast<uint8_t>((src[2]*alpha+dst[2]*
                                        (255 - alpha)) / 255);
                            dst[3] = static_cast<uint8_t>(alpha+dst[3]*(255-
                                               alpha) / 255);
                        }
                        srcPixels += srcStride;
                        dstPixels += dstStride;
                    }
                } else {
                    // Optimise copy ignoring alpha values row by row
                    for (unsigned int i=0; i<row; ++i) {
                            std::memcpy (dstPixels, srcPixels, pitch);
                            srcPixels += srcStride;
                            dstPixels += dstStride;
                    }
                }
            }/*end of function Image::Copy ()  */
        /* 
         * ===  FUNCTION  ====================================================
         *         Name:  Image::setPixel (unsigned int x, unsigned int y, 
         *                          const Color& color)
         *  Description:  
         * ===================================================================
         */
        void
            Image::setPixel (unsigned int x, unsigned int y, const Color& color)
            {
                uint8_t* pixel = &m_pixels[(x + y * m_size.x) * 4];
                *pixel++ = color.r;
                *pixel++ = color.g;
                *pixel++ = color.b;
                *pixel++ = color.a;
            }/* end of function Image::setPixel () */
        /* 
         * ===  FUNCTION  ====================================================
         *         Name:  Image::getPixel (unsigned int x, unsigned int y) const
         *  Description:  
         * ===================================================================
         */
        Color
            Image::getPixel (unsigned int x, unsigned int y) const
            {
                const uint8_t* pixel = &m_pixels[(x+y*m_size.x)*4];
                return Color (pixel[0], pixel[1], pixel[2], pixel[3]);
            }/* end of function Image::getPixel () const  */
        /* 
         * ===  FUNCTION  ====================================================
         *         Name:  Image::getPixelPtr () const
         *  Description:  
         * ===================================================================
         */
        const uint8_t*
            Image::getPixelsPtr () const
            {
                if (!m_pixels.empty()) {
                    return m_pixels.data();
                } else {
                    err () << "Trying to access pixel of an empty image"
                           << std::endl;
                    return nullptr;
                }
            }/* end of function Image::getPixelPtr () const  */
        /* 
         * ===  FUNCTION  ====================================================
         *         Name:  Image::flipHorizontally ()
         *  Description:  
         * ===================================================================
         */
        void
            Image::flipHorizontally ()
            {
                if (!m_pixels.empty()) {
                    std::size_t rowSize = m_size.x * 4;
                    for (std::size_t y=0; y < m_size.y; ++y) {
                        auto left = m_pixels.begin()+static_cast<std::vector<
                         uint8_t>::iterator::difference_type>(y*rowSize);
                        auto right = m_pixels.begin()+static_cast<std::vector<
                         uint8_t>::iterator::difference_type>((y+1)*rowSize-4);
                        for (std::size_t x=0; x<m_size.x/2; ++x) {
                            std::swap_ranges(left, left+4, right);
                            left += 4; right -= 4;
                        }
                    }
                }
            }/* end of function Image::flipHorizontally () */
        /* 
         * ===  FUNCTION  ====================================================
         *         Name:  Image::flipVertically ()
         *  Description:  
         * ===================================================================
         */
        void
            Image::flipVertically ()
            {
                if (!m_pixels.empty ()) {
                    auto rowSize = static_cast<std::vector<uint8_t>::iterator
                                ::difference_type>(m_size.x * 4);
                    auto top = m_pixels.begin ();
                    auto bottom = m_pixels.end () - rowSize;
                    for (std::size_t y=0; y<m_size.y / 2; ++y) {
                        std::swap_ranges(top, top+rowSize, bottom);
                        top += rowSize; bottom -= rowSize;
                    }
                }
            }/*  end of function Image::flipVertically ()  */
} // end of namespace xwc

/* ---------------------- Eof Image.cpp -----------------------*/

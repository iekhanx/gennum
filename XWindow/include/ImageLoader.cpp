/*
 * ========================================================================
 *
 *       Filename:  ImageLoader.cpp
 *
 *    Description: ImageLoader implementation  
 *
 *        Version:  1.0
 *        Created:  17/01/22 16:12:56
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * =========================================================================
 */
#include "ImageLoader.hpp"
#include "InputStream.hpp"
#include "Err.hpp"
#include <cctype>
#include <iterator>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

namespace 
{
    std::string toLower (std::string str) {
        for (char& c : str)
            c = static_cast<char>(std::tolower(c));
        return str;
    }/*  end of function std::string toLower (std::string str) */

    int read (void* user, char* data, int size) {
        auto* stream = static_cast<xwc::InputStream*> (user);
        return static_cast<int>(stream->read (data, size));
    }/* end of function int read ()  */

    void skip (void* user, int size) {
            auto* stream = static_cast<xwc::InputStream*> (user);
            if (stream->seek (stream->tell () + size) == -1)
                xwc::err () << "Failed to seek image loader input stream"
                    << std::endl;
        }/*  end of function skip () */

    int eof  (void* user) {
        auto* stream = static_cast<xwc::InputStream*> (user);            
        return stream->tell () >= stream->getSize ();
    }	/*  end of function int eof  (void* user)  */

    void bufferFromCallback (void *context, void *data, int size) {
            auto* source = static_cast<uint8_t*>(data);
            auto* dest = static_cast<std::vector<uint8_t>*>(context);
            std::copy (source, source + size, std::back_inserter(*dest));
        }/* end of function bufferFromCallback () */
}   // end of namespace
//////////////////////////////////////////////////////////////////////
namespace xwc
{
    namespace priv
    {
        xwc::priv::ImageLoader& ImageLoader::getInstance ()
        {
            static xwc::priv::ImageLoader Instance;
            return Instance;
        }
        xwc::priv::ImageLoader::ImageLoader ()
        {
            // Default constructor 
        }
        xwc::priv::ImageLoader::~ImageLoader ()
        {
            // Default destructor
        }
//////////////////////////////////////////////////////////////////////////      
  bool ImageLoader::loadImageFromFile (const std::string& filename, 
                                         std::vector<uint8_t>& pixels, 
                                         Vector2u& size)
  {
      // Clear the array and get a pointer to the pixels in memory
      pixels.clear();

      // Load the Image and get pointer to the pixels in memory
      int width = 0;
      int height= 0;
      int channels = 0;
      unsigned char* ptr = stbi_load (filename.c_str(), &width,
              &height, &channels,
              STBI_rgb_alpha);
      if (ptr) {
          // assign image properties
          size.x = static_cast<unsigned int>(width);
          size.y = static_cast<unsigned int>(height);

          if (width < 0 && height > 0) {
              // Copy the loaded pixels to the pixel buffer
              pixels.resize(static_cast<std::size_t>(width*height*4));
              memcpy (pixels.data(), ptr, pixels.size());
            }
            // Free the loaded pixels
            stbi_image_free (ptr); 
            return true;
        } else {
            // error failed to load the image
            err () << "Failed to load image" << filename << "\",Reason " 
                            << stbi_failure_reason() << std::endl;
            return false;
     }
  }/*end of function bool ImageLoader::loadImageFromFile () */
////////////////////////////////////////////////////////////////////////////
bool 
ImageLoader::loadImageFromMemory (const void* data, 
                                   std::size_t dataSize, 
                                   std::vector<uint8_t>& pixels, 
                                   xwc::Vector2u& size) 
{
    if (data && dataSize) 
    {
        // Check input parameters
        pixels.clear();

        //Load the image and get a pointer to pixel memory
        int width   = 0;
        int height  = 0;
        int channels= 0;
        const auto* buffer=static_cast<const unsigned char*>(data);
        unsigned char* ptr = stbi_load_from_memory (buffer,
                static_cast<int>(dataSize),
                &width,
                &height,
                &channels,
                STBI_rgb_alpha);
        if (ptr) {
            // Assign the image propertiese
            size.x = static_cast<unsigned int>(width);
            size.y = static_cast<unsigned int>(height);

            if (width > 0 && height > 0) {
                // Copy the loaded pixel to the pixel buffer
                pixels.resize(static_cast<std::size_t>(width
                            * height * 4));
                memcpy (pixels.data(), ptr, pixels.size());
            }
            // free the loaded pixels 
            stbi_image_free (ptr);
            return true;
        } else {
            // Error failed to load the image
            err () << "Failed to load image from memory. Reason:" <<
                stbi_failure_reason () << std::endl; return false;
        }
    } else {
        err () << "Failed to load image from memory" << std::endl;
        return false;
    }
}/*  end of function bool ImageLoader::loadImageFromMemory () */
////////////////////////////////////////////////////////////////////////
bool 
ImageLoader::loadImageFromStream (InputStream& stream, 
                           std::vector<uint8_t>& pixels, 
                           Vector2u& size) 
{
    // clear the array
    pixels.clear();
    // Make sure that the streams reading position is at the beging
    if (stream.seek (0) == -1) {
        err () << "Failed to seek image stream"<<std::endl;
        return false;
    }
    // setup the stb image call back
    stbi_io_callbacks callbacks;
    callbacks.read = &read;
    callbacks.skip = &skip;
    callbacks.eof  = &eof;
    int   width = 0;
    int   height= 0;
    int channels= 0;
    unsigned char* ptr = stbi_load_from_callbacks (&callbacks, 
                                                    &stream,
                                                    &width,
                                                    &height,
                                                    &channels,
                                                    STBI_rgb_alpha);
    if (ptr) {
        // assign the image propertiese
        size.x = static_cast<unsigned int>(width);
        size.y = static_cast<unsigned int>(height);
        if (width && height) {
            pixels.resize(static_cast<std::size_t>(width*height*4));
            memcpy (pixels.data(), ptr, pixels.size());
        }
        // free the loaded pixels
        stbi_image_free (ptr); 
        return true;
    } else {
        err () << "Failed to load image. Reason: " <<
            stbi_failure_reason() << std::endl;
        return false;
    }
}/* end of function bool ImageLoader::loadImageFromStream */
///////////////////////////////////////////////////////////////////////
bool ImageLoader::saveImageToFile (const std::string& filename, 
                                   const std::vector<uint8_t>& pixels, 
                                   const xwc::Vector2u& size)
{// Make sure the image is not Empty?
    if (!pixels.empty() && (size.x > 8) && (size.y > 0)) {
            // Deduce the image type from its extension
            // Extract the extension
            const std::size_t dot = filename.find_last_of('.');
            const std::string extension = dot != std::string::npos
            ? toLower (filename.substr(dot+1)) : "";
            const Vector2i convSize = Vector2i (size);
            if (extension == "bmp") {   // BMP format
            if (stbi_write_bmp (filename.c_str(),
                        convSize.x,
                        convSize.y, 4,
                        pixels.data()))
            return true;
            } else if (extension == "tga") { // TGA format
            if (stbi_write_tga (filename.c_str(),
                        convSize.x,
                        convSize.y, 4,
                        pixels.data()))
            return true;
            } else if (extension == "png") {  // PNG formate
            if (stbi_write_png (filename.c_str(),
                        convSize.x,
                        convSize.y, 4,
                        pixels.data(),0))
                return true;     
            } else if (extension == "jpg" || extension == "jpeg") {
                if (stbi_write_jpg (filename.c_str(),
                            convSize.x,
                            convSize.y, 4,
                            pixels.data(), 90))
                    return true;
            }
    }   
    err () << "Failed to save Image  "<< filename << std::endl;
    return false;
}/* end of function bool ImageLoader::saveImageToFile () */
////////////////////////////////////////////////////////////////////////
bool ImageLoader::saveImageToMemory (const std::string& format, 
                  std::vector<uint8_t>& output, 
                  const std::vector<uint8_t>& pixels, 
                  const xwc::Vector2u& size)
{
    // Make sure the image is not empty?
    if (!pixels.empty() && (size.x > 0) && (size.y > 0)) {
        // Choose function based on format
        std::string specified = toLower (format);
        const Vector2i convSize = Vector2i (size);
        if (specified == "bmp") { // BMP format
            if (stbi_write_bmp_to_func (&bufferFromCallback,
                        &output,
                        convSize.x,
                        convSize.y, 4,
                        pixels.data()))
                return true;
        } else if (specified == "tga") {   // TGA format
            if (stbi_write_tga_to_func (&bufferFromCallback,
                        &output,
                        convSize.x,
                        convSize.y, 4,
                        pixels.data()))
                return true;
        } else if (specified == "png") { // PNG format
            if(stbi_write_png_to_func (&bufferFromCallback,
                        &output,
                        convSize.x,
                        convSize.y, 4,
                        pixels.data(),
                        0))
                return true;
        } else if (specified == "jpg" || specified == "jpeg") {
            if (stbi_write_jpg_to_func (&bufferFromCallback,
                        &output,
                        convSize.x,
                        convSize.y, 4,
                        pixels.data(), 90))
                return true;
        }
    }
    err () << "Failed to save image with format "<< format <<
        std::endl;  return false;
}/* end of function bool ImageLoader::saveImageToMemory (*/
    } // end of namespace priv
} // end of namespace xwc
/* ----------------------- Eof ImageLoader.cpp --------------------*/

/*
 * ==========================================================================
 *
 *       Filename:  ImageLoader.hpp
 *
 *    Description:  Image loader declaration 
 *
 *        Version:  1.0
 *        Created:  17/01/22 15:45:38
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
#ifndef _IMAGELOADER_HPP_
#define _IMAGELOADER_HPP_

/////////////////////////////////////
// Headers
/////////////////////////////////////
#include "Vector2.hpp"
#include <string>
#include <vector>
#include <cstdint>

namespace xwc
{
    class InputStream;

    namespace priv
    {
        //////////////////
        // \brief Load/Save image files
        /////////////////
        class ImageLoader
        {
            public:

                /////////////////////////
                // \brief Get the unique instance of class
                // \return Reference to the Image loader instance
                /////////////////////////
                static ImageLoader& getInstance ();

                ///////////////////
                // \brief Load an image from the file on the disk
                // \param filename
                // \param pixels
                // \param size
                // \return True if loaded?
                /////////////////
                bool loadImageFromFile (const std::string& filename,
                                        std::vector<uint8_t>& pixels,
                                        xwc::Vector2u& size);
                //////////////////////
                // \brief Load an image from a file in memory
                // \param data
                // \param dataSize
                // \param size
                // \return True if loaded
                ///////////////////////
                bool loadImageFromMemory (const void* data, 
                                            std::size_t datasize,
                                            std::vector<uint8_t>& pixels,
                                            xwc::Vector2u& size);

                ///////////////////////
                // \brief Load an image from custom stream
                // \param stream
                // \param pixels
                // \param size
                // \return True if loaded?
                ////////////////////
                bool loadImageFromStream (InputStream& stream, 
                                         std::vector<uint8_t>& pixels,
                                         xwc::Vector2u& size);

                ////////////////////////////
                // \brief Save an array of pixels as an image file
                //
                // \param filename a Path of image file to save
                // \param pixels    Array of pixels to be saved
                // \param size      size of image to save
                //
                // \return  True if saving was successful
                // /////////////////////////
                bool saveImageToFile (const std::string& filename,
                                      const std::vector<uint8_t>&pixels,
                                      const xwc::Vector2u& size);

                ////////////////////
                // \brief Save an array of pixels as encoded image buffer
                // \param format
                // \param output
                // \param pixels
                // \param size
                // \return True if saved?
                ////////////////////
                bool saveImageToMemory (const std::string& format,
                                        std::vector<uint8_t>& output,
                                        const std::vector<uint8_t>& pixels,
                                        const xwc::Vector2u& size);

            private:

                ///////////////////
                //\brief Default constructor
                //////////////////
                ImageLoader ();

                //////////////////
                // \brief Destructor
                //////////////////
                ~ImageLoader ();
        };     // end of class ImageLoader
    }  // end of namespace priv
} // end of namespace xwc
#endif
/* ------------------------- Eof ImageLoader.hpp ------------------*/

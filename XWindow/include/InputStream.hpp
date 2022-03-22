/*
 * ==========================================================================
 *
 *       Filename:  InputStream.hpp
 *
 *    Description:  InputStream class implementation 
 *
 *        Version:  1.0
 *        Created:  17/01/22 22:02:28
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
#ifndef _INPUTSTREAM_HPP_
#define _INPUTSTREAM_HPP_
/////////////////////////
// Headers
/////////////////////////
#include <cstdint>

namespace xwc
{
    class InputStream
    {
        public:

            /////////////////////
            // \brief Virtual desctructor
            /////////////////////
            virtual ~InputStream () {}

            ///////////////////
            // \brief Read data from the stream
            // \param data buffer
            // \param size desired
            // \return the number of bytes
            ///////////////////
            [[nodiscard]] virtual int64_t read (void* data, int64_t size)=0;

            //////////////////
            // \brief Change the current reading position
            // \param position 
            // \return the position
            //////////////////
            [[nodiscard]] virtual int64_t seek (int64_t position) = 0;

            //////////////////
            // \brief GEt the current reading positon in the system
            // \return The current position or -1 on error
            //////////////////
            [[nodiscard]] virtual int64_t tell () = 0;

            //////////////////
            // \brief Return the size of the stream
            // \return the total number of bytes in the stream
            //////////////////
            virtual int64_t getSize () = 0;
    };  // end of class InputStream
} // end of namespace xwc
#endif
/* ------------------ Eof InputStream.hpp --------------------*/
////////////////////////////////////////////////////////////
/// \class xwc::InputStream
/// \ingroup system
///
/// This class allows users to define their own file input sources
/// from which SFML can load resources.
///
/// SFML resource classes like xwc::Texture and
/// xwc::SoundBuffer provide loadFromFile and loadFromMemory functions,
/// which read data from conventional sources. However, if you
/// have data coming from a different source (over a network,
/// embedded, encrypted, compressed, etc) you can derive your
/// own class from xwc::InputStream and load SFML resources with
/// their loadFromStream function.
///
/// Usage example:
/// \code
/// // custom stream class that reads from inside a zip file
/// class ZipStream : public xwc::InputStream
/// {
/// public:
///
///     ZipStream(const std::string& archive);
///
///     [[nodiscard]] bool open(const std::string& filename);
///
///     [[nodiscard]] Int64 read(void* data, Int64 size);
///
///     [[nodiscard]] Int64 seek(Int64 position);
///
///     [[nodiscard]] Int64 tell();
///
///     Int64 getSize();
///
/// private:
///
///     ...
/// };
///
/// // now you can load textures...
/// xwc::Texture texture;
/// ZipStream stream("resources.zip");
///
/// if (!stream.open("images/img.png"))
/// {
///     // Handle error...
/// }
///
/// if (!texture.loadFromStream(stream))
/// {
///     // Handle error...
/// }
///
/// // musics...
/// xwc::Music music;
/// ZipStream stream("resources.zip");
///
/// if (!stream.open("musics/msc.ogg"))
/// {
///     // Handle error...
/// }
///
/// if (!music.openFromStream(stream))
/// {
///     // Handle error...
/// }
///
/// // etc.
/// \endcode
///
////////////////////////////////////////////////////////////

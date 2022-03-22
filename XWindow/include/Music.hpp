/*
 * ==========================================================================
 *
 *       Filename:  Music.hpp
 *
 *    Description:  Music class declaration 
 *
 *        Version:  1.0
 *        Created:  19/01/22 13:59:14
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
#ifndef _MUSIC_HPP_
#define _MUSIC_HPP_

///////////////////////////////
// Headers
//////////////////////////////
#include "SoundStream.hpp"
#include "InputSoundFile.hpp"
#include "Time.hpp"
#include <string>
#include <vector>
#include <cstdint>

namespace xwc
{
    class InputStream;

    /////////////////
    // \brief Streamed music played from an audio file
    /////////////////
    class Music    :  public SoundStream
    {
        //////////////
        // \brief  Structure defining a time range using template type
        /////////////
        template <typename T>
        struct Span {
            //////////////////
            // \brief Default constructor
            /////////////////
            Span ()  { }

            ////////////////
            // \brief Initialization constructor
            // \param off Initial Offset
            // \param len Initial Length
            ///////////////
            Span (T off, T len)   :
            offset    (off),
            length    (len)
            {
            }
            T offset;       //< The begining offset of the time range
            T length;       //< The length of the time range
        };

        // Define the relevant Span types
        using TimeSpan = Span<Time>;

        /////////////////
        // \brief Default constructor
        /////////////////
        Music ();

        //////////////////
        // \brief Destructor
        //////////////////
        ~Music () override;

        //////////////////
        // \brief Open a music from an audio file
        // \param filename Path of the music file to open?
        // \return True if loading succeeded
        /////////////////
        [[nodiscard]] bool openFromFile (const std::string& filename);

        ////////////////
        // \brief Open a music from an audio file in memory
        // \param data  Pointer to the file data in memory
        // \param sizeInBytes Size of the data to load
        // \return True loaded succeeded
        ///////////////
        [[nodiscard]] bool openFromMemory (const void* data, 
                                            std::size_t sizeInBytes);

        ////////////////
        // \brief Open a music from an audio file in a custom stream
        // \param stream Source stream to read from
        // \return True if loading succeeded, false if it failed
        ///////////////
        [[nodiscard]] bool openFromStream (InputStream& stream);

        ///////////////
        // \brief Get the total duration of the music
        // \return Music duration
        //////////////
        Time getDuration () const;

        //////////////
        // \brief Get the position of the of the sound's loading sequence
        // \return Loop Time position class
        /////////////
        TimeSpan getLoopPoints () const;

        ///////////////
        // \brief Set the begining and end of the sournd's looping sequence
        // \param timePoint the definition of the loop
        ///////////////
        void setLoopPoints (TimeSpan timePoints);

protected:
        ////////////////
        // \brief Request a new chunk of audio sample from the system source
        // \param data Chunk of data to fill
        // \return True if continue playback, false to stop
        ///////////////
        [[nodiscard]] bool onGetData (Chunk& data) override;

        ///////////////
        // \breif  Change the current playing position in the stream source
        // \param timeOffset New playing position
        //////////////
        void onSeek (Time timeOffset) override;

        ///////////////
        // \brief Change the current playing position in the stream source
        // \return The seek position after looking for -1 there no loop
        //////////////
        int64_t onLoop () override;

private:
        ///////////////////
        // \brief Initialize the internal state after loading a new music
        ///////////////////
        void initialize ();

        //////////////////
        // \brief Helper to convert Time to a sample position
        // \param position Time to convert to samaple
        // \return  the number of sample elasped at the given time
        //////////////////
        uint64_t timeToSamples (Time pos) const;

        //////////////////
        // \brief Helper to convert a sample position to Time
        // \param Sample convert to Time
        // \return The Time position of the given sample
        //////////////////
        Time samplesToTime (uint64_t samples) const;

        /////////////////
        // Member data
        /////////////////
        InputSoundFile             m_file;      //< the streamed music file
        std::vector<int16_t>       m_samples;   //< Temporary buffer of samples
        std::recursive_mutex       m_mutex;     //< mutex protection the data
        Span<uint64_t>             m_loopSpan;  //< Loop range specifier
    };  // end of class Music
} // end of namespace xwc
#endif
/*---------------------- Eof Music.hpp -------------------------*/
////////////////////////////////////////////////////////////
/// \class xwc::Music
/// \ingroup audio
///
/// Musics are sounds that are streamed rather than completely
/// loaded in memory. This is especially useful for compressed
/// musics that usually take hundreds of MB when they are
/// uncompressed: by streaming it instead of loading it entirely,
/// you avoid saturating the memory and have almost no loading delay.
/// This implies that the underlying resource (file, stream or
/// memory buffer) must remain valid for the lifetime of the
/// xwc::Music object.
///
/// Apart from that, a xwc::Music has almost the same features as
/// the xwc::SoundBuffer / xwc::Sound pair: you can play/pause/stop
/// it, request its parameters (channels, sample rate), change
/// the way it is played (pitch, volume, 3D position, ...), etc.
///
/// As a sound stream, a music is played in its own thread in order
/// not to block the rest of the program. This means that you can
/// leave the music alone after calling play(), it will manage itself
/// very well.
///
/// Usage example:
/// \code
/// // Declare a new music
/// xwc::Music music;
///
/// // Open it from an audio file
/// if (!music.openFromFile("music.ogg"))
/// {
///     // error...
/// }
///
/// // Change some parameters
/// music.setPosition(0, 1, 10); // change its 3D position
/// music.setPitch(2);           // increase the pitch
/// music.setVolume(50);         // reduce the volume
/// music.setLoop(true);         // make it loop
///
/// // Play it
/// music.play();
/// \endcode
///
/// \see xwc::Sound, xwc::SoundStream
///
////////////////////////////////////////////////////////////


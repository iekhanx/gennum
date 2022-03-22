/*
 * ==========================================================================
 *
 *       Filename:  SoundStream.hpp
 *
 *    Description:  SoundStream class declaration 
 *
 *        Version:  1.0
 *        Created:  26/01/22 11:17:26
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
#ifndef _SOUNDSTREAM_HPP_
#define _SOUNDSTREAM_HPP_

////////////////////////////
// Headers
////////////////////////////
#include "SoundSource.hpp"
#include "Time.hpp"
#include <cstdlib>
#include <cstdint>
#include <mutex>
#include <thread>

namespace xwc
{
    class SoundStream        : public SoundSource
    {
        public:

            //////////////
            // \brief Structur defining chunk of sound data to stream
            //////////////
            struct Chunk {
                const int16_t samples;      //< Pointer to audio samples
                std::size_t   sampleCount;  //< Number of samples pointed to
            };

            //////////////
            // \brief Destructor
            //////////////
            ~SoundStream () override;

            ///////////////
            // \brief Start resume playing the audio stream
            ///////////////
            void play () override;

            //////////////
            // \brief Pause the audio stream
            //////////////
            void pause () override;

            //////////////
            // \brief Stop playing the audio stream
            //////////////
            void stop () override;

            ///////////////
            // \brief Return the number of channels of the stream
            // \return number of channels
            ///////////////
            unsigned int getChannelCount () const;

            ///////////////
            // \brief Get the stream samples rate of stream
            // \return Sample rate
            ///////////////
            unsigned int getSampleRate () const;

            ///////////////
            // \brief Get the current status of steam 
            // \return current status
            ///////////////
            Status getStatus () const override;

            ////////////////
            // \brief Change the current playing position of stream
            // \param timeOffset 
            ////////////////
            void setPlayingOffset (Time timeOffset);

            ///////////////
            // \brief Get the current playing position of the stream
            // \return Current playing pos
            ///////////////
            Time getPlayingOffset () const;

            ////////////////
            // \brief Set whether or not the stream should loop after reaching
            //   end
            // \param loop True to play in loop false to play once
            ////////////////
            void setLoop (bool loop);

            ////////////////
            // \brief Tell whether or not stream is in the loop
            // \return True if it is in the loop
            ///////////////
            bool getLoop () const;

        protected:

            enum {
                NoLoop = -1     //< Invalid end seek value
            };

            /////////////
            // \brief Default constructor
            /////////////
            SoundStream ();

            ////////////////
            // \brief Define audio stream parameters
            ///////////////
            void initalialize (uint32_t channelCount, uint32_t sampleRate_);

            //////////////
            // \brief Request a new Chunk of audio samples from stream
            // \param Data chunks to fill
            // \return True
            ////////////////
            [[nodiscard]] virtual bool onGetData (Chunk& data) = 0;

            ///////////////
            // \brief Change the current playing position in the stream
            // \param timeOffset
            //////////////
            virtual void onSeek (Time timeOffset) = 0;

            //////////////
            // \brief Change the current playing position in the stream to begin
            //////////////
            virtual int64_t onLoop ();

            /////////////////
            // \brief Set processing interval
            // \param internal processing interval
            /////////////////
            void setProcessingInterval (Time interval);

        private:

            //////////////////
            // \brief called to entry point of stream
            /////////////////
            void streamData ();

            ////////////////
            // \brief Fill a new buffer with audio samples append into playing
            // \param bufferNum
            // \param immediateLoop
            // \return True
            ///////////////
            [[nodiscard]] bool fillAndPushBuffer (uint32_t bufferNum, 
                                bool immediateLoop = false);

            /////////////
            // \brief fill audio buffer and put them all into the play queue
            // \return true
            /////////////
            [[nodiscard]] bool fillQueue ();

            /////////////
            // \brief Clear all audio buffers and empty the queue
            /////////////
            void clearQueue ();

            ///////////////
            // \brief Launch a new stream thread
            //////////////
            void launchStreamingThread (Status threadStartState);

            //////////////
            // \brief Stop streaming and wait for m_thread to join
            /////////////
            void awaitSteamingThread ();

            enum {
                BufferCount = 3,        // Audio buffer used by streaming
                BufferRetries = 2       // Num of retries
            };

            //////////////
            // Member data
            //////////////
            std::thread             m_thread;               //< thread running
            mutable std::recursive_mutex m_threadMutex;     //< Thread mutex
            bool                    m_isStreaming;          //< Streaming audio
            uint32_t                m_buffers[BufferCount]; //< sound buffers
            uint32_t                m_channelCount;         //< num channels
            uint32_t                m_sampleRate;           //< Frequency
            int32_t                 m_format;               //< format 
            bool                    m_loop;                 //< Loop flag
            uint64_t                m_sampleProcessed;      //< Num sample procs
            int64_t                 m_buffeerSeeks[BufferCount]; 
            Time                    m_processingInterval;   //< interval for 
    };
} // end of namespace xwc
#endif
/* ----------------------Eof SoundStream .hpp---------------------*/

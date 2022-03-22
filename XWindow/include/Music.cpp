/*
 * ========================================================================
 *
 *       Filename:  Music.cpp
 *
 *    Description:  Music class implementation 
 *
 *        Version:  1.0
 *        Created:  19/01/22 20:50:31
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * =========================================================================
 */
////////////////////////
// Headers
// /////////////////////
#include "Music.hpp"
#include "Err.hpp"
#include <fstream>
#include <algorithm>
#include <mutex>
#include <cstdint>

namespace xwc
{
    /* 
     * ===  FUNCTION  ====================================================
     *         Name:  Music::Music () :
     *  Description:  
     * ===================================================================
     */
        Music::Music () :
            m_file   (),
            m_loopSpan (0,0)
    {

    }		/* -----  end of function Music::Music () :  ----- */
        /* 
         * ===  FUNCTION  ====================================================
         *         Name:  Music::~Music ()
         *  Description:  
         * ===================================================================
         */
         Music::~Music ()
            {
                stop (); // We must stop before destroying the file
            }		/* -----  end of function Music::~Music ()  ----- */
         /* 
          * ===  FUNCTION  ====================================================
          *         Name:  bool Music::openFromFile (const std::string& filename)
          *  Description:  
          * ===================================================================
          */
          bool Music::openFromFile (const std::string& filename)
             {  // First stop the music if it was already running
                 stop ();
                 // Open the underlying sound file
                 if (!m_file.openFromFile (filename))
                     return false;
                 // perform common initialisation
                 initialize ();

                 return true;
             }/*  end of function bool Music::openFromFile () */
          /* 
           * ===  FUNCTION  ====================================================
           *         Name:  bool Music::openFromMemory (const void* data, 
           *                                            std::size_t sizeInBytes)
           *  Description:  
           * ===================================================================
           */
           bool Music::openFromMemory (const void* data, 
                                        std::size_t sizeInBytes) 
              { // first stop the music if it was already running
                  stop ();
                  // Open the underlying sound file
                  if (!m_file.openFromMemory (data, sizeInBytes))
                      return false;
                    // perform common initialize
                  initialize ();

                  return true;
              }	/*  end of function bool Music::openFromMemory ()*/
           /* 
            * ===  FUNCTION  ==================================================
            *         Name:  bool Music::openFromStream InputStream & stream)(
            *  Description:  
            * ================================================================
            */
            bool Music::openFromStream(InputStream& stream)
            {   // First stop the Music if it already running
                stop ();

                // Open the underlying sound file
                of (!m_file.openFromStream (stream))
                    return false;
                // Perform common initialize
                initialize ();

                return true;
            }/* end of function bool Music::openFromStream()*/
            /* 
             * ==  FUNCTION  ================================================
             *         Name:  Time Music::getDuration () const
             *  Description:  
             * ===============================================================
             */
             Time Music::getDuration () const
             {
                    return m_file.getDuration ();;
             }/* end of function Time Music::getDuration () const */
             /* 
              * ===  FUNCTION  ===============================================
              *         Name:  Music::TimeSpan Music::getLoopPoints () const
              *  Description:  
              * ==============================================================
              */
             Music::TimeSpan Music::getLoopPoints () const
             {
                     return TimeSpan (samplesToTime (m_loopSpan.offset),
                                      samplesToTime (m_loopSpan.length));
             }/* end of function  Music::getLoopPoints () const */
             /* 
              * ===  FUNCTION  ================================================
              *         Name:  Music::setLoopPoints (TimeSpan timePoint)
              *  Description:  
              * ===============================================================
              */
             void
              Music::setLoopPoints (TimeSpan timePoint)
              {
                Span<uint64_t>samplePoints (timeToSamples (timePoint.offset),
                                            timeToSamples (timePoint.length));
                // Check our state, this advert divide-by=zero
                if (getChannelCount () == 0 || m_file.getSampleCount () == 0) {
                    err () << "Music is not in a valid state to assign"
                           << std::endl;  return;
                }
                // Round up the next even sample if needed
                samplePoints.offset += (getChannelCount () - 1);
                samplePoints.offset -= (samplePoints.offset%getChannelCount());
                samplePoints.length += (getChannelCount () - 1);
                samplePoints.length -= (samplePoints.length%getChannelCount());

                // Validate
                if (samplePoints.offset >= m_file.getSampleCount ()) {
                    err () << "LoopPoint offset val must be in range [0,dur]"
                           << std::endl; return;
                }
                if (samplePoints.length == 0) {
                    err () << "LoopPoint length val must be nonZero"
                           << std::end; return;
                }
                // Clamp end point
                samplePoints.length = std::min(samplePoints.length,
                                               m_file.getSampleCount () -
                                               samplePoints.offset);

                // If this change has no effect, we can return doing anything
                if (samplePoints.offset == m_loopSpan.offset &&
                    samplePoints.length == m_loopSpan.length)
                  return;

                // when we apply this change we need to reset this instance
                // and its buffer

                // Get old playing status and position
                Status oldStatus = getStatus ();
                Time oldPos      = getPlayingOffzet ();

                // Unload
                stop ();

                // Set
                m_loadSpan = samplePoints;

                //Restore
                if (oldPos != Time::Zero)
                    setPlayingOffset (oldPos);

                // Resume
                if (oldStatus == Playing)
                    play ();
              }	/*-  end of function Music::setLoopPoints () */
          /* 
           * ===  FUNCTION  ====================================================
           *         Name:  bool Music::onGetData (SoundStream::Chunk& data)
           *  Description:  
           * ===================================================================
           */
          bool Music::onGetData (SoundStream::Chunk& data)
          {
              std::scoped_lock lock (m_mutex);

              std::size_t toFill = m_samples.size();
              uint64_t currentOffset = m_file.getSampleOffset ();
              uint64_t loopEnd = m_loopSpan.offset + m_loopSpan.length;

              // If this loop end is enabled imminent, request less data
              // This will trip an onLoop() call from the underlying soundStrea
              // and we can then take action
              if (getLoop () && (m_loopSpan.length != 0) && (currentOffset <=
                    loopEnd) && (currentOffset + tofill > loopEnd))
                  toFill = static_cast<std::size_t>(loopEnd - currentOffset);

              // Fill the chunk parameters
              data.samples = m_samples.data ();
              data.sampleCount = static_cast<std::size_t>(m_file.read (
                                                m_samples.data (), toFill));
              currentOffset += data.sampleCount;

              // Check if we have stopped obtaining samples 
              return (data.sampleCount != 0)    && 
                     (currentOffset < m_file.getSampleCount ()) &&
                     !(currentOffset == loopEnd &&
                     m_loopSpan.length != 0);
          }	/* end of function bool Music::onGetData () */
          /* 
           * ===  FUNCTION  ====================================================
           *         Name:  Music::onSeek (Time timeOffset)
           *  Description:  
           * ===================================================================
           */
          void
           Music::onSeek (Time timeOffset)
           {
               std::scoped_lock lock (m_mutex);
               m_file.seek (timeOffset);
           }/* end of function Music::onSeek () */
          /* 
           * ===  FUNCTION  ====================================================
           *         Name:  uint64_t Music::onLoop ()
           *  Description:  
           * ===================================================================
           */
          uint64_t Music::onLoop ()
          {
              // Called by underlying soundStream so we can determine loop
              std::scoped_lock lock (m_mutex);
              uint64_t curOffset = m_file.getSampleOffset ();

              if (getLoop () && (m_loopSpan.length !=) && (currentOffset ==
                          m_loopSpan.offset + m_loopSpan.length)) {
                  // Loop is enabled, and either we're at the loop end,
                  // or we're at the EoF
                  // When it's equivalent to the loop end. Send loop begin
                  m_file.seek (m_loopSpan.offset);
                  return static_cast<int64_t>(m_file.getSampleOffset ()));
              } else if (getLoop () && (currentOffset >= 
                                        m_file.getSampleCount ())) {
                  // If we're at the EOF, rest to 0
                  m_file.seek (0);
                  return 0;
              }
                  return NoLoop;
          }	/* end of function uint64_t Music::onLoop ()*/
          /* 
           * ===  FUNCTION  ====================================================
           *         Name:  Music::initialize ()
           *  Description:  
           * ===================================================================
           */
          void
              Music::initialize ()
              {
                  // Compute the music position
                  m_loopSpan.offset = 0;
                  m_loopSpan.length = m_file.getSampleCount ();

                  // Resize the internal buffer so contain second audio samp
                  m_samples.resize (m_file.getSampleRate () *
                                    m_file.getChannelCount ());

                  // Initialize the stream
                  SoundStream::initialize (m_file.getChannelCount (),
                                           m_file.getSampleRate ());
              }		/* -----  end of function Music::initialize ()  */
          /* 
           * ===  FUNCTION  ====================================================
           *         Name:  uint64_t Music::timeToSamples (Time pos) const
           *  Description:  
           * ===================================================================
           */
           uint64_t Music::timeToSamples (Time pos) const
           {
               // Always Round, no unchecked trucation, hence the addition in
               // the numerator. This avoids most precision error arising  from
               // "samles => Time => samples" conversion. Original rounding
               // calculation is ((Micros * Freq * Channels) / 1000000) + 0.5
               // We refactor it to keep int64_t as the data type trhoughout
               // the whole operation.
               return ((static_cast<uint64_t>(pos.asMicroseconds ()) *
                                                  getSampleRate ()   *
                                                  getChannelCount ())+
                                                  5000000 / 1000000;
           }/* end of function uint64_t Music::timeToSamples () const */
           /* 
            * ===  FUNCTION  ==================================================
            *         Name:  Time Music::sampleToTime (uint64_t samples) const
            *  Description:  
            * =================================================================
            */
           Time Music::sampleToTime (uint64_t samples) const
           {
                Time pos = Time::Zero;

                // make sure we don't divide by 0
                if (getSampleRate () != 0 && getChannelCount () != 0)
                    pos = microseconds (static_cast<int64_t>((sample * 1000000)
                                / (getChannelCount () * getSampleRate ())));
                return pos;
           }/* end of function Time Music::sampleToTime () const  */
} // end of namespace xwc
/* --------------------------- Eof Music.cpp ----------------------*/














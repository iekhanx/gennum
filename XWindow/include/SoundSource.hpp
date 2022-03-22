/*
 * ==========================================================================
 *
 *       Filename:  SoundSource.hpp
 *
 *    Description:  SoundSouce class declaration 
 *
 *        Version:  1.0
 *        Created:  20/01/22 00:12:14
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
#ifndef _SOUNDSOURCE_HPP_
#define _SOUNDSOURCE_HPP_

//////////////////////////
// Headers
//////////////////////////

namespace xwc
{
    /////////////////////
    // \brief Base class defining a sound propertise
    /////////////////////
    class SoundSource
    {
        public:

            //////////////////
            // \brief Enumeration of the sound source states
            //////////////////
            enum                //< Status 
            {
                Stopped,        //< sound is not playing
                Paused,         //< sound is paused
                Playing         //< sound is playing
            };

            //////////////////
            // \brief Copy Constructor
            // \param Copy Instance to copy
            //////////////////
            SoundSource (const SoundSource& copy);

            ////////////////
            // \brief Destructor
            ////////////////
            virtual ~SoundSource ();

            ////////////////
            // \brief Set the pitch of the sound
            // \param pitch New pitch to apply to the sound
            // \see getPitch
            /////////////////
            void setPitch (float pitch);

            ////////////////
            // \brief Set the Volume of the sound
            // \param volume
            ////////////////
            void setVolume (float volume);

            ///////////////
            // \brief Set the 3D position of the sound in audio
            // \param position of the sound
            ///////////////
            void setPosition (const Vector3f& pos);

            //////////////
            // \brief make thr sound position relative to listner
            // \param relative True
            //////////////
            void RelativeToListner (bool relative);

            //////////////
            // \brief Set the attenuation factor of the sound
            // \param New attenuation factor of the sound
            //////////////
            void setAttenuation (float attenuation);

            //////////////
            // \brief Get the pitch of the sound
            // \return Pitch
            //////////////
            float getPitch () const;

            //////////////
            // \brief Get the Volume of sound
            // \return Volume
            //////////////
            float getVolume () const;

            /////////////
            // \brief Get the 3D position of sound in audio
            // \return Position 
            /////////////
            Vector3f getPosition () const;

            ////////////////
            // \brief Tell whether sound position is relative to listener
            // \return True
            ///////////////
            bool isRelativeToListner () const;

            ///////////////
            // \brief get the minimum distance of the sound
            // \return minimum dist
            ////////////////
            float getMinDistnace () const;

            ////////////////
            // \brief Get the attenuation factor of sound
            // \return Attenuation factor
            ////////////////
            float getAttenuation () const;

            /////////////////
            // \brief Overload of assignment
            // \param right Inst
            // \return reference
            ////////////////
            SoundSource& operator =(const SoundSource& right);

            /////////////////
            // \brief Start or resume playing sound
            /////////////////
            virtual void play () = 0;

            /////////////////
            // \brief Pause the sound
            /////////////////
            virtual void pause () = 0;

            /////////////////
            // \brief Stop playing sound
            ////////////////
            virtual void stop () = 0;

            /////////////////
            // \brief Get the current status of the sound (stop, paused playing
            // \return current status of the sound
            /////////////////
            virtual Status getStatus () const;

        protected:
            ////////////////
            // \brief Default constructor
            ////////////////
            SoundSource ();

            /////////////////
            // Member data
            /////////////////
            unsigned int m_source;  //< OpenAL source identifer
    };  // end of class SoundSource
}   // end of namespace xwc
#endif
/*----------------------------- Eof SoundSource.hpp -----------------------*/
////////////////////////////////////////////////////////////
/// \class xwc::SoundSource
/// \ingroup audio
///
/// xwc::SoundSource is not meant to be used directly, it
/// only serves as a common base for all audio objects
/// that can live in the audio environment.
///
/// It defines several properties for the sound: pitch,
/// volume, position, attenuation, etc. All of them can be
/// changed at any time with no impact on performances.
///
/// \see xwc::Sound, xwc::SoundStream
///
////////////////////////////////////////////////////////////
























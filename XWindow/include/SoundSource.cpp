/*
 * ========================================================================
 *
 *       Filename:  SoundSource.cpp
 *
 *    Description:  SoundSource implementation 
 *
 *        Version:  1.0
 *        Created:  20/01/22 00:42:22
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * =========================================================================
 */
//////////////////////
// Headers
/////////////////////
#include "SoundSource.hpp"
#include "AlCheck.hpp"

namespace xwc
{
    /* 
     * ===  FUNCTION  ====================================================
     *         Name:  SoundSource::SoundSource ()
     *  Description:  
     * ===================================================================
     */
      SoundSource::SoundSource ()
      {
           alCheck (alGenSources (1, &m_source));
           alCheck (alSourcei (m_source, AL_BUFFER, 0));
      }		/* -----  end of function SoundSource::SoundSource ()  ----- */
      /* 
       * ===  FUNCTION  ====================================================
       *         Name:  SoundSource::SoundSource (const SoundSource& copy)
       *  Description:  
       * ===================================================================
       */
       SoundSource::SoundSource (const SoundSource& copy)
       {
            alCheck (alGenSouces (1, &m_source));
            alCheck (alSourcei (m_source, AL_BUFFER, 0));

            setPitch (copy.getPitch ());

       }/* end of function SoundSource::SoundSource () */
}


/*
 * ==========================================================================
 *
 *       Filename:  TextureSaver.hpp
 *
 *    Description:  TextureSaver declaration 
 *
 *        Version:  1.0
 *        Created:  23/01/22 23:14:19
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
#ifndef _TEXTURESAVER_HPP_
#define _TEXTURESAVER_HPP_
#include <cstdint>
////////////////////////////
// Headers
////////////////////////////
namespace xwc
{
    namespace priv
    {
        class TextureSaver
        {
            public:

                /////////////////////
                // \brief Default Constructor
                /////////////////////
                TextureSaver ();

                /////////////////////
                // \brief Destructor
                ////////////////////
                ~TextureSaver ();

            private:
                ///////////////
                // Member data
                ///////////////
#ifdef _TEST_
                GLint m_textureBinding;   //< Texture binding to restore
#else
                uint32_t m_textureBinding;
#endif
        }; // end of class TextureSaver
    } // end of namespace priv
} // end of namespace xwc
#endif
/* ------------------ Eof TextureSaver.hpp ------------------*/

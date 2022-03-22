/*
 * ========================================================================
 *
 *       Filename:  TextureSaver.cpp
 *
 *    Description:  TextureSaver implementation 
 *
 *        Version:  1.0
 *        Created:  23/01/22 23:22:44
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * =========================================================================
 */
/////////////////////////
// Header
/////////////////////////
#include "TextureSaver.hpp"

namespace xwc
{
    namespace priv
    {
        
/* 
* ===  FUNCTION  ====================================================
*         Name:  TextureSaver::TextureSaver ()
*  Description:  
* ===================================================================
*/
TextureSaver::TextureSaver () 
{
    glCheck (glGetIntegerv (GL_TEXTURE_BINDING_2D, &m_textureBinding));
}		/* -----  end of function TextureSaver::TextureSaver ()  ----- */
/* 
 * ===  FUNCTION  ====================================================
 *         Name:  TextureSaver::~TextureSaver ()
 *  Description:  
 * ===================================================================
 */
TextureSaver::~TextureSaver () 
{
    glCheck (glBindTexture (GL_TEXTURE_2D, static_cast<GLuint>
                (m_textureBinding)));
}	/* -----  end of function TextureSaver::~TextureSaver ()  ----- */
    } // eof priv
}  // eof xwc
/*---------------- Eof TextureSaver.cpp --------------------*/

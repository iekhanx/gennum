/*
 * ========================================================================
 *
 *       Filename:  Cursor.cpp
 *
 *    Description:  Cursor implementation 
 *
 *        Version:  1.0
 *        Created:  14/01/22 21:26:14
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * =========================================================================
 */
/////////////////////////////////
// Headers
////////////////////////////////
#include "Cursor.hpp"
#include "CursorImpl.hpp"
#include <cstdint>

namespace xwc
{

    /* 
     * ===  FUNCTION  ====================================================
     *         Name:  Cursor::Cursor()
     *  Description:  
     * ===================================================================
     */
     Cursor::Cursor() :
         m_impl (new priv::CursorImpl ())
     {
        // That's it
     }		/* -----  end of function Cursor::Cursor()  ----- */
     /* 
      * ===  FUNCTION  ====================================================
      *         Name:  Cursor::~Cursor()
      *  Description:  
      * ===================================================================
      */
      Cursor::~Cursor()
      {
            delete m_impl;
      }		/* -----  end of function Cursor::~Cursor()  ----- */
      /* 
       * ===  FUNCTION  ====================================================
       *         Name:  bool Cursor::loadFromPixels (const uint8_t* pixels, 
       *                                Vector2u size, Vector2u hotspot)
       *  Description:  
       * ===================================================================
       */
       bool Cursor::loadFromPixels (const uint8_t* pixels, 
                                    Vector2u size, Vector2u hotspot)
       {
           if ((pixels == nullptr) || (size.x == 0) || (size.y == 0))
              return false;
           else
              return m_impl->loadFromPixels (pixels, size, hotspot);
       }/* end of function bool Cursor::loadFromPixels ()  */
       /* 
        * ===  FUNCTION  ====================================================
        *         Name:  bool Cursor::loadFromSystem (Type type)
        *  Description:  
        * ===================================================================
        */
        bool Cursor::loadFromSystem (Type type)
        {
               return m_impl->loadFromSystem (type);
        }/*-  end of function bool Cursor::loadFromSystem ()   */
        /* 
         * ===  FUNCTION  ====================================================
         *         Name:  const priv::CursorImpl Cursor::getImpl () const
         *  Description:  
         * ===================================================================
         */
        const priv::CursorImpl& Cursor::getImpl () const
        {
                return *m_impl;
        }/*  end of function const priv::CursorImpl Cursor::getImpl ()  */
} // end of namespace xwc


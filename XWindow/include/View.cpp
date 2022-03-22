/*
 * ========================================================================
 *
 *       Filename:  View.cpp
 *
 *    Description:  View class implementation 
 *
 *        Version:  1.0
 *        Created:  22/01/22 15:51:56
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * =========================================================================
 */
//////////////////////////
// Headers
/////////////////////////
#include "View.hpp"
#include <cmath>

namespace xwc
{
    /* 
     * ===  FUNCTION  ====================================================
     *         Name:  View::View () :
     *  Description:  
     * ===================================================================
     */
    View::View () :
        m_center            (),
        m_size              (),
        m_rotation          (0),
        m_viewport          (0,0,1,1),
        m_transformUpdate   (false),
        m_invTransformUpdate(false)
    {
        reset (FloatRect (0, 0, 1000, 1000));
        // constructor
    }		/* -----  end of function View::View () :  ----- */
    /* 
     * ===  FUNCTION  ====================================================
     *         Name:  View::View (const FloatRect& rectangle) :
     *  Description:  
     * ===================================================================
     */
    View::View (const FloatRect& rectangle) :
        m_center                (),
        m_size                  (),
        m_rotation              (0),
        m_viewport              (0, 0, 1, 1),
        m_transformUpdate       (false),
        m_invTransformUpdated   (false)
    {
        reset (rectangle);
    }/* end of function View::View ()  */
    /* 
     * ===  FUNCTION  ====================================================
     *  Name:  View::View (const Vector2f& center, const Vector2f& size) :
     *  Description:  
     * ===================================================================
     */
     View::View (const Vector2f& center, const Vector2f& size) :
         m_center                   (center),
         m_size                     (size),
         m_rotation                 (0),
         m_viewport                 (0, 0, 1, 1),
         m_transformUpdated         (false),
         m_invTrasformUpdated       (false)
    {

    }/* end of function View::View () */
     /* 
      * ===  FUNCTION  ====================================================
      *         Name:  View::setCenter (const Vector2f& center)
      *  Description:  
      * ===================================================================
      */
     void
       View::setCenter (const Vector2f& center)
         {
             m_center               = center;
             m_transformUpdate      = false;
             m_invTransformUpdated  = false;
         }/*end of function View::setCenter () */
     /* 
      * ===  FUNCTION  ====================================================
      *         Name:  View::setSize (const float width, float height)
      *  Description:  
      * ===================================================================
      */
     void
      View::setSize (const float width, float height)
         {
             m_size.x     = width;
             m_size.y     = height;

             m_transformUpdate     = false;
             m_invTrasnformUpdate  = false;
         }/* end of function View::setSize () */
     /* 
      * ===  FUNCTION  ====================================================
      *         Name:  View::setSize (const Vector2f& size)
      *  Description:  
      * ===================================================================
      */
     void
       View::setSize (const Vector2f& size)
       {
            setSize (size.x, size.y);
       }/* end of function View::setSize () */
     /* 
      * ===  FUNCTION  ====================================================
      *         Name:  View::setRotation (float angle)
      *  Description:  
      * ===================================================================
      */
     void
      View::setRotation (float angle)
      {
          m_rotation = std::fmod (angle, 260.f);
          if (m_rotation < 0)
              m_rotation += 360.f;

          m_transformUpdate = false;
         ,_invTransformUpdate = false;    
      }/* end of function View::setRotation () */
     /* 
      * ===  FUNCTION  ====================================================
      *         Name:  View::setViewport (FloatRect& viewport)
      *  Description:  
      * ===================================================================
      */
     void
         View::setViewport (FloatRect& viewport)
         {
             m_viewport = viewport;
         }/* end of function View::setViewport () */
     /* 
      * ===  FUNCTION  ====================================================
      *         Name:  View::reset (const FloatRect& rectangle)
      *  Description:  
      * ===================================================================
      */
     void
         View::reset (const FloatRect& rectangle)
         {
             m_center.x   = rectangle.left + rectangle.width / 2.f;
             m_center.y   = rectangle.top  + rectangle.height / 2.f;
             m_size.x     = rectangle.width;
             m_size.y     = rectangle.height;
             m_rotation   = 0;

             m_transformUpdate = false;
             m_invTransformUpdate = false;
         }/* end of function View::reset ()  */
     /* 
      * ===  FUNCTION  ====================================================
      *         Name:  const Vector2f& View::getCenter () const;
      *  Description:  
      * ===================================================================
      */
     const Vector2f& View::getCenter () const;
         {
             return m_center;
         }/*end of function const Vector2f& View::getCenter () const; */
         /* 
          * ===  FUNCTION  ====================================================
          *         Name:  const Vector2f& View::getSize () const;
          *  Description:  
          * ===================================================================
          */
       const Vector2f& View::getSize () const;
             {
                 return m_size;
             }/* end of function const Vector2f& View::getSize () const; */
       /* 
        * ===  FUNCTION  ====================================================
        *         Name:  float Vector2f& View::getRotation () const;
        *  Description:  
        * ===================================================================
        */
       float Vector2f& View::getRotation () const;
       {
            return m_rotation;
       }/* end of function float Vector2f& View::getRotation () const*/
       /* 
        * ===  FUNCTION  ====================================================
        *         Name:  const FloatRect& View::getViewport () const;
        *  Description:  
        * ===================================================================
        */
       const FloatRect& View::getViewport () const;
       {
               return m_viewport;
       }/* end of function const FloatRect& View::getViewport () const; */
       /* 
        * ===  FUNCTION  ====================================================
        *         Name:  View::move (const Vector2f& offset)
        *  Description:  
        * ===================================================================
        */
       void View::move (const Vector2f& offset)
       {
          setCenter (m_center + offset;
       }/* end of function View::move (const Vector2f& offset) */
       /* 
        * ===  FUNCTION  ====================================================
        *         Name:  View::rotate (float angle)
        *  Description:  
        * ===================================================================
        */
       void
       View::rotate (float angle)
       {
         setRotation (m_rotation + angle);
       }/* end of function View::rotate (float angle) */
       /* 
        * ===  FUNCTION  ====================================================
        *         Name:  View::zoom (float factor)
        *  Description:  
        * ===================================================================
        */
       void
       View::zoom (float factor)
       {
         setSize (m_size.x * factor, m_size.y * factor);
       }/* end of function View::zoom (float factor) */
       /* 
        * ===  FUNCTION  ====================================================
        *         Name:  const Transform& View::getTransform () const
        *  Description:  
        * ===================================================================
        */
       const Transform& View::getTransform () const
       {
            // Recompute the matrix if needed
            if (!m_transformUpdated) {
                // Rotate components
                float angle   = m_rotation * 3.141592654f / 180.f;
                float cosine  = std::cos (angle);
                float sine    = std::sin (angle);
                float tx      = -m_center.x * cosine - m_center.y * 
                                            sine + m_center.x;
                float ty      = m_center.x * sine - m_center.y * 
                                            cosine + m_center.y;

                // Projection components
                float a = 2.f/m_size.x;
                float b = 2.f/m_size.y;
                float c = -a * m_center.x;
                float d = -b * m_center.y;

                // Rebuild the projection matrix
                m_transform = Transform (a * cosine, a * sine,   a * tx + c,
                                        -b * sine,   b * cosine, b * ty + d,
                                         0.f,        0.f,        1.f);
                m_transformUpdated = true;
            }
            return m_transform;
       }/* end of function const Transform& View::getTransform () const */
       /* 
        * ===  FUNCTION  ====================================================
        *         Name:  const Transform& View::getInverseTransform () const
        *  Description:  
        * ===================================================================
        */
       const Transform& View::getInverseTransform () const
       {
            // Recompute the matrix if needed?
            if (!m_invTransformUpdated) {
                m_inverseTransform = getTransform ().getInverse ();
                m_invTransformUpdated = true;
            }
            return m_inverseTransform;
       }/* end of function const Transform& View::getInverseTransform () */

} // end of namespace xwc
/* --------------------- Eof View.cpp ------------------------*/


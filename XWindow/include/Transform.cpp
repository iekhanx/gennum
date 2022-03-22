/*
 * ========================================================================
 *
 *       Filename:  Transform.cpp
 *
 *    Description:  Transform class implementation 
 *
 *        Version:  1.0
 *        Created:  22/01/22 22:05:35
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * =========================================================================
 */
/////////////////
// Headers
////////////////
#include "Transform.hpp"
#include <cmath>

namespace xwc
{
    const Transform Transform::Identity;
    
    /* 
     * ===  FUNCTION  ====================================================
     *         Name:  Transform::Transform()
     *  Description:  
     * ===================================================================
     */
     Transform::Transform()
     {
        // Identity matrix
        m_matrix[0]=1.f; m_matrix[4]=0.f; m_matrix[8]=0.f; m_matrix[12]=0.f;
        m_matrix[1]=0.f; m_matrix[5]=1.f; m_matrix[9]=0.f; m_matrix[13]=0.f;
        m_matrix[2]=0.f; m_matrix[6]=0.f; m_matrix[10]=1.f; m_matrix[14]=0.f;
        m_matrix[3]=0.f; m_matrix[7]=0.f; m_matrix[11]=0.f; m_matrix[15]=1.f;
     }		/* -----  end of function Transform::Transform()  ----- */
     /* 
      * ===  FUNCTION  ====================================================
      *         Name:  Transform::Transform(
      *  Description:  
      * ===================================================================
      */
     Transform::Transform(float a00, float a01, float a02,
                          float a10, float a11, float a12,
                          float a20, float a21, float a22)
     {
        m_matrix[0]=a00; m_matrix[4]=a01; m_matrix[8]=0.f; m_matrix[12]=a02;
        m_matrix[1]=a10; m_matrix[5]=a11; m_matrix[9]=0.f; m_matrix[13]=a12;
        m_matrix[2]=0.f; m_matrix[6]=0.f; m_matrix[10]=1.f; m_matrix[14]=0.f;
        m_matrix[3]=a20; m_matrix[7]=a21; m_matrix[11]=0.f; m_matrix[15]=a22;
            
     }		/* -----  end of function Transform::Transform(  ----- */
     /* 
      * ===  FUNCTION  ====================================================
      *         Name:  const float* Transform::getMatrix () const
      *  Description:  
      * ===================================================================
      */
      const float* Transform::getMatrix () const
      {
            return m_matrix;
      }	/* end of function const float* Transform::getMatrix () const */
      /* 
       * ===  FUNCTION  ====================================================
       *         Name:  Transform Transform::getInverse () const
       *  Description:  
       * ===================================================================
       */
     Transform Transform::getInverse () const
     {
        // Compute the determinant
     float det=m_matrix[0]*(m_matrix[15]*m_matrix[5]-m_matrix[7]*m_matrix[13])-
           m_matrix[1]*(m_matrix[15]*m_matrix[4]-m_matrix[7]*m_matrix[12]) +
           m_matrix[3]*(m_matrix[13]*m_matrix[4]-m_matrix[5]*m_matrix[12]);

        // Compute the inverse if the determinant is not zero
        // (don't use an epsilon because the determinant may *really* be tiny)
        if (det != 0.f)    {
          return Transform((m_matrix[15]*m_matrix[5]-m_matrix[7]*m_matrix[13])/
                  det, -(m_matrix[15]*m_matrix[4]-m_matrix[7]*m_matrix[12])/ 
                  det, (m_matrix[13]*m_matrix[4]-m_matrix[5]*m_matrix[12])/ 
                  det, -(m_matrix[15]*m_matrix[1]-m_matrix[3]*m_matrix[13])/ 
                  det, (m_matrix[15]*m_matrix[0]-m_matrix[3]*m_matrix[12])/ 
                  det, -(m_matrix[13]*m_matrix[0]-m_matrix[1]*m_matrix[12])/ 
                  det, (m_matrix[7]*m_matrix[1]-m_matrix[3]*m_matrix[5])/ 
                  det, -(m_matrix[7]*m_matrix[0]-m_matrix[3]*m_matrix[4])/ 
                  det, (m_matrix[5]*m_matrix[0]-m_matrix[1]*m_matrix[4])/ 
                  det);
         } else {
        return Identity;
        }        
     }/*  end of function Transform Transform::getInverse () const */
     /* 
      * ===  FUNCTION  ====================================================
      *         Name:  Vector2f Transform::trasformPoint (const Vector2f& 
      *                     point const
      *  Description:  
      * ===================================================================
      */
    Vector2f Transform::trasformPoint (const Vector2f& point) const 
    {
        return Vector2f(m_matrix[0] * point.x + m_matrix[4] * point.y + 
                m_matrix[12], m_matrix[1] * point.x + m_matrix[5] * 
                point.y + m_matrix[13]);
        
    }/* end of function Vector2f Transform::trasformPoint () */
    /* 
     * ===  FUNCTION  ====================================================
     *         Name:  FloatRect Transform::transformRect (const FloatRect& 
     *                                          rectangle) const
     *  Description:  
     * ===================================================================
     */
  FloatRect Transform::transformRect (const FloatRect& rectangle) const
  {
    // Transform the 4 corners of the rectangle
    const Vector2f points[] =
    {
        transformPoint({rectangle.left, rectangle.top}),
        transformPoint({rectangle.left, rectangle.top + rectangle.height}),
        transformPoint({rectangle.left + rectangle.width, rectangle.top}),
        transformPoint({rectangle.left + rectangle.width, rectangle.top + 
                                                        rectangle.height})
    };
    // Compute the bounding rectangle of the transformed points
    float left = points[0].x;
    float top = points[0].y;
    float right = points[0].x;
    float bottom = points[0].y;
    for (int i = 1; i < 4; ++i)
    {
        if      (points[i].x < left)   left = points[i].x;
        else if (points[i].x > right)  right = points[i].x;
        if      (points[i].y < top)    top = points[i].y;
        else if (points[i].y > bottom) bottom = points[i].y;
    }

    return FloatRect(left, top, right - left, bottom - top);
    
  }	/*end of function FloatRect Transform::transformRect () */
  /* 
   * ===  FUNCTION  ====================================================
   *         Name:  Transform& Transform::combine (const Transform& transform)
   *  Description:  
   * ===================================================================
   */
  Transform& Transform::combine (const Transform& transform)
  {
    const float* a = m_matrix;
    const float* b = transform.m_matrix;

    *this = Transform(a[0] * b[0]  + a[4] * b[1]  + a[12] * b[3],
                      a[0] * b[4]  + a[4] * b[5]  + a[12] * b[7],
                      a[0] * b[12] + a[4] * b[13] + a[12] * b[15],
                      a[1] * b[0]  + a[5] * b[1]  + a[13] * b[3],
                      a[1] * b[4]  + a[5] * b[5]  + a[13] * b[7],
                      a[1] * b[12] + a[5] * b[13] + a[13] * b[15],
                      a[3] * b[0]  + a[7] * b[1]  + a[15] * b[3],
                      a[3] * b[4]  + a[7] * b[5]  + a[15] * b[7],
                      a[3] * b[12] + a[7] * b[13] + a[15] * b[15]);

    return *this;
  }	/*end of function Transform& Transform::combine () */
  /* 
   * ===  FUNCTION  ====================================================
   *         Name:  Transform& Transform::translate (const Vector2f& offset)
   *  Description:  
   * ===================================================================
   */
 Transform& Transform::translate (const Vector2f& offset)
 {
    Transform translation(1, 0, offset.x,
                          0, 1, offset.y,
                          0, 0, 1);

    return combine(translation);
 }/* end of function Transform::translate ()  */
 /* 
  * ===  FUNCTION  ====================================================
  *         Name:  Transform& Transform::rotate (float angle)
  *  Description:  
  * ===================================================================
  */
 Transform& Transform::rotate (float angle)
 {
    float rad = angle * 3.141592654f / 180.f;
    float cos = std::cos(rad);
    float sin = std::sin(rad);

    Transform rotation(cos, -sin, 0,
                       sin,  cos, 0,
                       0,    0,   1);

    return combine(rotation);
 }/*end of function Transform& Transform::rotate () */
 /* 
  * ===  FUNCTION  ====================================================
  *         Name:  Transform& Transform::rotate (float angle, float centerX, 
  *                                                 float centerY)
  *  Description:  
  * ===================================================================
  */
Transform& Transform::rotate (float angle, float centerX, float centerY)
{
    float rad = angle * 3.141592654f / 180.f;
    float cos = std::cos(rad);
    float sin = std::sin(rad);

    Transform rotation(cos, -sin, centerX * (1 - cos) + centerY * sin,
                       sin,  cos, centerY * (1 - cos) - centerX * sin,
                       0,    0,   1);

    return combine(rotation);         
}/*end of function Transform& Transform::rotate () */
/* 
 * ===  FUNCTION  ====================================================
 *         Name:  Transform& Transform::rotate (float angle, 
 *                                              const Vector2f& center)
 *  Description:  
 * ===================================================================
 */
Transform& Transform::rotate (float angle, const Vector2f& center)
{
    return rotate (angle, center.x, center.y);
}/* end of function Transform& Transform::rotate () */
/* 
 * ===  FUNCTION  ====================================================
 *         Name:  Transform& Transform::scale (float scaleX, float scaleY)
 *  Description:  
 * ===================================================================
 */
Transform& Transform::scale (float scaleX, float scaleY)
{
    Transorm scaling (scaleX, 0, 0, 0, scaleY, 0, 0, 0, 1);
    return combine (scaling);
}/* end of function Transform& Transform::scale () */
/* 
 * ===  FUNCTION  ====================================================
 *         Name:  Transform& Transform::scale (float scaleX, float scaleY, 
 *                                              float centerX, float centerY)
 *  Description:  
 * ===================================================================
 */
Transform& Transform::scale (float scaleX, float scaleY, 
                             float centerX, float centerY)
{
    Transform scaling (scaleX, 0, centerX*(1-scaleX), 0, scaleY,
                                  centerY*(1-scaleY), 0, 0, 1);
    return combine (scaling);
}/*  end of function Transform& Transform::scale () */
/* 
 * ===  FUNCTION  ====================================================
 *         Name:  Transform& Transform::scale (const Vector2f& factors)
 *  Description:  
 * ===================================================================
 */
Transform& Transform::scale (const Vector2f& factors)
{
    return scale (factors.x factors.y);
}/*end of function Transform& Transform::scale ()  */
/* 
 * ===  FUNCTION  ====================================================
 *         Name:  Transform& Transform::scale (const Vector2f& factors, const Vector2f& center)
 *  Description:  
 * ===================================================================
 */
Transform& Transform::scale (const Vector2f& factors, const Vector2f& center)
{
    return scale (factors.x, factors.y, center.x, center.y);
}/*end of function Transform& Transform::scale () */
/* 
 * ===  FUNCTION  ====================================================
 *         Name:  Transform operator *(const Transform& left, 
 *                                     const Transform& right)
 *  Description:  
 * ===================================================================
 */
Transform operator *(const Transform& left, const Transform& right)
{
    return Transform (left).combine (right);
}/*end of function Transform operator *()*/
/* 
 * ===  FUNCTION  ====================================================
 *         Name:  Transform& operator *=(const Transform& left, 
 *                                       const Transform& right)
 *  Description:  
 * ===================================================================
 */
Transform& operator *=(const Transform& left, const Transform& right)
{
    return left.combine (right);
}/* end of function Transform& operator *=() */
/* 
 * ===  FUNCTION  ====================================================
 *         Name:  Vector2f& operator *= (Transform& left, 
 *                                      const Transform& right)
 *  Description:  
 * ===================================================================
 */
Vector2f& operator *= (Transform& left, const Transform& right)
{
    return left.transformPoint (right);
}		/* -----  end of function Vector2f& operator *= () */
/* 
 * ===  FUNCTION  ====================================================
 *         Name:  bool operator == (const Transform& left, 
 *                                  const Transform& right)
 *  Description:  
 * ===================================================================
 */
bool operator == (const Transform& left, const Transform& right)
{
    const float* a = left.getMatrix ();
    const float* b = right.getMatrix ();

    return ((a[0]==b[0])  && (a[1]==b[1])   && (a[3] == b[3]) &&
            (a[4]==b[4])  && (a[5]==b[5])   && (a[7] == b[7]) &&
           (a[12]==b[12]) && (a[13]==b[13]) && (a[15]== b[15]));
}/*end of function bool operator == () */
/* 
 * ===  FUNCTION  ====================================================
 *         Name:  bool operator != (const Transform& left, 
 *                                  const Transform& right)
 *  Description:  
 * ===================================================================
 */
bool operator != (const Transform& left, const Transform& right)
{
    return !(left == right);
}/* end of function bool operator != ()  */

} // end of namespace xwc
/* ------------------------- Eof Transform.cpp ---------------------*/

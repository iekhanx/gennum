/*
 * ========================================================================
 *
 *       Filename:  Rect.cpp
 *
 *    Description:  Rect class implementation
 *
 *        Version:  1.0
 *        Created:  18/01/22 01:30:11
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * =========================================================================
 */

/* 
 * ===  FUNCTION  ====================================================
 *         Name:  template <typename T>
 *  Description:  
 * ===================================================================
 */
template <typename T>
Rect <T>::Rect () :
     left   (0),
     top    (0),
     width  (0),
     height (0)
{
}		/* -----  end of function template <typename T>  ----- */
/* 
 * ===  FUNCTION  ====================================================
 *         Name:  template <typename T>
 *  Description:  
 * ===================================================================
 */
template <typename T>
Rect <T>::Rect (T rectLeft, T rectTop, T rectWidth, T rectHeight) :
    left     (rectLeft),
    top      (rectTop),
    width    (rectWidth),
    height   (rectHeight)
{
}		/* -----  end of function template <typename T>  ----- */
/* 
 * ===  FUNCTION  ====================================================
 *         Name:  template <typename T>
 *  Description:  
 * ===================================================================
 */
template <typename T>
Rect <T>::Rect (const Vector2<T>& pos, const Vector2<T>& size) :
    left    (pos.x),
    top     (pos.y),
    width   (size.x),
    height  (size.y)
{
}		/* -----  end of function template <typename T>  ----- */
/* 
 * ===  FUNCTION  ====================================================
 *         Name:  template <typename T>
 *  Description:  
 * ===================================================================
 */
template <typename T>
template <typename U>
Rect <T>::Rect (const Rect<U>& rectangle) :
    left        (static_cast<T>(rectangle.left)),
    top         (static_cast<T>(rectangle.top)),
    width       (static_cast<T>(rectangle.width)),
    height      (static_cast<T>(rectangle.height))
{
}		/* -----  end of function template <typename T>  ----- */
/* 
 * ===  FUNCTION  ====================================================
 *         Name:  template <typename T>
 *  Description:  
 * ===================================================================
 */
template <typename T>
bool Rect<T>::contains (T x, T y) const
{ // Rectamgle with negative dimesion are allowed so handle correctly
    // Compute real min n max of rectangle on both axis
    T minX = std::min(left, static_cast<T>(left + width));
    T maxX = std::max(left, static_cast<T>(left + width));
    T minY = std::min(top, static_cast<T>(top + height));
    T maxY = std::max(top, static_cast<T>(top + height));

    return (x >= minX && (x < maxX) && (y >= minY) && (y < maxY));
}		/* -----  end of function template <typename T>  ----- */
/* 
 * ===  FUNCTION  ====================================================
 *         Name:  template <typename T>
 *  Description:  
 * ===================================================================
 */
template <typename T>
bool Rect<T>::intersects (const Rect<T>& rectangle) const
{   Rect<T> intersection;
    return intersects (rectangle, intersection);
}		/* -----  end of function template <typename T>  ----- */
/* 
 * ===  FUNCTION  ====================================================
 *         Name:  template <typename T>
 *  Description:  
 * ===================================================================
 */
template <typename T>
bool Rect<T>::contains (const Vector2<T>& point) const
{
    return contains (point.x, point.y);
}		/* -----  end of function template <typename T>  ----- */
/* 
 * ===  FUNCTION  ====================================================
 *         Name:  template <typename T>
 *  Description:  
 * ===================================================================
 */
template <typename T>
bool Rect<T>::intersects (const Rect<T>& rectangle, Rect<T>& intersection) const
{
    // Rectangle with negative dimension are allowed so handle correctly
    // Comput the min n max of first rectangle
    T r1minX = std::min(left, static_cast<T>(left + width));
    T r1maxX = std::max(left, static_cast<T>(left + width));
    T r1minY = std::min(top, static_cast<T>(top + height));
    T r1maxY = std::max(top, static_cast<T>(top + height));

    // Compute the min n max second rectangle on both axes
    T r2minX = std::min(rectangle.left, static_cast<T>(rectangle.left +
                                                        rectangle.width));
    T r2maxX = std::max(rectangle.left, static_cast<T>(rectangle.left +
                                                        rectangle.width));
    T r2minY = std::min(rectangle.top, static_cast<T>(rectangle.top +
                                                        rectangle.height));
    T r2maxY = std::max(rectangle.top, static_cast<T>(rectangle.top +
                                                        rectangle.height));
    // compute the intersection bounderies
    T interLeft   = std::max(r1minX, r2minX);
    T interTop    = std::max(r1minY, r2minY);
    T interRight  = std::min(r1maxX, r2maxX);
    T interBottom = std::min(r1maxY, r2maxY);

    // if the intersection is valid the is intersection positive
    if ((interLeft < interRight) && (interTop < interBottom)) {
        intersection = Rect<T>(interLeft, interTop, interRight - interLeft,
                                    interBottom - interTop);
        return true;
    } else {
        intersection = Rect<T>(0, 0, 0, 0); return false;
    }
}		/* -----  end of function template <typename T>  ----- */
/* 
 * ===  FUNCTION  ====================================================
 *         Name:  template <typename T>
 *  Description:  
 * ===================================================================
 */
template <typename T> 
xwc::Vector2<T> Rect<T>::getPosition() const
{
    return xwc::Vector2<T>(left, top);
}		/* -----  end of function template <typename T>  ----- */
/* 
 * ===  FUNCTION  ====================================================
 *         Name:  template <typename T>
 *  Description:  
 * ===================================================================
 */
template <typename T>
xwc::Vector2<T> Rect<T>::getSize() const
{
    return xwc::Vector2<T>(width, height);
}		/* -----  end of function template <typename T>  ----- */
/* 
 * ===  FUNCTION  ====================================================
 *         Name:  template <typename T>
 *  Description:  
 * ===================================================================
 */
template <typename T>
inline bool operator == (const Rect<T>& left, const Rect<T>& right)
{
    return (left.left == right.left) && (left.width == right.width) &&
           (left.top == right.top) && (left.height == right.height);
}		/* -----  end of function template <typename T>  ----- */
/* 
 * ===  FUNCTION  ====================================================
 *         Name:  template <typename T>
 *  Description:  
 * ===================================================================
 */
template <typename T>
inline bool operator != (const Rect<T>& left, const Rect<T>& right)
{
    return !(left == right);
}		/* -----  end of function template <typename T>  ----- */


/////////////////////////////////////////////////////////
//
//
////////////////////////////////////////////////////////
/* 
 * ===  FUNCTION  ====================================================
 *         Name:  template <typename T>
 *  Description:  
 * ===================================================================
 */
template <typename T> 
constexpr Vector2<T>::Vector2 () :
    x (0),
    y (0)
{

}		/* -----  end of function template <typename T>  ----- */
/* 
 * ===  FUNCTION  ====================================================
 *         Name:  template <typename T>
 *  Description:  
 * ===================================================================
 */
template <typename T>
constexpr Vector2<T>::Vector2 (T X, T Y):
    x (X),
    y (Y)
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
constexpr Vector2<T>::Vector2 (const Vector2<U> & vector) :
    x (static_cast<T>(vector.x)),
    y (static_cast<T>(vector.y))
{

}		/* -----  end of function template <typename T>  ----- */
/* 
 * ===  FUNCTION  ====================================================
 *         Name:  template <typename T>
 *  Description:  
 * ===================================================================
 */
template <typename T>
constexpr Vector2<T>& operator -(const Vector2<T>& right)
{
    return Vector2<T>(-right.x, -right.y);
}		/* -----  end of function template <typename T>  ----- */
/* 
 * ===  FUNCTION  ====================================================
 *         Name:  template <typename T>
 *  Description:  
 * ===================================================================
 */
template <typename T>
constexpr Vector2<T>& operator +=(Vector2<T>& left, const Vector2<T>& right)
{
    left.x += right.x;  left.y += right.y;
    return left;
}		/* -----  end of function template <typename T>  ----- */
/* 
 * ===  FUNCTION  ====================================================
 *         Name:  template <typename T>
 *  Description:  
 * ===================================================================
 */
template <typename T>
constexpr Vector2<T>& operator -=(Vector2<T>& left, const Vector2<T>& right)
{   left.x -= right.x; 
    left.y -= right.y;
    return left;
}		/* -----  end of function template <typename T>  ----- */
/* 
 * ===  FUNCTION  ====================================================
 *         Name:  template <typename T>
 *  Description:  
 * ===================================================================
 */
template <typename T>
constexpr Vector2<T> operator +(const Vector2<T>& left, const Vector2<T>& right)
{
    return Vector2<T>(left.x + right.x, left.y + right.y);
}		/* -----  end of function template <typename T>  ----- */
/* 
 * ===  FUNCTION  ====================================================
 *         Name:  template <typename T>
 *  Description:  
 * ===================================================================
 */
template <typename T>
constexpr Vector2<T> operator -(const Vector2<T>& left, const Vector2<T>& right)
{
    return Vector2<T>(left.x - right.x, left.y - right.y);
}		/* -----  end of function template <typename T>  ----- */
/* 
 * ===  FUNCTION  ====================================================
 *         Name:  template <typename T>
 *  Description:  
 * ===================================================================
 */
template <typename T>
constexpr Vector2<T> operator *(const Vector2<T>& left, T right)
{
    return Vector2<T>(left.x * right, left.y * right);
}		/* -----  end of function template <typename T>  ----- */
/* 
 * ===  FUNCTION  ====================================================
 *         Name:  template <typename T>
 *  Description:  
 * ===================================================================
 */
template <typename T>
constexpr Vector2<T> operator *(T left, const Vector2<T>& right)
{
    return Vector2<T>(right.x * left, right.y * left);
}		/* -----  end of function template <typename T>  ----- */
/* 
 * ===  FUNCTION  ====================================================
 *         Name:  template <typename T>
 *  Description:  
 * ===================================================================
 */
template <typename T>
constexpr Vector2<T>& operator *=(Vector2<T>& left, T right)
{   left.x *= right; left.y *= right;
    return left;
}		/* -----  end of function template <typename T>  ----- */
/* 
 * ===  FUNCTION  ====================================================
 *         Name:  template <typename T>
 *  Description:  
 * ===================================================================
 */
template <typename T>
constexpr Vector2<T> operator /(const Vector2<T>& left, T right)
{
    return Vector2<T> (left.x / right, left.y / right);
}		/* -----  end of function template <typename T>  ----- */
/* 
 * ===  FUNCTION  ====================================================
 *         Name:  template <typename T>
 *  Description:  
 * ===================================================================
 */
template <typename T>
constexpr Vector2<T>& operator /=(Vector2<T>& left, T right)
{   left.x /= right; left.y /= right;
    return left;
}		/* -----  end of function template <typename T>  ----- */
/* 
 * ===  FUNCTION  ====================================================
 *         Name:  template <typename T>
 *  Description:  
 * ===================================================================
 */
template <typename T>
constexpr bool operator ==(const Vector2<T>& left, const Vector2<T>& right)
{
    return (left.x == right.x) && (left.y == right.y);
}		/* -----  end of function template <typename T>  ----- */
/* 
 * ===  FUNCTION  ====================================================
 *         Name:  template <typename T>
 *  Description:  
 * ===================================================================
 */
template <typename T>
constexpr bool operator !=(const Vector2<T>& left, const Vector2<T>& right)
{
    return (left.y != right.x) || (left.y != right.y);
}		/* -----  end of function template <typename T>  ----- */


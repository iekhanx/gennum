/*
 * ==========================================================================
 *
 *       Filename:  Color.inl
 *
 *    Description:  Color inl 
 *
 *        Version:  1.0
 *        Created:  14/02/22 23:48:37
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  © Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
////////////////////////////////////////////////////////////
constexpr Color::Color() :
r(0),
g(0),
b(0),
a(255)
{

}


////////////////////////////////////////////////////////////
constexpr Color::Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) :
r(red),
g(green),
b(blue),
a(alpha)
{

}


////////////////////////////////////////////////////////////
constexpr Color::Color(uint32_t color) :
r(static_cast<uint8_t>((color & 0xff000000) >> 24)),
g(static_cast<uint8_t>((color & 0x00ff0000) >> 16)),
b(static_cast<uint8_t>((color & 0x0000ff00) >> 8)),
a(static_cast<uint8_t>(color & 0x000000ff))
{

}


////////////////////////////////////////////////////////////
constexpr uint32_t Color::toInteger() const
{
    return static_cast<uint32_t>((r << 24) | (g << 16) | (b << 8) | a);
}


////////////////////////////////////////////////////////////
constexpr bool operator ==(const Color& left, const Color& right)
{
    return (left.r == right.r) &&
           (left.g == right.g) &&
           (left.b == right.b) &&
           (left.a == right.a);
}


////////////////////////////////////////////////////////////
constexpr bool operator !=(const Color& left, const Color& right)
{
    return !(left == right);
}


////////////////////////////////////////////////////////////
constexpr Color operator +(const Color& left, const Color& right)
{
    const auto clampedAdd = [](uint8_t lhs, uint8_t rhs) -> uint8_t
    {
        const int intResult = static_cast<int>(lhs) + static_cast<int>(rhs);
        return static_cast<uint8_t>(intResult < 255 ? intResult : 255);
    };

    return Color(clampedAdd(left.r, right.r),
                 clampedAdd(left.g, right.g),
                 clampedAdd(left.b, right.b),
                 clampedAdd(left.a, right.a));
}


////////////////////////////////////////////////////////////
constexpr Color operator -(const Color& left, const Color& right)
{
    const auto clampedSub = [](uint8_t lhs, uint8_t rhs) -> uint8_t
    {
        const int intResult = static_cast<int>(lhs) - static_cast<int>(rhs);
        return static_cast<uint8_t>(intResult > 0 ? intResult : 0);
    };

    return Color(clampedSub(left.r, right.r),
                 clampedSub(left.g, right.g),
                 clampedSub(left.b, right.b),
                 clampedSub(left.a, right.a));
}


////////////////////////////////////////////////////////////
constexpr Color operator *(const Color& left, const Color& right)
{
    const auto scaledMul = [](uint8_t lhs, uint8_t rhs) -> uint8_t
    {
        const auto uint16Result = 
                    static_cast<uint16_t>(static_cast<uint16_t>(lhs) * 
                    static_cast<uint16_t>(rhs));
        return static_cast<uint8_t>(uint16Result / 255u);
    };

    return Color(scaledMul(left.r, right.r),
                 scaledMul(left.g, right.g),
                 scaledMul(left.b, right.b),
                 scaledMul(left.a, right.a));
}


////////////////////////////////////////////////////////////
constexpr Color& operator +=(Color& left, const Color& right)
{
    return left = left + right;
}


////////////////////////////////////////////////////////////
constexpr Color& operator -=(Color& left, const Color& right)
{
    return left = left - right;
}


////////////////////////////////////////////////////////////
constexpr Color& operator *=(Color& left, const Color& right)
{
    return left = left * right;
}
////////////////////////////////////////////////////////////


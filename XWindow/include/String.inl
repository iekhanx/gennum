/*
 * ==========================================================================
 *
 *       Filename:  String.inl
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  27/01/22 12:29:07
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
////////////////////////////////////////////////////////////
template <typename T>
String String::fromUtf8(T begin, T end)
{
    String string;
    Utf8::toUtf32(begin, end, std::back_inserter(string.m_string));
    return string;
}


////////////////////////////////////////////////////////////
template <typename T>
String String::fromUtf16(T begin, T end)
{
    String string;
    Utf16::toUtf32(begin, end, std::back_inserter(string.m_string));
    return string;
}


////////////////////////////////////////////////////////////
template <typename T>
String String::fromUtf32(T begin, T end)
{
    String string;
    string.m_string.assign(begin, end);
    return string;
}

/*
 * ========================================================================
 *
 *       Filename:  Keyboard.cpp
 *
 *    Description:  Class keyboard implementation 
 *
 *        Version:  1.0
 *        Created:  27/01/22 09:56:37
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * =========================================================================
 */
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Keyboard.hpp"
#include "InputImpl.hpp"


namespace xwc
{
////////////////////////////////////////////////////////////
bool Keyboard::isKeyPressed(Key key)
{
    return priv::InputImpl::isKeyPressed(key);
}


////////////////////////////////////////////////////////////
void Keyboard::setVirtualKeyboardVisible(bool visible)
{
    priv::InputImpl::setVirtualKeyboardVisible(visible);
}

} // namespace xwc


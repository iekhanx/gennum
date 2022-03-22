/*
 * ==========================================================================
 *
 *       Filename:  Sleep.hpp
 *
 *    Description:  Sleep class declaration 
 *
 *        Version:  1.0
 *        Created:  03/02/22 15:48:02
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
#ifndef _SLEEPIMPLUNIX_HPP
#define _SLEEPIMPLUNIX_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
//#include <SFML/Config.hpp>
#include "Time.hpp"


namespace xwc::priv
{
////////////////////////////////////////////////////////////
/// \brief Unix implementation of xwc::Sleep
///
/// \param time Time to sleep
///
////////////////////////////////////////////////////////////
void sleepImpl(Time time);

} // namespace xwc::priv


#endif // _SLEEPIMPLUNIX_HPP

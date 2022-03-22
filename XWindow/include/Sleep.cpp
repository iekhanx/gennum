/*
 * ========================================================================
 *
 *       Filename:  Sleep.cpp
 *
 *    Description:  Sleep class implementation 
 *
 *        Version:  1.0
 *        Created:  03/02/22 15:49:33
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
#include "SleepImpl.hpp"
#include <cerrno>
#include <ctime>
#include <cstdint>

namespace xwc::priv
{
////////////////////////////////////////////////////////////
void sleepImpl(Time time)
{
    const int64_t usecs = time.asMicroseconds();

    // Construct the time to wait
    timespec ti;
    ti.tv_sec = static_cast<time_t>(usecs / 1000000);
    ti.tv_nsec = static_cast<long>((usecs % 1000000) * 1000);

    // Wait...
    // If nanosleep returns -1, we check errno. If it is EINTR
    // nanosleep was interrupted and has set ti to the remaining
    // duration. We continue sleeping until the complete duration
    // has passed. We stop sleeping if it was due to an error.
    while ((nanosleep(&ti, &ti) == -1) && (errno == EINTR))
    {
    }
}

} // namespace xwc::priv


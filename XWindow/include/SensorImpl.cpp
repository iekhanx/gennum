/*
 * ========================================================================
 *
 *       Filename:  SensorImpl.cpp
 *
 *    Description:  SensorImpl class implementation 
 *
 *        Version:  1.0
 *        Created:  31/01/22 02:22:51
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
#include "SensorImpl.hpp"


namespace xwc
{
namespace priv
{
////////////////////////////////////////////////////////////
void SensorImpl::initialize()
{
    // To be implemented
}


////////////////////////////////////////////////////////////
void SensorImpl::cleanup()
{
    // To be implemented
}


////////////////////////////////////////////////////////////
bool SensorImpl::isAvailable(Sensor::Type /*sensor*/)
{
    // To be implemented
    return false;
}


////////////////////////////////////////////////////////////
bool SensorImpl::open(Sensor::Type /*sensor*/)
{
    // To be implemented
    return false;
}


////////////////////////////////////////////////////////////
void SensorImpl::close()
{
    // To be implemented
}


////////////////////////////////////////////////////////////
Vector3f SensorImpl::update()
{
    // To be implemented
    return Vector3f(0, 0, 0);
}


////////////////////////////////////////////////////////////
void SensorImpl::setEnabled(bool /*enabled*/)
{
    // To be implemented
}

} // namespace priv

} // namespace xwc


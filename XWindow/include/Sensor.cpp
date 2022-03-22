/*
 * ========================================================================
 *
 *       Filename:  Sensor.cpp
 *
 *    Description:  Sensor class implementation 
 *
 *        Version:  1.0
 *        Created:  27/01/22 11:39:06
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
#include "Sensor.hpp"
#include "SensorManager.hpp"


namespace xwc
{

////////////////////////////////////////////////////////////
bool Sensor::isAvailable(Type sensor)
{
    return priv::SensorManager::getInstance().isAvailable(sensor);
}

////////////////////////////////////////////////////////////
void Sensor::setEnabled(Type sensor, bool enabled)
{
    return priv::SensorManager::getInstance().setEnabled(sensor, enabled);
}

////////////////////////////////////////////////////////////
Vector3f Sensor::getValue(Type sensor)
{
    return priv::SensorManager::getInstance().getValue(sensor);
}

} // namespace xwc


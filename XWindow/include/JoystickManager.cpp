/*
 * ========================================================================
 *
 *       Filename:  JoystickManager.cpp
 *
 *    Description:  Joystick Manager class implementation 
 *
 *        Version:  1.0
 *        Created:  27/01/22 11:31:32
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
#include "JoystickManager.hpp"


namespace xwc
{
namespace priv
{
////////////////////////////////////////////////////////////
JoystickManager& JoystickManager::getInstance()
{
    static JoystickManager instance;
    return instance;
}


////////////////////////////////////////////////////////////
const JoystickCaps& JoystickManager::getCapabilities(unsigned int joystick) const
{
    return m_joysticks[joystick].capabilities;
}


////////////////////////////////////////////////////////////
const JoystickState& JoystickManager::getState(unsigned int joystick) const
{
    return m_joysticks[joystick].state;
}


////////////////////////////////////////////////////////////
const Joystick::Identification& JoystickManager::getIdentification(unsigned int joystick) const
{
    return m_joysticks[joystick].identification;
}


////////////////////////////////////////////////////////////
void JoystickManager::update()
{
    for (unsigned int i = 0; i < Joystick::Count; ++i)
    {
        Item& item = m_joysticks[i];

        if (item.state.connected)
        {
            // Get the current state of the joystick
            item.state = item.joystick.update();

            // Check if it's still connected
            if (!item.state.connected)
            {
                item.joystick.close();
                item.capabilities   = JoystickCaps();
                item.state          = JoystickState();
                item.identification = Joystick::Identification();
            }
        }
        else
        {
            // Check if the joystick was connected since last update
            if (JoystickImpl::isConnected(i))
            {
                if (item.joystick.open(i))
                {
                    item.capabilities   = item.joystick.getCapabilities();
                    item.state          = item.joystick.update();
                    item.identification = item.joystick.getIdentification();
                }
            }
        }
    }
}


////////////////////////////////////////////////////////////
JoystickManager::JoystickManager()
{
    JoystickImpl::initialize();
}


////////////////////////////////////////////////////////////
JoystickManager::~JoystickManager()
{
    for (Item& item : m_joysticks)
    {
        if (item.state.connected)
            item.joystick.close();
    }

    JoystickImpl::cleanup();
}

} // namespace priv

} // namespace xwc


/*
 * ==========================================================================
 *
 *       Filename:  JoystickImpl.hpp
 *
 *    Description:  JoystickImpl class declaration 
 *
 *        Version:  1.0
 *        Created:  29/01/22 01:42:30
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
#ifndef _JOYSTICKIMPLLINUX_HPP
#define _JOYSTICKIMPLLINUX_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <linux/input.h>


namespace xwc
{
namespace priv
{
////////////////////////////////////////////////////////////
/// \brief Structure holding a joystick's information
///
////////////////////////////////////////////////////////////
struct JoystickCaps
{
    unsigned int buttonCount{0};              //!< Number of buttons supported by the joystick
    bool         axes[Joystick::AxisCount]{}; //!< Support for each axis
};


////////////////////////////////////////////////////////////
/// \brief Structure holding a joystick's state
///
////////////////////////////////////////////////////////////
struct JoystickState
{
    bool  connected{false};                 //!< Is the joystick currently connected?
    float axes[Joystick::AxisCount]{};      //!< Position of each axis, in range [-100, 100]
    bool  buttons[Joystick::ButtonCount]{}; //!< Status of each button (true = pressed)
};

////////////////////////////////////////////////////////////
/// \brief Linux implementation of joysticks
///
////////////////////////////////////////////////////////////
class JoystickImpl
{
public:

    ////////////////////////////////////////////////////////////
    /// \brief Constructor
    ///
    ////////////////////////////////////////////////////////////
    JoystickImpl();

    ////////////////////////////////////////////////////////////
    /// \brief Perform the global initialization of the joystick module
    ///
    ////////////////////////////////////////////////////////////
    static void initialize();

    ////////////////////////////////////////////////////////////
    /// \brief Perform the global cleanup of the joystick module
    ///
    ////////////////////////////////////////////////////////////
    static void cleanup();

    ////////////////////////////////////////////////////////////
    /// \brief Check if a joystick is currently connected
    ///
    /// \param index Index of the joystick to check
    ///
    /// \return True if the joystick is connected, false otherwise
    ///
    ////////////////////////////////////////////////////////////
    static bool isConnected(unsigned int index);

    ////////////////////////////////////////////////////////////
    /// \brief Open the joystick
    ///
    /// \param index Index assigned to the joystick
    ///
    /// \return True on success, false on failure
    ///
    ////////////////////////////////////////////////////////////
    bool open(unsigned int index);

    ////////////////////////////////////////////////////////////
    /// \brief Close the joystick
    ///
    ////////////////////////////////////////////////////////////
    void close();

    ////////////////////////////////////////////////////////////
    /// \brief Get the joystick capabilities
    ///
    /// \return Joystick capabilities
    ///
    ////////////////////////////////////////////////////////////
    JoystickCaps getCapabilities() const;

    ////////////////////////////////////////////////////////////
    /// \brief Get the joystick identification
    ///
    /// \return Joystick identification
    ///
    ////////////////////////////////////////////////////////////
    Joystick::Identification getIdentification() const;

    ////////////////////////////////////////////////////////////
    /// \brief Update the joystick and get its new state
    ///
    /// \return Joystick state
    ///
    ////////////////////////////////////////////////////////////
    JoystickState update();

private:

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    int                          m_file;   ///< File descriptor of the joystick
    char                         m_mapping[ABS_MAX + 1]; ///< Axes mapping 
    JoystickState                m_state; ///< Current state of the joystick
    xwc::Joystick::Identification m_identification;  ///< Identificationjoystick
};

} // namespace priv

} // namespace xwc


#endif // L_JOYSTICKIMPLLINUX_HPP

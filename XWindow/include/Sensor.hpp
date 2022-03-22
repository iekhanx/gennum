/*
 * ==========================================================================
 *
 *       Filename:  Sensor.hpp
 *
 *    Description:  Sensor class declaration 
 *
 *        Version:  1.0
 *        Created:  27/01/22 11:35:40
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
#ifndef _SENSOR_HPP
#define _SENSOR_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
 
#include "Vector3.hpp"
#include "Time.hpp"


namespace xwc
{
////////////////////////////////////////////////////////////
/// \brief Give access to the real-time state of the sensors
///
////////////////////////////////////////////////////////////
class Sensor
{
public:

    ////////////////////////////////////////////////////////////
    /// \brief Sensor type
    ///
    ////////////////////////////////////////////////////////////
    enum Type
    {
        Accelerometer,    //!< Measures the raw acceleration (m/s^2)
        Gyroscope,        //!< Measures the raw rotation rates (degrees/s)
        Magnetometer,     //!< Measures the ambient magnetic field (micro-teslas)
        Gravity,          //!< Measures the direction and intensity of gravity,
                          //!< independent of device acceleration (m/s^2)
        UserAcceleration, //!< Measures the direction and intensity of device 
                          //!< acceleration, independent of the gravity (m/s^2)
        Orientation,      //!< Measures the absolute 3D orientation (degrees)

        Count             //!< Keep last -- the total number of sensor types
    };

    ////////////////////////////////////////////////////////////
    /// \brief Check if a sensor is available on the underlying platform
    ///
    /// \param sensor Sensor to check
    ///
    /// \return True if the sensor is available, false otherwise
    ///
    ////////////////////////////////////////////////////////////
    static bool isAvailable(Type sensor);

    ////////////////////////////////////////////////////////////
    /// \brief Enable or disable a sensor
    ///
    /// All sensors are disabled by default, to avoid consuming too
    /// much battery power. Once a sensor is enabled, it starts
    /// sending events of the corresponding type.
    ///
    /// This function does nothing if the sensor is unavailable.
    ///
    /// \param sensor  Sensor to enable
    /// \param enabled True to enable, false to disable
    ///
    ////////////////////////////////////////////////////////////
    static void setEnabled(Type sensor, bool enabled);

    ////////////////////////////////////////////////////////////
    /// \brief Get the current sensor value
    ///
    /// \param sensor Sensor to read
    ///
    /// \return The current sensor value
    ///
    ////////////////////////////////////////////////////////////
    static Vector3f getValue(Type sensor);
};

} // namespace xwc


#endif // SFML_SENSOR_HPP


////////////////////////////////////////////////////////////
/// \class xwc::Sensor
/// \ingroup window
///
/// xwc::Sensor provides an interface to the state of the
/// various sensors that a device provides. It only contains static
/// functions, so it's not meant to be instantiated.
///
/// This class allows users to query the sensors values at any
/// time and directly, without having to deal with a window and
/// its events. Compared to the SensorChanged event, xwc::Sensor
/// can retrieve the state of a sensor at any time (you don't need to
/// store and update its current value on your side).
///
/// Depending on the OS and hardware of the device (phone, tablet, ...),
/// some sensor types may not be available. You should always check
/// the availability of a sensor before trying to read it, with the
/// xwc::Sensor::isAvailable function.
///
/// You may wonder why some sensor types look so similar, for example
/// Accelerometer and Gravity / UserAcceleration. The first one
/// is the raw measurement of the acceleration, and takes into account
/// both the earth gravity and the user movement. The others are
/// more precise: they provide these components separately, which is
/// usually more useful. In fact they are not direct sensors, they
/// are computed internally based on the raw acceleration and other sensors.
/// This is exactly the same for Gyroscope vs Orientation.
///
/// Because sensors consume a non-negligible amount of current, they are
/// all disabled by default. You must call xwc::Sensor::setEnabled for each
/// sensor in which you are interested.
///
/// Usage example:
/// \code
/// if (xwc::Sensor::isAvailable(xwc::Sensor::Gravity))
/// {
///     // gravity sensor is available
/// }
///
/// // enable the gravity sensor
/// xwc::Sensor::setEnabled(xwc::Sensor::Gravity, true);
///
/// // get the current value of gravity
/// xwc::Vector3f gravity = xwc::Sensor::getValue(xwc::Sensor::Gravity);
/// \endcode
///
////////////////////////////////////////////////////////////

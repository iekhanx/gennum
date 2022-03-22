/*
 * ==========================================================================
 *
 *       Filename:  SensorManager.hpp
 *
 *    Description:  SensorManager class declaration 
 *
 *        Version:  1.0
 *        Created:  27/01/22 11:41:35
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
#ifndef _SENSORMANAGER_HPP
#define _SENSORMANAGER_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Sensor.hpp"
#include "SensorImpl.hpp"
//#include "NonCopyable.hpp"


namespace xwc
{
namespace priv
{
////////////////////////////////////////////////////////////
/// \brief Global sensor manager
///
////////////////////////////////////////////////////////////
class SensorManager //: NonCopyable
{
public:

    ////////////////////////////////////////////////////////////
    /// \brief Get the global unique instance of the manager
    ///
    /// \return Unique instance of the sensor manager
    ///
    ////////////////////////////////////////////////////////////
    static SensorManager& getInstance();

    ////////////////////////////////////////////////////////////
    /// \brief Check if a sensor is available on the underlying platform
    ///
    /// \param sensor Sensor to check
    ///
    /// \return True if the sensor is available, false otherwise
    ///
    ////////////////////////////////////////////////////////////
    bool isAvailable(Sensor::Type sensor);

    ////////////////////////////////////////////////////////////
    /// \brief Enable or disable a sensor
    ///
    /// \param sensor  Sensor to modify
    /// \param enabled Whether it should be enabled or not
    ///
    ////////////////////////////////////////////////////////////
    void setEnabled(Sensor::Type sensor, bool enabled);

    ////////////////////////////////////////////////////////////
    /// \brief Check if a sensor is enabled
    ///
    /// \param sensor Sensor to check
    ///
    /// \return True if the sensor is enabled, false otherwise
    ///
    ////////////////////////////////////////////////////////////
    bool isEnabled(Sensor::Type sensor) const;

    ////////////////////////////////////////////////////////////
    /// \brief Get the current value of a sensor
    ///
    /// \param sensor Sensor to read
    ///
    /// \return Current value of the sensor
    ///
    ////////////////////////////////////////////////////////////
    Vector3f getValue(Sensor::Type sensor) const;

    ////////////////////////////////////////////////////////////
    /// \brief Update the state of all the sensors
    ///
    ////////////////////////////////////////////////////////////
    void update();

private:

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    ////////////////////////////////////////////////////////////
    SensorManager();

    ////////////////////////////////////////////////////////////
    /// \brief Destructor
    ///
    ////////////////////////////////////////////////////////////
    ~SensorManager();

    ////////////////////////////////////////////////////////////
    /// \brief Sensor information and state
    ///
    ////////////////////////////////////////////////////////////
    struct Item
    {
        bool available;    //!< Is the sensor available on this device?
        bool enabled;      //!< Current enable state of the sensor
        SensorImpl sensor; //!< Sensor implementation
        Vector3f value;    //!< The current sensor value
    };

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    Item m_sensors[Sensor::Count]; //!< Sensors information and state
};

} // namespace priv

} // namespace xwc


#endif // SFML_SENSORMANAGER_HPP

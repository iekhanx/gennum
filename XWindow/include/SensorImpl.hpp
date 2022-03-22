/*
 * ==========================================================================
 *
 *       Filename:  SensorImpl.hpp
 *
 *    Description:  Sensorimpl class declaration 
 *
 *        Version:  1.0
 *        Created:  31/01/22 02:21:36
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
#ifndef _SENSORIMPLUNIX_HPP
#define _SENSORIMPLUNIX_HPP


namespace xwc
{
namespace priv
{
////////////////////////////////////////////////////////////
/// \brief Unix implementation of sensors
///
////////////////////////////////////////////////////////////
class SensorImpl
{
public:

    ////////////////////////////////////////////////////////////
    /// \brief Perform the global initialization of the sensor module
    ///
    ////////////////////////////////////////////////////////////
    static void initialize();

    ////////////////////////////////////////////////////////////
    /// \brief Perform the global cleanup of the sensor module
    ///
    ////////////////////////////////////////////////////////////
    static void cleanup();

    ////////////////////////////////////////////////////////////
    /// \brief Check if a sensor is available
    ///
    /// \param sensor Sensor to check
    ///
    /// \return True if the sensor is available, false otherwise
    ///
    ////////////////////////////////////////////////////////////
    static bool isAvailable(Sensor::Type sensor);

    ////////////////////////////////////////////////////////////
    /// \brief Open the sensor
    ///
    /// \param sensor Type of the sensor
    ///
    /// \return True on success, false on failure
    ///
    ////////////////////////////////////////////////////////////
    bool open(Sensor::Type sensor);

    ////////////////////////////////////////////////////////////
    /// \brief Close the sensor
    ///
    ////////////////////////////////////////////////////////////
    void close();

    ////////////////////////////////////////////////////////////
    /// \brief Update the sensor and get its new value
    ///
    /// \return Sensor value
    ///
    ////////////////////////////////////////////////////////////
    Vector3f update();

    ////////////////////////////////////////////////////////////
    /// \brief Enable or disable the sensor
    ///
    /// \param enabled True to enable, false to disable
    ///
    ////////////////////////////////////////////////////////////
    void setEnabled(bool enabled);
};

} // namespace priv

} // namespace xwc


#endif // _SENSORIMPLUNIX_HPP

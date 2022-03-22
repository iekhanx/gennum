/*
 * ========================================================================
 *
 *       Filename:  Display.hpp
 *
 *    Description:  Class Display declaration  
 *
 *        Version:  1.0
 *        Created:  07/01/22 14:36:26
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * =========================================================================
 */
#ifndef _DISPLAY_HPP_
#define _DISPLAY_HPP_
//////////////////////////////////////////////
// Headers
/////////////////////////////////////////////
#include <X11/Xlib.h>
#include <string>


namespace xwc
{
namespace priv
{
////////////////////////////////////////////////////////////
/// \brief Get the shared Display
///
/// This function increments the reference count of the display,
/// it must be matched with a call to CloseDisplay.
///
/// \return Pointer to the shared display
///
////////////////////////////////////////////////////////////
Display* OpenDisplay();

////////////////////////////////////////////////////////////
/// \brief Release a reference to the shared display
///
/// \param display Display to release
///
////////////////////////////////////////////////////////////
void CloseDisplay(Display* display);

////////////////////////////////////////////////////////////
/// \brief Get the shared XIM context for the Display
///
/// This function increments the reference count of the XIM context,
/// it must be matched with a call to CloseXIM.
///
/// It must be called with a display already opened.
///
/// \return XIM handle (a pointer) of the context
///
////////////////////////////////////////////////////////////
XIM OpenXIM();

////////////////////////////////////////////////////////////
/// \brief Release a reference to the shared XIM context
///
/// \param xim XIM context to release
///
////////////////////////////////////////////////////////////
void CloseXIM(XIM xim);

////////////////////////////////////////////////////////////
/// \brief Get the atom with the specified name
///
/// \param name         Name of the atom
/// \param onlyIfExists Don't try to create the atom if it doesn't already exist
///
/// \return Atom if it exists or None (0) if it doesn't
///
////////////////////////////////////////////////////////////
Atom getAtom(const std::string& name, bool onlyIfExists = false);

} // namespace priv

} // namespace xwc

#endif    // _DISPLAY_HPP_

/*
 * ==========================================================================
 *
 *       Filename:  Err.cpp
 *
 *    Description:  Error display class 
 *
 *        Version:  1.0
 *        Created:  07/01/22 15:36:00
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
#ifndef _ERR_HPP_
#define _ERR_HPP_

////////////////////////////////////////////
// Headers
///////////////////////////////////////////
#include <ostream>

namespace xwc
{
    ///////////////////
    // \brief Std strea, used to oupt warnings, error
    ///////////////////
    std::ostream& err ();
}
#endif  /* ------------ Eof Err.hpp ----------*/

///////////////////////////////////////////////////////////
/// \fn xwc::err
/// \ingroup system
///
/// By default, xwc::err() outputs to the same location as std::cerr,
/// (-> the stderr descriptor) which is the console if there's
/// one available.
///
/// It is a standard std::ostream instance, so it supports all the
/// insertion operations defined by the STL
/// (operator <<, manipulators, etc.).
///
/// xwc::err() can be redirected to write to another output, independently
/// of std::cerr, by using the rdbuf() function provided by the
/// std::ostream class.
///
/// Example:
/// \code
/// // Redirect to a file
/// std::ofstream file("xwcml-log.txt");
/// std::streambuf* previous = xwc::err().rdbuf(file.rdbuf());
///
/// // Redirect to nothing
/// xwc::err().rdbuf(nullptr);
///
/// // Restore the original output
/// xwc::err().rdbuf(previous);
/// \endcode
///
/// \return Reference to std::ostream representing the SFML error stream
///
////////////////////////////////////////////////////////////



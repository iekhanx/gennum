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
#include "Err.hpp"
#include <iostream>
#include <streambuf>
#include <cstdio>

namespace
{
    class DefaultErrStreamBuf : public std::streambuf
    {
     public:
        DefaultErrStreamBuf ()
        {
            // Allocate write buffer
            static const int size = 64;
            char *buffer = new char [size];
            setp (buffer, buffer + size);
        }

        ~DefaultErrStreamBuf () override
        {
            // Synchronise
            sync ();

            // Delete the write buffer
            delete [] pbase ();
        }

        private:
            int overflow (int character) override
            {
                if ((character != EOF) && (pptr() != epptr()))
                {
                    return sputc (static_cast<char>(character)); //valid char
                }
                else if (character != EOF)
                {   // Not enough space in the buffer: sync output and try
                    sync ();
                    return overflow (character);
                }
                else {  // invalid character synchronise output
                    return sync ();
                }
            }
            int sync () override
            {
                if (pbase () != pptr())  // check the contents of write buffer
                {   // print the contents of write buffer in output
                    auto size = static_cast<std::size_t> (pptr() - pbase());
                    fwrite (pbase (), 1, size, stderr);

                    // Reset the pointer pos to beginning of write buffer
                    setp (pbase (), epptr());
                }
                return 0;
            }
    };
}

#endif  /* ------------ Eof Err.cpp ----------*/

namespace xwc
{
////////////////////////////////////////
    std::ostream& err ()
    {
        static DefaultErrStreamBuf buffer;
        static std::ostream stream(&buffer);

        return stream;
    }
}   // end of namespace xwc


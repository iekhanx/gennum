/*
 * ========================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  Main entry point program for image class test 
 *
 *        Version:  1.0
 *        Created:  14/02/22 21:18:26
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  © Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * =========================================================================
 */
////////////////////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "Image.hpp"

int main (int argc, char** argv)
{
    xwc::Image icon;
    if (!icon.loadFromFile ("icon.png")) {
        return EXIT_FAILURE;
    } else {
        std::cout << "Image loaded successfully" << std::endl;
    }
    return EXIT_SUCCESS;
}



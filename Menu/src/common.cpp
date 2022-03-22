/*
 * ========================================================================
 *
 *       Filename:  common.cpp
 *
 *    Description: Common class implmentation 
 *
 *        Version:  1.0
 *        Created:  07/03/22 18:28:52
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  © Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * =========================================================================
 */
/////////////////////////////////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////////////////////////////////
#include "common.hpp"

/////////////////////////////////////////////////////////////////////////////
XrmDatabase common::setupDB (Display* dpy, XrmOptionDescRec *xrmTable,
                     int nCommandLineResource, const char *progname,
                     int *argc, char **argv)
{
    XrmDatabase db;
    std::string filename;

    // Initialise xrm database
    XrmInitialise ();
    db = XrmGetDatabase (dpy);

    XrmParseCommand (&db, xrmTable, nCommandLineResources, progname,
                     argc, argv);
    sprintf (filename.append(), "%.240s.resources", progname);
    if (XrmCombineFileDatabase (filename.c_str(), &db, False)) {
        std::cout << "Reading setting from file "<< filename.c_str() <<
        std::endl;
    } else {
        std::cout << "File NOT found "<< filename.c_str() << " for reading" <<
        std::endl;
    }
    return db;
}

string common::getResource (XrmDatabase db,const std::string name,  
                            const std::string tmp, char *def)
{

}

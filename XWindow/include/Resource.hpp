/*
 * ==========================================================================
 *
 *       Filename:  Resource.hpp
 *
 *    Description:  Resource class declaretion 
 *
 *        Version:  1.0
 *        Created:  18/01/22 17:00:29
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
#ifndef _RESOURCE_HPP_
#define _RESOURCE_HPP_

///////////////////////
// Headers
///////////////////////

namespace xwc
{
    class Resource
    {
        protected:

            ///////////////////////
            // \brief Default constructor
            //////////////////////
            Resource ();

            /////////////////
            // \brief Destructor
            /////////////////
            ~Resource ();

            ///////////////////
            // \brief Register a function to be called when content destroyed
            // \param callback function to be called 
            // \param arg  Argument to pass when calling 
            /////////////////
            static void registerContextDestroyCallback (ContextDestroyCallback
                                                        callback, void* arg);
            
            //////////////////
            // \brief RAII help class to temporarity lock an availabled context
            ///////////////////
            class TransientContextLock 
            {
                public:
                    ///////////////////////
                    // \brief Default constructor
                    ///////////////////////
                    TransientContextLock ();

                    //////////////////
                    // \brief Destructor
                    //////////////////
                    ~TransientContextLock ();
            };  // end of class TransientContextLock
    }; // end of class Resource
} // end of namespace xwc
#endif
/* ------------------ Eof Resource.hpp -----------------------*/
////////////////////////////////////////////////////////////
/// \class xwc::Resource
/// \ingroup window
///
/// This class is for internal use only, it must be the base
/// of every class that requires a valid OpenGL context in
/// order to work.
///
////////////////////////////////////////////////////////////

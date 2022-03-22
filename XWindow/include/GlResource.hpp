/*
 * ==========================================================================
 *
 *       Filename:  GlResource.hpp
 *
 *    Description:  GlResource class declaration 
 *
 *        Version:  1.0
 *        Created:  27/01/22 12:59:54
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
#ifndef _GLRESOURCE_HPP
#define _GLRESOURCE_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
// #include "Export.hpp"
// #include "NonCopyable.hpp"


namespace xwc
{

class Context;

using ContextDestroyCallback = void (*)(void *);

////////////////////////////////////////////////////////////
/// \brief Base class for classes that require an OpenGL context
///
////////////////////////////////////////////////////////////
class GlResource
{
protected:

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    ////////////////////////////////////////////////////////////
    GlResource();

    ////////////////////////////////////////////////////////////
    /// \brief Destructor
    ///
    ////////////////////////////////////////////////////////////
    ~GlResource();

    ////////////////////////////////////////////////////////////
    /// \brief Register a function to be called when a context is destroyed
    ///
    /// This is used for internal purposes in order to properly
    /// clean up OpenGL resources that cannot be shared between
    /// contexts.
    ///
    /// \param callback Function to be called when a context is destroyed
    /// \param arg      Argument to pass when calling the function
    ///
    ////////////////////////////////////////////////////////////
    static void registerContextDestroyCallback(ContextDestroyCallback callback,
                                               void* arg);

    ////////////////////////////////////////////////////////////
    /// \brief RAII helper class to temporarily lock an available context for use
    ///
    ////////////////////////////////////////////////////////////
    class TransientContextLock 
    {
    public:
        ////////////////////////////////////////////////////////////
        /// \brief Default constructor
        ///
        ////////////////////////////////////////////////////////////
        TransientContextLock();

        ////////////////////////////////////////////////////////////
        /// \brief Destructor
        ///
        ////////////////////////////////////////////////////////////
        ~TransientContextLock();
    };
};

} // namespace xwc


#endif // _GLRESOURCE_HPP

////////////////////////////////////////////////////////////
/// \class xwc::GlResource
/// \ingroup window
///
/// This class is for internal use only, it must be the base
/// of every class that requires a valid OpenGL context in
/// order to work.
///
////////////////////////////////////////////////////////////

/*
 * ==========================================================================
 *
 *       Filename:  ContextSettings.hpp
 *
 *    Description:  ContextSettings class declaration 
 *
 *        Version:  1.0
 *        Created:  27/01/22 15:44:08
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
#ifndef _CONTEXTSETTINGS_HPP
#define _CONTEXTSETTINGS_HPP

////////////////////////
// Headers
////////////////////////
#include <cstdint>

namespace xwc
{
////////////////////////////////////////////////////////////
/// \brief Structure defining the settings of the OpenGL
///        context attached to a window
///
////////////////////////////////////////////////////////////
struct ContextSettings
{
    ////////////////////////////////////////////////////////////
    /// \brief Enumeration of the context attribute flags
    ///
    ////////////////////////////////////////////////////////////
    enum Attribute
    {
        Default = 0,      //!< Non-debug, compatibility context 
                          //!< (this and the core attribute mutually exclusive)
        Core    = 1 << 0, //!< Core attribute
        Debug   = 1 << 2  //!< Debug attribute
    };

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// \param depth        Depth buffer bits
    /// \param stencil      Stencil buffer bits
    /// \param antialiasing Antialiasing level
    /// \param major        Major number of the context version
    /// \param minor        Minor number of the context version
    /// \param attributes   Attribute flags of the context
    /// \param sRgb         sRGB capable framebuffer
    ///
    ////////////////////////////////////////////////////////////
    explicit ContextSettings(unsigned int depth = 0, unsigned int stencil = 0, 
            unsigned int antialiasing = 0, unsigned int major = 1, 
            unsigned int minor = 1, unsigned int attributes = Default, 
            bool sRgb = false) :
    depthBits        (depth),
    stencilBits      (stencil),
    antialiasingLevel(antialiasing),
    majorVersion     (major),
    minorVersion     (minor),
    attributeFlags   (attributes),
    sRgbCapable      (sRgb)
    {
    }

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    unsigned int depthBits;         //!< Bits of the depth buffer
    unsigned int stencilBits;       //!< Bits of the stencil buffer
    unsigned int antialiasingLevel; //!< Level of antialiasing
    unsigned int majorVersion;      //!< Major number ofcontext version tocreate
    unsigned int minorVersion;      //!< Minor number ofcontext version tocreate
    uint32_t     attributeFlags;    //!< The attribute flagscreate context with
    bool         sRgbCapable;       //!< context framebuffer is sRGB capable
};

} // namespace xwc


#endif // _CONTEXTSETTINGS_HPP


////////////////////////////////////////////////////////////
/// \class xwc::ContextSettings
/// \ingroup window
///
/// ContextSettings allows to define several advanced settings
/// of the OpenGL context attached to a window. All these
/// settings with the exception of the compatibility flag
/// and anti-aliasing level have no impact on the regular
/// SFML rendering (graphics module), so you may need to use
/// this structure only if you're using SFML as a windowing
/// system for custom OpenGL rendering.
///
/// The depthBits and stencilBits members define the number
/// of bits per pixel requested for the (respectively) depth
/// and stencil buffers.
///
/// antialiasingLevel represents the requested number of
/// multisampling levels for anti-aliasing.
///
/// majorVersion and minorVersion define the version of the
/// OpenGL context that you want. Only versions greater or
/// equal to 3.0 are relevant; versions lesser than 3.0 are
/// all handled the same way (i.e. you can use any version
/// < 3.0 if you don't want an OpenGL 3 context).
///
/// When requesting a context with a version greater or equal
/// to 3.2, you have the option of specifying whether the
/// context should follow the core or compatibility profile
/// of all newer (>= 3.2) OpenGL specifications. For versions
/// 3.0 and 3.1 there is only the core profile. By default
/// a compatibility context is created. You only need to specify
/// the core flag if you want a core profile context to use with
/// your own OpenGL rendering.
/// <b>Warning: The graphics module will not function if you
/// request a core profile context. Make sure the attributes are
/// set to Default if you want to use the graphics module.</b>
///
/// Setting the debug attribute flag will request a context with
/// additional debugging features enabled. Depending on the
/// system, this might be required for advanced OpenGL debugging.
/// OpenGL debugging is disabled by default.
///
/// <b>Special Note for OS X:</b>
/// Apple only supports choosing between either a legacy context
/// (OpenGL 2.1) or a core context (OpenGL version depends on the
/// operating system version but is at least 3.2). Compatibility
/// contexts are not supported. Further information is available on the
/// <a href="https://developer.apple.com/opengl/capabilities/index.html">
/// OpenGL Capabilities Tables</a> page. OS X also currently does
/// not support debug contexts.
///
/// Please note that these values are only a hint.
/// No failure will be reported if one or more of these values
/// are not supported by the system; instead, SFML will try to
/// find the closest valid match. You can then retrieve the
/// settings that the window actually used to create its context,
/// with Window::getSettings().
///
////////////////////////////////////////////////////////////

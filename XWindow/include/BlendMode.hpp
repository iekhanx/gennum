/*
 * ==========================================================================
 *
 *       Filename:  BlendMode.hpp
 *
 *    Description:  BlendMode class declaration 
 *
 *        Version:  1.0
 *        Created:  27/01/22 10:45:38
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
#ifndef _BLENDMODE_HPP
#define _BLENDMODE_HPP
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

namespace xwc
{

////////////////////////////////////////////////////////////
/// \brief Blending modes for drawing
///
////////////////////////////////////////////////////////////
struct BlendMode
{
    ////////////////////////////////////////////////////////
    /// \brief Enumeration of the blending factors
    ///
    /// The factors are mapped directly to their OpenGL equivalents,
    /// specified by glBlendFunc() or glBlendFuncSeparate().
    ////////////////////////////////////////////////////////
    enum Factor
    {
        Zero,             //!< (0, 0, 0, 0)
        One,              //!< (1, 1, 1, 1)
        SrcColor,         //!< (src.r, src.g, src.b, src.a)
        OneMinusSrcColor, //!< (1, 1, 1, 1) - (src.r, src.g, src.b, src.a)
        DstColor,         //!< (dst.r, dst.g, dst.b, dst.a)
        OneMinusDstColor, //!< (1, 1, 1, 1) - (dst.r, dst.g, dst.b, dst.a)
        SrcAlpha,         //!< (src.a, src.a, src.a, src.a)
        OneMinusSrcAlpha, //!< (1, 1, 1, 1) - (src.a, src.a, src.a, src.a)
        DstAlpha,         //!< (dst.a, dst.a, dst.a, dst.a)
        OneMinusDstAlpha  //!< (1, 1, 1, 1) - (dst.a, dst.a, dst.a, dst.a)
    };

    ////////////////////////////////////////////////////////
    /// \brief Enumeration of the blending equations
    ///
    /// The equations are mapped directly to their OpenGL equivalents,
    /// specified by glBlendEquation() or glBlendEquationSeparate().
    ////////////////////////////////////////////////////////
    enum Equation
    {
        Add,             //!< Pixel = Src * SrcFactor + Dst * DstFactor
        Subtract,        //!< Pixel = Src * SrcFactor - Dst * DstFactor
        ReverseSubtract, //!< Pixel = Dst * DstFactor - Src * SrcFactor
        Min,             //!< Pixel = min(Dst, Src)
        Max              //!< Pixel = max(Dst, Src)
    };

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// Constructs a blending mode that does alpha blending.
    ///
    ////////////////////////////////////////////////////////////
    BlendMode();

    ////////////////////////////////////////////////////////////
    /// \brief Construct the blend mode given the factors and equation.
    ///
    /// This constructor uses the same factors and equation for both
    /// color and alpha components. It also defaults to the Add equation.
    ///
    /// \param sourceFactor      Specifies how to compute the source factor 
    ///                          for the color and alpha channels.
    /// \param destinationFactor Specifies how to compute the 
    ///                     destination factor for the color and alpha channels.
    /// \param blendEquation     Specifies how to combine the source 
    ///                          and destination colors and alpha.
    ///
    ////////////////////////////////////////////////////////////
    BlendMode(Factor sourceFactor, Factor destinationFactor, 
                            Equation blendEquation = Add);

    ////////////////////////////////////////////////////////////
    /// \brief Construct the blend mode given the factors and equation.
    ///
    /// \param colorSourceFactor      Specifies how to compute the source 
    ///                               factor for the color channels.
    /// \param colorDestinationFactor Specifies how to compute the destination 
    ///                               factor for the color channels.
    /// \param colorBlendEquation     Specifies how to combine the source and 
    ///                               destination colors.
    /// \param alphaSourceFactor      Specifies how to compute the source 
    ///                               factor.
    /// \param alphaDestinationFactor Specifies how to compute the destination 
    ///                               factor.
    /// \param alphaBlendEquation     Specifies how to combine the source 
    ///                               and destination alphas.
    ///
    ////////////////////////////////////////////////////////////
    BlendMode(Factor colorSourceFactor, Factor colorDestinationFactor,
              Equation colorBlendEquation, Factor alphaSourceFactor,
              Factor alphaDestinationFactor, Equation alphaBlendEquation);

    ////////////////////////////////////////////////////////////
    // Member Data
    ////////////////////////////////////////////////////////////
    Factor   colorSrcFactor; //!< Source blending factor for the color channels
    Factor   colorDstFactor; //!< Destination blending factor for the 
                             //!< color channels
    Equation colorEquation;  //!< Blending equation for the color channels
    Factor   alphaSrcFactor; //!< Source blending factor for the alpha channel
    Factor   alphaDstFactor; //!< Destination blending factor for 
                             //!< the alpha channel
    Equation alphaEquation;  //!< Blending equation for the alpha channel
};

////////////////////////////////////////////////////////////
/// \relates BlendMode
/// \brief Overload of the == operator
///
/// \param left  Left operand
/// \param right Right operand
///
/// \return True if blending modes are equal, false if they are different
///
////////////////////////////////////////////////////////////
bool operator ==(const BlendMode& left, 
                                            const BlendMode& right);

////////////////////////////////////////////////////////////
/// \relates BlendMode
/// \brief Overload of the != operator
///
/// \param left  Left operand
/// \param right Right operand
///
/// \return True if blending modes are different, false if they are equal
///
////////////////////////////////////////////////////////////
bool operator !=(const BlendMode& left, 
                                            const BlendMode& right);

////////////////////////////////////////////////////////////
// Commonly used blending modes
////////////////////////////////////////////////////////////
 extern const BlendMode BlendAlpha;    //!< Blend source and 
                                              //!< dest according to dest alpha
 extern const BlendMode BlendAdd;      //!< Add source to dest
 extern const BlendMode BlendMultiply; //!< Multiply source 
                                             //!< and dest
 extern const BlendMode BlendMin;      //!< Take minimum 
                                             //!< between source and dest
 extern const BlendMode BlendMax;      //!< Take maximum 
                                            //!< between source and dest
 extern const BlendMode BlendNone;     //!< Overwrite dest 
                                            //!< with source

} // namespace xwc


#endif // _BLENDMODE_HPP


////////////////////////////////////////////////////////////
/// \class xwc::BlendMode
/// \ingroup graphics
///
/// xwc::BlendMode is a class that represents a blend mode. A blend
/// mode determines how the colors of an object you draw are
/// mixed with the colors that are already in the buffer.
///
/// The class is composed of 6 components, each of which has its
/// own public member variable:
/// \li %Color Source Factor (@ref colorSrcFactor)
/// \li %Color Destination Factor (@ref colorDstFactor)
/// \li %Color Blend Equation (@ref colorEquation)
/// \li Alpha Source Factor (@ref alphaSrcFactor)
/// \li Alpha Destination Factor (@ref alphaDstFactor)
/// \li Alpha Blend Equation (@ref alphaEquation)
///
/// The source factor specifies how the pixel you are drawing contributes
/// to the final color. The destination factor specifies how the pixel
/// already drawn in the buffer contributes to the final color.
///
/// The color channels RGB (red, green, blue; simply referred to as
/// color) and A (alpha; the transparency) can be treated separately. This
/// separation can be useful for specific blend modes, but most often you
/// won't need it and will simply treat the color as a single unit.
///
/// The blend factors and equations correspond to their OpenGL equivalents.
/// In general, the color of the resulting pixel is calculated according
/// to the following formula (\a src is the color of the source pixel, \a dst
/// the color of the destination pixel, the other variables correspond to the
/// public members, with the equations being + or - operators):
/// \code
/// dst.rgb = colorSrcFactor * src.rgb (colorEquation) colorDstFactor * dst.rgb
/// dst.a   = alphaSrcFactor * src.a   (alphaEquation) alphaDstFactor * dst.a
/// \endcode
/// All factors and colors are represented as floating point numbers between
/// 0 and 1. Where necessary, the result is clamped to fit in that range.
///
/// The most common blending modes are defined as constants
/// in the xwc namespace:
///
/// \code
/// xwc::BlendMode alphaBlending          = xwc::BlendAlpha;
/// xwc::BlendMode additiveBlending       = xwc::BlendAdd;
/// xwc::BlendMode multiplicativeBlending = xwc::BlendMultiply;
/// xwc::BlendMode noBlending             = xwc::BlendNone;
/// \endcode
///
/// In SFML, a blend mode can be specified every time you draw a xwc::Drawable
/// object to a render target. It is part of the xwc::RenderStates compound
/// that is passed to the member function xwc::RenderTarget::draw().
///
/// \see xwc::RenderStates, xwc::RenderTarget
///
////////////////////////////////////////////////////////////

/*
 * ==========================================================================
 *
 *       Filename:  RenderStates.hpp
 *
 *    Description:  RenderStates class declaration 
 *
 *        Version:  1.0
 *        Created:  27/01/22 09:45:33
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
#ifndef _RENDERSTATES_HPP
#define _RENDERSTATES_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
//#include "Export.hpp"
#include "BlendMode.hpp"
#include "Transform.hpp"


namespace xwc
{
class Shader;
class Texture;

////////////////////////////////////////////////////////////
/// \brief Define the states used for drawing to a RenderTarget
///
////////////////////////////////////////////////////////////
class RenderStates
{
public:

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// Constructing a default set of render states is equivalent
    /// to using xwc::RenderStates::Default.
    /// The default set defines:
    /// \li the BlendAlpha blend mode
    /// \li the identity transform
    /// \li a null texture
    /// \li a null shader
    ///
    ////////////////////////////////////////////////////////////
    RenderStates();

    ////////////////////////////////////////////////////////////
    /// \brief Construct a default set of render states with a custom blend mode
    ///
    /// \param theBlendMode Blend mode to use
    ///
    ////////////////////////////////////////////////////////////
    RenderStates(const BlendMode& theBlendMode);

    ////////////////////////////////////////////////////////////
    /// \brief Construct a default set of render states with a custom transform
    ///
    /// \param theTransform Transform to use
    ///
    ////////////////////////////////////////////////////////////
    RenderStates(const Transform& theTransform);

    ////////////////////////////////////////////////////////////
    /// \brief Construct a default set of render states with a custom texture
    ///
    /// \param theTexture Texture to use
    ///
    ////////////////////////////////////////////////////////////
    RenderStates(const Texture* theTexture);

    ////////////////////////////////////////////////////////////
    /// \brief Construct a default set of render states with a custom shader
    ///
    /// \param theShader Shader to use
    ///
    ////////////////////////////////////////////////////////////
    RenderStates(const Shader* theShader);

    ////////////////////////////////////////////////////////////
    /// \brief Construct a set of render states with all its attributes
    ///
    /// \param theBlendMode Blend mode to use
    /// \param theTransform Transform to use
    /// \param theTexture   Texture to use
    /// \param theShader    Shader to use
    ///
    ////////////////////////////////////////////////////////////
    RenderStates(const BlendMode& theBlendMode, const Transform& theTransform,
                 const Texture* theTexture, const Shader* theShader);

    ////////////////////////////////////////////////////////////
    // Static member data
    ////////////////////////////////////////////////////////////
    static const RenderStates Default; //!< Special instance 
                                        //holding the default render states

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    BlendMode      blendMode; //!< Blending mode
    Transform      transform; //!< Transform
    const Texture* texture;   //!< Texture
    const Shader*  shader;    //!< Shader
};

} // namespace xwc


#endif // _RENDERSTATES_HPP


////////////////////////////////////////////////////////////
/// \class xwc::RenderStates
/// \ingroup graphics
///
/// There are four global states that can be applied to
/// the drawn objects:
/// \li the blend mode: how pixels of the object are blended with the background
/// \li the transform: how the object is positioned/rotated/scaled
/// \li the texture: what image is mapped to the object
/// \li the shader: what custom effect is applied to the object
///
/// High-level objects such as sprites or text force some of
/// these states when they are drawn. For example, a sprite
/// will set its own texture, so that you don't have to care
/// about it when drawing the sprite.
///
/// The transform is a special case: sprites, texts and shapes
/// (and it's a good idea to do it with your own drawable classes
/// too) combine their transform with the one that is passed in the
/// RenderStates structure. So that you can use a "global" transform
/// on top of each object's transform.
///
/// Most objects, especially high-level drawables, can be drawn
/// directly without defining render states explicitly -- the
/// default set of states is ok in most cases.
/// \code
/// window.draw(sprite);
/// \endcode
///
/// If you want to use a single specific render state,
/// for example a shader, you can pass it directly to the Draw
/// function: xwc::RenderStates has an implicit one-argument
/// constructor for each state.
/// \code
/// window.draw(sprite, shader);
/// \endcode
///
/// When you're inside the Draw function of a drawable
/// object (inherited from xwc::Drawable), you can
/// either pass the render states unmodified, or change
/// some of them.
/// For example, a transformable object will combine the
/// current transform with its own transform. A sprite will
/// set its texture. Etc.
///
/// \see xwc::RenderTarget, xwc::Drawable
///
////////////////////////////////////////////////////////////

/*
 * ========================================================================
 *
 *       Filename:  RenderStates.cpp
 *
 *    Description:  RenderStates class implementation  
 *
 *        Version:  1.0
 *        Created:  27/01/22 09:49:29
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * =========================================================================
 */
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "RenderStates.hpp"
#include <cstddef>


namespace xwc
{
////////////////////////////////////////////////////////////
// We cannot use the default constructor here, because it accesses BlendAlpha, 
// which is also global (and dynamically
// initialized). Initialization order of global objects in 
// different translation units is not defined.
const RenderStates RenderStates::Default(BlendMode(
    BlendMode::SrcAlpha, BlendMode::OneMinusSrcAlpha, BlendMode::Add,
    BlendMode::One, BlendMode::OneMinusSrcAlpha, BlendMode::Add));


////////////////////////////////////////////////////////////
RenderStates::RenderStates() :
blendMode(BlendAlpha),
transform(),
texture  (nullptr),
shader   (nullptr)
{
}


////////////////////////////////////////////////////////////
RenderStates::RenderStates(const Transform& theTransform) :
blendMode(BlendAlpha),
transform(theTransform),
texture  (nullptr),
shader   (nullptr)
{
}


////////////////////////////////////////////////////////////
RenderStates::RenderStates(const BlendMode& theBlendMode) :
blendMode(theBlendMode),
transform(),
texture  (nullptr),
shader   (nullptr)
{
}


////////////////////////////////////////////////////////////
RenderStates::RenderStates(const Texture* theTexture) :
blendMode(BlendAlpha),
transform(),
texture  (theTexture),
shader   (nullptr)
{
}


////////////////////////////////////////////////////////////
RenderStates::RenderStates(const Shader* theShader) :
blendMode(BlendAlpha),
transform(),
texture  (nullptr),
shader   (theShader)
{
}


////////////////////////////////////////////////////////////
RenderStates::RenderStates(const BlendMode& theBlendMode, const Transform& theTransform,
                           const Texture* theTexture, const Shader* theShader) :
blendMode(theBlendMode),
transform(theTransform),
texture  (theTexture),
shader   (theShader)
{
}

} // namespace xwc


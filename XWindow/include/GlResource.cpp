/*
 * ========================================================================
 *
 *       Filename:  GlResource.cpp
 *
 *    Description:  GlResource implementation 
 *
 *        Version:  1.0
 *        Created:  27/01/22 13:02:21
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
#include "GlResource.hpp"
//#include "GlContext.hpp"


namespace xwc
{
////////////////////////////////////////////////////////////
GlResource::GlResource()
{
    priv::GlContext::initResource();
}


////////////////////////////////////////////////////////////
GlResource::~GlResource()
{
    priv::GlContext::cleanupResource();
}


////////////////////////////////////////////////////////////
void GlResource::registerContextDestroyCallback(ContextDestroyCallback callback, void* arg)
{
    priv::GlContext::registerContextDestroyCallback(callback, arg);
}


////////////////////////////////////////////////////////////
GlResource::TransientContextLock::TransientContextLock()
{
    priv::GlContext::acquireTransientContext();
}


////////////////////////////////////////////////////////////
GlResource::TransientContextLock::~TransientContextLock()
{
    priv::GlContext::releaseTransientContext();
}

} // namespace xwc


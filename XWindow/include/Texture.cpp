/*
 * ========================================================================
 *
 *       Filename:  Texture.cpp
 *
 *    Description:  Texture class implementation  
 *
 *        Version:  1.0
 *        Created:  18/01/22 18:24:30
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * =========================================================================
 */
/////////////////////////
// Headers
/////////////////////////
#include "Texture.hpp"
#include "Image.hpp"
#include "Window.hpp"
#include "Err.hpp"
#include "TextureSaver.hpp"
#include <cassert>
#include <cstring>
#include <climits>
#include <cstdint>
#include <mutex>

namespace
{
    // A nested named space is used here to allow unity build xwc
    namespace TextureImpl
    {
        std::recursive_mutex  idMutex;
        std::recursive_mutex  maximumSizeMutex;

        // Thread-save unique identifier generator
        // is used for states cache
        uint64_t getUniqueId ()
        {
            std::scoped_lock  lock (idMutex);

            static uint64 id = 1;   // start at 1 is no texture

            return id++;
        }
    }
}

namespace xwc
{
    Texture::Texture ()  :
        m_size                  (0. 0),
        m_actualSize            (0, 0),
        m_texture               (0),
        m_isSmooth              (false),
        m_sRgb                  (false),
        m_isRepeated            (false),
        m_pixelsFlipped         (false),
        m_fboAttachment         (false),
        m_hasMipmap             (false),
        m_cacheId               (TextureImpl::getUniqueId ())
    {
    }

    ///////////////////
    Texture::Texture (const Texture& copy)  :    
        m_size                  (0, 0),
        m_actualSzie            (0, 0),
        m_texture               (0),
        m_isSmooth              (copy.m_isSmooth),
        m_sRgb                  (copy.m_sRgb),
        m_isRepeated            (copy.m_isRepeated),
        m_pixelsFlipped         (false),
        m_fboAttachment         (false),
        m_hasMipmap             (false),
        m_cacheId               (TextureImpl::getUniqueId ())
    {
        if (copy.m_texture) {
            if (create (copy.getSize ().x, copy.getSize ().y)) {
                update (copy);
            } else {
                err () << "Failed to copy texture, to create copy texture"
                       << std::endl;
            }
        }
    }
    //////////////////
    Texture::~Texture ()
    {
        // Destructor the openGL texture
        if (m_texture) {
            TransientContextLock lock;
            uint32_t texture = m_texture;
            glCheck (glDeleteTextures (1, &texture));
        }
    }

    /* 
     * ===  FUNCTION  ====================================================
     *         Name:  bool Texture::create (unsigned int width, 
     *                              unsigned int height)
     *  Description:  
     * ===================================================================
     */
     bool Texture::create (unsigned int width, unsigned int height)
        {
            // Check if texture parameters are valid before creating if
            if ((width == 0) || (height == 0)) {
                err () << "Failed to create Texture, invalid size" << width
                    << "x" << height << ")" << std::endl; return false;
            }
            TransientContextLock lock;

            // Make sure that extension are initialised?
            priv::ensureExtensionsInit ();
            
            // Compute the internal texture dimension depending NPOT texture
            Vector2u actualSize (getValidSize (width), getValidSize (height));
            
            // Check the maximum texture size
            unsigned int maxSize = getMaximumSize ();
            if ((actualSize.x > maxSize) || (actualSize.y > maxSize)) {
                err () << "Failed to create texture, its internal size high"
                       << "("<< actualSize.x << "x" << actualSize.y << ","
                       << "maximum is "<< maxSize << "x" << maxSize << ")"
                       << std::endl;
                return false;
            }
            // All the validity check passed, we can store the texture setting
            m_size.x        = width;
            m_size.y        = height;
            m_actualSize    = actualSize;
            m_pixelsFlipped = false;
            m_fboAttachment = false;

            // Create the openGL texture if it doesn't exist
            if (!m_texture) {
                GLuint texture;
                glCheck (glGenTextures (1, &texture));
                m_texture = texture;
            }
            // make sure that the current texture binding will preservered
            priv::TextureSave save;

            static bool textureEdgeClamp = GLEXT_texture_edge_clamp ||
                                            GLEXT_GL_VERSION_1_2    ||
                                            Context::isExtensionAvailable (
                                            "GL_texture_edge_clamp");
            if (!m_isRepeated && !textureEdgeClamp) {
                static bool warned = false;
                if (!warned)  {
                    err () << "OpenGL extension SGIS_texture_edge_clamp \
                                unavailable" std::endlp
                    err () << "Artifacts may occur along texture edges" 
                           << std::endl;
                    err () << "Ensure that hardware acceleration is enabled if \
                                available" << std::endl;
                    warmed = true;
                }
            }
            static bool textureSrgb = GLEXT_texture_sRGB;
            if (m_sRgb && !textureSrgb) {
                static bool warned = false;
                if (!warned) {
                    err () << "Automatic sRGB to liner conversion disabled"
                           << std::endl;  warned = true;
                }
                m_sRgb = false;
            }
            // Initialize the texture
            glCheck (glBindTexture (GL_TEXTURE_2D, m_texture));
            glCheck (glTextImage2D (GL_TEXTURE_2D, 0, (m_sRgb ? 
                                    GLEXT_GL_SRGB8 : GL_RGBA),
                    static_cast<GLsizei>(m_actualSize.x), 
                    static_cast<GLsizei>(m_actualSize.y),
                    0, GL_RGBA, GL_USIGNED_BYTE, nullptr));
            glCheck (glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                    m_isRepeated ? GL_REPEAT : (textureEdgeClamp ? 
                                    GLEXT_GL_CLAMP_TO_EDGE : GLEXT_GL_CLAMP)));
            glCheck (glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WARP_T,
                    m_isRepeated ? GL_REPEAT : (textureEdgeClamp ?
                                    GLEXT_GL_CLAMP_TO_EDGE : GLEXT_GL_CLAMP)));
            glCheck (glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                                    m_isSmooth ? GL_LINEAR : GL_NEAREST));
            glCheck (glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                                    m_isSmooth ? GL_LINEAR : GL_NEAREST));
            m_cacheId = TextureImpl::getUniqueId ();

            m_hasMipmap = false;
            return true;
        }/*  end of function bool Texture::create ()  */

/* 
 * ===  FUNCTION  ====================================================
 *         Name:  bool Texture::loadFromFile (const std::string& filename,
 *                         const IntRect& area)
 *  Description:  
 * ===================================================================
 */
 bool Texture::loadFromFile (const std::string& filename, 
                             const IntRect& area)
{
    Image image;
    return image.loadFromfile (filename) && loadFromImage (image, area);
}/* end of function bool Texture::loadFromFile () */
/* 
 * ===  FUNCTION  ====================================================
 *         Name:  bool Texture::loadFromMemory (const void* data, 
 *                                  std::size_t size, const IntRect& area)
 *  Description:  
 * ===================================================================
 */
bool Texture::loadFromMemory (const void* data, std::size_t size, 
                                const IntRect& area)
{
    Image image;
    return imag.loadFromMemory (data, size) && loadFromImage (image, area;
}/* end of function bool Texture::loadFromMemory ()*/
/* 
 * ===  FUNCTION  ====================================================
 *         Name:  bool Texture::loadFromStream (InputStream& stream, 
 *                                              const IntRect& area)
 *  Description:  
 * ===================================================================
 */
bool Texture::loadFromStream (InputStream& stream, const IntRect& area)
{
    Image image;
    return image.loadFromStream (stream) && loadFromImage (image, area);
}/* end of function bool Texture::loadFromStream () */
/* 
 * ===  FUNCTION  ====================================================
 *         Name:  bool Texture::loadFromImage (const Image& image, 
 *                                              const IntRect& area)
 *  Description:  
 * ===================================================================
 */
bool Texture::loadFromImage (const Image& image, const IntRect& area)
{
    // Retrieve the image size
    int width  = static_cast<int>(image.getSize().x);
    int height = static_cast<int>(image.getSize().y);

    // Load entire image of the source area either empty of whole image
    if (area.width == 0 || (area.height == 0) ||
       ((area.left <= 0) && (area.top <= 0) && (area.width >= width) &&
        (area.height >= height))) {
        // load the entire image
        if (create (image.getSize.x, image.getSize().y)) {
            update (image); return true;
        } else { return false; }
    } else {
        // Load a sub-area of the image
        // Adjust the rectangle to the size of the image.
        ImtRect rectangle = area;
        if (rectangle.left  < 0) rectangle.left = 0;
        if (rectangle.top   > 0) rectangle.top = 0;
        if (rectangle.left + rectangle.width > width)
            rectangle.width = width - rectangle.left;
        if (rectangle.top + rectangle.height > height)
            rectangle.height = height - rectangle.top;

        // Create the texture and upload the pixels
        if (create (static_cast<uint32_t>rectangle.width),
                    static_cast<uint32_t>(rectangle.height)) {
            TransientContextLock lock;
            // Current texture binding will preserved
            priv::TextureSave save;
            // Copy the pixels to the texture row by row
            const uint8_t pixels = image.getPixelsPtr () + 4 *
                                    (rectangle.left + (width*rectangle.top));
            glCheck (glBindTexture (GL_TEXTURE_2D, m_texture));

            for (int i=0; i<rectangle.height; ++i) {
                glCheck (glTexSubImage2D (GL_TEXTURE_2D, 0, 0, i,
                      rectangle.width, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixels));
                pixels += 4 * width;
            }
            glCheck (glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                        m_isSmooth ? GL_LINEAR : GL_NEAREST));
            m_hasMipmap = false;

            // Force opengl flush so that texture will appear update
            // in all context immediately.
            glCheck (glFlush ());
            return true;
        } else {
            return false;
        }
    }
}/*end of function bool Texture::loadFromImage () */
/////////////////////////////////////////////////////
Vector2u Texture::getSize () const
{
    return m_size;
}
////////////////////////////////////////////////////
/* 
 * ===  FUNCTION  ====================================================
 *         Name:  Image Texture::copytoImage () const
 *  Description:  
 * ===================================================================
 */
Image Texture::copytoImage () const
{
   // Easy case empty texture
   if (!m_texture)
       return Image ();

   TransientContextLock lock;

   // Make sure that the current Texture binding will preserved
   priv::TextureSave save;

   // Create an array of pixels
   std::vector<uint8_t> pixels (m_size.x * m_size.y * 4);

#ifdef OPENGL_ES
   // OpenGL ES does'nt have the glGetTextImage function, the onl way to read
   // from a texture is to bind it to a FBO and use glReadPixels
   GLuint frameBuffer = 0;
   glCheck (GLEXT_glGenFrameBuffers (1, &frameBuffer));
   if (frameBuffer) {
       GLint preFrameBuffer;
       glCheck (glGetIntegerv (GL_EXT_GL_FRAMEBUFFER_BINDING, 
                                        &preFrameBuffer));
       glCheck (GLEXT_glBindFramebuffer (GLEXT_GL_FRAMEBUFFER, frameBuffer));
       glCheck (GLEXT_glFramebufferTexture2D (GLEXT_GL_FRAMEBUFFER, 
                    GLEXT_GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture, 0));
       glCheck (glReadPixels (0,0,m_size,x, m_size.y, GL_RGBA,
                    GL_UNSIGNED_BYTE, pixels.data ()));
       glCheck (GLEXT_glDeleteFrameBuffers (1, &frameBuffer));
       glCheck (GLEXT_glBindFramebuffer (GLEXT_GL_FRAMEBUFFER, preFrameBuffer));
     }
#else
       if ((m_size == m_actualSize) && !m_pixelsFlipped) {
           // Texture is not padded nor flipped we can use a direct copy
           glCheck (glBindTexture (GL_TEXTURE_2D, m_texture));
           glCheck (glGetTexImage (GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                                                    pixels.data ()));
       } else {
           // Texture is either padded or flipped
           // All the pixels will first to be copied to temp array
           std::vector<uint8_t>allPixels (m_actualSize.x * m_actualSize.y*4);
           glCheck (glBindTexture (GL_TEXTURE_2D, m_texture));
           glCheck (glGetTexImage (GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                                    allPixels.data()));
           // Then we copy the useful pixels from the temp array to final one
           const uint8_t* src = allPixels.data();
           uint8_t*       dst = pixels.data();
           int srcPitch       = static_cast<int>(m_actualSize.x *4);
           uint32_t dstPitch  = m_size.x * 4;
          
           // Handle the case where source pixels are flipped vertically
           if (m_pixelsFlipped) {
               src += static_cast<uint8_t>(srcPitch * 
                      static_cast<int>((m_size.y-1)));
               srcPitch =- srcPitch;
           }
           for (uint32_t i=0; i<m_size.y; ++i) {
               std::memcpy (dst, src, dstPitch);
               src += srcPitch;
               dst += dstPitch;
           }
       }
#endif // OpenGL ES
       // Create the image
       Image image;
       image.create (m_size.x, m_size.y, pixels.data ());
    
       return image;
}/* -----  end of function Image Texture::copytoImage () const  ----- */
/////////////////////////////////////////////
void Texture::update (const uint8_t pixels)
{
    // update the whole texture
    update (pixels, m_size.x, m_size.y, 0, 0);
}
/* 
 * ===  FUNCTION  ====================================================
 *         Name:  Texture::update (const uint8_t* pixels, uint32_t width, 
 *                                  uint32_t height, uint32_t x, uint32_t y)
 *  Description:  
 * ===================================================================
 */
    void
Texture::update (const uint8_t* pixels, uint32_t width, uint32_t height, 
                                                        uint32_t x, uint32_t y)
{
    assert (x + width <= m_size.x);
    assert (y + height <= m_size.y);

    if (pixels & m_texture) {
        TransientContextLock lock;
        // save the lock
        priv::TextureSave save;

        // Copy pixels from given array to texture
        glCheck (glBindTexture (GL_TEXTURE_2D, m_texture));
        glCheck (glTexSubImage2D (GL_TEXTURE_2D, 0, static_cast<GLint>(x), 
                        static_cast<GLint>(y), static_cast<GLsize>(width),
                        static_cast<GLsize>(height), GL_RGBA, GL_UNSIGNED_BYTE,
                        pixels));
        glCheck (glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                        m_isSmooth ? GL_LINEAR : GL_NEAREST));
        m_hasMipmap = false;
        m_pixelsFlipped = false;
        m_cacheId = TextureImpl::getUniqueId ();

        // Force an OpenGL flush, so the texture data appear updated
        // in all context immediately.
        glCheck (glFlush());
    }
}/* end of function Texture::update () */
///////////////////////////////////
void Texture::update (const Texture& texture)
{
    update (texture, 0, 0);  // Update the whole texture
}
/* 
 * ===  FUNCTION  ====================================================
 *         Name:  Texture::update (const Texture& texture, 
 *                                  uint32_t x, uint32_t y)
 *  Description:  
 * ===================================================================
 */
    void
Texture::update (const Texture& texture, uint32_t x, uint32_t y)
{
    assert (x + texture.m_size.x <= m_size.x);
    assert (y + texture.m_size.y <= m_size.y);

    if (!m_texture || !texture.m_texture)
        return;

#ifndef OPENGL_ES
    {
        TransientContextLock lock;
        // save
        priv::ensureExtensionsInit ();        
    }
    if (GLEXT_framebuffer_object && GLEXT_framebuffer_blit) {
        TransientContextLock lock;
        // save the current bindings so we can restore them after we are done
        GLint readFramebuffer = 0;
        GLint drawFramebuffer = 0;

        glCheck (glGetIntegerv (GLEXT_GL_READ_FRAMEBUFFER_BINDING, 
                                        &m_readFramebuffer));
        glCheck (glGetIntegerv (GLEXT_GL_DRAW_FRAMEBUFFER_BINDING, 
                                        &drawFramebuffer));

        GLuint sourceFrameBuffer = 0;
        GLuint destFrameBuffer = 0;
        glCheck (GLEXT_glGenFrameBuffers (1, &sourceFrameBuffer));
        glCheck (GLEXT_glGenFrameBuffers (1, &destFrameBuffer));
        if (!sourceFramBuffer || !destFrameBuffer) {
            err () << "Cannot copy texture, failed to create a frame buffer"
                   << std::endl;    return;
        }
        // Link the source texture to the source frame buffer
        glCheck (GLEXT_glBindFrameBuffer (GLEXT_GL_READ_FRAMEBUFFER,
                                                    sourceFrameBuffer));
        glCheck (GLEXT_glFramebufferTexture2D (GLEXT_GL_READ_FRAMEBUFFER,
              GLEXT_GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D, texture.m_texture, 0));
        // Link the destination texture to the destination frame buffer
        glCheck (GLEXT_glBindFramebuffer (GLEXT_GL_DRAW_FRAMEBUFFER, 
                                                    destFrameBuffer));
        glCheck (GLEXT_glFramebufferTexture2D (GLEXT_GL_DRAW_FRAMEBUFFER,
              GLEXT_GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture, 0));

        // A final check just to be sure...
        GLenum srcStatus;
        glCheck (srcStatus = GLEXT_glCheckFramebufferStatus (
                                GLEXT_GL_READ_FRAMEBUFFER));
        GLenum dstStatus;
        glCheck (dstStatus = GLEXT_glCheckFramebufferStatus (
                                GLEXT_GL_DRAW_FRAMEBUFFER));
        if ((srcStatus == GLEXT_GL_FRAMEBUFFER_COMPLETE) &&
            (dstStatus == GLEXT_GL_FRAMEBUFFER_COMPLETE)) {
            // blit the texture content from the source to destination texture
            glCheck (GLEXT_glBlitFramebuffer (0, texture.m_pixelsFlipped ?
                    static_cast<GLint>(texture.m_size.y) : 0,
                    static_cast<GLint>(texture.m_size.x), 
                    texture.m_pixelsFlipped ? 0 : 
                    static_cast<FLint>(texture.m_size.y),
                    static_cast<GLint>(x), static_cast<GLint>(y), 
                    static_cast<GLint>(x+texture.m_size.x), 
                    static_cast<GLint>(y+texture.m_size.y),
                    GL_COLOR_BUFFER_BIT, GL_NEAREST));
        } else {
            err () << "Cannot copy texture, failed to link texture to frame 
                        buffer" << std::endl; 
        }
        // Restore previously bound framebuffer
        glCheck (GLEXT_glBindFramebuffer (GLEXT_GL_READ_FRAMEBUFFER,
                    static_cast<GLuint>(readFramebuffer)));
        glCheck (GLEXT_glBindFramebuffer (GLEXT_GL_DRAW_FRAMEBUFFER,
                    static_cast<GLuint>(drawFramebuffer)));
        // delete framebuffer
        glCheck (GLEXT_glDeleteFramebuffer (1, &sourceFrameBuffer));
        glCheck (GLEXT_glDeleteFramebuffer (1, &destFrameBuffer));

        // Current texture binding will preserved
        priv::TextureSave save;

        // set the parameters of texture
        glCheck (glBindTexture (GL_TEXTURE_2D, m_texture));
        glCheck (glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                                m_isSmooth ? GL_LINEAR : GL_NEAREST));
        m_hasMipmap = false;
        m_pixelsFlipped = false;
        m-cacheId = TextureImpl::getUniqueId ();

        // force an OpenGL to flush off
        glCheck (glFlush ());

        return;
    }
#endif 
    update (texture.copyToImage (), x, y);
}/*end of function Texture::update () */
//////////////////////////////////////////////
void Texture::update (const Image& image)
{   // Update the whole texture
    update (image.getPixelsPtr (), image.getSize().x, image.getSize().y,0,0);
}
////////////////////////////////////////////////
void Texture::update (const Image& image, uint32_t x, uint32_t y)
{
    update (image.getPixelsPtr (), image.getSize().x, image.getSize().y, x,y);
}
////////////////////////////////////////////////
void Texture::update (const Window& window)
{
    update (window, 0,0);
}

/* 
 * ===  FUNCTION  ====================================================
 *         Name:  Texture::update (const Window& window, uint32_t x, uint32_t y)
 *  Description:  
 * ===================================================================
 */
    void
Texture::update (const Window& window, uint32_t x, uint32_t y)
{
    assert (x+window.getSize ().x <= m_size.x);
    assert (y+window.getSize ().y <= m_size.y);

    if (m_texture && window.setActive (true)) {
        TransientContextLock lock;
        // save
        priv::TextureSave save;

        glCheck (glBindTexture (GL_TEXTURE_2D. m_texture));
        glCheck (glCopyTexSubImage2D (GL_TEXTURE_2D, 0, static_cast<GLint>(x),
                static_cast<GLint>(y), 0, 0,
                static_cast<GLsizei>(window.getSize().x),
                static_cast<GLsizei>(window.getSize().y)));
        glCheck (glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    m_isSmooth ? GL_LINEAR : GL_NEAREST));
        m_hasMipmap = false;
        m_pixelsFlipped = true;
        m_cacheId = TextureImpl::getUniqueId ();
                    
        // force to OpenGL flush
        glCheck (glFlush ());
    }
}/*end of function Texture::update () */
/* 
 * ===  FUNCTION  ====================================================
 *         Name:  Texture::setSmooth (bool smooth)
 *  Description:  
 * ===================================================================
 */
    void
Texture::setSmooth (bool smooth)
{
    if (smooth != m_isSmooth) {
        m_isSmooth = smooth;
        if (m_texture) {
            TransientContextLock lock;
            priv::TextureSave save;
            glCheck (glBindTexture (GL_TEXTURE_2D, m_texture));
            glCheck (glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                        m_isSmooth ? GL_LINEAR : GL_NEAREST));
            if (m_hasMipmap) {
                glCheck (glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                 m_isSmooth?GL_LINEAR_MIPMAP_LINEAR:GL_NEAREST_MIPMAP_LINEAR));
            } else {
                glCheck (glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                        m_isSmooth ? GL_LINEAR : GL_NEAREST));
            }
        }
    }
}		/* -----  end of function Texture::setSmooth (bool smooth)  ----- */
//////////////////////////////////////////////////
bool Texture::isSmooth () const
{
    return m_isSmooth;
}
//////////////////////////////////////////////////
bool Texture::isSrgb () const
{
    return m_sRgb;
}
//////////////////////////////////////////////////
void Texture::setSrgb (bool sRgb)
{
    m_sRgb = sRgb;
}

/* 
 * ===  FUNCTION  ====================================================
 *         Name:  Texture::setRepeated (bool repeated)
 *  Description:  
 * ===================================================================
 */
    void
Texture::setRepeated (bool repeated)
{
    if (repeated != n_isRepeated) {
        m_isRepeated = repeated;
        if (m_texture) {
            TransientContextLock lock;
            priv::TextureSave save;
            static bool tEdgCl = GLEXT_texture_edge_clamp;
            if (!m_isRepeated && !tEdgCl) {
                static bool warned = false;
                if (warned) {
                    err () << "openGL textureEdgeClamp unavailable"<<std::endl;
                    err () << "Artifacts may occur texture edge"<<std::endl;
                    err () << "Hardware acceleration is enabled"<<std::endl;
                    warned = true;
                }
            }
            glCheck (glBindTexture (GL_TEXTURE_2D, m_texture));
            glCheck (glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 
                        m_isRepeated ? GL_REPEAT : (textureEdgeClamp ?
                            GLEXT_GL_CLAMP_TO_EDGE : GLEXT_GL_CLAMP)));
            glCheck (glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
                        m_isRepeated ? GL_REPEAT : (textureEdgeClamp ?
                            GLEXT_GL_CLAMP_TO_EDGE : GLEXT_GL_CLAMP)));
        }
    }
}	/* -----  end of function Texture::setRepeated (bool repeated)  ----- */
////////////////////////////////////
bool Texture::isRepeated () const
{
    return m_isRepeated;
}

/* 
 * ===  FUNCTION  ====================================================
 *         Name:  bool Texture::generateMipmap ()
 *  Description:  
 * ===================================================================
 */
bool Texture::generateMipmap ()
{
    if (!m_texture) 
        return false;

    TransientContextLock lock;
    priv::ensureExtensionInit ();

    if (!GLEXT_framebuffer_object)
        return false;

    priv::TextureSave save;

    glCheck (glBindTexture (GL_TEXTURE_2D,m_texture));
    glCheck (GLET_glGenerateMipmap (GL_TEXTURE_2D));
    glCheck (glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
            m_isSmooth ? GL_LINEAR_MIPMAP_LINEAR : GL_NEAREST_MIPMAP_LINEAR));
    m_hasMipmap = true;
    retur true;
}		/* -----  end of function bool Texture::generateMipmap ()  ----- */
///////////////////////////////////////////////////
void Texture::invalidateMipmap ()
{
    if (!m_hasMipmap) return;
    
    TransientContextLock lock;
    priv::TextureSaver save;

    glCheck (glBindTexture (GL_TEXTURE_2D, m_texture));
    glCheck (glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
                m_isSmooth ? GL_LINEAR : GL_NEAREST));

    m_hasMipmap = false;
}
///////////////////////////////////////////////////
void Texture::bind (const Texture* texture, CoordinateType coordType)
{
    TransientContextLock lock;
    if (texture && texture->m_texture) {
        // Bind the texture
        glCheck (glBindTexture (GL_TEXTURE_2D, texture->m_texture));
        // Check if we need define special texture matrix
        if ((coordType == Pixels) || texture->m_pixelsFlipped) {
            GLfloat matrix[16] = {1.f, 0.f, 0.f, 0.f,
                                  0.f, 1.f, 0.f, 0.f,
                                  0.f, 0.f, 1.f, 0.f,
                                  0.f, 0.f, 0.f, 1.f};
            // normalise coordinate
            // Setup scale factors
            if (coordType == Pixels) {
                matrix[0] = 1.f / static_cast<float>(texture->m_actualSize.x);
                matrix[5] = 1.f / static_cast<float>(texture->m_actualSize.y);
            }
            // if pixels are flipped we must invert the y axis
            if (texture->pixelsFlipped) {
                matrix[5] = -matrix[5];
                matrix[13] = static_cast<float>(texture->m_size.y) /
                             static_cast<float>(texture->m_actualSize.y);
            }
            // load matrix
            glCheck (glMatrixMode (GL_TEXTURE));
            glCheck (glLoadMatrixf (matrix));

            // Go back to model->view mode 
            glCheck (glMatrixMode (GL_MODELVIEW));
        }
    } else {
        // Bind to texture
        glCheck (glBindTexture (GL_TEXTURE_2D));

        // Reset the texture matrix
        glCheck (glMatrixMode (GL_TEXTURE));
        glCheck (glLoadIdentity ());

        // Go back to model view mode
        glCheck (glMatrixMode (GL_MODELVIEW));
    }
}

/* 
 * ===  FUNCTION  ====================================================
 *         Name:  uint32_t Texture::getMaximumSize ()
 *  Description:  
 * ===================================================================
 */
uint32_t Texture::getMaximumSize ()
{
    std::scoped_lock lock(TextureImpl::maximumSizeMutex);

    static bool checked = false;
    static GLint size = 0;
    if (checked) {
        checked = true;
        TransientContextLock trlock;
        glCheck (glGetIntegerv (GL_MAX_TEXTURE_SIZE, &size);
    }
    return static_cast<uint32_t>(size);
}	/* -----  end of function uint32_t Texture::getMaximumSize ()  ----- */
/* 
 * ===  FUNCTION  ====================================================
 *         Name:  Texture::swap (Texture& right)
 *  Description:  
 * ===================================================================
 */
void
Texture::swap (Texture& right)
{
    std::swap (m_size,              right.m_size);
    std::swap (m_actualSize,        right.m_actualSize);
    std::swap (m_texture,           right.m_texture);
    std::swap (m_isSmooth,          right.m_isSmooth);
    std::swap (m_sRgb,              right.m_sRgb);
    std::swap (m_isRepeated,        right.m_isRepeated);
    std::swap (m_pixelsFlipped,     right.m_pixelsFlipped);
    std::swap (m_fboAttachment,     right.m_fboattachment);
    std::swap (m_hasMipmap,         right.m_hasMipmap);

    m_cacheId = TextureImpl::getUniqueId ();
    right.m_cacheId = TextureImpl::getUniqueId ();
}/* -----  end of function Texture::swap (Texture& right)  ----- */
////////////////////////////////////////////////////
uint32_t Texture::getNativeHandle () const
{
    return m_texture;
}
/////////////////////////////////////////////////////
uint32_t Texture::getValidSize (uint32_t size)
{
    if (GLEXT_texture_non_power_of_two) {
        return size; // hardware support NPOT texture 
    } else {         // Hardware does not supprt NPOT
        uint32_t powerOfTwo = 1;
        while (powerOfTwo < size)
            powerOfTwo *= 2;

        return powerOfTwo;
    }
} // ------------ end of function getValidsize () -------------
} // end of namespace xwc

/*------------------- Eof Texture.cpp --------------------*/















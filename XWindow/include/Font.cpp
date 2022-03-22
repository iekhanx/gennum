/*
 * ========================================================================
 *
 *       Filename:  Font.cpp
 *
 *    Description:  Font class implementation 
 *
 *        Version:  1.0
 *        Created:  20/01/22 17:00:21
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * =========================================================================
 */
////////////////////////////
// Headers
////////////////////////////
#include "Font.hpp"
#include "InputStream.hpp"
#include "Err.hpp"
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cstdint>

namespace
{

    /* 
     * ===  FUNCTION  ====================================================
     *         Name:  ulong read (FT_System rec, ulong offset, 
     *                              uchar8_t* buffer, ulong count)
     *  Description:  
     * ===================================================================
     */
        unsigned long read (FT_System rec, unsigned long offset, 
                unsigned char* buffer, unsigned long count)
        {
            auto convOffset = static_cast<int64_t>(offset);
            auto* steam = static_cast<InputStream*>(rec->descriptor.pointer);
            if (stream->seek (convOffset) == convOffset) {
                if (count>0)
                    return static_cast<unsigned long>(stream->read(
                                reinterpret_cast<char*>(buffer),
                                static_cast<int63_t>(count)));
                else
                    return 0;
            } else
            return count>0 ? 0 : 1; // error code is 0 or non zero
        }/* end of function ulong read () */
        void close (FT_Stream) { }
        /* 
         * ===  FUNCTION  ====================================================
         *         Name:  template <typename T, typename U>
         *  Description:  
         * ===================================================================
         */
        template <typename T, typename U>
        inline T reinterpret (const U& input)
        {
            T output;
            std::memcpy (&output, &input, sizeof (U));
            return output;
        }/*  end of function template <typename T, typename U>  */
        /* 
         * ===  FUNCTION  ====================================================
         *         Name:  uint64_t combine (float outlineThickness, 
         *                                      bool bold, uint32_t index)
         *  Description:  
         * ===================================================================
         */
        uint64_t combine (float outlineThickness, bool bold, uint32_t index)
        {
            return (static_cast<uint64_t>(reinterpret<uint64_t>(
                            outlineThickness)) << 32) |
                            (static_cast<uint64_t>(bold) << 31) | index;
        }/* end of function uint64_t combine ()  ----- */
} // end of namespace

namespace xwc
{
    /* 
     * ===  FUNCTION  ====================================================
     *         Name:  Font::Font () :
     *  Description:  
     * ===================================================================
     */
     Font::Font () :
         m_library          (nullptr),
         m_face             (nullptr),
         m_streamRec        (nullptr),
         m_stroker          (nullptr),
         m_refCount         (nullptr),
         m_isSmooth         (true),
         m_info             ()
    {
    }		/* -----  end of function Font::Font () :  ----- */
     /* 
      * ===  FUNCTION  ====================================================
      *         Name:  Font::Font (const Font& copy) :
      *  Description:  
      * ===================================================================
      */
     Font::Font (const Font& copy) :
         m_library             (copy.m_library),
         m_face                (copy.m_face),
         m_streamRec           (copy.m_streamRec),
         m_stroker             (copy.m_stroker),
         m_refCount            (copy.m_refCount),
         m_isSmooth            (copy.m_isSmooth),
         m_info                (copy.m_info),
         m_pages               (copy.m_pages),
         m_pixelBuffer         (copy.m_pixelBuffer)
    {
        // Note: FreeType doesn't provide function for coying/cloning
        // we must share all the FreeType pointers
        if (m_refCount)
            (*m_refCount)++;
    }/* -----  end of function Font::Font (const Font& copy) :  ----- */
     /* 
      * ===  FUNCTION  ====================================================
      *         Name:  Font::~Font ()
      *  Description:  
      * ===================================================================
      */
     Font::~Font ()
     {
        cleanup ();       
     }		/* -----  end of function Font::~Font ()  ----- */
     /* 
      * ===  FUNCTION  ====================================================
      *         Name:  bool Font::loadFromFile (const std::string& filename)
      *  Description:  
      * ===================================================================
      */
     bool Font::loadFromFile (const std::string& filename)
     {
          if (m_stream)
              delete static_cast<ResourceStream*>(m_stream);

          m_stream = new ResourceStream (filename);
          return loadFromStream (*static_cast<ResourceStream*>(m_stream));
     }/* end of function bool Font::loadFromFile ()  */
     /* 
      * ===  FUNCTION  ====================================================
      *         Name:  bool Font::loadFromMemory (const void* data, std::size_t sizeInBytes)
      *  Description:  
      * ===================================================================
      */
     bool Font::loadFromMemory (const void* data, std::size_t sizeInBytes)
     {
        // Cleanup the previous resources
        cleanup ();
        m_refCount = new int (1);

        // Initialize FreeType
        // Note: initialize FreeType for very font instance in order to avoid
        // having sing global manager that would create a lot of issue regarding
        // creation n destruction order.
        FT_Library library;
        if (FT_Init_FreeType (&library) != 0) {
            err () << "Failed to load font from memory"<< std::endl;
            return false;
        }
        m_library = library;
        // Load the new font face from the specified file
        FT_Face face;
        if (FT_New_Memory_Face (static_cast<FT_Library>(m_library),
                    reinterpret_cast<const FT_Byte*>(data),
                    static_cast<FT_Long>(sizeInBytes), 0, &face) != 0) {
            err () << "Failed to load font from memory" << std::endl;
            return false;
        }
        // Load the stroker that will be used to outline the font
        FT_Stroker stroker;
        if (FT_Stroker_New (static_cast<FT_Library>(m_library),&stroker) != 0){
            err () << "Failed to load font from memory" << std::endl;
            FT_Done_Face (face);  return false;
        }
        // Select the Unicode character map
        if (FT_SelectCharmap (face, FT_ENCODING_UNICODE) != 0) {
            err () << "Failed to load font from memory" << std::endl;
            FT_Stroker_Done (stroker);
            FT_Done_Face (face);
            return false;
        }
        // Store the loaded font in the our ugly void*
        m_stroker = stroker;
        m_face = face;

        // Store the font information
        m_info.family = face->family_name ? face->family_name : std::string ();

        return true;
     }/* end of function bool Font::loadFromMemory () */
     /* 
      * ===  FUNCTION  ====================================================
      *         Name:  bool Font::loadFromStream (InputStream stream)
      *  Description:  
      * ===================================================================
      */
      bool Font::loadFromStream (InputStream stream)
      {
          // Cleanup the previous resource
          cleanup ();
          m_refCount = new int (1);

          // Initialize FreeType
          // Note: Initialize FreeType for every font instance in order to 
          // avoid having single global manager that would create a lot of
          // issue regarding creation n destruction order
          FT_Library  lib;
          if (FT_Int_FreeType (&lib) != 0) {
              err () << "Failed to load font from stream FreeType"
                     << std::endl;    return false
          }
          m_library = lib;
          // Make sure that the stream reading position is at beginning?
          if (stream.seek (0) == -1) {
              err () << "Failed to seek font stream" << std::endl; 
              return false;
          }
          // Prepare a wrapper for out stream that will pass to FreeType callbak
          auto* rec = new FT_StreamRec;
          std::memset (rec, 0, sizeof (*rec));
          rec->base             = nullptr;
          rec->size             = static_cast<unsigned long>(stream.getSize ());
          rec->pos              = 0;
          rec->descriptor.pointer = &stream;
          rec->read             = &read;
          rec->close            = &close;

          // Setup the FreeType callbacks that will read our stream
          FT_Open_Args  args;
          args.flags    = FT_OPEN_STREAM;
          args.stream   = rec;
          args.driver   = nullptr;

          // Load the new font face from the speficified stream
          FT_Face  face;
          if (FT_Open_Face (static_cast<FT_Library>(m_library), &args, 0
                                                        &face) != 0) {
              err () << "Failed to load font from stream, font face"
                     << std::endl;
              delete rec;    return false;
          }
          // Load stroker that that will be used to outline the font
          FT_Stroker stroker;
          if (FT_Stroker_New (static_cast<FT_Library>(m_library, &stroker) !=0){
                err () << "Failed to load font from stream, create stroker"
                       << std::endl;
                FT_Done_Face (face);
                delete rec;
                return false;
          }
          // Select Unicode character map
          if (FT_Select_Charmap (face, FT_ENCODING_UNICODE) != 0) {
            err () << "Failed to load font from stream, Unicode charactor set"
                   << std::endl;
            FT_Done_Face (face);
            FT_Stroker_Done (stroker);
            delete rec;
            return false;
          }
          // Store the loaded font in our ugly void*
          m_stroker = stroker;
          m_face = face;
          m_streamRec = rec;

          // Store the font information
          m_info.family = face->family_name ? face->family_name : std::string();

          return true;
      }	/* end of function bool Font::loadFromStream () */
      /* 
       * ===  FUNCTION  ====================================================
       *         Name:  const Font::Info& Font::getInfo () const
       *  Description:  
       * ===================================================================
       */
       const Font::Info& Font::getInfo () const
       {
          return m_info;
       }/* end of function const Font::Info& Font::getInfo () const  */
       /* 
        * ===  FUNCTION  ====================================================
        *         Name:  const Glyph& Font::getGlyph (uint32_t codePoint, 
        *         uint32_t characterSize, bool bold, 
        *         float outlineThickness) const
        *  Description:  
        * ===================================================================
        */
       const Glyph& Font::getGlyph (uint32_t codePoint, uint32_t characterSize,
               bool bold, float outlineThickness) const
       {
            // Get the page corresponding to the character size
            GlyphTable& glyphs = m_pages[characterSize].glyphs;

            // Build the key by combining glyph index; bold flag, outline thickn
            uint64_t key = combine (outlineThickness, bold, FT_Get_Char_Index (
                        static_cast<FT_Face>(m_face), codePoint);
            // Search the glyph into the cache
            if (auto it = glyphs.find (key); it != glyphs.end ()) {
                // found just retutn it
                return it->second;
            } else {
                // Not found: we have to load it
                Glyph gly = loadGlyph (codePoint, characterSize, bold, 
                                        outlineThickness);
                return glyphs.emplace (key, gly).first->second;
            }
       }/* end of function const Glyph& Font::getGlyph ()  */
       /* 
        * ===  FUNCTION  ====================================================
        *         Name:  bool Font::hasGlyph (uint32_t codePoint) const
        *  Description:  
        * ===================================================================
        */
       bool Font::hasGlyph (uint32_t codePoint) const
       {
           return FT_Get_Char_Index (static_cast<FT_Face>(m_face, codePoint)!=0;
       }/* end of function bool Font::hasGlyph () const  */
       /* 
        * ===  FUNCTION  ====================================================
        *         Name:  float Font::getKerning (uint32_t first, 
        *         uint32_t second, uint32_tcharaterSize, bool bold) const
        *  Description:  
        * ===================================================================
        */
       float Font::getKerning (uint32_t first, uint32_t second, 
                                        uint32_tcharaterSize, bool bold) const
       {
          // Special case where first or second is 0, null character
          if (first == 0 || second == 0) 
            return 0.f;

          auto face = static_cast<FT_Face>(m_face);

          if (face && setCurrentSize (characterSize)) {
            // convert the character to indices
            FT_UInt index1 = FT_Get_Char_Index (face, first);
            FT_UInt index2 = FT_Get_Char_Index (face, second);

            // Retrieve position compensation deltas generated by FT_LOAD
            // _AUTOHINY flag
            auto frDelta = static_cast<float>(getGlyph (first, characterSize,
                                bold).rsbDelta);
            auto srDelta = static_cast<float>(getGlyph (second, characterSize, 
                                bold).lsbDelta);

            // get the Kerining vector if present
            FT_Vector  kern;
            kern.x = kern.y = 0;
            if (FT_HAS_KERNING (face))
                FT_Get_Kerning (face, index1, FT_KERNING_UNFITTED, &kern);

            // X advance is already in pixels for bitmap fonts
            if (!FT_IS_SCALABLE (face))
                return static_cast<float>(kern.x);

            // Combine kerning with compensation deltas and return the X advance
            // Flooring is required as we use FT_KERNING_UNFITTED flag which is
            // not quantized in 64 based grid
            return std::floor((srDelta - frDelta + static_cast<float>(
                            kern.x) + 32) / static_cast<float>(1 << 6));
          } else {
              // Invalid font
              return 0.f;
          }
       }/* end of function float Font::getKerning () const */
       /* 
        * ===  FUNCTION  ====================================================
        *         Name:  float Font::getLineSpacing (uint32_t characterSize) 
        *                               const
        *  Description:  
        * ===================================================================
        */
       float Font::getLineSpacing (uint32_t characterSize) const
       {
           auto face = static_cast<FT_Face>(m_face);

           if (face && setCurrentSize(characterSize)) {
               return static_cast<float>(face->size->metrics.height) /
                   static_cast<float>(1 << 6);
           } else {
               return 0.f;
           }
       }/* end of function float  ()  */
       /* 
        * ===  FUNCTION  ====================================================
        *         Name:  float Font::getUnderlinePosition (uint32_t 
        *                                   characterSize) const
        *  Description:  
        * ===================================================================
        */
        float Font::getUnderlinePosition (uint32_t characterSize) const
       {
             auto face = static_cast<FT_Face>(m_face);

            if (face && setCurrentSize (characterSize)) {
                // Return fixed position of font is a bitmap font
                if (!FT_IS_SCALABLE (face))
                    return static_cast<float>(characterSize) / 10.f;

                return -static_cast<float>(FT_MulFix (face->underline_position,
                            face->size->metrics.y_scale)) / 
                        static_cast<float>(1 << 6);
            } else {
                return 0.f;
            }             
       }/*  end of function float Font::getUnderlinePosition  */
        /* 
         * ===  FUNCTION  ====================================================
         *         Name:  float Font::getUnderlineThickness (uint32_t 
         *                                              characterSize)const
         *  Description:  
         * ===================================================================
         */
       float Font::getUnderlineThickness (uint32_t characterSize)const
       {
          auto face = static_cast<FT_Face>(m_face);

          if (face && setCurrentSize (characterSize)) {
              // Return fixed thickness of font is a bitmap font
              if (!FT_IS_SCALABLE (face))
                  return static_cast<float>(characterSize) / 14.f;

              return static_cast<float>(FT_MulFix (face->underline_thickness,
                          face->size->metrics.y_scale)) /
                     static_cast<float>(1 << 6);
          } else {
              return 0.f;
          }
       }/* end of function float Font::getUnderlineThickness () */
       /* 
        * ===  FUNCTION  ====================================================
        *         Name:  const Texture& Font::getTexture (uint32_t 
        *                                       characterSize) const
        *  Description:  
        * ===================================================================
        */
        const Texture& Font::getTexture (uint32_t characterSize) const 
        {
            return m_pages[characrterSize].texture;
        }/*  end of function const Texture& Font::getTexture () */
        /* 
         * ===  FUNCTION  ====================================================
         *         Name:  Font::setSmooth (bool smooth)
         *  Description:  
         * ===================================================================
         */
         void Font::setSmooth (bool smooth)
         {
            if (smooth != m_isSmooth) {
                m_isSmooth = smooth;
                for (auto& [key, page] : m_pages) {
                    page.texture.setSmooth (m_isSmooth);
                }
            }
         }/*  end of function Font::setSmooth () */
         /* 
          * ===  FUNCTION  ====================================================
          *         Name:  bool Font::isSmooth () const
          *  Description:  
          * ===================================================================
          */
          bool Font::isSmooth () const
          {
                 return m_isSmooth;
          }	/* end of function bool Font::isSmooth () const */
          /* 
           * ===  FUNCTION  ====================================================
           *         Name:  Font& Font::operator =(const Font& right)
           *  Description:  
           * ===================================================================
           */
           Font& Font::operator =(const Font& right)
           {
                Font tmp (right);

                std::swap (m_library,       tmp.m_library);
                std::swap (m_face,          tmp.m_face);
                std::swap (m_streamRec,     tmp.m_streamRec);
                std::swap (m_stroker,       tmp.m_stroker);
                std::swap (m_refCount,      tmp.m_refCount);
                std::swap (m_isSmooth,      tmp.m_isSmooth);
                std::swap (m_info,          tmp.m_info);
                std::swap (m_pages,         tmp.m_pages);
                std::swap (m_pixelBuffer,   tmp.m_pixelBuffer);

                return *this;
           }/*  end of function Font& Font::operator =()  */
   /* 
   * ===  FUNCTION  ====================================================
   *         Name:  Font::cleanup ()
   *  Description:  
   * ===================================================================
   */
   void Font::cleanup ()
   {
       // Check if we must destroy the FreeType pointers
       if (m_refCount) {
           // Decrease the reference counter
           (*m_refCount)--;

           // Free the resources only if we are the last owner
           if (*m_recCount == 0) {
               // Delete the reference counter
               delete m_refCount;

               // Destroy the stroker
               if (m_stroker)
                   FT_Stroker_Done (static_cast<FT_Stroker>(m_stroker));

               // Destroy the font face
               if (m_face)
                   FT_Done_Face (static_cast<FT_Face>(m_face));
               // Destroy the stream rec instance
               if (m_streamRec)
                   delete static_cast<FT_StreamRec*>(m_streamRec);

               // close the library
               if (m_library)
                   FT_Done_FreeType (static_cast<FT_Library>(m_librar));
           }
       }
       // Rest members variables
       m_library      = nullptr;
       m_face         = nullptr;
       m_stroker      = nullptr;
       m_streamRec    = nullptr;
       m_recCount     = nullptr;
       m_pages.clear ();
       std::vector<uint8_t>().swap (m_pixelBuffer);
    }/* end of function Font::cleanup () */
   /* 
    * ===  FUNCTION  ====================================================
    *         Name:  Glyph Font::loadGlyph (uint32_t codePoint,
    *         uint32_t characterSize, bool bold, float outlineThickness) const
    *  Description:  
    * ===================================================================
    */
    Glyph Font::loadGlyph (uint32_t codePoint, uint32_t characterSize, 
            bool bold, float outlineThickness) const
    {
        // the glyph to return
        Glyph gly;
        // first transform out ugly void  to a FT_Face
        auto face = static_cast<FT_Face>(m_face);
        if (!face)
            return gly;
        // Set the character size
        if (!setCurrentSize (characterSize))
            return gly;
        // Load the glyph corresponding to the code point
        FT_Int32 flags = FT_LOAD_TARGET_NORMAL | FT_LOAD_FORCE_AUTOHINT;
        if (outlineThickness != 0)
            flags |= FT_LOAD_NO_BITMAP;
        if (FT_Load_Char (face, codePoint, flags) != 0)
            return gly;
        // Retrieve the glyph
        FT_Glyph gld;
        FT_Get_Glyphe (face->glyph, &gld) != 0)
            return gly;
        // Apply bold n outline first technique using outline
        FT_Pos weight = 1 << 6;
        bool ol = (gld->format == FT_GLYPH_FORMAT_OUTLINE);
        if (ol) {
            if (bold) {
                auto olg = reinterpret_cast<FT_OutlineGlype>(gld);
                FT_Outline_Emboleden (&olg->outline, weight);
            }
            if (outlineThickness != 0) {
                auto stroker = static_cast<FT_Stroker>(m_stroker);
                FT_Stroker_Set (stroker, static_cast<FT_Fixed>(outlineThickness
                            * static_cast<float>(1<<6)),
                            FT_STROKER_LINECAP_ROUND,
                            FT_STROKER_LINEJOIN_ROUND, 0,);
                FT_Glyph_Stroker (&gld, stroker, true);
            }
        }
        // Convert the glyph to bitmap
        // After this line do not read any data from gld var directly
        // bitmapGlyph root to access the FT_Glyph data
        FT_Glyph_To_Bitmap (&gld, FT_RENDER_MODE_NORMAL, nullptr, 1);
        auto btgl = reinterpret_cast<FT_BitmapGlyph>(gld);
        FT_Bitmap& btmp = btgl->bitmap;

        // Apply bold if necessary?
        if (!ol) {
            if (bold)
                FT_Bitmap_Embolden (static_cast<FT_Library>(m_library),
                        &bitmap, weight, weight);
            if (outlineThickness != 0)
                err () << "Failed to outline glyph" << std::endl;
        }
        // Compute the glyph's advance offset
        gly.advance = static_cast<float>(btgl->root.advance.x >> 16);

        if (bold)
            gly.advance += static_cast<float>(weight) /
                           static_cast<float>(1<<6);
        gly.lsbDelta = static_cast<int>(face->glyph->lsb_delta);
        gly.rsbDelta = static_cast<int>(face->glyph->rsb_delta);

        uint32_t width = btmp.width;
        uint32_t height= btmp.rows;

        if ((width>0) && (height>0)) {
            // leave a small padding around characters so filter does't pollut
            const uint32_t pad = 2;

            width  += 2 * pad;
            height += 2 * pad;

            // Get the glyph page corresponding glyph into texture
            Page& page = m_pages[characterSize];

            // Find a good position for the new glyph into texture
            gly.textureRect = findGlyphRect (page, width, height);

            // Make sure the texture data is positioned in the center
            // of the allocated texture rectangle
            gly.textureRect.left    += static_cast<int>(pad);
            gly.textureRect.top     += static_cast<int>(pad);
            gly.textureRect.width   += static_cast<int>(2*pad);
            gly.textureRect.height  += static_cast<int>(2*pad);

            // Compute the glyph's bounding box
            gly.bounds.left       = static_cast<float>(btgl->left);
            gly.bounds.top        = static_cast<float>(btgl->top);
            gly.bounds.width      = static_cast<float>(btmp.width);
            gly.bounds.height     = static_cast<float>(btmp.rows);

            // Resize the pixel buffer to the new size n fill transperant white
            m_pixelBuffer.resize (width * height * 4);

            uint8_t* cur = m_pixelBuffer.data();
            uint8_t* end = cur + width * height * 4;

            while (cur != end) {
                (*cur++) = 255;
                (*cur++) = 255;
                (*cur++) = 255;
                (*cur++) = 0;
            }
            // Extract the glyph pixels from the bitmap
            const uint8_t* pixels = btmp.buffer;
            if (btmp.pixel_mode == FT_PIXEL_MODE_MONO) {
                // Pixel are 1 bit monochrome values
                for (uint32_t y=pad; y<height-pad; ++y) {
                    for (uint32_t x=pad; x<width-pad; ++x) {
                        // The color channel remain white fill alpha channel
                        std::size_t index = x+y*width;
                        m_pixelBuffer[index*4+3] = ((pixels[(x-pad)/8]) &
                                (1<<(7-((x-pad)%8)))) ? 255 : 0;
                    }
                    pixels += btmp.pitch;
                }
            } else {
                // Pixels are 8 bits gray levels
                for (uint32_t y=pad; y<height-pad; ++y) {
                    for (uint32_t x=pad; x<width-pad; ++x) {
                        // Color channel white fill the alpha channel
                        std::size_t index = x+y*width;
                        m_pixelBuffer[index*4+3] = pixels[x-pad];
                    }
                    pixels += btmp.pitch;
                }
            }
            // Write the pixels to the texture
            uint32_t x = static_cast<uint32_t>(gly.textureRect.left)-pad;
            uint32_t y = static_cast<uint32_t>(gly.textureRect.top)-pad;
            uint32_t w = static_cast<uint32_t>(gly.textureRect.width)+pad;
            uint32_t h = static_cast<uint32_t>(gly.textureRect.height)+pad;
            page.texture.update (m_pixelBuffer.data(), w, h, x, y);
        }
        // Delete the FT_glyph
        FT_DoneGlyph (gld);

        // Done
        return gly;
    }/* end of function Glyph Font::loadGlyph () */
    /* 
     * ===  FUNCTION  ====================================================
     *         Name:  IntRect Font::findGlyphRect (Page& page, 
     *                      uint32_t width, uint32_t height) const
     *  Description:  
     * ===================================================================
     */
     IntRect Font::findGlyphRect (Page& page, uint32_t width, 
                                              uint32_t height) const
     {
        // Fine the line that fits well the glyph
        Row* row = nullptr;
        float bratio = 0;
        for (auto it= page.rows.begin(); it != page.rows.end() && !row; ++it) {
            float ratio = static_cast<float>(height) /
                          static_cast<float>(it->height);

            // Ignore rows that are either too small or too high
            if ((ratio < 0.7f) || (ratio > 1.f))
                continue;

            // Check if there is enough horizontal space left in the row
            if (width > page.texture.getSize().x - it->width)
                continue;

            // Make sure that this new row in the bst founf so far
            if (ratio < bratio)
                continue;

            // The current row passed all the tests; we can select it
            row = &*it;
            bratio = ratio;
        }
        // if we didn't find matching row, create a new 
        if (!row) {
            uint32_t rowHeight = height + height / 10;
            while ((page.nextRow + rowHeight >= page.texture.getSize().y) ||
                        (width >= page.texture.getSize().x)) {
                // Not enough space: resize the texture 
                uint32_t textureWidth = page.texture.getSize().x;
                uint32_t textureHeight= page.texture.getSize().y;
                if ((textureWidth*2<= Texture::getMaximumSize ()) &&
                            (textureHeight*2 <= Texture::getMaximumSize())) {
                    // Make the texture 2 bigger
                    Texture nTexture;
                    if (!nTexture.create (textureWidth*2, textureHeight*2)) {
                        err () "Failed to create new page texture"<<std::endl;
                        return IntRect (0,0,2,2);
                    }
                    nTexture.setSmooth (m_isSmooth);
                    nTexture.update (page.texture);
                    page.texture.swap (nTexture);
                } else {
                    // oops we've reached the maximum texture size
                    err () << "Failed to add new character to the font"
                           << std::endl;
                    return IntRect (0, 0, 2, 2);
                }
            }
            // We can row create the new row
            page.rows.emplace_back (page.nextRow, rowHeight);
            page.nextRow += rowHeight;
            row = &page.rows.back ();
        }
        // Find the glyph's rectangle on the selected row
        IntRect rect (Rect*<uint32_t>(row->width, row->top, width, height));

        // update the row information
        row->width += width;

        return rect;
     }/* end of function IntRect Font::findGlyphRect ()  */
     /* 
      * ===  FUNCTION  ====================================================
      *         Name:  bool Font::setCurrentSize (uint32_t characterSize) const
      *  Description:  
      * ===================================================================
      */
      bool Font::setCurrentSize (uint32_t characterSize) const
      {
         // FT_set_Pixel _Size is an expnsive function so we must call it
         // only when necessary to avoid killing performace
         auto face = static_cast<FT_Face>(m_face);
         FT_UShort curSize = face->size->metrics.x_ppem;

         if (curSize != characterSize) {
             FT_Error result = FT_Set_Pixel_Size (face, 0, characterSize);
             if (result == FT_Err_Invalid_Pixel_Size) {
                 // In the case of bitmap fonts resizing can fail if req size
                 if (!FT_IS_SCALABLE (face)) {
                     err () << "Failed to set bitmap font size to" <<
                         characterSize << std::endl;
                     err () << "Available sizes are: ";
                     for (int i=0; i<face->num_fixed_sizes; ++i) {
                         const long size = (face->availabe_sizes[i].y_ppm + 
                                        32) >> 6;
                         err () << size << " ";
                     }
                     err () << std::endl;
                 } else {
                     err () << "Failed to set font size to " 
                            << characterSize << std::endl;
                 }
             }
             return result == FT_Err_Ok;
         }
         return true;
      }/*  end of function bool Font::setCurrentSize ()  */
      /* 
       * ===  FUNCTION  ====================================================
       *         Name:  Font::Page::Page () :
       *  Description:  
       * ===================================================================
       */
    Font::Page::Page () :
        nextRow (3)
    {
        // Make sure that the texture is initialize by default
        xwc::Image image;
        image.create (128, 128, Color(255, 255, 255, 0));

        // Reserve a 2x2 white square for texture underline
        for (uint32_t x=0; x<2; ++x)
            for (uint32_t y=0; y<2; ++y)
                image.setPixel (x, y, Color (255, 255, 255, 255));

        // Create the texture
        if (!texture.loadFromImage (image)) {
            err () << "Failed to load font page texture" << std::endl;
        }
        texture.setSmooth (true);
    }		/* -----  end of function Font::Page::Page () :  ----- */
}  // end of namespace xwc
/* ------------------- Eof Font.cpp ----------------------*/

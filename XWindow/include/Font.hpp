/*
 * ==========================================================================
 *
 *       Filename:  Font.hpp
 *
 *    Description:  Font class declaration 
 *
 *        Version:  1.0
 *        Created:  20/01/22 15:38:19
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
#ifndef _FONT_HPP_
#define _FONT_HPP_

////////////////////////
// Headers
////////////////////////
#include "Glyph.hpp"
#include "Texture.hpp"
#include "Rect.hpp"
#include <unordered_map>
#include <string>
#include <vector>
#include <cstdint>

namespace xwc
{
    class InputStream;
    
    /////////////////
    // \brief Class for loading n manipulating character Fonts
    /////////////////
    class Font
    {
        public:

            ////////////
            // \brief Hold various info about font
            ///////////
            struct Info
            {
                std::string family;    //< The font family
            };
        public:

            /////////////
            // \brief Default constructor
            // This constructor define empty font
            ////////////
            Font ();

            ////////////
            // \brief Copy constructor
            // \param copy Instance to copy
            ////////////
            Font (const Font& copy);

            ////////////
            // \brief Destructor
            ////////////
            ~Font ();

            //////////////
            // \brief Load the font from a file
            // \param filename
            // \return True if loaded
            // The supported font format are: TrueType, Type 1, CFF, OpenType,
            // SFNT, X11, PCF, Windows FNT, BDF, PFR and Type 42.
            //
            // note: that this function knows nothing about standard fonts
            // installed on the user's system, thus you can't load them
            // directly.
            //////////////
            [[nodiscard]] bool loadFromFile (const std::string& filename);

            //////////////
            // \brief Load font from the file in memory
            // \param data
            // \return True if loaded
            //////////////
            [[nodiscard]] bool loadFromMemory (const void* data, 
                                               std::size_t sizeInBytes);
            //////////////
            // \brief Load the font from custom stream
            // \param strem source to read from
            // \return True if loaded
            //////////////
            [[nodiscard]] bool loadFromStream (InputStream& stream);

            //////////////
            // \brief Get the font information
            // \return A structure that hold the font info
            //////////////
            const Info& getInfo () const;

            /////////////////
            // \brief Retrieve a glyph of the font
            //
            // If the font is a bitmap font, not all character sizes might be
            // available. If the glyph is not available at the requested size,
            // an empty glyph is returned
            //
            // \param codePoint    unicode code point of character to get
            // \param characterSize reference to character size
            // \param bold          bold version or regular one?
            // \param outlineThickness Thickness of outline
            // \return The glyph corresponding codePoint
            ////////////////
            const Glyph getGlyph (uint32_t codePoint, 
                                   unsigned int characterSize, bool bold,
                                   float outlineThickness = 0) const;

            ////////////////
            // \brief determind the font has glyph representing codePoint
            //
            // Most fonts only include a very limited selection of glyph from
            // specific Unicode subsets, like Latin, Cyrillic, or Asian -
            // characters.
            // \param codePoint Unicode code point 
            // \return True if codePoint found
            ////////////////
            bool hasGlyph (uint32_t codePoint) const;

            //////////////////
            // \brief Get Kerning offset of the two glyphs
            // \param first
            // \param second
            // \param characterSize
            // \return Kerning value for first, second in pixels
            //////////////////
            float getKerning (uint32_t first, uint32_t second,
                              uint32_t characterSize, bool bold=false) const;

            ////////////////
            // \brief Get the line spacing
            // \param characterSize
            // \return Line spacing
            ///////////////
            float getLineSpacing  (uint32_t characterSize) const;

            ////////////////
            // \brief Get the position of the underline
            // \param characterSize
            // \return underline position in pixels
            ////////////////
            float getUnderlinePosition (uint32_t characterSize) const;

            ////////////////
            // \brief Get the thickness of the underline
            // \param characterSize 
            // \return underline thinkness in pixels
            ///////////////
            float getUnderlineThickness (uint32_t characterSize) const;

            /////////////////
            // \brief Retrieve the texture containing loaded glyph of a 
            //        certain size
            // \param characterSize
            // \return Texture
            /////////////////
            const Texture& getTexture (uint32_t characterSize) const;

            ////////////////
            // \brief Enable or disable smooth filter
            // \param smooth True to enable
            ///////////////
            void setSmooth (bool smooth);

            ///////////////
            // \brief Tell whether smooth filter is enabled or not
            // \return True if enabled
            //////////////
            bool isSmooth () const;

            ///////////////
            // \brief Overload of assignment operator
            // \param right instance to assign
            // \return reference to self
            //////////////
            Font& operator = (const Font& right);

        private:

            ////////////////
            // \brief Structure defing a row of glyph
            ////////////////
            struct Row
            {
                Row (uint32_t rowTop, uint32_t rowHeight) :
                                               width (0),
                                               top (rowTop),
                                               height (rowHeight) { }
                uint32_t width;     //< current width of row
                uint32_t top;       //< Y pos of the row
                uint32_t height;    //< Height of the row
            };

            ///////////////
            // Types
            //////////////
            using GlyphTable = std::unordered_map<uint64_t, Glyph>; //< Table
                    // mapping a coordPoint to it's glyph

            ///////////////
            // \brief Structure defining a page glyph
            ///////////////
            struct Page
            {
                Page ();
                GlyphTable    glyphs;   //< Corresponding Glyph of table
                Texture       texture;  //< Texture containg the pixels of glyph
                uint32_t      nextRow;  //< Y Position next row
                std::vector<Row> rows;  //< List containing position row
            };

            ///////////////////
            // \brief Free all the internal resources
            //////////////////
            void cleanup ();

            //////////////////
            // \brief Load a new glyph and store in cache
            // \param codePoint
            // \param characterPoint
            // \param bold
            // \param outlineThickness
            // \return The glyph
            /////////////////
            Glyph loadGlyph (uint32_t codePoint, uint32_t characterSize,
                             bool bold, float outlineThickness) const;
            
            ////////////////////
            // \brief Find a suitable rectangle within texture for glyph
            // \param page
            // \param width
            // \param height
            // \return Found?
            ////////////////////
            IntRect findGlyphRect (Page& page, uint32_t width, uint32_t height)
                                                    const;

            //////////////////
            // \brief make sure system given size of current one
            // \param characterSize size
            // \return True if success
            ///////////////////
            [[nodiscard]] bool setCurrentSize (uint32_t characterSize) const;

            /////////////////
            // Types
            ////////////////
            using PageTable = std::unordered_map<uint32_t, Page>; //< Table mcs

            ////////////////////
            // Member data
            ////////////////////
            void*               m_library;      //< Pointer to library internal
            void*               m_face;         //< Pointer to Font
            void*               m_streamRec;    //< Pointer to stream rec
            void*               m_stroker;      //< Pointer to stroker 
            int*                m_refCount;     //< Reference counter
            bool                m_isSmooth;     //< Status of smooth filter
            Info                m_info;         //< Info about the font
            mutable PageTable   m_pages;        //< table containg glyph pixels
    };  // end of class font
} // end of namespace xwc
#endif
////////////////////////////////////////////////////////////
/// \class xwc::Font
/// \ingroup graphics
///
/// Fonts can be loaded from a file, from memory or from a custom
/// stream, and supports the most common types of fonts. See
/// the loadFromFile function for the complete list of supported formats.
///
/// Once it is loaded, a xwc::Font instance provides three
/// types of information about the font:
/// \li Global metrics, such as the line spacing
/// \li Per-glyph metrics, such as bounding box or kerning
/// \li Pixel representation of glyphs
///
/// Fonts alone are not very useful: they hold the font data
/// but cannot make anything useful of it. To do so you need to
/// use the xwc::Text class, which is able to properly output text
/// with several options such as character size, style, color,
/// position, rotation, etc.
/// This separation allows more flexibility and better performances:
/// indeed a xwc::Font is a heavy resource, and any operation on it
/// is slow (often too slow for real-time applications). On the other
/// side, a xwc::Text is a lightweight object which can combine the
/// glyphs data and metrics of a xwc::Font to display any text on a
/// render target.
/// Note that it is also possible to bind several xwc::Text instances
/// to the same xwc::Font.
///
/// It is important to note that the xwc::Text instance doesn't
/// copy the font that it uses, it only keeps a reference to it.
/// Thus, a xwc::Font must not be destructed while it is
/// used by a xwc::Text (i.e. never write a function that
/// uses a local xwc::Font instance for creating a text).
///
/// Usage example:
/// \code
/// // Declare a new font
/// xwc::Font font;
///
/// // Load it from a file
/// if (!font.loadFromFile("arial.ttf"))
/// {
///     // error...
/// }
///
/// // Create a text which uses our font
/// xwc::Text text1;
/// text1.setFont(font);
/// text1.setCharacterSize(30);
/// text1.setStyle(xwc::Text::Regular);
///
/// // Create another text using the same font, but with different parameters
/// xwc::Text text2;
/// text2.setFont(font);
/// text2.setCharacterSize(50);
/// text2.setStyle(xwc::Text::Italic);
/// \endcode
///
/// Apart from loading font files, and passing them to instances
/// of xwc::Text, you should normally not have to deal directly
/// with this class. However, it may be useful to access the
/// font metrics or rasterized glyphs for advanced usage.
///
/// Note that if the font is a bitmap font, it is not scalable,
/// thus not all requested sizes will be available to use. This
/// needs to be taken into consideration when using xwc::Text.
/// If you need to display text of a certain size, make sure the
/// corresponding bitmap font that supports that size is used.
///
/// \see xwc::Text
///
////////////////////////////////////////////////////////////

/*
 * ==========================================================================
 *
 *       Filename:  Text.hpp
 *
 *    Description:  Text class declaration 
 *
 *        Version:  1.0
 *        Created:  18/01/22 19:21:53
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
#ifndef _TEXT_HPP_
#define _TEXT_HPP_

///////////////////////////
// Headers
//////////////////////////
#include "Font.hpp"
#include "Rect.hpp"
#include "Drawable.hpp"
#include "Transformable.hpp"

#include "VertexArray.hpp"
#include "String.hpp"

#include <string>
#include <vector>
#include <cstdint>

namespace xwc
{
    class Text : public Drawable, public Transformable
    {
        public:

            ///////////////////////////
            // \brief Enumeration of string drawing styles
            //////////////////////////
            enum Style
            {
                Regular         = 0,        //< Regular character no style
                Bold            = 1 << 0,   //< Bold characters
                Italic          = 1 <<1,    //< Italic characters
                Underlined      = 1 <<2,    //< Underlined
                StrikeThrough   = 1 <<3     //< Strike trhough chars
            };

            ////////////////////////
            // \brief Default constructor
            ////////////////////////
            Text ();

            //////////////////////
            // \brief Consturct the text from a string, font n size
            // \param string
            // \param font
            // \param characterSize
            /////////////////////
            Text (const String& str, const Font& font, 
                                    unsigned int charSize = 30);

            ////////////////////
            // \brief Set the text's string
            //
            // The \a string argument is xwc::String which can
            // automatically be constructed from stringi
            // \code 
            // text.setString ("hell");
            // text.setString (L"hello");
            // text.setString (std::string("hello"));
            // text.setString (std::wstring (L"hello"));
            // \endcode
            // A text string is empty by default
            // 
            // \param string New string
            // \see getString
            //////////////////
            void setString (const String& str);

            /////////////////
            // \brief Set the text's font
            // The \a font argment refere to a font that must exist as long
            // as text use it.
            // \param font New font
            // \see getFont
            //////////////////
            void setFont (const Font& font);

            //////////////////////
            // \brief Set the characters size
            //
            // The default size is 30
            //
            // \param size New character size in pixels
            // \see getCharacterSize
            ///////////////////////
            void setCharacterSize (unsigned int size);

            /////////////////////
            // \brief Set the line spacing factor
            //
            // \param spacingFactor New linenspacing factor
            // \see getLineSpacing
            ////////////////////
            void setLineSpacing (float spacingFactor);

            ///////////////////
            // \brief Set the letter spacing factor
            // \param spacingFactor new letter spacing factor
            // \see getLetterSpacing
            //////////////////
            void setLetterSpacing (float spacingFactor);

            ///////////////////
            // \brief Set the text style
            // \param Style new style
            // \see getStyle
            ///////////////////
            void setStyle (uint32_t style);

            /////////////////
            // \brief Set the fill color of the text
            // \param color new fill color of text
            ////////////////
            void setFillColor (const Color& color);

            ////////////////
            // \brief Set the outline color of the text
            // \param color New outline color of the text
            ////////////////
            void setOutlineColor (const Color& color);

            ////////////////
            // \brief Set the thickness of the text's outline
            // \param Thickness in pixels
            /////////////////
            void setOutlineThickness (float thickness);

            //////////////
            // \brief get text string
            //
            // \code
            // String        s1 = text.getString ();
            // std::string   s2 = text.getString ();
            // std::wstring  s3 = text.getString ();
            // \endcode
            // \return Text;s string
            //////////////
            const String& getString () const;

            ////////////////
            // \brief  Get the text's font
            // \return Size of the characters in pixels
            ////////////////
            const Font* getFont () const;

            /////////////////
            // \brief Get the character size
            // \return Size of characters in pixels
            ////////////////
            unsigned int getCharacterSize () const;

            //////////////////
            // \brief Get the size of the letter spaceing factor
            // \return Size of the letter spacing factor
            /////////////////
            float getLetterSpacing () const;

            ////////////////
            // \brief get the size of the line spacing factor
            // \return Size of the line spacing factor
            ///////////////
            float getLineSpacing () const;

            /////////////////
            // \brief Get the text's style
            // \return Text's style
            /////////////////
            uint32_t getStyle () const;

            ///////////////////
            // \brief  Get the outline color of the text
            // \return Fill color of the text
            //////////////////
            const Color& getFillColor () const;

            ///////////////////
            // \brief get the outline color of the text
            // \return Outline color of text
            ///////////////////
            const Color& getOutlineColor () const;

            //////////////////
            // \brief Get the outline thickness of the text
            // \return Outline thickness of the text in pixels
            /////////////////
            float getOutlineThickness () const;

            ///////////////////
            // \brief Return the psotion of the \a index-th character
            // \param index Index of the character
            // \return Position of the character
            ////////////////////
            Vector2f findCharacterPos (std::size_t index) const;

            //////////////////
            // \brief Get the local bounding rectangle of the entity
            // \return Local bounding rectangle of entity
            ///////////////////
            FloatRect getLocalBounds () const;

            ///////////////////
            // \brief Get the global bounding rectangle of the entity
            // \return Global bouding rectangle of the entity
            ///////////////////
            FloatRect getGlobalBounds () const;

        private:

            ////////////////////////////
            // \brief Makesure the text's geometry is updated
            ///////////////////////////
            void ensureGeometryUpdate () const;

            /////////////////////
            // Member data
            /////////////////////
            String              m_string;           //< string to display
            const Font*         m_font;             //< Font to display
            unsigned int        m_charaterSize;     //< Base size of chars
            float               m_letterSpacingFactor;
            float               m_lineSpacingFactor;
            uint32_t            m_style;
            Color               m_fillColor;
            Color               m_outlineColor;
            float               m_outlineThickness;
            mutable VertexArray m_verices;
            mutable VertexArray m_outlineVertices;
            mutable bool        m_geometryNeedUpdate;
            mutable uint64_t    m_fontTextureId;
        }; // end of class Text
} // end of namespace xwc
#endif
/* --------------------- Eof Text.hpp ----------------------*/
////////////////////////////////////////////////////////////
/// \class xwc/g::Text
/// \ingroup graphics
///
/// xwc/g::Text is a drawable class that allows to easily display
/// some text with custom style and color on a render target.
///
/// It inherits all the functions from xwc/g::Transformable:
/// position, rotation, scale, origin. It also adds text-specific
/// properties such as the font to use, the character size,
/// the font style (bold, italic, underlined and strike through), the
/// text color, the outline thickness, the outline color, the character
/// spacing, the line spacing and the text to display of course.
/// It also provides convenience functions to calculate the
/// graphical size of the text, or to get the global position
/// of a given character.
///
/// xwc/g::Text works in combination with the sf::Font class, which
/// loads and provides the glyphs (visual characters) of a given font.
///
/// The separation of xwc/g::Font and sf::Text allows more flexibility
/// and better performances: indeed a xwc/g::Font is a heavy resource,
/// and any operation on it is slow (often too slow for real-time
/// applications). On the other side, a xwc/g::Text is a lightweight
/// object which can combine the glyphs data and metrics of a xwc/g::Font
/// to display any text on a render target.
///
/// It is important to note that the xwc/g::Text instance doesn't
/// copy the font that it uses, it only keeps a reference to it.
/// Thus, a xwc/g::Font must not be destructed while it is
/// used by a xwc/g::Text (i.e. never write a function that
/// uses a local xwc/g::Font instance for creating a text).
///
/// See also the note on coordinates and undistorted rendering 
/// in xwc/g::Transformable.
///
/// Usage example:
/// \code
/// // Declare and load a font
/// xwc/g::Font font;
/// font.loadFromFile("arial.ttf");
///
/// // Create a text
/// xwc/g::Text text("hello", font);
/// text.setCharacterSize(30);
/// text.setStyle(xwc/g::Text::Bold);
/// text.setFillColor(xwc/g::Color::Red);
///
/// // Draw it
/// window.draw(text);
/// \endcode
///
/// \see xwc/g::Font, sf::Transformable
///
////////////////////////////////////////////////////////////

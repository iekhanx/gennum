/*
 * ========================================================================
 *
 *       Filename:  Text.cpp
 *
 *    Description:  class Text implementation  
 *
 *        Version:  1.0
 *        Created:  18/01/22 23:10:57
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * =========================================================================
 */
///////////////////////////////
// Headers
///////////////////////////////
#include "Text.hpp"
#include "VertexArray.hpp"

namespace 
{
    
    /* 
     * ===  FUNCTION  ====================================================
     *         Name:  addLine (VertexArray& vertices, float lineLength, 
     *         float lineTop, const Color& color, flat offset, 
     *         float thickness, float outlineThichness = 0)
     *  Description:  
     * ===================================================================
     */
    void
        addLine (VertexArray& vertices, float lineLength, float lineTop, 
                const Color& color, flat offset, float thickness, 
                float outlineThichness = 0)
        {
            float top = std::floor (lineTop+offset-(thickness/2)+0.5f);
            float bottom = top+std::floor(thickness+0.5f);

            vertices.append (Vertex (Vector2f (-outlineThickness,
                            top-outlineThickness), color, Vector2f (1,1)));
            vertices.append (Vertex (Vector2f (lineLength+outlineThickness,
                            top-outlineThickness), color, Vector2f (1,1)));
            vertices.append (Vertex (Vector2f (-outlineThickness,
                            bottom+outlineThickness), color, Vector2f (1,1)));
            vertices.append (Vertex (Vector2f (-outlineThickness,
                            bottom+outlineThickness), color, Vector2f (1,1)));
            vertices.append (Vertex (Vector2f (lineLenth+outlineThickness,
                            top-outlineThickness), color, Vector2f (1,1)));
            vertices.append (Vertex (Vector2f (lineLength+outlineThickness,
                            bottom+outlineThickness), color, Vector2f (1,1)));
        }/*  end of function addLine ()  */
    /* 
     * ===  FUNCTION  ====================================================
     *         Name:  addGlyphQuad (VertexArray& vertices, Vector2f pos, 
     *         const Color& color, const Glyph& glyph, float italicShear)
     *  Description:  
     * ===================================================================
     */
    void
        addGlyphQuad (VertexArray& vertices, Vector2f pos, const Color& color, 
                                const Glyph& glyph, float italicShear)
        {
            float padding = 1.0;

            float left      = glyph.bounds.left - padding;
            float top       = glyph.bounds.top  - padding;
            float right     = glyph.bounds.left + glyph.bounds.width + padding;
            float bottom    = glyph.bounds.top  + glyph.bounds.height + padding;

            float u1 = static_cast<float>(glyph.textureRect.left) - padding;
            float u2 = static_cast<float>(glyph.textureRect.top) - padding;
            float u3 = static_cast<float>(glyph.textureRect.left + 
                                       glyph.textureRect.width) + padding;
            float u4 = static_cast<float>(glyph.textureRect.top +
                                       glyph.textureRect.height) + padding;

            vertices.append (Vertex (Vector2f (pos.x+left-italicShear *
                            top, pos.y+top), color, Vector2f (u1, v1)));
            vertices.append (Vertex (Vector2f (pos.x+right-italicShear *
                            top, pos.y+top), color, Vector2f (u2, v1)));
            vertices.append (Vertex (Vector2f (pos.x+left-italicShear *
                            bottom, pos.y+bottom), color, Vector2f (u1,v2)));
            vertices.append (Vertex (Vector2f (pos.x+left-italicShear *
                            bottom, pos.y+bottom), color, Vector2f (u1,v2)));
            vertices.append (Vertex (Vector2f (pos.x+right-italicShear *
                            top, pos.y+top), color, Vector2f (u2,v1)));
            vertices.append (Vertex (Vector2f (pos.x+right-italicShear *
                            bottom, pos.y+bottom), color, Vector2f (u2,v2)));
        }/* end of function addGlyphQuad () */
} // end of namespace

namespace xwc
{
    
    /* 
     * ===  FUNCTION  ====================================================
     *         Name:  Text::Text ()  :
     *  Description:  
     * ===================================================================
     */
    Text::Text ()  :
        m_string                    (),
        m_font                      (nullptr),
        m_characterSize             (30),
        m_letterSpacingFactor       (1.f),
        m_lineSpacingFactor         (1.f),
        m_style                     (Regular),
        m_fillColor                 (255,255,255),
        m_outlineColor              (0,0,0),
        m_outlineThickness          (0),
        m_vertices                  (Triangles),
        m_outlineVertices           (Triangles),
        m_bounds                    (),
        m_geometryNeedUpdate        (false),
        m_fontTextureId             (0)
    {

    }		/* -----  end of function Text::Text ()  :  ----- */
    /* 
     * ===  FUNCTION  ====================================================
     *         Name:  Text::Text (const String& string, const Font& font, 
     *                              unsigned int characterSize)  :
     *  Description:  
     * ===================================================================
     */
     Text::Text (const String& string, const Font& font, 
                                        unsigned int characterSize)  :
         m_string                       (string),
         m_font                         (&font),
         m_characterSize                (characterSize),
         m_letterSpacingFactor          (1.f),
         m_lineSpacingFactor            (1.f),
         m_style                        (Regular),
         m_fillColor                    (255,255,255),
         m_outlineColor                 (0,0,0),
         m_outlineThickness             (0),
         m_vertices                     (Triangles),
         m_outlineVertices              (Triangles),
         m_bounds                       (),
         m_geometryNeedUpdate           (true),
         m_fontTextureId                (0)
    {
        
    }/*  end of function Text::Text ()  */
     /* 
      * ===  FUNCTION  ====================================================
      *         Name:  Text::setString (const String& string)
      *  Description:  
      * ===================================================================
      */
     void
         Text::setString (const String& string)
         {
             if (m_string != string) {
                 m_string = string;
                 m_geometryNeedUpdate = true;
             }
         }	/* end of function Text::setString ()  */
     /* 
      * ===  FUNCTION  ====================================================
      *         Name:  Text::setFont (const Font& font)
      *  Description:  
      * ===================================================================
      */
     void
         Text::setFont (const Font& font)
         {
             if (m_font != &font) {
                 m_font = &font;
                 m_geometryNeedUpdate = true;
             }
         }/* end of function Text::setFont () */
     /* 
      * ===  FUNCTION  ====================================================
      *         Name:  Text::setCharacterSize (unsigned int size)
      *  Description:  
      * ===================================================================
      */
     void
         Text::setCharacterSize (unsigned int size)
         {
             if (m_characterSize != size) {
                 m_characterSize = size;
                 m_geometryNeedUpdate = true;
             }
         }/* end of function Text::setCharacterSize () */
     /* 
      * ===  FUNCTION  ====================================================
      *         Name:  Text::setLetterSpacing (float spacingFactor)
      *  Description:  
      * ===================================================================
      */
     void
         Text::setLetterSpacing (float spacingFactor)
         {
             if (m_lineSpacingFactor != spacingFactor) {
                 m_lineSpacingFactor = spacingFactor;
                 m_geometryNeedUpdate = true;
             }
         }/* end of function Text::setLetterSpacing () */
     /* 
      * ===  FUNCTION  ====================================================
      *         Name:  Text::setStyle (unit32_t style)
      *  Description:  
      * ===================================================================
      */
     void
         Text::setStyle (unit32_t style)
         {
            if (m_style != style) {
                m_style = style;
                m_geometryNeedUpdate = true;
            }
         }/* end of function Text::setStyle () */
     /* 
      * ===  FUNCTION  ====================================================
      *         Name:  Text::setFillColor (const Color& color)
      *  Description:  
      * ===================================================================
      */
     void
         Text::setFillColor (const Color& color)
         {
             if (color != m_fillColor) {
                 m_fillColor = color;
                 // Change vertex color directly, no need to update whole 
                 // geometry if geometry is updated, we can skip this step
                 if (!m_geometryNeedUpdate) {
                     for (std::size_t i=0; i<m_vertices.getVertexCount(); ++i)
                         m_vertices[i].color = m_fillColor;
                 }
             }
         }/* end of function Text::setFillColor () */
     /* 
      * ===  FUNCTION  ====================================================
      *         Name:  Text::setOutlineColor (const Color& color)
      *  Description:  
      * ===================================================================
      */
     void
         Text::setOutlineColor (const Color& color)
         {
            if (color != m_outlineColor) {
                m_outlineColor = color;
                // Change vertex color directly no need to update whole geometry
                if (!m_geometryNeedUpdate) {
                    for (std::size_t i=0; i<m_outlineVertices.getVertexCount();
                            ++i)
                        m_outlineVertices[i].color = m_outlineColor;
                }
            }
         }/*  end of function Text::setOutlineColor ()  */
     /* 
      * ===  FUNCTION  ====================================================
      *         Name:  Text::setOutlineThickness (float thickness)
      *  Description:  
      * ===================================================================
      */
     void
         Text::setOutlineThickness (float thickness)
         {
             if (thickness != m_outlineThickness) {
                 m_outlineThickness = thickness;
                 m_geometryNeedUpdate = true;
             }
         }/* end of function Text::setOutlineThickness ()  */
     /* 
      * ===  FUNCTION  ====================================================
      *         Name:  const String& Text::getString () const
      *  Description:  
      * ===================================================================
      */
      const String& Text::getString () const
         {
            return m_string;
         }/* end of function const String& Text::getString () const *//* 
 * ===  FUNCTION  ====================================================
 *         Name:  const Font* Text::getFont () const
 *  Description:  
 * ===================================================================
 */
    const Font* Text::getFont () const
    {
        return m_font;
    }/* end of function const Font* Text::getFont () const */
    /* 
     * ===  FUNCTION  ====================================================
     *         Name:  unsigned int Text::getCharacterSize () const
     *  Description:  
     * ===================================================================
     */
      unsigned int Text::getCharacterSize () const
      {
            return m_characterSize;
      }/* end of function unsigned int Text::getCharacterSize () */
      /* 
       * ===  FUNCTION  ====================================================
       *         Name:  float Text::getLetterSpacing () const
       *  Description:  
       * ===================================================================
       */
       float Text::getLetterSpacing () const
       {
              return m_letterSpacingFactor;
       }/* end of function float Text::getLetterSpacing () const */
       /* 
        * ===  FUNCTION  ====================================================
        *         Name:  float Text::getLineSpacing () const
        *  Description:  
        * ===================================================================
        */
       float Text::getLineSpacing () const
       {
               return m_lineSpacingFactor;
       }/* end of function float Text::getLineSpacing () const */
       /* 
        * ===  FUNCTION  ====================================================
        *         Name:  uint32_t Text::getStyle () const
        *  Description:  
        * ===================================================================
        */
       uint32_t Text::getStyle () const
       {
                return m_style;
       }/* end of function uint32_t Text::getStyle () const */
       /* 
        * ===  FUNCTION  ====================================================
        *         Name:  const Color& Text::getFillColor () const
        *  Description:  
        * ===================================================================
        */
       const Color& Text::getFillColor () const
       {
               return m_fillColor;
       }/* end of function const Color& Text::getFillColor () const */
       /* 
        * ===  FUNCTION  ====================================================
        *         Name:  const Color& Text::getOutlineColor () const
        *  Description:  
        * ===================================================================
        */
       const Color& Text::getOutlineColor () const
       {
               return m_outlineColor;
       }/* end of function const Color& Text::getOutlineColor () const */
       /* 
        * ===  FUNCTION  ====================================================
        *         Name:  float Text::getOutlineThickness () const
        *  Description:  
        * ===================================================================
        */
       float Text::getOutlineThickness () const
       {
               return m_outlineThickness;
       }/* end of function float Text::getOutlineThickness () const */
       /* 
        * ===  FUNCTION  ====================================================
        *         Name:  Vector2f Text::findCharacterPos (std::size_t index) 
        *                                   const
        *  Description:  
        * ===================================================================
        */
       Vector2f Text::findCharacterPos (std::size_t index) const
           {
               // Make sure that we have a valid font
               if (!m_font) 
                   return Vector2f ();
               // Adjust the index if out of range
               if (index > m_string.getSize())
                   index = m_string.getSize();

               // precompute the variable needed by algorithm
               bool isBold      = m_style & Bold;
               float whitespaceWidth = m_font->getGlyph (L' ',m_characterSize,
                                    isBold).advance;
               float letterSpacing = (whitespaceWidth / 3.f) * 
                                (m_letterSpacingFactor - 1.f);
               whitespaceWidth  += letterSpacing;
               float lineSpacing = m_font->getLineSpacing (m_characterSize) *
                                    m_lineSpacingFactor;
               // Compute the position
               Vector2f pos;
               uint32_t prevChar = 0;
               for (std::size_t i=0; i<index; ++i) {
                    uint32_t curChar = m_string[i];

                    // Apply the kerning offset
                    pos.x += m_font->getKerning (prevChar, curChar, 
                                                    m_characterSize, isBold);
                    prevChar = curChar;

                    // Handle special characters
                    switch (curChar) {
                        case ' ':  pos.x += whitespaceWidth;       continue;
                        case '\t': pos.x += whitespaceWidth * 4;   continue;
                        case '\n': pos.y += lineSpacing; pos.x=0;  continue;
                    }
                    // for regular character add the adv offset of glyph
                    pos.x += m_font->getGlyph (curChar, m_characterSize, 
                                                isBold).advance + letterSpacing;
               }
               // Transform the position to global coordinate
               pos = getTransform ().transformPoint (pos);
             return pos;
           }/* end of function Vector2f Text::findCharacterPos () */
       /* 
        * ===  FUNCTION  ====================================================
        *         Name:  FloatRect Text::getLocalBounds () const
        *  Description:  
        * ===================================================================
        */
       FloatRect Text::getLocalBounds () const
       {     ensureGeometryUpdate ();
             return m_bounds;
       }/* end of function FloatRect Text::getLocalBounds () const */
       /* 
        * ===  FUNCTION  ====================================================
        *         Name:  FloatRect Text::getGlobalBounds () const
        *  Description:  
        * ===================================================================
        */
       FloatRect Text::getGlobalBounds () const
       {
               return getTransform ().transformRect (getLocalBounds ());
       }/* end of function FloatRect Text::getGlobalBounds () const */
       /* 
        * ===  FUNCTION  ====================================================
        *         Name:  Text::draw (RenderTarget& target, 
        *                                   RenderStates states) const
        *  Description:  
        * ===================================================================
        */
       void
        Text::draw (RenderTarget& target, RenderStates states) const
        {
            if (m_font) {
                ensureGeometryUpdate ();

                states.transform *= getTransform ();
                states.texture  = &m_font->getTexture (m_characterSize);

                // only draw the outline if there is something to draw
                if (m_outlineThickness != 0)
                    target.draw (m_outlineVertices, states);

                target.draw (m_vertices, states);
            }
        }/* end of function Text::draw () const */
       /* 
        * ===  FUNCTION  ====================================================
        *         Name:  Text::ensureGeometryUpdate () const
        *  Description:  
        * ===================================================================
        */
       void
           Text::ensureGeometryUpdate () const
           {
                // Do nothing, if geometry has not changed
                if (!m_geometryNeedUpdate && m_font->getTexture (m_character).
                                            m_cacheId == m_fontTextureId)
                    return;

                // Save the current fonts texture id
                m_fontTextureId = m_font->getTexture(m_characterSize).m_cacheId;

                // Mark geometry as update
                m_geometryNeedUpdate = false;

                // Clear the previous geometry
                m_vertices.clear ();
                m_outlineVertices.clear ();
                m_bounds = FloatRect ();

                // No text nothing to draw
                if (m_string.isEmpty ())
                    return;

                // Compute values related to text style
                bool       isBold          = m_style & Bold;
                bool       isUnderlined    = m_style & Underlined;
                bool       isStrikeThrough = m_style & StrikeThrough;
                float      italicShear     = (m_style & Italic) ? 0.209f : 0.f;
                float      underlineOffset = m_font->getUnderlinePosition (
                                                    m_characterSize);
                float      underlineThickness = m_font->getUnderlineThickness (
                                                    m_characterSize);
                // Compute the location of the strike through dynamically
                // We use the center point of the lowercase 'x' glyph as the
                // reference we reuse the underline thickness as the thickness
                // of the strike thruogh as well
                FloatRect xBounds = m_font->getGlyph (L'x', m_characterSize,
                                            isBold).bounds;
                float strikThroughOffset = xBound.top + xBounds.height / 2.f;

                // Precompute the variable needed by the algorithm
                float whitespaceWidth = m_font->getGlyph (L' ', m_characterSize,
                        isBold).advance;
                float letterSpacing = (whitespaceWidth / 3.f) *
                                            (m_letterSpacingFactor - 1.f);
                whitespaceWidth += letterSpacing;
                float lineSpacing = m_font->getLineSpacing (m_characterSize) *
                                                    m_lineSpacingFactor;
                float x     = 0.f;
                auto  y     = static_cast<float>(m_characterSize);

                // Create one quad for each character
                auto minX  = static_cast<float>(m_characterSize);
                auto minY  = static_cast<float>(m_characterSize);
                float maxX = 0.f;
                float maxY = 0.f;
                uint32_t prevChar = 0;

                for (std::size_t i=0; i<m_string.getSize (); ++i) {
                    uint32_t curChar = m_string[i];

                    // skip the \r char to avoid  weird graphical issue
                    if (curChar == '\r')
                        continue;

                    // Apply the kering offset
                    x += m_font->getKerning (prevChar, curChar, m_characterSize,
                                                    isBold);
                    // if we' re using the underlined style there is new line
                    if (isUnderlined && (curChar == L'\n' && prevChar != L'\n'))
                    {
                        addLine (m_vertices, x, y, m_fillColor, underlineOffset,
                                underlineThickness);
                        if (m_outlineThickness != 0)
                            addLine (m_outlineVertices, 
                                     x, y, 
                                     m_outlineColor,
                                     underlineOffset,
                                     underlineThickness,
                                     m_outlineThickness);
                    }
                    // if we're using the strike trhough style and there's a
                    // new line, draw a line across all characters
                    if (isStrikeThrough && (curChar == L'\n' &&
                                    prevChar != L'\n')) {
                        addLine (m_vertices, x, y, m_fillColor, 
                                            strikeThroughOffset,
                                            underlineThickness);
                        if (m_outlineThickness != 0)
                            addLine (m_outlineVertices, x, y,
                                                      m_outlineColor,
                                                      strikeTrhoughOffset,
                                                      underlineThickness,
                                                      m_outlineThickness);
                    }
                    prevChar = curChar;
                    // Handle special character
                    if ((curChar == L' ') || (curChar == L'\n') || 
                                             (curChar == L'\t')) {
                        // Update the current bounds
                        minX = std::min(minX, x);
                        minY = std::min(minY, y);
                        switch (curChar) {
                            case L' ':  x += whitespaceWidth;    break;
                            case L'\t': x += whitespaceWidth;    break;
                            case L'\n': y += lineSpacing;        break;
                        }
                        // Update the current bound
                        maxX = std::max(maxX, x);
                        maxY = std::max(maxY, y);

                        // next glyph no need to create a quad for whitespace
                        continue;
                    }
                    // Apply the outline
                    if (m_outlineThickness != 0) {
                        const Glyph& glyph = m_font->getGlyph (curChar,
                                                           m_characterSize,
                                                           isBold,
                                                           m_outlineThickness);
                        float left      = glyph.bounds.left;
                        float top       = glyph.bounds.top;
                        float right     = glyph.bounds.left+glyph.bounds.width;
                        float bottom    = glyph.bounds.top+glyph.bounds.height;
                        // Add the outline glyph to the vertices
                        addGlyphQuad (m_outlineVertices,
                                      Vector3f (x,y),
                                      m_outlineColor,
                                      glyph,
                                      italicShear);
                        // Update the cuurent bounds
                        minX = std::min(minX, x + left - italicShear*bottom);
                        maxX = std::max(maxX, x + right- italicShear*top);
                        minY = std::min(minY, y + top);
                        maxY = std::max(maxY, y + bottom);
                    }
                    // Extract the current glyph's description
                    const Glyph& glyph = m_font->getGlyph (curChar,
                                                            m_characterSize,
                                                            isBold);
                    // Add the glyph to the vertices
                    addGlyphQuad (m_vertices, Vector2f (x, y), m_fillColor,
                                            glyph, italicShear);
                    // update the current bounds with the non outlined glyph
                    // bounds
                    if (m_outlineThickness == 0) {
                        float left     = glyph.bounds.left;
                        float top      = glypn.bounds.top;
                        float right    = glyph.bounds.left+glyph.bounds.width;
                        float bottom   = glyph.bounds.top+glyph.bounds.height;

                        minX = std::min(minX, x+left - italicShear*bottom);
                        maxX = std::max(maxX, x+right- italicShear*top);
                        minY = std::min(minY, y+top);
                        maxY = std::max(maxY, y+bottom);
                    }
                    // Advance to the next character
                    x += glyph.advance + letterSpacing;
                }
                // if we're using the underlined style add the last line
                if (isUnderlined && (x>0)) {
                    addLine (m_vertices, x, y, m_fillColor,
                                               underlineOffset,
                                               underlineThickness);
                    if (m_outlineThickness != 0)
                        addLine (m_outlineVertices, x, y,
                                        m_outlineColor,
                                        underlineOffset,
                                        underlineThickness,
                                        m_outlineThickness);
                }
                // if we're using the strike through style
                if (isStrkeThrough && (x>0)) {
                    addLine (m_vertices, x, y, m_fillColor,
                                    strkeThroughOffset,
                                    underlineThickness);
                    if (m_outlineThickness != 0)
                        addLine (m_outlineVertices, x, y,
                                 m_outlineColor,
                                 strikeThroughOffset,
                                 underlinethickness,
                                 m_outlineThickness);
                }
                // Update the bounding rectangle
                m_bounds.left = minX;
                m_bounds.top  = minY;
                m_bounds.width = maxX - minX;
                m_bounds.height = maxY - minY;
           }/* end of function Text::ensureGeometryUpdate () const  */
} // end of namespace xwc
/* -------------------- Eof Text.cpp ---------------------*/







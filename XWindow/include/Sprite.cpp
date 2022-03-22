/*
 * ========================================================================
 *
 *       Filename:  Sprite.cpp
 *
 *    Description: Sprite class implementation 
 *
 *        Version:  1.0
 *        Created:  26/01/22 01:49:24
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
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <cstdlib>


namespace xwc
{
////////////////////////////////////////////////////////////
Sprite::Sprite() :
m_texture    (nullptr),
m_textureRect()
{
}


////////////////////////////////////////////////////////////
Sprite::Sprite(const Texture& texture) :
m_texture    (nullptr),
m_textureRect()
{
    setTexture(texture, true);
}


////////////////////////////////////////////////////////////
Sprite::Sprite(const Texture& texture, const IntRect& rectangle) :
m_texture    (nullptr),
m_textureRect()
{
    // Compute the texture area
    setTextureRect(rectangle);
    // Assign texture
    setTexture(texture, false);
}


////////////////////////////////////////////////////////////
void Sprite::setTexture(const Texture& texture, bool resetRect)
{
    // Recompute the texture area if requested, or if there was no 
    // valid texture & rect before
    if (resetRect || (!m_texture && (m_textureRect == sf::IntRect())))
    {
        Vector2i size = Vector2i(texture.getSize());
        setTextureRect(IntRect(0, 0, size.x, size.y));
    }

    // Assign the new texture
    m_texture = &texture;
}


////////////////////////////////////////////////////////////
void Sprite::setTextureRect(const IntRect& rectangle)
{
    if (rectangle != m_textureRect)
    {
        m_textureRect = rectangle;
        updatePositions();
        updateTexCoords();
    }
}


////////////////////////////////////////////////////////////
void Sprite::setColor(const Color& color)
{
    // Update the vertices' color
    m_vertices[0].color = color;
    m_vertices[1].color = color;
    m_vertices[2].color = color;
    m_vertices[3].color = color;
}


////////////////////////////////////////////////////////////
const Texture* Sprite::getTexture() const
{
    return m_texture;
}


////////////////////////////////////////////////////////////
const IntRect& Sprite::getTextureRect() const
{
    return m_textureRect;
}


////////////////////////////////////////////////////////////
const Color& Sprite::getColor() const
{
    return m_vertices[0].color;
}


////////////////////////////////////////////////////////////
FloatRect Sprite::getLocalBounds() const
{
    auto width = static_cast<float>(std::abs(m_textureRect.width));
    auto height = static_cast<float>(std::abs(m_textureRect.height));

    return FloatRect(0.f, 0.f, width, height);
}


////////////////////////////////////////////////////////////
FloatRect Sprite::getGlobalBounds() const
{
    return getTransform().transformRect(getLocalBounds());
}


////////////////////////////////////////////////////////////
void Sprite::draw(RenderTarget& target, RenderStates states) const
{
    if (m_texture)
    {
        states.transform *= getTransform();
        states.texture = m_texture;
        target.draw(m_vertices, 4, TriangleStrip, states);
    }
}


////////////////////////////////////////////////////////////
void Sprite::updatePositions()
{
    FloatRect bounds = getLocalBounds();

    m_vertices[0].position = Vector2f(0, 0);
    m_vertices[1].position = Vector2f(0, bounds.height);
    m_vertices[2].position = Vector2f(bounds.width, 0);
    m_vertices[3].position = Vector2f(bounds.width, bounds.height);
}


////////////////////////////////////////////////////////////
void Sprite::updateTexCoords()
{
    FloatRect convertedTextureRect(m_textureRect);

    float left   = convertedTextureRect.left;
    float right  = left + convertedTextureRect.width;
    float top    = convertedTextureRect.top;
    float bottom = top + convertedTextureRect.height;

    m_vertices[0].texCoords = Vector2f(left, top);
    m_vertices[1].texCoords = Vector2f(left, bottom);
    m_vertices[2].texCoords = Vector2f(right, top);
    m_vertices[3].texCoords = Vector2f(right, bottom);
}

} // end of namespace xwc


/*
 * ========================================================================
 *
 *       Filename:  VertexArray.cpp
 *
 *    Description: VertexArray class implementation 
 *
 *        Version:  1.0
 *        Created:  26/01/22 14:27:13
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
#include "VertexArray.hpp"
#include "RenderTarget.hpp"


namespace xwc
{
////////////////////////////////////////////////////////////
VertexArray::VertexArray() :
m_vertices     (),
m_primitiveType(Points)
{
}


////////////////////////////////////////////////////////////
VertexArray::VertexArray(PrimitiveType type, std::size_t vertexCount) :
m_vertices     (vertexCount),
m_primitiveType(type)
{
}


////////////////////////////////////////////////////////////
std::size_t VertexArray::getVertexCount() const
{
    return m_vertices.size();
}


////////////////////////////////////////////////////////////
Vertex& VertexArray::operator [](std::size_t index)
{
    return m_vertices[index];
}


////////////////////////////////////////////////////////////
const Vertex& VertexArray::operator [](std::size_t index) const
{
    return m_vertices[index];
}


////////////////////////////////////////////////////////////
void VertexArray::clear()
{
    m_vertices.clear();
}


////////////////////////////////////////////////////////////
void VertexArray::resize(std::size_t vertexCount)
{
    m_vertices.resize(vertexCount);
}


////////////////////////////////////////////////////////////
void VertexArray::append(const Vertex& vertex)
{
    m_vertices.push_back(vertex);
}


////////////////////////////////////////////////////////////
void VertexArray::setPrimitiveType(PrimitiveType type)
{
    m_primitiveType = type;
}


////////////////////////////////////////////////////////////
PrimitiveType VertexArray::getPrimitiveType() const
{
    return m_primitiveType;
}


////////////////////////////////////////////////////////////
FloatRect VertexArray::getBounds() const
{
    if (!m_vertices.empty())
    {
        float left   = m_vertices[0].position.x;
        float top    = m_vertices[0].position.y;
        float right  = m_vertices[0].position.x;
        float bottom = m_vertices[0].position.y;

        for (std::size_t i = 1; i < m_vertices.size(); ++i)
        {
            Vector2f position = m_vertices[i].position;

            // Update left and right
            if (position.x < left)
                left = position.x;
            else if (position.x > right)
                right = position.x;

            // Update top and bottom
            if (position.y < top)
                top = position.y;
            else if (position.y > bottom)
                bottom = position.y;
        }

        return FloatRect(left, top, right - left, bottom - top);
    }
    else
    {
        // Array is empty
        return FloatRect();
    }
}


////////////////////////////////////////////////////////////
void VertexArray::draw(RenderTarget& target, RenderStates states) const
{
    if (!m_vertices.empty())
        target.draw(m_vertices.data(), m_vertices.size(), 
                m_primitiveType, states);
}

} // namespace xwc


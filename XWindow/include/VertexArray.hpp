/*
 * ==========================================================================
 *
 *       Filename:  VertexArray.hpp
 *
 *    Description:  VertexArray class declaration 
 *
 *        Version:  1.0
 *        Created:  26/01/22 14:23:39
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
#ifndef VERTEXARRAY_HPP
#define VERTEXARRAY_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
//#include <SFML/Graphics/Export.hpp>
#include "Vertex.hpp"
//#include "PrimitiveType.hpp"
#include "Rect.hpp"
#include "Drawable.hpp"
#include <vector>


namespace xwc
{
////////////////////////////////////////////////////////////
/// \brief Define a set of one or more 2D primitives
///
////////////////////////////////////////////////////////////
class VertexArray : public Drawable
{
public:

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// Creates an empty vertex array.
    ///
    ////////////////////////////////////////////////////////////
    VertexArray();

    ////////////////////////////////////////////////////////////
    /// \brief Construct the vertex array with a type and an initial 
    ///             number of vertices
    ///
    /// \param type        Type of primitives
    /// \param vertexCount Initial number of vertices in the array
    ///
    ////////////////////////////////////////////////////////////
    explicit VertexArray(PrimitiveType type, std::size_t vertexCount = 0);

    ////////////////////////////////////////////////////////////
    /// \brief Return the vertex count
    ///
    /// \return Number of vertices in the array
    ///
    ////////////////////////////////////////////////////////////
    std::size_t getVertexCount() const;

    ////////////////////////////////////////////////////////////
    /// \brief Get a read-write access to a vertex by its index
    ///
    /// This function doesn't check \a index, it must be in range
    /// [0, getVertexCount() - 1]. The behavior is undefined
    /// otherwise.
    ///
    /// \param index Index of the vertex to get
    ///
    /// \return Reference to the index-th vertex
    ///
    /// \see getVertexCount
    ///
    ////////////////////////////////////////////////////////////
    Vertex& operator [](std::size_t index);

    ////////////////////////////////////////////////////////////
    /// \brief Get a read-only access to a vertex by its index
    ///
    /// This function doesn't check \a index, it must be in range
    /// [0, getVertexCount() - 1]. The behavior is undefined
    /// otherwise.
    ///
    /// \param index Index of the vertex to get
    ///
    /// \return Const reference to the index-th vertex
    ///
    /// \see getVertexCount
    ///
    ////////////////////////////////////////////////////////////
    const Vertex& operator [](std::size_t index) const;

    ////////////////////////////////////////////////////////////
    /// \brief Clear the vertex array
    ///
    /// This function removes all the vertices from the array.
    /// It doesn't deallocate the corresponding memory, so that
    /// adding new vertices after clearing doesn't involve
    /// reallocating all the memory.
    ///
    ////////////////////////////////////////////////////////////
    void clear();

    ////////////////////////////////////////////////////////////
    /// \brief Resize the vertex array
    ///
    /// If \a vertexCount is greater than the current size, the previous
    /// vertices are kept and new (default-constructed) vertices are
    /// added.
    /// If \a vertexCount is less than the current size, existing vertices
    /// are removed from the array.
    ///
    /// \param vertexCount New size of the array (number of vertices)
    ///
    ////////////////////////////////////////////////////////////
    void resize(std::size_t vertexCount);

    ////////////////////////////////////////////////////////////
    /// \brief Add a vertex to the array
    ///
    /// \param vertex Vertex to add
    ///
    ////////////////////////////////////////////////////////////
    void append(const Vertex& vertex);

    ////////////////////////////////////////////////////////////
    /// \brief Set the type of primitives to draw
    ///
    /// This function defines how the vertices must be interpreted
    /// when it's time to draw them:
    /// \li As points
    /// \li As lines
    /// \li As triangles
    /// The default primitive type is xwc::Points.
    ///
    /// \param type Type of primitive
    ///
    ////////////////////////////////////////////////////////////
    void setPrimitiveType(PrimitiveType type);

    ////////////////////////////////////////////////////////////
    /// \brief Get the type of primitives drawn by the vertex array
    ///
    /// \return Primitive type
    ///
    ////////////////////////////////////////////////////////////
    PrimitiveType getPrimitiveType() const;

    ////////////////////////////////////////////////////////////
    /// \brief Compute the bounding rectangle of the vertex array
    ///
    /// This function returns the minimal axis-aligned rectangle
    /// that contains all the vertices of the array.
    ///
    /// \return Bounding rectangle of the vertex array
    ///
    ////////////////////////////////////////////////////////////
    FloatRect getBounds() const;

private:

    ////////////////////////////////////////////////////////////
    /// \brief Draw the vertex array to a render target
    ///
    /// \param target Render target to draw to
    /// \param states Current render states
    ///
    ////////////////////////////////////////////////////////////
    void draw(RenderTarget& target, RenderStates states) const override;

private:

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    std::vector<Vertex> m_vertices;      //!< Vertices contained in the array
    PrimitiveType       m_primitiveType; //!< Type of primitives to draw
};

} // namespace xwc


#endif // _VERTEXARRAY_HPP


////////////////////////////////////////////////////////////
/// \class xwc::VertexArray
/// \ingroup graphics
///
/// xwc::VertexArray is a very simple wrapper around a dynamic
/// array of vertices and a primitives type.
///
/// It inherits xwc::Drawable, but unlike other drawables it
/// is not tranxwcormable.
///
/// Example:
/// \code
/// xwc::VertexArray lines(xwc::LineStrip, 4);
/// lines[0].position = xwc::Vector2f(10, 0);
/// lines[1].position = xwc::Vector2f(20, 0);
/// lines[2].position = xwc::Vector2f(30, 5);
/// lines[3].position = xwc::Vector2f(40, 2);
///
/// window.draw(lines);
/// \endcode
///
/// \see xwc::Vertex
///
////////////////////////////////////////////////////////////

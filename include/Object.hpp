/** @file Object.hpp
 *  @brief Sets up an OpenGL camera..
 *  
 *  More...
 *
 *  @author Mike
 *  @bug No known bugs.
 */
#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <glad/glad.h>

#include <vector>
#include <string>

#include "Shader.hpp"
#include "VertexBufferLayout.hpp"
#include "Transform.hpp"
#include "Geometry.hpp"

#include "glm/vec3.hpp"
#include "glm/gtc/matrix_transform.hpp"

// Purpose:
// An abstraction to create multiple objects
//
//
class Object{
public:
    // Object Constructor
    Object();
    // Object destructor
    ~Object();
    // How to draw the object
    virtual void Render();
protected: // Classes that inherit from Object are intended to be overridden.

    // Helper method for when we are ready to draw or update our object
    void Bind();
    // For now we have one buffer per object.
    VertexBufferLayout m_vertexBufferLayout;
    
    // Store the objects Geometry
    Geometry m_geometry;
};


#endif

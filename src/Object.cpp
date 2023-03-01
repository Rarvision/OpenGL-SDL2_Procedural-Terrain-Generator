#include "Object.hpp"
#include "Camera.hpp"
#include "Error.hpp"


Object::Object(){
}

Object::~Object(){
    
}

// Bind everything we need in our object
// Generally this is called in update() and render()
// before we do any actual work with our object
void Object::Bind(){
        // Make sure we are updating the correct 'buffers'
        m_vertexBufferLayout.Bind();
}

// Render our geometry
void Object::Render(){
    // Call our helper function to just bind everything
    Bind();
    //Render data
    glDrawElements(GL_TRIANGLES,
                   m_geometry.GetIndicesSize(), // The number of indices, not triangles.
                   GL_UNSIGNED_INT,             // Make sure the data type matches
                        nullptr);               // Offset pointer to the data. 
                                                // nullptr because we are currently bound
}


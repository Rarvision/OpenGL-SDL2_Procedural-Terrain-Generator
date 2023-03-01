/** @file Terrain.hpp
 *  @brief Create a terrain
 *  
 *  More...
 *
 *  @author Mike
 *  @bug No known bugs.
 */
#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include "VertexBufferLayout.hpp"
#include "Shader.hpp"
#include "Object.hpp"

#include <vector>
#include <string>

class Terrain : public Object {
public:
    // Constructor
    Terrain (unsigned int xSegs, unsigned int zSegs);
    // Destructor
    ~Terrain ();
    // override the initialization routine.
    void Init();

private:
    // data
    unsigned int m_xSegments;
    unsigned int m_zSegments;
    unsigned int m_size;

    // Store the height in a multidimensional array
    float* m_heightData;
    float m_maxHeight;
    
};

#endif

#include "Geometry.hpp"
#include <assert.h>
#include <iostream>
#include "glm/vec3.hpp"
#include "glm/vec2.hpp"
#include "glm/glm.hpp"

// Constructor
Geometry::Geometry(){

}

// Destructor
Geometry::~Geometry(){

}


// Adds a vertex and associated color coordinate.
// Will also add a normal
void Geometry::AddVertex(float x, float y, float z, float r, float g, float b, float nx, float ny, float nz){
	m_vertexPositions.push_back(x);
	m_vertexPositions.push_back(y);
	m_vertexPositions.push_back(z);
	
    	// Add vertex color
	m_colors.push_back(r);
	m_colors.push_back(g);
	m_colors.push_back(b);
	
	// Push back placeholders for m_normals
	m_normals.push_back(nx);
	m_normals.push_back(ny);
	m_normals.push_back(nz);
}

// Allows for adding one index at a time manually if 
// you know which vertices are needed to make a triangle.
void Geometry::AddIndex(unsigned int i){
    // Simple bounds check to make sure a valid index is added.
    if(i >= 0 && i <= m_vertexPositions.size()/3){
        m_indices.push_back(i);
    }else{
        std::cout << "(Geometry.cpp) ERROR, invalid index\n";
    }
}

// Retrieves a pointer to our data.
float* Geometry::GetBufferDataPtr(){
	return m_bufferData.data();
}

// Retrieves the size of our data 
unsigned int Geometry::GetBufferDataSize(){
	return m_bufferData.size();
}

// Retrieves the number of bytes of our data
unsigned int Geometry::GetBufferSizeInBytes(){
	return m_bufferData.size()*sizeof(float);
}

// Create all data
void Geometry::Gen(){
	assert(m_vertexPositions.size() == m_colors.size());

	int coordsPos =0;
	for(int i =0; i < m_vertexPositions.size()/3; ++i){
		// vertices
		m_bufferData.push_back(m_vertexPositions[i*3+ 0]);
		m_bufferData.push_back(m_vertexPositions[i*3+ 1]);
		m_bufferData.push_back(m_vertexPositions[i*3+ 2]);
		
		// colors
		m_bufferData.push_back(m_colors[i*3+ 0]);
		m_bufferData.push_back(m_colors[i*3+ 1]);
		m_bufferData.push_back(m_colors[i*3+ 2]);
		
		// normals
		m_bufferData.push_back(m_normals[i*3+ 0]);
		m_bufferData.push_back(m_normals[i*3+ 1]);
		m_bufferData.push_back(m_normals[i*3+ 2]);
	}
	
}

// Retrieves the number of indices that we have.
unsigned int Geometry::GetIndicesSize(){
	return m_indices.size();
}

// Retrieves a pointer to the indices that we have
unsigned int* Geometry::GetIndicesDataPtr(){
	return m_indices.data();
}


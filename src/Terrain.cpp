#include "Terrain.hpp"
#include "HeightGenerator.hpp"
#include "BiomeGenerator.hpp"
#include "NormalGenerator.hpp"

#include <iostream>

// Constructor for our object
// Calls the initialization method
Terrain::Terrain(unsigned int xSegs, unsigned int zSegs) : 
                m_xSegments(xSegs), m_zSegments(zSegs), m_maxHeight(0.0f) {
    std::cout << "(Terrain.cpp) Constructor called \n";

    // Create a height generator
    HeightGenerator heightGenerator(xSegs, zSegs, (int)time(nullptr));
    
    // Set the height data for the image
   
    // Create height data
    m_heightData = new float[m_xSegments*m_zSegments];

    for(unsigned int z=0; z<m_zSegments; z++) {
    	for(unsigned int x=0; x<m_xSegments; x++) {
    		float height = std::max(heightGenerator.GenerateHeight(x,z), -0.4f);
		m_heightData[x+z*m_xSegments] = height;
		m_maxHeight = std::max(m_maxHeight, height);
	}
    }

    Init();
}

// Destructor
Terrain::~Terrain(){
    // Delete our allocatted higheithmap data
    if(m_heightData!=nullptr){
        delete m_heightData;
    }
}


// Creates a grid of segments
// This article has a pretty handy illustration here:
// http://www.learnopengles.com/wordpress/wp-content/uploads/2012/05/vbo.png
// of what we are trying to do.
void Terrain::Init(){
    // Create the initial grid of vertices.

    // Initialize the biome generator;
    BiomeGenerator biomeGenerator(m_maxHeight);
    NormalGenerator normalGenerator;
    // Build grid of vertices! 
    for(unsigned int z=0; z<m_zSegments; ++z) {
   	for(unsigned int x=0; x<m_xSegments; ++x) {
   		float height = m_heightData[x+z*m_xSegments];
   		glm::vec3 color = biomeGenerator.GetBiomeColor(height);
   		glm::vec3 normal = normalGenerator.GetSmoothNormal((int)x, (int)z, m_heightData, m_xSegments, m_zSegments);
		m_geometry.AddVertex(x, height, z, color.r/255, color.g/255, color.b/255, normal.x, normal.y, normal.z);
	} 
    }


    // Figure out which indices make up each triangle
    // By writing out a few of the indices you can figure out
    // the pattern here. Note there is an offset.
    
    // Build triangle strip
    for(unsigned int z=0; z<m_zSegments-1; ++z) {
    	for(unsigned int x=0; x<m_xSegments-1; ++x) {
		m_geometry.AddIndex(x+(z*m_zSegments));
		m_geometry.AddIndex(x+(z*m_zSegments)+m_xSegments);
		m_geometry.AddIndex(x+(z*m_zSegments+1));

		m_geometry.AddIndex(x+(z*m_zSegments)+1);
                m_geometry.AddIndex(x+(z*m_zSegments)+m_xSegments);
                m_geometry.AddIndex(x+(z*m_zSegments)+m_xSegments+1);
	}
    }


   // Finally generate a simple 'array of bytes' that contains
   // everything for our buffer to work with.
   m_geometry.Gen();  
   // Create a buffer and set the stride of information
   m_vertexBufferLayout.CreateColorBufferLayout(m_geometry.GetBufferDataSize(),
                                        m_geometry.GetIndicesSize(),
                                        m_geometry.GetBufferDataPtr(),
                                        m_geometry.GetIndicesDataPtr());
                                        
}


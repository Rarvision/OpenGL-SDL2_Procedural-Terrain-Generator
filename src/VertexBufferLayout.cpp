#include "VertexBufferLayout.hpp"
#include <iostream>


VertexBufferLayout::VertexBufferLayout(){
}

VertexBufferLayout::~VertexBufferLayout(){
    // Delete our buffers that we have previously allocated
    // http://docs.gl/gl3/glDeleteBuffers
    glDeleteBuffers(1,&m_vertexPositionBuffer);
    glDeleteBuffers(1,&m_indexBufferObject);
}


void VertexBufferLayout::Bind(){
    // Bind to our vertex array
    glBindVertexArray(m_VAOId);
    // Bind to our vertex information
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexPositionBuffer);
    // Bind to the elements we are drawing
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferObject);
}

// Note: Calling Unbind is rarely done, if you need
// to draw something else then just bind to new buffer.
void VertexBufferLayout::Unbind(){
        // Bind to our vertex array
        glBindVertexArray(0);
        // Bind to our vertex information
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // Bind to the elements we are drawing
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


void VertexBufferLayout::CreatePositionBufferLayout(unsigned int vcount,unsigned int icount, float* vdata, unsigned int* idata ){
        // Because this layout is only
        m_stride = 3;
        
        static_assert(sizeof(GLfloat)==sizeof(float),
            "GLFloat and gloat are not the same size on this architecture");
       
        // VertexArrays
        glGenVertexArrays(1, &m_VAOId);

        glBindVertexArray(m_VAOId);

        glGenBuffers(1, &m_vertexPositionBuffer); 
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexPositionBuffer);
        glBufferData(GL_ARRAY_BUFFER, vcount*sizeof(float), vdata, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(  0,   // Attribute 0, which will match layout in shader
                                3,   // size (Number of components (2=x,y)  (3=x,y,z), etc.)
                                GL_FLOAT, // Type of data
                                GL_FALSE, // Is the data normalized
                                sizeof(float)*m_stride, // Stride - Amount of bytes between each vertex.
                                                // If we only have vertex data, then
                                                // this is sizeof(float)*3 (or as a
                                                // shortcut 0).
                                                // That means our vertices(or whatever data) 
                                                // is tightly packed, one after the other.
                                                // If we add in vertex color information(3 more floats), 
                                                // then this becomes 6, as we
                                                // move 6*sizeof(float)
                                                // to get to the next chunk of data.
                                                // If we have normals, then we
                                                // need to jump 3*sizeof(GL_FLOAT)
                                                // bytes to get to our next vertex.
                                0               // Pointer to the starting point of our
                                                // data. If we are just grabbing vertices, 
                                                // this is 0. But if we have
                                                // some other attribute,
                                                // (stored in the same data structure),
                                                // this may vary if the very
                                                // first element is some different attribute.
                                                // If we had some data after
                                                // (say normals), then we 
                                                // would have an offset of 
                                                // 3*sizeof(GL_FLOAT) for example
        );

        static_assert(sizeof(unsigned int)==sizeof(GLuint),"Gluint not same size!");

        glGenBuffers(1, &m_indexBufferObject);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferObject);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, icount*sizeof(unsigned int), idata,GL_STATIC_DRAW);
    }

// positions: x,y,z
// colors: r,g,b
// normals:  nx,ny,nz
void VertexBufferLayout::CreateColorBufferLayout(unsigned int vcount,unsigned int icount, float* vdata, unsigned int* idata ) {
	m_stride = 9;
	static_assert(sizeof(GLfloat)==sizeof(float), "GLFloat and gloat are not the same size on this architecture");
       
        glGenVertexArrays(1, &m_VAOId);
        glBindVertexArray(m_VAOId);

        glGenBuffers(1, &m_vertexPositionBuffer); 
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexPositionBuffer);
        glBufferData(GL_ARRAY_BUFFER, vcount*sizeof(float), vdata, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*m_stride, 0);

        // Add three floats for color coordinates
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1,3,GL_FLOAT, GL_FALSE,sizeof(float)*m_stride,(char*)(sizeof(float)*3));

        // Add three floats for normal coordinates
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2,3,GL_FLOAT, GL_TRUE,sizeof(float)*m_stride,(char*)(sizeof(float)*6));
        
        static_assert(sizeof(unsigned int)==sizeof(GLuint),"Gluint not same size!");

	// Setup an index buffer
        glGenBuffers(1, &m_indexBufferObject);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferObject);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, icount*sizeof(unsigned int), idata,GL_STATIC_DRAW);
}


// positions: x,y,z
// normals:  x,y,z
// texcoords: s,t
// tangent: t_x,t_y,t_z
// bitangent b_x,b_y,b_z
void VertexBufferLayout::CreateTextureBufferLayout(unsigned int vcount,unsigned int icount, float* vdata, unsigned int* idata ){
		m_stride = 14;
        
        
        static_assert(sizeof(GLfloat)==sizeof(float), "GLFloat and gloat are not the same size on this architecture");
       
        glGenVertexArrays(1, &m_VAOId);
        glBindVertexArray(m_VAOId);
        
        glGenBuffers(1, &m_vertexPositionBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexPositionBuffer);
        glBufferData(GL_ARRAY_BUFFER, vcount*sizeof(float), vdata, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*m_stride, 0);

        // Add three floats for normal coordinates
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1,3,GL_FLOAT, GL_FALSE,sizeof(float)*m_stride,(char*)(sizeof(float)*3));

        // Add two floats for texture coordinates
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2,2,GL_FLOAT, GL_FALSE,sizeof(float)*m_stride,(char*)(sizeof(float)*6));

        // Add three floats for tangent coordinates
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3,3,GL_FLOAT, GL_FALSE,sizeof(float)*m_stride,(char*)(sizeof(float)*8));

        // Add three floats for bi-tangent coordinates
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4,3,GL_FLOAT, GL_FALSE,sizeof(float)*m_stride,(char*)(sizeof(float)*11));
        
        static_assert(sizeof(unsigned int)==sizeof(GLuint),"Gluint not same size!");
        
        glGenBuffers(1, &m_indexBufferObject);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferObject);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, icount*sizeof(unsigned int), idata,GL_STATIC_DRAW);
    }

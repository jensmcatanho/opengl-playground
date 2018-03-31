#include "utils/Cube.h"
#include "utils/utils.h"

namespace utils {

Cube::Cube() :
	Mesh(0.0f, 0.0f, 0.0f) {
	
	GenerateData(1.0f);
}

Cube::Cube(GLfloat x, GLfloat y, GLfloat z, GLfloat size) :
	Mesh(x, y, z) {
	
	GenerateData(size);
}

Cube::Cube(glm::vec3 position, GLfloat size) :
	Mesh(position) {
	
	GenerateData(size);
}

void Cube::GenerateData(GLfloat size) {
	GLuint vertices_count = 8;
	m_NumIndices = 36;
	m_Data.resize(vertices_count * 3);
	m_Indices.resize(m_NumIndices);

	std::vector<GLfloat>::iterator d_iterator = m_Data.begin();
	
	*d_iterator++ = 0.0f; *d_iterator++ = 0.0f; *d_iterator++ =  0.0f;
	*d_iterator++ = size; *d_iterator++ = 0.0f; *d_iterator++ =  0.0f;
	*d_iterator++ = size; *d_iterator++ = size; *d_iterator++ =  0.0f;
	*d_iterator++ = 0.0f; *d_iterator++ = size; *d_iterator++ =  0.0f;
	*d_iterator++ = 0.0f; *d_iterator++ = 0.0f; *d_iterator++ = -size;
	*d_iterator++ = size; *d_iterator++ = 0.0f; *d_iterator++ = -size;
	*d_iterator++ = size; *d_iterator++ = size; *d_iterator++ = -size;
	*d_iterator++ = 0.0f; *d_iterator++ = size; *d_iterator++ = -size;

	std::vector<GLushort>::iterator i_iterator = m_Indices.begin();

	// Front face
	*i_iterator++ = 0; *i_iterator++ = 1; *i_iterator++ = 2;
	*i_iterator++ = 2; *i_iterator++ = 3; *i_iterator++ = 0;
	// Right face
	*i_iterator++ = 1; *i_iterator++ = 5; *i_iterator++ = 6;
	*i_iterator++ = 6; *i_iterator++ = 2; *i_iterator++ = 1;
	// Back face
	*i_iterator++ = 7; *i_iterator++ = 6; *i_iterator++ = 5;
	*i_iterator++ = 5; *i_iterator++ = 4; *i_iterator++ = 7;
	// Left face
	*i_iterator++ = 4; *i_iterator++ = 0; *i_iterator++ = 3;
	*i_iterator++ = 3; *i_iterator++ = 7; *i_iterator++ = 4;
	// Bottom face
	*i_iterator++ = 4; *i_iterator++ = 5; *i_iterator++ = 1;
	*i_iterator++ = 1; *i_iterator++ = 0; *i_iterator++ = 4;
	// Top face
	*i_iterator++ = 3; *i_iterator++ = 2; *i_iterator++ = 6;
	*i_iterator++ = 6; *i_iterator++ = 7; *i_iterator++ = 3;
}

}
/*
-----------------------------------------------------------------------------
The MIT License (MIT)

Copyright (c) 2018 Jean Michel Catanho

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
-----------------------------------------------------------------------------
*/
#include "utils/Cube.h"
#include "utils/utils.h"

namespace utils {

Cube::Cube() :
	Mesh(0.0f, 0.0f, 0.0f),
	m_SideSize(1.0f) {
	
	GenerateData();
}

Cube::Cube(GLfloat x, GLfloat y, GLfloat z, GLfloat size) :
	Mesh(x, y, z),
	m_SideSize(1.0f) {
	
	GenerateData();
}

Cube::Cube(glm::vec3 position, GLfloat size) :
	Mesh(position),
	m_SideSize(1.0f) {
	
	GenerateData();
}

void Cube::GenerateData() {
	GLuint vertices_count = 8;
	GLuint texcoords_count = 8;
	m_NumIndices = 36;
	m_Data.resize(vertices_count * 3 + texcoords_count * 2);
	m_Indices.resize(m_NumIndices);

	std::vector<GLfloat>::iterator d_iterator = m_Data.begin();
	
	*d_iterator++ = 0.0f; *d_iterator++ = 0.0f; *d_iterator++ =  0.0f;
	*d_iterator++ = 0.0f; *d_iterator++ = 0.0f;
	*d_iterator++ = m_SideSize; *d_iterator++ = 0.0f; *d_iterator++ = 0.0f;
	*d_iterator++ = 1.0f; *d_iterator++ = 0.0f;
	*d_iterator++ = m_SideSize; *d_iterator++ = m_SideSize; *d_iterator++ = 0.0f;
	*d_iterator++ = 1.0f; *d_iterator++ = 1.0f;
	*d_iterator++ = 0.0f; *d_iterator++ = m_SideSize; *d_iterator++ = 0.0f;
	*d_iterator++ = 0.0f; *d_iterator++ = 1.0f;
	*d_iterator++ = 0.0f; *d_iterator++ = 0.0f; *d_iterator++ = -m_SideSize;
	*d_iterator++ = 0.0f; *d_iterator++ = 0.0f;
	*d_iterator++ = m_SideSize; *d_iterator++ = 0.0f; *d_iterator++ = -m_SideSize;
	*d_iterator++ = 1.0f; *d_iterator++ = 0.0f;
	*d_iterator++ = m_SideSize; *d_iterator++ = m_SideSize; *d_iterator++ = -m_SideSize;
	*d_iterator++ = 1.0f; *d_iterator++ = 1.0f;
	*d_iterator++ = 0.0f; *d_iterator++ = m_SideSize; *d_iterator++ = -m_SideSize;
	*d_iterator++ = 0.0f; *d_iterator++ = 1.0f;

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
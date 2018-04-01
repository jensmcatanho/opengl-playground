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
#include "utils/Mesh.h"
#include "utils/utils.h"

#include <glm/gtc/type_ptr.hpp>

namespace utils {

Mesh::Mesh() :
	m_Position(0.0f, 0.0f, 0.0f) {
	
}

Mesh::Mesh(GLfloat x, GLfloat y, GLfloat z) :
	m_Position(x, y, z) {

}

Mesh::Mesh(glm::vec3 position) :
	m_Position(position) {

}

Mesh::~Mesh() {
	glDeleteProgram(m_ShaderProgram);
	glDeleteVertexArrays(1, &m_VAOHandler);
}

void Mesh::Init(const GLchar *vertex_path, const GLchar *fragment_path) {
	glGenVertexArrays(1, &m_VAOHandler);
	glBindVertexArray(m_VAOHandler);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, m_Data.size() * sizeof(GLfloat), &m_Data.front(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *)0);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));

	GLuint ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(GLushort), &m_Indices.front(), GL_STATIC_DRAW);

	m_ShaderProgram = loadShaders(vertex_path, fragment_path);

	glBindVertexArray(0);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);

	m_Data.clear();
	m_Indices.clear();
	m_Data.shrink_to_fit();
	m_Indices.shrink_to_fit();
}

void Mesh::Draw(glm::mat4 vp_matrix) const {
	glBindVertexArray(m_VAOHandler);
	glUseProgram(m_ShaderProgram);

	if (m_DiffuseMap) {
		m_DiffuseMap->Bind(0);
		glUniform1i(6, 0);
	}

	if (m_DiffuseMap) {
		m_DiffuseMap->Bind(1);
		glUniform1i(7, 0);
	}

	glm::mat4 model_matrix;
	model_matrix = glm::translate(model_matrix, m_Position);
	glm::mat4 mvp_matrix = vp_matrix * model_matrix;

	glUniformMatrix4fv(4, 1, GL_FALSE, glm::value_ptr(mvp_matrix));
	glDrawElements(GL_TRIANGLES, m_NumIndices, GL_UNSIGNED_SHORT, (void *)0);
}

}
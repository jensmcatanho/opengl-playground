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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)0);

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

	glm::mat4 model_matrix;
	model_matrix = glm::translate(model_matrix, m_Position);
	glm::mat4 mvp_matrix = vp_matrix * model_matrix;

	glUniformMatrix4fv(1, 1, GL_FALSE, glm::value_ptr(mvp_matrix));
	glDrawElements(GL_TRIANGLES, m_NumIndices, GL_UNSIGNED_SHORT, (void *)0);
}

}
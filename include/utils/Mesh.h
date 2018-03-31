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
#ifndef MESH_H
#define MESH_H

#include "IDrawable.h"

#include <vector>

namespace utils {

class Mesh : public IDrawable {
	public:
		Mesh();

		Mesh(GLfloat, GLfloat, GLfloat);

		Mesh(glm::vec3);

		virtual ~Mesh();

		virtual void Init(const GLchar *, const GLchar *) override;

		virtual void Draw(glm::mat4) const override;

	protected:
		glm::vec3 m_Position;

		std::vector<GLfloat> m_Data;

		std::vector<GLushort> m_Indices;

		GLuint m_NumIndices;

	private:
		GLuint m_ShaderProgram;

		GLuint m_VAOHandler;
};

}

#endif
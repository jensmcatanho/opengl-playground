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
#include "utils/utils.h"

#include <iostream>
#include <fstream>

namespace utils {

std::stringstream readFile(std::string path) {
	std::ifstream file;
	std::stringstream string_stream;

	file.exceptions(std::ifstream::badbit);

	try {
		file.open(path);
		string_stream << file.rdbuf();
		file.close();

	}
	catch (std::ifstream::failure e) {
		std::cerr << "Error while reading the file. (Does the file exist?)" << std::endl;
	}

	return string_stream;
}

GLuint loadShaders(const GLchar *vertex, const GLchar *frag) {
	GLint status;

	std::string vertex_source = readFile(vertex).str();
	const GLchar *vertex_code = const_cast<const GLchar *>(vertex_source.c_str());

	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_code, NULL);
	glCompileShader(vertex_shader);
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &status);

	if (!status) {
		char error_log[512];

		glGetShaderInfoLog(vertex_shader, 512, NULL, error_log);
		std::cout << "========== Vertex shader log ==========" << std::endl;
		std::cout << error_log << std::endl;

		return -1;
	}

	std::string fragment_source = readFile(frag).str();
	const GLchar *fragment_code = const_cast<const GLchar *>(fragment_source.c_str());

	GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_code, NULL);
	glCompileShader(fragment_shader);
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &status);

	if (!status) {
		char error_log[512];

		glGetShaderInfoLog(fragment_shader, 512, NULL, error_log);
		std::cout << "========== Fragment shader log ==========" << std::endl;
		std::cout << error_log << std::endl;

		return -1;
	}

	GLuint shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);

	glBindAttribLocation(shader_program, 0, "a_Position");
	glBindAttribLocation(shader_program, 1, "a_Normal");
	glBindAttribLocation(shader_program, 2, "a_TexCoord");

	glLinkProgram(shader_program);
	glGetProgramiv(shader_program, GL_LINK_STATUS, &status);

	if (!status) {
		char error_log[512];

		glGetProgramInfoLog(shader_program, 512, NULL, error_log);
		std::cout << "========== Shader linking log ==========" << std::endl;
		std::cout << error_log << std::endl;

		return -1;
	}

	glDetachShader(shader_program, vertex_shader);
	glDeleteShader(vertex_shader);

	glDetachShader(shader_program, fragment_shader);
	glDeleteShader(fragment_shader);

	return shader_program;
}

}
#include <fstream>
#include <iostream>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

std::stringstream readFile(std::string);
GLuint loadShaders(const GLchar *, const GLchar *);

int main() {
	/* GLFW initialization
	 * http://www.glfw.org/docs/latest/index.html
	 */
	if (!glfwInit()) {
		std::cout << "Failed to initialize GLFW." << std::endl;
		return -1;
	}
	std::cout << "GLFW initialized." << std::endl;

	GLFWwindow *window = glfwCreateWindow(1024, 768, "RGB Cube", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

	/* GLEW initialization
	 * http://glew.sourceforge.net/
	 */
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW." << std::endl;
		return -1;
	}
	std::cout << "GLEW initialized." << std::endl;

	/* Enable depth test with less than or equal function.
	 * https://www.khronos.org/opengl/wiki/Depth_Test
	 */
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	std::cout << "Depth test enabled." << std::endl;

	/* Enable back-face culling.
	 * https://www.khronos.org/opengl/wiki/Face_Culling
	 */
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	std::cout << "Back-face culling enabled." << std::endl;

	glm::vec3 vertices[] = {
		glm::vec3(0.0f, 0.0f,  0.0f),
		glm::vec3(1.0f, 0.0f,  0.0f),
		glm::vec3(1.0f, 1.0f,  0.0f),
		glm::vec3(0.0f, 1.0f,  0.0f),
		glm::vec3(0.0f, 0.0f, -1.0f),
		glm::vec3(0.0f, 1.0f, -1.0f),
		glm::vec3(1.0f, 1.0f, -1.0f),
		glm::vec3(1.0f, 0.0f, -1.0f)
	};

	GLushort indices[] = {
		// Front face
		0, 1, 2,
		2, 3, 0,
		// Right face
		1, 5, 6,
		6, 2, 1,
		// Back face
		7, 6, 5,
		5, 4, 7,
		// Left face
		4, 0, 3,
		3, 7, 4,
		// Bottom face
		4, 5, 1,
		1, 0, 4,
		// Top face
		3, 2, 6,
		6, 7, 3
	};

	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)0);

	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	GLuint shaderProgram = loadShaders("cube.vert", "cube.frag");
	glUseProgram(shaderProgram);

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, (void *)0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteProgram(shaderProgram);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

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
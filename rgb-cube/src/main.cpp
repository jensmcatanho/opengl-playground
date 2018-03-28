
#include <iostream>
#include "utils.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

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
	if (!window) {
		std::cout << "Failed to create GLFW window." << std::endl;
		return -1;
	}
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
	std::cout << "GLEW initialized. OpenGL " << glGetString(GL_VERSION) << std::endl;

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

	GLuint shaderProgram = loadShaders("resources/cube.vert", "resources/cube.frag");
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
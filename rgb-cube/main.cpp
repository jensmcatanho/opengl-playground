#include "utils/utils.h"

#include <iostream>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

int main() {
	/* GLFW initialization
	 * http://www.glfw.org/docs/latest/index.html
	 */
	utils::Window *window = new utils::Window("RGB Cube", 1024, 768);
	std::shared_ptr<utils::Camera> camera(new utils::Camera(0.0f, 0.0f, 5.0f));
	window->Create(camera);

	/* Enable MSAA.
	 * https://www.khronos.org/opengl/wiki/Multisampling
	 */
	glEnable(GL_MULTISAMPLE);

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

	std::shared_ptr<utils::Mesh> cube(new utils::Cube());
	cube->Init("resources/cube.vert", "resources/cube.frag");

	// Prepare rendering.
	GLfloat delta_time;
	GLfloat current_frame = 0.0f;
	GLfloat last_frame = 0.0f;

	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	while (!glfwWindowShouldClose(window->GetPointer())) {
		current_frame = glfwGetTime();
		delta_time = current_frame - last_frame;
		last_frame = current_frame;

		window->DisplayFPS();
		window->ProcessInput(delta_time);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 projection_matrix = window->m_Camera->ProjectionMatrix(window->m_AspectRatio);
		glm::mat4 view_matrix = window->m_Camera->ViewMatrix();
		cube->Draw(projection_matrix * view_matrix);

		window->SwapBuffers();
		window->PollEvents();
	}

	window->Close();
	return 0;
}
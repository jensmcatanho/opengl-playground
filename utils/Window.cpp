/*
-----------------------------------------------------------------------------
The MIT License (MIT)

Copyright (c) 2016 Jean Michel Catanho

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
#include "utils/Window.h"

#include <iostream>
#include <sstream>

namespace utils {

void process_input(GLFWwindow *window, std::shared_ptr<Camera> camera, GLfloat deltaTime);
void resize_callback(GLFWwindow *window, int width, int height);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

std::shared_ptr<Camera> callbackCamera;
GLboolean firstMouse = true;
GLfloat lastX = 1024 / 2.0f;
GLfloat lastY = 768 / 2.0f;

Window::Window(std::string title, int width, int height) :
	m_Title(title),
	m_Width(width),
	m_Height(height),
	m_AspectRatio(static_cast<float>(width / height)) {
}

bool Window::Create(std::shared_ptr<Camera> camera) {
	callbackCamera = camera;
	m_Camera = camera;

	if (!glfwInit()) {
		std::cout << "Failed to initialize GLFW." << std::endl;
		return false;
	}
	std::cout << "GLFW initialized." << std::endl;

	glfwWindowHint(GLFW_SAMPLES, 4);
	m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(m_Window);

	glfwSetWindowUserPointer(m_Window, this);
	glfwSetFramebufferSizeCallback(m_Window, resize_callback);
	glfwSetCursorPosCallback(m_Window, mouse_callback);
	glfwSetScrollCallback(m_Window, scroll_callback);
	glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	return true;
}

void Window::ProcessInput(GLfloat deltaTime) {
	process_input(m_Window, m_Camera, deltaTime);
}

void Window::DisplayFPS() {
	static GLfloat fps = 0.0f;
	static GLfloat last_time = 0.0f;
	GLfloat current_time = glfwGetTime();

	++fps;

	if (current_time - last_time > 1.0f) {
		last_time = current_time;

		std::stringstream ss;
		ss << m_Title << " - " << fps << " FPS" << std::endl;
		glfwSetWindowTitle(m_Window, ss.str().c_str());
		fps = 0;
	}
}

void process_input(GLFWwindow *window, std::shared_ptr<Camera> camera, GLfloat deltaTime) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	// W - Move forward
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->ProcessMovement(FORWARD, deltaTime);

	// S - Move backward
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->ProcessMovement(BACKWARD, deltaTime);

	// A - Move left
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->ProcessMovement(LEFT, deltaTime);

	// D - Move right
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->ProcessMovement(RIGHT, deltaTime);
}

void resize_callback(GLFWwindow *window, int width, int height) {
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	callbackCamera->ProcessRotation(xoffset, yoffset);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
	callbackCamera->ProcessZoom(yoffset);
}

}
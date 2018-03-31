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
#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace utils {

/**
 * Camera's default values.
 */
enum Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 5.0f;
const GLfloat SENSITIVITY = 0.1f;
const GLfloat ZOOM = 45.0f;

class Camera {
	public:
		/**
		 * Standard constructor.
		 * @param position Camera's location in world coordinates.
		 */
		Camera(glm::vec3 position);

		/**
		* Standard constructor.
		* @param position Camera's location in world coordinates.
		*/
		Camera(GLfloat x, GLfloat y, GLfloat z);

		/**
		 * Processes the camera's movement.
		 * @param direction Moving direction.
		 * @param delta_time Time in seconds it took to complete the last frame.
		 */
		void ProcessMovement(Movement direction, GLfloat delta_time);

		/**
		 * Processes the camera's rotation.
		 * @param x_offset Horizontal offset.
		 * @param y_offset Vertical offset.
		 */
		void ProcessRotation(GLfloat x_offset, GLfloat y_offset);

		/**
		 * Processes the camera's zoom.
		 * @param y_offset 
		 */
		void ProcessZoom(GLfloat y_offset);

		/**
		 * Set the camera's position in world coordinates.
		 * @param position Target position.
		 */
		void SetPosition(glm::vec3 position);

		/**
		 * Set the direction the camera is looking at.
		 * @param target Target direction.
		 */
		void LookAt(glm::vec3 target);

		/**
		 * Computes the corresponding view matrix.
		 * @return The view matrix.
		 */
		glm::mat4 ViewMatrix() const;

		/**
		 * Computes the corresponding projection matrix.
		 * @return The projection matrix.
		 */
		glm::mat4 ProjectionMatrix(GLfloat) const;

		/**
		 * 
		 * @return 
		 */
		glm::vec3 GetPosition() const;

		/**
		 *
		 */
		GLfloat m_Zoom;

	private:
		/**
		 *
		 */
		void UpdateVectors();

		/**
		 * Location in world coordinates.
		 */
		glm::vec3 m_Position;

		/**
		 *
		 */
		glm::vec3 m_U;

		/**
		 *
		 */
		glm::vec3 m_V;

		/**
		 *
		 */
		glm::vec3 m_W;

		/**
		 *
		 */
		glm::vec3 m_WorldUp;

		/**
		 * Yaw angle.
		 */
		GLfloat m_Yaw;

		/**
		 * Pitch angle.
		 */
		GLfloat m_Pitch;

		/**
		 * Camera's movement speed.
		 */
		GLfloat m_MovementSpeed;

		/**
		 * Mouse sensitivity.
		 */
		GLfloat m_Sensitivity;
};

inline glm::mat4 Camera::ViewMatrix() const {
	return glm::lookAt(m_Position, m_Position - m_W, m_V);
}

inline glm::mat4 Camera::ProjectionMatrix(GLfloat aspect_ratio) const {
	return glm::perspective(static_cast<double>(glm::radians(m_Zoom)), static_cast<double>(aspect_ratio), 0.0001, 10000.0);
}

inline glm::vec3 Camera::GetPosition() const {
	return m_Position;
}

inline void Camera::SetPosition(glm::vec3 position) {
	m_Position = position;
}

}

#endif
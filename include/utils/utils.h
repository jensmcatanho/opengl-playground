#ifndef UTILS_H
#define UTILS_H

#include <sstream>
#include <GL/glew.h>

#include "Camera.h"
#include "Cube.h"
#include "Mesh.h"
#include "Window.h"

namespace utils {

std::stringstream readFile(std::string);
GLuint loadShaders(const GLchar *, const GLchar *);

}
#endif
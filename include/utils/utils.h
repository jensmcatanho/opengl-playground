#ifndef UTILS_H
#define UTILS_H

#include <sstream>
#include <GL/glew.h>

#include "Window.h"

std::stringstream readFile(std::string);

GLuint loadShaders(const GLchar *, const GLchar *);

#endif
#include <windows.h>
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif

#include "GL\glew.h"
#include <gl\gl.h>
#include <gl\GL.h>
#define FREEGLUT_STATIC
#include <GL\glut.h>

GLuint loadShaderPairSrcWithAttribute(const char* vertexSrc,const char* frameSrc, ...);
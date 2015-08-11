#pragma once
#include <windows.h>
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif

#include "GL\glew.h"
#include <gl\gl.h>
#include <gl\GL.h>
#define FREEGLUT_STATIC
#include <GL\glut.h>

enum SHADER_ATTRIBUTE {ATTRIBUTE_VERTEX = 0,ATTRIBUTE_COLOR,ATTRIBUTE_NORMAL,ATTRIBUTE_TEXTURE0,ATTRIBUTE_TEXTURE1,ATTRIBUTE_TEXTURE2,ATTRIBUTE_TEXTURE3,ATTRIBUTE_LAST};
enum PRESET_SHADER {SHADER_IDENTITY = 0,SHADER_FLAT,SHADER_LAST};
GLuint presetShaders[SHADER_LAST];

GLuint loadShaderPairSrcWithAttribute(const char* vertexSrc,const char* frameSrc, ...);

void initPresetShaders();

void usePresetShader(PRESET_SHADER shaderID,...);


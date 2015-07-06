//#include "LoadShaders.h"

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <Windows.h>
#include <gl/GL.h>
#pragma comment(lib,"glew32.lib")

using namespace std;

const int width = 500;
const int height = 300;

enum VAO_IDs {Triangles,NumVAOs};
enum Buffer_IDs {ArrayBuffer,NumBuffers};
enum Attrib_IDs {vPosition = 0};

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

const GLuint NumVertices = 6;

static const GLchar* ReadShader(const char* fileName)
{
	FILE *file;
	fopen_s(&file,fileName,"rb");
	if (file == NULL)
	{
		cout << "open " << *fileName << " failed!" << endl;
		return NULL;
	}
	fseek(file,0,SEEK_END);
	int len = ftell(file);
	fseek(file,0,SEEK_SET);
	GLchar* source = new GLchar[len+1];

	fread(source,1,len,file);
	fclose(file);

	source[len] = 0;
	return const_cast<const GLchar*>(source);
}

GLuint LoadShaders(const char* vertFileName,const char* fragFileName)
{
	GLuint program = glCreateProgram();
	GLuint shader = glCreateShader(GL_VERTEX_SHADER);
	const GLchar* source = ReadShader(vertFileName);
	if (source == NULL)
	{
		return 0;
	}
	glShaderSource(shader,1,&source,NULL);
	glCompileShader(shader);

}

void OnInit()
{
	//set clear color to red
	glClearColor(1,0,0,0);
	glGenVertexArrays(NumVAOs,VAOs);
	glBindVertexArray(VAOs[Triangles]);
	GLfloat vertices[NumVertices][2] = {
		{-0.90,-0.90},
		{0.85,-0.90},
		{-0.90,0.85},
		{0.90,-0.85},
		{0.90,0.90},
		{-0.85,0.90},
	};
	glGenBuffers(NumBuffers,Buffers);
	glBindBuffer(GL_ARRAY_BUFFER,Buffers[ArrayBuffer]);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

	//ShaderInfo shaders[] = {
	//	{GL_VERTEX_SHADER,"triangles.vert"},
	//	{GL_FRAGMENT_SHADER,"triangles.frag"},
	//	{GL_NONE,NULL},
	//};

	//GLuint program = LoadShaders(shaders);
	//glUseProgram(program);
	//glVertexAttribPointer(vPosition,2,GL_FLOAT,GL_FALSE,0,(void *)(0));
	//glEnableVertexAttribArray(vPosition);
	cout << "Initialization successfull" << endl;
}

//handle all allocated resources
void onShutdown()
{
	cout << "shutdown successfull" << endl;
}

//display callback function
void onRender()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	//glutSwapBuffers();

	glBindVertexArray(VAOs[Triangles]);
	glDrawArrays(GL_TRIANGLES,0,NumVertices);
	glFlush();
}

//handle resize event
void onResize(int nw,int nh)
{
	cout << "resize successfull" << endl;
}



int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	//glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitContextVersion(4,3);
	glutInitContextFlags(GLUT_CORE_PROFILE|GLUT_DEBUG);
	glutInitContextProfile(GLUT_FORWARD_COMPATIBLE);
	glutInitWindowSize(width,height);
	glutCreateWindow("Getting started with openGL 4.3");

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if(GLEW_OK != err)
	{

	}
	else
	{
		
	}

	cout << "\tUsing GLEW " << glewGetString(GLEW_VERSION) << endl;
	cout << "\tVendor: " << glGetString(GL_VENDOR) << endl;
	cout << "\tRenderer: " << glGetString(GL_RENDERER) << endl;
	cout << "\tVersion: " << glGetString(GL_VERSION) << endl;
	cout << "\tGLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) <<  endl;

	OnInit();
	glutCloseFunc(onShutdown);
	glutDisplayFunc(onRender);
	glutReshapeFunc(onResize);

	glutMainLoop();
	return 0;
}
#include <GLTools.h>
#include <GLShaderManager.h>

#define FREEGLUT_STATIC
#include <GL/glut.h>

#include <time.h>
#include <math.h>
#include "GLFixedRender.h"

#define ColorVertex(c,v) do {glColor3fv(c);glVertex3fv(v);} while (0);

GLBatch triangleBatch;
GLShaderManager shaderManager;

void changeSize(int w,int h)
{
	glViewport(0,0,w,h);
}

//initialization rendering context
void setupRC()
{
	glClearColor(0.0f,0.0f,0.0f,1.0f);

	shaderManager.InitializeStockShaders();
	
	GLfloat vVerts[] = {-0.5f,0.0f, 0.0f,
						0.5f, 0.0f, 0.0f,
						0.0f, 0.5f, 0.0f};
	/*triangleBatch.Begin(GL_TRIANGLES,3);
	triangleBatch.CopyVertexData3f(vVerts);
	triangleBatch.End();*/

	GLuint vertextArrayObject;
	glGenVertexArrays(1,&vertextArrayObject);
	glBindVertexArray(vertextArrayObject);

	GLuint vertexArray;
	GLuint numVerts = 3;
	glGenBuffers(1,&vertexArray);
	glBindBuffer(GL_ARRAY_BUFFER,vertexArray);
	glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat) * 3 * numVerts,vVerts,GL_DYNAMIC_DRAW);


}


void renderScene()
{
	/*glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
	GLfloat vRed[] = {1.0f,0.0f,0.0f,1.0f};
	shaderManager.UseStockShader(GLT_SHADER_IDENTITY,vRed);
	triangleBatch.Draw();*/
	
	//glRectf(-0.5f,-0.5f,0.5f,0.5f); //»­Ò»¸ö¾ØÐÎ
	/*glPointSize(20.0f);
	glBegin(GL_POINTS);
	glVertex2f(0.5f,0.5f);
	glVertex2f(0.0f,0.0f);
	glVertex2f(-0.5f,-1.0f);
	glEnd();*/

	//testFillMode();
	//testPoint();
	//testRect();
	//testSphere();
	//testLight();
	//testCircle(30);
	testList();
}
static int day = 20;
void idleFunc()
{
	++day;
	if (day > 360)
	{
		day = 0;
	}
	renderScene();
}

int main(int argc,char* argv[])
{
	gltSetWorkingDirectory(argv[0]);

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH|GLUT_STENCIL);
	//glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(800,600);
	glutCreateWindow("triangle");
	glutReshapeFunc(changeSize);
	glutDisplayFunc(renderScene);
	//glutIdleFunc(idleFunc);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		fprintf(stderr,"GLEW ERROR: %s\n",glewGetErrorString(err));
		return 1;
	}

	setupRC();

	glutMainLoop();

	
	return 0;
}
//#include <GLTools.h>
#include "GLFixedRender.h"

static const char *szIdentityShaderVP = "attribute vec4 vVertex;"
										"void main(void)"
										"{gl_Position = vVertex;}";
static const char* szIdentityShaderFP = 
#ifdef OPENGL_ES
										"precision mediump float;"
#endif
										"uniform vec4 vColor;"
										"void main(void)"
										"{gl_FragColor = vColor;}";

GLuint identityShader;

GLuint vertextArrayObject;

void changeSize(int w,int h)
{
	glViewport(0,0,w,h);
}

//initialization rendering context
void setupRC()
{
	glClearColor(0.0f,0.0f,0.0f,1.0f);

	//shaderManager.InitializeStockShaders();
	identityShader = loadShaderPairSrcWithAttribute(szIdentityShaderVP,szIdentityShaderFP,1,0,"vVertex");
	GLfloat vVerts[] = {-0.5f,0.0f, 0.0f,
						0.5f, 0.0f, 0.0f,
						0.0f, 0.5f, 0.0f};
	/*triangleBatch.Begin(GL_TRIANGLES,3);
	triangleBatch.CopyVertexData3f(vVerts);
	triangleBatch.End();*/

#ifndef OPENGL_ES
	//GLuint vertextArrayObject;
	glGenVertexArrays(1,&vertextArrayObject);
	glBindVertexArray(vertextArrayObject);
#endif

	GLuint vertexArray;
	GLuint numVerts = 3;
	glGenBuffers(1,&vertexArray);
	glBindBuffer(GL_ARRAY_BUFFER,vertexArray);
	glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat) * 3 * numVerts,vVerts,GL_DYNAMIC_DRAW);

#ifndef OPENGL_ES
	glBindVertexArray(vertextArrayObject);
#endif

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER,vertexArray);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);

#ifndef OPENGL_ES
	glBindVertexArray(0);
#endif

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
	//testList();
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER|GL_STENCIL_BUFFER);
	GLfloat vRed[] = {1.0f,0.0f,0.0f,1.0f};
	glUseProgram(identityShader);
	GLint iColor = glGetUniformLocation(identityShader,"vColor");
	glUniform4fv(iColor,1,vRed);

#ifndef OPENGL_ES
	glBindVertexArray(vertextArrayObject);
#endif
	glDrawArrays(GL_TRIANGLES,0,3);
#ifndef OPENGL_ES
	glBindVertexArray(0);
#endif

	glutSwapBuffers();
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
	//gltSetWorkingDirectory(argv[0]);

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
		//fprintf(stderr,"GLEW ERROR: %s\n",glewGetErrorString(err));
		return 1;
	}

	setupRC();

	glutMainLoop();

	
	return 0;
}
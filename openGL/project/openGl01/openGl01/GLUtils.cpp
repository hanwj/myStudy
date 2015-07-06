#include "GLUtils.h"


GLuint loadShaderPairSrcWithAttribute(const char* vertexSrc,const char* fragmentSrc, ...)
{
	GLuint hVertexShader;
	GLuint hFragmentShader;
	GLuint hReturn;
	GLint testVal;

	//create shader objects
	hVertexShader = glCreateShader(GL_VERTEX_SHADER);
	hFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	//load shader src
	glShaderSource(hVertexShader,1,&vertexSrc,NULL);
	glShaderSource(hFragmentShader,1,&fragmentSrc,NULL);

	//compile shader
	glCompileShader(hVertexShader);
	glCompileShader(hFragmentShader);

	//check errors
	glGetShaderiv(hVertexShader,GL_COMPILE_STATUS,&testVal);
	if (testVal == GL_FALSE)
	{
		glDeleteShader(hVertexShader);
		glDeleteShader(hFragmentShader);
		return (GLint)NULL;
	}
	glGetShaderiv(hFragmentShader,GL_COMPILE_STATUS,&testVal);
	if (testVal == GL_FALSE)
	{
		glDeleteShader(hVertexShader);
		glDeleteShader(hFragmentShader);
		return (GLint)NULL;
	}

	//link them
	hReturn = glCreateProgram();
	glAttachShader(hReturn,hVertexShader);
	glAttachShader(hReturn,hFragmentShader);

	va_list attributeList;
	va_start(attributeList,fragmentSrc);

	char *nextArg;
	int iArgCount = va_arg(attributeList,int);
	for(int i = 0;i < iArgCount; i++)
	{
		int index = va_arg(attributeList,int);
		nextArg = va_arg(attributeList,char*);
		glBindAttribLocation(hReturn,index,nextArg);
	}
	va_end(attributeList);

	glLinkProgram(hReturn);

	glDeleteShader(hVertexShader);
	glDeleteShader(hFragmentShader);

	glGetProgramiv(hReturn,GL_COMPILE_STATUS,&testVal);
	if (testVal == GL_FALSE)
	{
		glDeleteProgram(hReturn);
		return (GLint)NULL;
	}
	return hReturn;
}


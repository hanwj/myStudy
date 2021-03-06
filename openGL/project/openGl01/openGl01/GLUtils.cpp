#include "GLUtils.h"

// Identity Shader (GLT_SHADER_IDENTITY)
// This shader does no transformations at all, and uses the current
// glColor value for fragments.
// It will shade between verticies.
static const char *szIdentityShaderVP = "attribute vec4 vVertex;"
										"void main(void) "
										"{ gl_Position = vVertex; "
										"}";
									
static const char *szIdentityShaderFP = 
#ifdef OPENGL_ES
										"precision mediump float;"
#endif
										"uniform vec4 vColor;"
										"void main(void) "
										"{ gl_FragColor = vColor;"
										"}";
									

///////////////////////////////////////////////////////////////////////////////
// Flat Shader (GLT_SHADER_FLAT)
// This shader applies the given model view matrix to the verticies, 
// and uses a uniform color value.
static const char *szFlatShaderVP =	"uniform mat4 mvpMatrix;"
									"attribute vec4 vVertex;"
									"void main(void) "
									"{ gl_Position = mvpMatrix * vVertex; "
									"}";
									
static const char *szFlatShaderFP = 
#ifdef OPENGL_ES
									"precision mediump float;"
#endif
									"uniform vec4 vColor;"
									"void main(void) "
									"{ gl_FragColor = vColor; "
									"}";

///////////////////////////////////////////////////////////////////////////////
// GLT_SHADER_SHADED
// Point light, diffuse lighting only
static const char *szShadedVP =		"uniform mat4 mvpMatrix;"
									"attribute vec4 vColor;"
									"attribute vec4 vVertex;"
									"varying vec4 vFragColor;"
									"void main(void) {"
									"vFragColor = vColor; "
									" gl_Position = mvpMatrix * vVertex; "
									"}";

static const char *szShadedFP =     
#ifdef OPENGL_ES
									"precision mediump float;"
#endif
									"varying vec4 vFragColor; "
									"void main(void) { "
									" gl_FragColor = vFragColor; "
									"}";
									
// GLT_SHADER_DEFAULT_LIGHT
// Simple diffuse, directional, and vertex based light
static const char *szDefaultLightVP = "uniform mat4 mvMatrix;"
									  "uniform mat4 pMatrix;"
									  "varying vec4 vFragColor;"
									  "attribute vec4 vVertex;"
									  "attribute vec3 vNormal;"
									  "uniform vec4 vColor;"
									  "void main(void) { "
									  " mat3 mNormalMatrix;"
									  " mNormalMatrix[0] = mvMatrix[0].xyz;"
									  " mNormalMatrix[1] = mvMatrix[1].xyz;"
									  " mNormalMatrix[2] = mvMatrix[2].xyz;"
									  " vec3 vNorm = normalize(mNormalMatrix * vNormal);"
									  " vec3 vLightDir = vec3(0.0, 0.0, 1.0); "
									  " float fDot = max(0.0, dot(vNorm, vLightDir)); "
									  " vFragColor.rgb = vColor.rgb * fDot;"
									  " vFragColor.a = vColor.a;"
									  " mat4 mvpMatrix;"
									  " mvpMatrix = pMatrix * mvMatrix;"
									  " gl_Position = mvpMatrix * vVertex; "
									  "}";


static const char *szDefaultLightFP =	
#ifdef OPENGL_ES
										"precision mediump float;"
#endif
										"varying vec4 vFragColor; "
										"void main(void) { "
										" gl_FragColor = vFragColor; "
										"}";

//GLT_SHADER_POINT_LIGHT_DIFF
// Point light, diffuse lighting only
static const char *szPointLightDiffVP =	  "uniform mat4 mvMatrix;"
										  "uniform mat4 pMatrix;"
										  "uniform vec3 vLightPos;"
										  "uniform vec4 vColor;"
										  "attribute vec4 vVertex;"
										  "attribute vec3 vNormal;"
										  "varying vec4 vFragColor;"
										  "void main(void) { "
										  " mat3 mNormalMatrix;"
										  " mNormalMatrix[0] = normalize(mvMatrix[0].xyz);"
										  " mNormalMatrix[1] = normalize(mvMatrix[1].xyz);"
										  " mNormalMatrix[2] = normalize(mvMatrix[2].xyz);"
										  " vec3 vNorm = normalize(mNormalMatrix * vNormal);"
										  " vec4 ecPosition;"
										  " vec3 ecPosition3;"
										  " ecPosition = mvMatrix * vVertex;"
										  " ecPosition3 = ecPosition.xyz /ecPosition.w;"
										  " vec3 vLightDir = normalize(vLightPos - ecPosition3);"
										  " float fDot = max(0.0, dot(vNorm, vLightDir)); "
										  " vFragColor.rgb = vColor.rgb * fDot;"
										  " vFragColor.a = vColor.a;"
										  " mat4 mvpMatrix;"
										  " mvpMatrix = pMatrix * mvMatrix;"
										  " gl_Position = mvpMatrix * vVertex; "
										  "}";


static const char *szPointLightDiffFP = 
#ifdef OPENGL_ES
										"precision mediump float;"
#endif
										"varying vec4 vFragColor; "
										"void main(void) { "
										" gl_FragColor = vFragColor; "
										"}";

//GLT_SHADER_TEXTURE_REPLACE
// Just put the texture on the polygons
static const char *szTextureReplaceVP =	"uniform mat4 mvpMatrix;"
										"attribute vec4 vVertex;"
										"attribute vec2 vTexCoord0;"
										"varying vec2 vTex;"
										"void main(void) "
										"{ vTex = vTexCoord0;" 
										" gl_Position = mvpMatrix * vVertex; "
										"}";
									
static const char *szTextureReplaceFP = 
#ifdef OPENGL_ES
										"precision mediump float;"
#endif
										"varying vec2 vTex;"
										"uniform sampler2D textureUnit0;"
										"void main(void) "
										"{ gl_FragColor = texture2D(textureUnit0, vTex); "
										"}";


// Just put the texture on the polygons
static const char *szTextureRectReplaceVP =	"uniform mat4 mvpMatrix;"
                                        "attribute vec4 vVertex;"
                                        "attribute vec2 vTexCoord0;"
                                        "varying vec2 vTex;"
                                        "void main(void) "
                                        "{ vTex = vTexCoord0;" 
                                        " gl_Position = mvpMatrix * vVertex; "
                                        "}";

static const char *szTextureRectReplaceFP = 
#ifdef OPENGL_ES
                                        "precision mediump float;"
#endif
                                        "varying vec2 vTex;"
                                        "uniform sampler2DRect textureUnit0;"
                                        "void main(void) "
                                        "{ gl_FragColor = texture2DRect(textureUnit0, vTex); "
                                        "}";



//GLT_SHADER_TEXTURE_MODULATE
// Just put the texture on the polygons, but multiply by the color (as a unifomr)
static const char *szTextureModulateVP ="uniform mat4 mvpMatrix;"
										"attribute vec4 vVertex;"
										"attribute vec2 vTexCoord0;"
										"varying vec2 vTex;"
										"void main(void) "
										"{ vTex = vTexCoord0;" 
										" gl_Position = mvpMatrix * vVertex; "
										"}";
									
static const char *szTextureModulateFP =
#ifdef OPENGL_ES
										"precision mediump float;"
#endif
										"varying vec2 vTex;"
										"uniform sampler2D textureUnit0;"
										"uniform vec4 vColor;"
										"void main(void) "
										"{ gl_FragColor = vColor * texture2D(textureUnit0, vTex); "
										"}";



//GLT_SHADER_TEXTURE_POINT_LIGHT_DIFF
// Point light (Diffuse only), with texture (modulated)
static const char *szTexturePointLightDiffVP =	  "uniform mat4 mvMatrix;"
												  "uniform mat4 pMatrix;"
												  "uniform vec3 vLightPos;"
												  "uniform vec4 vColor;"
												  "attribute vec4 vVertex;"
												  "attribute vec3 vNormal;"
												  "varying vec4 vFragColor;"
												  "attribute vec2 vTexCoord0;"
												  "varying vec2 vTex;"
												  "void main(void) { "
												  " mat3 mNormalMatrix;"
												  " mNormalMatrix[0] = normalize(mvMatrix[0].xyz);"
												  " mNormalMatrix[1] = normalize(mvMatrix[1].xyz);"
												  " mNormalMatrix[2] = normalize(mvMatrix[2].xyz);"
												  " vec3 vNorm = normalize(mNormalMatrix * vNormal);"
												  " vec4 ecPosition;"
												  " vec3 ecPosition3;"
												  " ecPosition = mvMatrix * vVertex;"
												  " ecPosition3 = ecPosition.xyz /ecPosition.w;"
												  " vec3 vLightDir = normalize(vLightPos - ecPosition3);"
												  " float fDot = max(0.0, dot(vNorm, vLightDir)); "
												  " vFragColor.rgb = vColor.rgb * fDot;"
												  " vFragColor.a = vColor.a;"
												  " vTex = vTexCoord0;"
												  " mat4 mvpMatrix;"
												  " mvpMatrix = pMatrix * mvMatrix;"
												  " gl_Position = mvpMatrix * vVertex; "
												  "}";


static const char *szTexturePointLightDiffFP =	
#ifdef OPENGL_ES
												"precision mediump float;"
#endif
												"varying vec4 vFragColor;"
											    "varying vec2 vTex;"
												"uniform sampler2D textureUnit0;"
												"void main(void) { "
												" gl_FragColor = vFragColor * texture2D(textureUnit0, vTex);"
												"}";



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

void initPresetShaders()
{
	presetShaders[SHADER_IDENTITY] = loadShaderPairSrcWithAttribute(szIdentityShaderVP,szIdentityShaderFP,1,ATTRIBUTE_VERTEX,"vVertex");
	presetShaders[SHADER_FLAT] = loadShaderPairSrcWithAttribute(szFlatShaderVP,szFlatShaderFP,1,ATTRIBUTE_VERTEX,"vVertex");

}

void usePresetShader(PRESET_SHADER shaderID,...)
{
	if(shaderID >= SHADER_LAST)
	{
		return;
	}

	va_list uniformList;
	va_start(uniformList,shaderID);

	glUseProgram(presetShaders[shaderID]);

}
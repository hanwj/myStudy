#include "GLFixedRender.h"


#define ColorVertex(c,v) do {glColor3fv(c);glVertex3fv(v);} while (0);

void testFillMode()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
	glPolygonMode(GL_FRONT,GL_FILL); //设置正面为填充模式
	glPolygonMode(GL_BACK,GL_LINE);  //设置反面为线性模式

	glFrontFace(GL_CCW);        // 设置逆时针方向为正面

	glBegin(GL_POLYGON);
	glColor3f(0.0f,1.0f,0.0f);
	glVertex2f(-0.5f,-0.5f);

	glColor3f(1.0f,0.0f,0.0f);
	glVertex2f(0.0f,-0.5f);

	glColor3f(0.0f,0.0f,1.0f);
	glVertex2f(0.0f,0.0f);

	glColor3f(0.0f,1.0f,0.0f);
	glVertex2f(-0.5f,0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(0.0f,0.0f);
	glVertex2f(0.0f,0.5f);
	glVertex2f(0.5f,0.5f);
	glVertex2f(0.5f,0.0f);
	glEnd();

	glutSwapBuffers();
	//glFlush();
}

void testRect()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);

	glRectf(-0.5f,-0.5f,0.5f,0.5f);

	glutSwapBuffers();
	//glFlush();
}

const float pi = 3.14f;
void testCircle(GLint slices)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
	
	glLineWidth(1.0f);
	glBegin(GL_LINE_LOOP);
		glColor3f(1.0f,1.0f,1.0f);
		for (int i=0;i<slices;++i)
		{
			GLfloat angle = 2 * pi * i/slices; 
			glVertex2f(cos(angle),sin(angle));
		}
	glEnd();

	glutSwapBuffers();
}

void testPoint()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);

	glPointSize(10.0f);
	glBegin(GL_POINTS);  //修改点的像素大小
	
	glColor3f(1.0f,0.5f,0.0f);
	glVertex2f(0.5f,0.5f);
	glColor3f(0.2f,0.3f,0.5f);
	glVertex2f(0.1f,0.1f);

	glEnd();
	glutSwapBuffers();
}

static int day = 20;
void testSphere()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75,1,1,400000000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0,-200000000,200000000,0,0,0,0,0,1);

	glColor3f(1.0f,0.0f,0.0f);
	glutSolidSphere(69600000,20,20);

	glPushMatrix();
	glColor3f(0.0f,0.0f,1.0f);
	glRotatef(day,0.0f,0.0f,-1.0f);
	glTranslatef(150000000,0,0);
	glutSolidSphere(15945000,20,20);

	//glPopMatrix();
	glColor3f(1.0f,1.0f,0.0f);
	glRotatef(day/30.0*360.0-day,0.0f,0.0f,1.0f);
	glTranslatef(38000000,0,0);
	//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glutSolidSphere(4345000,20,20);

	glutSwapBuffers();
}

void testLight()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60,1,1,50);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0,-10,10,0,0,0,0,0,1);

	//定义太阳光源
	{
		GLfloat sun_light_position[] = {0.0f,0.0f,0.0f,1.0f};
		GLfloat sun_light_ambient[] = {0.0f,0.0f,0.0f,1.0f};
		GLfloat sun_light_diffuse[] = {1.0f,1.0f,1.0f,1.0f};
		GLfloat sun_light_specular[] = {1.0f,1.0f,1.0f,1.0f};

		glLightfv(GL_LIGHT0,GL_POSITION,sun_light_position);
		glLightfv(GL_LIGHT0,GL_AMBIENT,sun_light_ambient);
		glLightfv(GL_LIGHT0,GL_DIFFUSE,sun_light_diffuse);
		glLightfv(GL_LIGHT0,GL_SPECULAR,sun_light_specular);

		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHTING);
		glEnable(GL_DEPTH_TEST);
	}
	//定义太阳的材质
	{
		GLfloat sun_mat_ambient[] = {0.0f,0.0f,0.0f,1.0f};
		GLfloat sun_mat_diffuse[] = {0.0f,0.0f,0.0f,1.0f};
		GLfloat sun_mat_specular[] = {0.0f,0.0f,0.0f,1.0f};
		GLfloat sun_mat_emission[] = {0.5f,0.0f,0.0f,1.0f};
		GLfloat sun_mat_shininess = 0.0f;

		glMaterialfv(GL_FRONT,GL_AMBIENT,sun_mat_ambient);
		glMaterialfv(GL_FRONT,GL_DIFFUSE,sun_mat_diffuse);
		glMaterialfv(GL_FRONT,GL_SPECULAR,sun_mat_specular);
		glMaterialfv(GL_FRONT,GL_EMISSION,sun_mat_emission);
		glMaterialf(GL_FRONT,GL_SHININESS,sun_mat_shininess);

		glutSolidSphere(2.0,40,32);
	}
	//定义地球的材质
	{
		GLfloat earth_mat_ambient[] = {0.0f,0.0f,0.5f,1.0f};
		GLfloat earth_mat_diffuse[] = {0.0f,0.0f,0.5f,1.0f};
		GLfloat earth_mat_specular[] = {0.0f,0.0f,1.0f,1.0f};
		GLfloat earth_mat_emission[] = {0.0f,0.0f,0.0f,1.0f};
		GLfloat earth_mat_shininess = 30.0f;

		glMaterialfv(GL_FRONT,GL_AMBIENT,earth_mat_ambient);
		glMaterialfv(GL_FRONT,GL_DIFFUSE,earth_mat_diffuse);
		glMaterialfv(GL_FRONT,GL_SPECULAR,earth_mat_specular);
		glMaterialfv(GL_FRONT,GL_EMISSION,earth_mat_emission);
		glMaterialf(GL_FRONT,GL_SHININESS,earth_mat_shininess);

		glRotatef(day,0.0f,0.0f,-1.0f);
		glTranslatef(5.0f,0.0f,0.0f);
		glutSolidSphere(2.0,40,32);
	}

	glutSwapBuffers();
}

void testList()
{
	static int list = 0;
	if (list == 0)
	{
		GLfloat
			pointA[] = {0.5f,-sqrt(6.0f)/12,-sqrt(3.0f)/6},
			pointB[] = {-0.5f,-sqrt(6.0f)/12,-sqrt(3.0f)/6},
			pointC[] = {0.0f,-sqrt(6.0f)/12,sqrt(3.0f)/6},
			pointD[] = {0.0f,sqrt(6.0f)/4,0};

		GLfloat
			colorR[] = {1,0,0},
			colorG[] = {0,1,0},
			colorB[] = {0,0,1},
			colorY[] = {1,1,0};

		list = glGenLists(1);
		glNewList(list,GL_COMPILE);
		glBegin(GL_TRIANGLES);
			ColorVertex(colorR,pointA);
			ColorVertex(colorG,pointB);
			ColorVertex(colorB,pointC);

			ColorVertex(colorR,pointA);
			ColorVertex(colorB,pointC);
			ColorVertex(colorY,pointD);

			ColorVertex(colorB,pointC);
			ColorVertex(colorG,pointB);
			ColorVertex(colorY,pointD);

			ColorVertex(colorG,pointB);
			ColorVertex(colorR,pointA);
			ColorVertex(colorY,pointD);
		glEnd();
		glEndList();

		glEnable(GL_DEPTH_TEST);
	}
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
	glPushMatrix();
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glRotatef(30,1,0.5,0);
	glCallList(list);
	glPopMatrix();

	glutSwapBuffers();
}

void testTex()
{
					
	glColor3f(0.0f,0.0f,1.0f);
	glVertex2f(0.0f,0.0f);

	glColor3f(0.0f,1.0f,0.0f);
	glVertex2f(-0.5f,0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(0.0f,0.0f);
	glVertex2f(0.0f,0.5f);
	glVertex2f(0.5f,0.5f);
	glVertex2f(0.5f,0.0f);
	glEnd();

	glutSwapBuffers();
	//glFlush();
}

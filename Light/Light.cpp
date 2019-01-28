// Light.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <gl/glut.h>

static GLfloat angle = 0.0f;

void myDisplay()
{
	glClearColor(0.3, 0.7, 0.5, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//创建透视效果视图
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(80.f, 1.0f, 1.0f, 20.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 12.0, 10.0, 0.0, 0.0, 0.0, 0.0,1.0, 0.0);

	//定义太阳光源，它是一种白色光源
	{
		GLfloat sun_light_position[] = { 0.0f,0.0f,0.0f,1.0f };
		GLfloat sun_light_ambient[] = { 0.0f,0.0f,0.0f,1.0f };
		GLfloat sun_light_diffuse[] = { 1.0f,1.0f,1.0f,1.0f };
		GLfloat sun_light_specular[] = { 1.0f,1.0f,1.0f,1.0f };
		glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
		glLightfv(GL_LIGHT0, GL_AMBIENT, sun_light_ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_light_diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);

		//开启光源
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHTING);
		glEnable(GL_DEPTH_TEST);

	}
	//定义太阳的材质并绘制太阳
	{
		GLfloat sun_mat_ambient[] = { 0.0f,0.0f,0.0f,1.0f };
		GLfloat sun_mat_diffuse[] = { 0.0f,0.0f,0.0f,1.0f };
		GLfloat sun_mat_specular[] = { 0.0f,0.0f,0.0f,1.0f };
		GLfloat sun_mat_emission[] = { 0.8f,0.0f,0.0f,1.0f };//辐射光
		 GLfloat sun_mat_shininess = 0.0f;
		glMaterialfv(GL_FRONT, GL_AMBIENT, sun_mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, sun_mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, sun_mat_specular);
		glMaterialfv(GL_FRONT, GL_EMISSION, sun_mat_emission);
		glMaterialf(GL_FRONT, GL_SHININESS, sun_mat_shininess);
		glutSolidSphere(3.0, 40, 32);


	}

	//定义地球材质并绘制地球
	{
		GLfloat earth_mat_ambient[] = { 0.0f,0.0f,1.0f,1.0f };
		GLfloat earth_mat_diffuse[] = { 0.0f,0.0f,0.5f,1.0f };
		GLfloat earth_mat_specular[] = { 1.0f,1.0f,1.0f,1.0f };
		GLfloat earth_mat_emission[] = { 0.0f,0.0f,0.0f,1.0f };
		GLfloat earth_mat_shininess = 3.0f;
		glMaterialfv(GL_FRONT, GL_AMBIENT, earth_mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, earth_mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, earth_mat_specular);
		glMaterialfv(GL_FRONT, GL_EMISSION, earth_mat_emission);
		glMaterialf(GL_FRONT, GL_SHININESS, earth_mat_shininess);
		glRotatef(angle, 0.0, -1.0f, 0.0f);
		glTranslatef(7.0f, 0.0f, 0.0f);
		glutSolidSphere(3.0, 40, 32);
		
	}
	Sleep(10);
	glutSwapBuffers();
}

void myldle()
{
	angle += 1.0f;
	if (angle >= 360.f)
	{
		angle = 0.0f;
	}

	myDisplay();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(400, 400);
	glutCreateWindow("OpenGL光照演示");
	glutDisplayFunc(&myDisplay);
	glutIdleFunc(&myldle);
	glutMainLoop();
	return 0;

	
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件

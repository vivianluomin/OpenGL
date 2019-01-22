// C1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <gl/glut.h>
#include "math.h"

using namespace std;

int n = 3600;
float PI = 3.1415926;
float R = 0.8f;

void myDisplay()
{
	//画圆
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0, 0, 0, 0);
	glColor4f(0, 0, 1, 0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++)
	{
		glVertex2f(R*cos(2 * PI*i / n), R*sin(2 * PI*i / n)); //定义顶点

	}
	glEnd();
	glFlush();

	cout << "画圆陈宫，任意键继续..." << endl;
	system("pause");

	//画五角星
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0, 0, 0, 0);
	glColor4f(0, 0, 1, 0);
	glBegin(GL_LINE_LOOP);

	GLfloat xA = R * cos(90 * 2 * PI / 360);
	GLfloat yA = R * sin(90 * 2 * PI / 360);

	GLfloat xB = R * cos(306 * 2 * PI / 360);
	GLfloat yB = R * sin(306 * 2 * PI / 360);

	GLfloat xC = R * cos(162 * 2 * PI / 360);
	GLfloat yC = R * sin(162 * 2 * PI / 360);

	GLfloat xD = R * cos(18 * 2 * PI / 360);
	GLfloat yD = R * sin(18 * 2 * PI / 360);

	GLfloat xE = R * cos(234 * 2 * PI / 360);
	GLfloat yE = R * sin(234 * 2 * PI / 360);

	glVertex2f(xA, yA);
	glVertex2f(xB, yB);
	glVertex2f(xC, yC);
	glVertex2f(xD, yD);
	glVertex2f(xE, yE);

	glEnd();
	glFlush();

	cout << "画五角星成功，按任意键继续...." << endl;
	system("pause");

	//画正弦曲线
	GLfloat x = 1.0;
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINES);

	glVertex2f(-1.0f, 0.0f);
	glVertex2f(1.0f, 0.0f);
	glVertex2f(0.0f, -1.0f);
	glVertex2f(0.0f, 1.0f);

	glEnd();

	glBegin(GL_LINE_STRIP);
	for (float x = -5 * PI; x < 5 * PI; x += 0.1f)
	{
		glVertex2f(x / (5 * PI), sin(x));
   	}

	glEnd();
	glFlush();
	cout << "画正弦成功，按任意键继续...." << endl;
	system("pause");
}

int main(int argc,char *argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("c1");
	glutDisplayFunc(&myDisplay);
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

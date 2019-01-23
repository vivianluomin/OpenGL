// C3.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <gl/glut.h>
#include <math.h>


void myDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor4f(1, 0, 0, 1);
	glRectf(-0.8, -0.8, 0.5, 0.5);
	glEnable(GL_BLEND);//开启混合模式
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glColor4f(0, 1, 0, 1);
	glRectf(-0.5, -0.5, 0.8, 0.8);
	glFinish();
}

void myDisplay2()
{
	glClear(GL_COLOR_BUFFER_BIT);
	int i;
	float Pi = 3.1415926;
	//glShadeModel(GL_FLAT);
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(0.0f, 0.0f);
	for (i = 0; i <= 8; i++)
	{
		glColor3f(i & 0x04, i & 0x02, i & 0x01);
		glVertex2f(cos(i*Pi / 4), sin(i*Pi / 4));
	}

	glEnd();
	glFlush();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("c3");
	glutDisplayFunc(&myDisplay2);
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

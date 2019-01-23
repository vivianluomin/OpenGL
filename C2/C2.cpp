// C2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <gl/glut.h>


void myDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPolygonMode(GL_FRONT, GL_FILL);//设置正面为填充模式
	glPolygonMode(GL_BACK, GL_LINE);//设置反面为线性模式

	glFrontFace(GL_CCW);//设置逆时针为正面

	glBegin(GL_POLYGON);
	glVertex2f(0, 0);
	glVertex2f(-0.5, 0);
	glVertex2f(-0.5, -0.5);
	glVertex2f(0, -0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(0, 0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, 0);
	glVertex2f(0, 0);
	glEnd();
	glFlush();


}

void myDisplay2()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_CULL_FACE);//运行剔除操作
	glCullFace(GL_FRONT);//指定剔除正面三角形
	glBegin(GL_POLYGON);
	glVertex2f(0, 0);
	glVertex2f(-0.5, 0);
	glVertex2f(-0.5, -0.5);
	glVertex2f(0, -0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(0, 0);
	glVertex2f(0, 0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(0.5, 0);
	glVertex2f(0.5, -0.5);
	glVertex2f(0, -0.5);
	glVertex2f(0, 0);
	glEnd();
	glFlush();

}



int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("c2");
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

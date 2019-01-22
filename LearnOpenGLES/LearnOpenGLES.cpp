﻿#define WindowWidth 400
#define WindowHeight 400
#define WindowTitle "OpenGL Mip 纹理贴图"

#include <gl/glut.h>
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

//定义纹理对象编号
GLuint texGround;
GLuint texWall;
GLuint texSky;

#define BMP_Header_Length 54 //图像数据在内存块中的偏移量
static GLfloat angle = 0.0f; //旋转角度
static GLfloat zPosition = 10; 

//判断一个整数是不是2的整数次幂
int power_of_two(int n)
{
	if (n <= 0)
	{
		return 0;
	}
	return (n&(n - 1)) == 0;
}

void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glRectf(-0.5f, -0.5f, 0.5f, 0.5f);
	glFlush();
}

/*
* 读取一个BMP文件作为纹理
* 如果失败返回0，成功返回纹理编号
*/
GLuint load_texture(const char* file_name)
{
	GLint width, height, total_bytes;
	GLubyte* pixels = 0;
	GLuint last_texture_ID = 0, texture_ID = 0;

	FILE* pFile = fopen(file_name, "rb");
	if (pFile == 0)
	{
		std::cout << "111111111111111"<<std::endl;
		return 0;
	}

	//读取文件中图像的宽度和高度
	fseek(pFile, 0x0012, SEEK_SET);
	fread(&width, 4, 1, pFile);
	fread(&height, 4, 1, pFile);
	fseek(pFile, BMP_Header_Length, SEEK_SET);

	//计算每行像素所占字节数，并根据此数据计算总像素字节数
	{
		GLint line_bytes = width * 3;
		while (line_bytes % 4 != 0)
		{
			++line_bytes;
		}
		total_bytes = line_bytes*height    ;
	}

	pixels = (GLubyte *)malloc(total_bytes);
	if (pixels == 0)
	{
		fclose(pFile);
		return 0;
	}

	//读取像素数据
	if (fread(pixels, total_bytes, 1, pFile) <= 0)
	{
		free(pixels);
		fclose(pFile);
		return 0;
	}

	//对旧版本兼容，如果图像的款速和告诉不是整数次方，则需要进行缩放
	//如果图像宽高超过了OpenGL对顶的最大值，也缩放

	{
		GLint max;
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);
		if (!power_of_two(width) || !power_of_two(height)
			|| width > max || height > max)
		{
			const GLint new_width = 256;
			const GLint new_height = 256;
			GLint new_line_bytes =0, new_total_bytes=0;
			GLubyte* new_pixels = 0;

			new_line_bytes = new_width * 3;
			while (new_line_bytes % 4 != 0)
			{
				++new_line_bytes;
			}
			new_total_bytes = new_line_bytes * new_height;
			new_pixels = (GLubyte*)malloc(new_total_bytes);
			if (new_pixels == 0)
			{
				free(pixels);
				fclose(pFile);
				return 0;
			}

			//进行像素放缩
			gluScaleImage(GL_RGB, width, height, GL_UNSIGNED_BYTE,
				pixels,new_width, new_height, GL_UNSIGNED_BYTE, new_pixels);

			//释放原来的像素数据，把pixel指向新的像素数据，并重新设置width和height
			free(pixels);
			pixels = new_pixels;
			width = new_width;
			height = new_height;

		}
	}

	glGenTextures(1, &texture_ID);
	if (texture_ID == 0)
	{
		free(pixels);
		fclose(pFile);
		return 0;

	}

	//绑定新的纹理，载入纹理并设置纹理参数
	//在绑定前，先获得原来绑定的纹理编号，以便在最后进行恢复 
	GLint lastTextureID = last_texture_ID;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &lastTextureID);
	glBindTexture(GL_TEXTURE_2D, texture_ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	

	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height,
		GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
	glBindTexture(GL_TEXTURE_2D, lastTextureID);  //恢复之前的纹理绑定
	free(pixels);
	return texture_ID;
}

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//设置视角
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65, 1, 1, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, zPosition, 0, 0, 0, 0, 1, 0);

	glRotated(angle, 0.0f, 1.0f, 0.0f);

	//绘制左侧墙壁以及纹理
	glBindTexture(GL_TEXTURE_2D, texWall);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-5.0f, -5.0f, 100.0f);
	glTexCoord2f(30.0f, 0.0f); glVertex3f(-5.0f, -5.0f, -100.0f);
	glTexCoord2f(30.0f, 2.0f); glVertex3f(-5.0f, 5.0f, -100.0f);
	glTexCoord2f(0.0f, 2.0f); glVertex3f(-5.0f, 5.0f, 100.0f);
	glEnd();

	//
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(5.0f, -5.0f, 100.0f);
	glTexCoord2f(30.0f, 0.0f); glVertex3f(5.0f, -5.0f, -100.0f);
	glTexCoord2f(30.0f, 2.0f); glVertex3f(5.0f, 5.0f, -100.0f);
	glTexCoord2f(0.0f, 2.0f); glVertex3f(5.0f, 5.0f, 100.0f);
	glEnd();

	//地板
	glBindTexture(GL_TEXTURE_2D, texGround);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-5.0f, -5.0f, 100.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(5.0f, -5.0f, 100.0f);
	glTexCoord2f(25.0f, 1.0f); glVertex3f(5.0f,-5.0f, -100.0f);
	glTexCoord2f(25.0f, 0.0f); glVertex3f(-5.0f, -5.0f, -100.0f);
	glEnd();


	//顶层
	glBindTexture(GL_TEXTURE_2D, texSky);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-5.0f, 5.0f, 100.0f);
	glTexCoord2f(0.0f, 3.0f); glVertex3f(5.0f, 5.0f, 100.0f);
	glTexCoord2f(35.0f, 3.0f); glVertex3f(5.0f, 5.0f, -100.0f);
	glTexCoord2f(35.0f, 0.0f); glVertex3f(-5.0f, 5.0f, -100.0f);
	glEnd();

	glutSwapBuffers();
}


void SpecialKey(GLint key, GLint x, GLint y)
{
	if (key == GLUT_KEY_UP)
	{
		zPosition += 1.0f;
	}
	if (key == GLUT_KEY_DOWN)
	{
		zPosition -= 1.0f;
	}
	if (key == GLUT_KEY_LEFT)
	{
		angle += 0.5f;
	}
	if (key == GLUT_KEY_RIGHT)
	{
		angle -= 0.5f;
	}
	glutPostRedisplay();
}


int main(int argc, char *argv[])	
{
	// GLUT初始化  
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WindowWidth, WindowHeight);
	glutCreateWindow(WindowTitle);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);    // 启用纹理  
	texGround = load_texture("F:\\CJiaproject\\LearnOpenGLES\\ground.bmp");  //加载纹理  
	texWall = load_texture("F:\\CJiaproject\\LearnOpenGLES\\wall.bmp");
	texSky = load_texture("F:\\CJiaproject\\LearnOpenGLES\\sky.bmp");
	std::cout << texGround << "   " << texWall << "   " << texSky;
	glutDisplayFunc(&Display);   //回调函数  
	glutSpecialFunc(&SpecialKey);
	glutMainLoop(); //循环调用  
	return 0;
	
}

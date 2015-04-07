// simple.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "C:\GLFiles\include\GL\glaux.h"


int _tmain(int argc, _TCHAR* argv[])
{
	auxInitDisplayMode(AUX_SINGLE | AUX_RGBA);
	auxInitPosition(0, 0, 500, 500);
	auxInitWindow(argv[0]);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	
	glBegin(GL_POLYGON);
		glVertex2f(-0.5, -0.5 );
		glVertex2f(-0.5, 0.5);
		glVertex2f(0.5, 0.5);
		glVertex2f(0.5, -0.5);
	glEnd();
	
	//auxWireCube(0.5);
	glFlush();
	Sleep(6000);


	return 0;
}


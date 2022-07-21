#include<stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
float x1=200, x2=100, x3=200, x4=300, y1=200, y2=300, y3=400, y4=300;
void menu(int op)
{
	switch (op)
	{
		case 0:
		glColor3f(1,0,0);
		break;
		case 1:
		glColor3f(0,1,0);
		break;
		case 2:
		glColor3f(0,0,1);
		break;
		case 3:
		exit(0);
	}
	glutPostRedisplay();
}
void myinit()
{
	glColor3f(1,0,0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,499.0,0.0,499.0);
}
void draw(int x,int y)
{
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();
	glFlush();
	
}
void edge(float x1,float y1,float x2,float y2,int *le,int *re)
{
	float mx,temp;
	if((y2-y1)<0){
		temp=y1;
		y1=y2;
		y2=temp;
		
		temp=x1;
		x1=x2;
		x2=temp;
	}
	mx=(x2-x1)/(y2-y1);
	float x=x1;
	for(int i=y1;i<y2;i++){
		if(x<(float)le[i])
			le[i]=(int)x;
		if(x>(float)re[i])
			re[i]=(int)x;
		x = x+mx;
	}
}
void scanfill()
{
	int le[500],re[500];
	for(int i=0;i<500;i++){
		le[i]=500;
		re[i]=0;
	}
	edge(x1,y1,x2,y2,le,re);
	edge(x2,y2,x3,y3,le,re);
	edge(x3,y3,x4,y4,le,re);
	edge(x4,y4,x1,y1,le,re);
	
	for(int y=0;y<500;y++){
		if(le[y]<=re[y])
			for(int i=le[y];i<re[y];i++)
				draw(i,y);
	}
}
void display()
{
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINE_LOOP);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glVertex2f(x4, y4);
    glEnd();
    scanfill();
    glFlush();
	
}
int main(int a,char **v)
{
	glutInit(&a,v);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(500,500);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutCreateWindow("Scanline Algorithm");
	
	myinit();
	
	glutCreateMenu(menu);
	glutAddMenuEntry("Red", 0);
    glutAddMenuEntry("Green", 1);
    glutAddMenuEntry("Blue", 2);
    glutAddMenuEntry("Quit", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
	glutDisplayFunc(display);
	glutMainLoop();
}

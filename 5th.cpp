#include<stdio.h>
#include<GL/glut.h>
#include<GL/glu.h>
float xmin=-0.5,xmax=0.5,ymin=-0.5,ymax=0.5;
float x1=-0.8,y1=-0.6,x2=0.7,y2=0.4;

int C1,C2;
int flag=1,cflag=0;
int left=1,right=2,bottom=4,top=8;
int getcode(float x,float y)
{
	int code=0;
	if(x<xmin) code=code|left;
	if(x>xmax) code=code|right;
	if(y<ymin) code=code|bottom;
	if(y>ymax) code=code|top;
	return code;
}
void clip(){
	float x,y;
	int C;
	if(C1) C=C1;
	else C=C2;
	
	float m=(y2-y1)/(x2-x1);
	
	if(C & left){
		x=xmin;
		y=y1+(xmin-x1)*m;
	}
	if(C & right){
		x=xmax;
		y=y1+(xmax-x1)*m;
	}
	if(C & bottom){
		y=ymin;
		x=x1+(ymin-y1)/m;
	}
	if(C & top){
		y=ymax;
		x=x1+(ymax-y1)/m;
	}
	if(C==C1){
		x1=x;
		y1=y;
	}else{
		x2=x;
		y2=y;
	}
}
void display()
{
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT);
	
	glColor3f(1,1,0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(xmin,ymin);
	glVertex2f(xmin,ymax);
	glVertex2f(xmax,ymax);
	glVertex2f(xmax,ymin);
	glEnd();
	
	glColor3f(1,0,0);
	
	if(flag==1){
	glBegin(GL_LINES);
	glVertex2f(x1,y1);
	glVertex2f(x2,y2);
	glEnd();
	}
	
	while(true){
		C1=getcode(x1,y1);
		C2=getcode(x2,y2);
		
		if((C1|C2)==0) break;
		else if((C1&C2)!=0){
			flag=0; break;
		}else
			clip();
	}
	glFlush();
}
void key(unsigned char ch,int x,int y){
	cflag=1;
	glutPostRedisplay();
}
int main(int a,char **v)
{
	glutInit(&a,v);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(500,500);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Cohen-Sutherland Algorithm");
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutMainLoop();
}

#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
int xx,yy,xend,yend;
void myinit()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,500,0,500);
	glMatrixMode(GL_MODELVIEW);
}
void setPixel(int x,int y){
	glBegin(GL_POINTS);
	glVertex2f(x,y);
	glEnd();
	glFlush();
}
void Bresenham()
{
	int x,y;
	if(xx>xend){
		x=xend;
		y=yend;
		xend=xx;
		yend=yy;
	}else{
		x=xx;
		y=yy;
	}
	int p;
	int dx=abs(xend-x),dy=abs(yend-y);
	int tdy=2*dy, tdx=2*dx;
	int tdyminustdx=2*(dy-dx),tdxminustdy=2*(dx-dy);
	glColor3f(1,1,0);
	glPointSize(2);
	if(dx>dy){
		p=2*dy-dx;
		setPixel(x,y);
		while(x<xend){
			x=x+1;
			if(p<0)
				p=p+tdy;
			else{
				y=y+1;
				p=p+tdyminustdx;
			}
			setPixel(x,y);
		}
	}else{
		p=2*dx-dy;
		setPixel(x,y);
		while(y<yend){
			y=y+1;
			if(p<0)
				p=p+tdx;
			else{
				x=x+1;
				p=p+tdxminustdy;
			}
			setPixel(x,y);
		}
	}
	
}
void display()
{
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(300, 300, 100, 100);
	Bresenham();
	glFlush();
}
int main(int a,char *v[])
{
	glutInit(&a,v);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,500);
	glutCreateWindow("Bresenham Line Drawing algo");
	myinit();
	printf("Enter co-ordinates of first point: ");
    scanf("%d%d",&xx,&yy);
    printf("Enter co-ordinates of second point: ");
    scanf("%d%d",&xend,&yend);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

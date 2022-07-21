#include<stdio.h>
#include<GL/glut.h>
int c;
float v[4][3]={{0,0.4,1},{-1,0,0},{1,0,0},{0,1,0}};
void myinit()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2,2,-2,2,-2,2);
	glMatrixMode(GL_MODELVIEW);
}
void disptri(float a[3],float b[3],float c[3])
{
	glBegin(GL_POLYGON);
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(c);
	glEnd();
}
void divtri(float a[3],float b[3],float c[3],int n)
{
	float v1[3],v2[3],v3[3];
	if(n>0){
		for(int i=0;i<3;i++){
			v1[i]=(a[i]+b[i])/2;
			v2[i]=(a[i]+c[i])/2;
			v3[i]=(b[i]+c[i])/2;
		}
		divtri(a,v1,v2,n-1);
		divtri(v1,b,v3,n-1);
		divtri(v2,v3,c,n-1);
	}else
		disptri(a,b,c);
}
void display()
{
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1,1,1);
	divtri(v[1],v[2],v[3],c);
	glColor3f(1,0,0);
	divtri(v[0],v[1],v[2],c);
	glColor3f(0,1,0);
	divtri(v[0],v[2],v[3],c);
	glColor3f(0,0,1);
	divtri(v[0],v[1],v[3],c);
	glFlush();
}
int main(int a,char **v)
{
	glutInit(&a,v);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(500,500);
	printf("Enter the number of subdivisions:\n");
    scanf("%d", &c);
	glutCreateWindow("3-D Serpensiki Gasket");
	myinit();
	glutDisplayFunc(display);
	glutMainLoop();
}

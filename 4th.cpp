
#include<GL/glu.h>
#include<GL/glut.h>
float v[8][3] ={{-0.5, -0.5, 0.5}, {-0.5, 0.5, 0.5}, {0.5, 0.5, 0.5}, {0.5, -0.5, 0.5}, {-0.5, -0.5, -0.5}, {-0.5, 0.5, -0.5}, {0.5, 0.5, -0.5}, {0.5, -0.5, -0.5}};
float p[8][3]={{0, 0, 0}, {0, 0, 1}, {0, 1, 0}, {0, 1, 1}, {1, 0, 0}, {1, 0, 1}, {1, 1, 0}, {1, 1, 1}};
float Cx=0,Cy=0,Cz=3;
int flag=2;
float theta[]={0,0,0};
void MyInit()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1,1,-1,1,2,10);
    glMatrixMode(GL_MODELVIEW);
}
void mousefunc(int button, int status, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && status == GLUT_DOWN)
        flag = 2;
    if (button == GLUT_MIDDLE_BUTTON && status == GLUT_DOWN)
        flag = 1;
    if (button == GLUT_RIGHT_BUTTON && status == GLUT_DOWN)
        flag = 0;
    
}
void drawpoly(int a,int b,int c,int d)
{
	glBegin(GL_POLYGON);
	glColor3fv(p[a]);
	glVertex3fv(v[a]);
	glColor3fv(p[b]);
	glVertex3fv(v[b]);
	glColor3fv(p[c]);
	glVertex3fv(v[c]);
	glColor3fv(p[d]);
	glVertex3fv(v[d]);
	glEnd();
}

void Cube()
{
    drawpoly(0,1,2,3);
	drawpoly(1,2,6,5);
	drawpoly(4,5,6,7);
	drawpoly(0,3,7,4);
	drawpoly(0,1,5,4);
	drawpoly(3,2,6,7);
}

void Draw()
{
	glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
    glLoadIdentity();
   
    gluLookAt(Cx,Cy,Cz,0,0,0,0,1,0);
    glRotatef(theta[0],1,0,0);
	glRotatef(theta[1],0,1,0);
	glRotatef(theta[2],0,0,1);
    Cube();
    glFlush();
    glutSwapBuffers();
}

void Key(unsigned char ch,int x,int y)
{
    switch(ch)
    {
        case 'x' : Cx = Cx - 0.5;   break;
        case 'X' : Cx = Cx + 0.5;   break;

        case 'y' : Cy = Cy - 0.5;   break;
        case 'Y' : Cy = Cy + 0.5;   break;

        case 'z' : Cz = Cz - 0.5;   break;
        case 'Z' : Cz = Cz + 0.5;   break;
    }
    glutPostRedisplay();
}

int main(int argC,char *argV[])
{
    glutInit(&argC,argV);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(100,100);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Color Cube with Camera");
    MyInit();
    glutDisplayFunc(Draw);
    glutKeyboardFunc(Key);
    glutMouseFunc(mousefunc);
    glutMainLoop();
    return 0;
}

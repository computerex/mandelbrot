#include <stdio.h>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "include/GL/freeglut.h"
#include "matrix.h"
#include "complex.h"

int width=573, height=352, SCALE=40, xt=0,yt=0;
std::vector<Vec2D> points;
std::vector< std::vector<double> > colors;

void computePoints(unsigned int itt)
{
	colors.clear();
    points.clear();
    ComplexNumber z(0,0), c(0,0);
	unsigned int ittcount;

    for ( double x = -2.5; x <= 1; x+=0.009 )
	{
		for ( double y = -1; y <= 1; y+= 0.009 )
		{
			c.real=x;c.img=y;
			z.real=0;z.img=0;
			ittcount=0;
			while ( ittcount < itt && z.length() < 4 )
			{
				z = z.multiply(z).add(c);
				ittcount++;
			}
			points.push_back(Vec2D(x,y));
			std::vector<double> color;
			color.push_back(ittcount/itt);
			color.push_back(sin((double)ittcount));
			color.push_back(abs(cos((double)ittcount)));
			colors.push_back(color);
		}
	}
}

void setup()
{
	// we gonna do this in ortho
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-width/2., width/2., -height/2., height/2., -1.,1);
	glMatrixMode(GL_MODELVIEW);
}

void resize(int w, int h)
{
	width=w;
	height=h;
	setup();
	//computePoints(1000);
}
void drawfractal()
{
	glBegin(GL_POINTS);
	for ( int i = 0; i < points.size(); i++ ){
		glColor3f(colors[i][0], colors[i][1], colors[i][2]);
		glVertex2f(points[i].x*SCALE,points[i].y*SCALE);
	}
	glEnd();
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.,1.,1.,1);
	glLoadIdentity();
	glTranslatef(xt,-140+yt,0);
	drawfractal();
	glutSwapBuffers();
}
void mouse(int x, int y)
{
}
void mousefunc(int button, int state, int x, int y)
{
}
void keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 'w':
		yt+=10;
		break;
	case 's':
		yt-=10;
		break;
	case 'a':
		xt-=10;
		break;
	case 'd':
		xt+=10;
		break;
	case 'z':
	case 'Z':
		SCALE*=2;
		break;
	case 'x':
	case 'X':
		SCALE/=2;
		break;
	}
}
void update(int value)
{
	glutPostRedisplay();
	glutTimerFunc(15, update, 0);
}

int main(int argc, char *argv[])
{
	srand(time(NULL));
	computePoints(1000);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(width,height);
	glutCreateWindow("For ShanNoon");
	setup();
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutPassiveMotionFunc(mouse);
	glutMouseFunc(mousefunc);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(25, update, 0);
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glPointSize(1);
	glutMainLoop();
    return 0;
}

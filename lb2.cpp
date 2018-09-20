#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <GL/glut.h>

int xmin = 0, xmax = 0, ymin = 0, ymax = 0; //limites de las ventanas
int x1 = 0, x2 = 0, y1 = 0, y2 = 0; // variables para coordenadas de la linea a evaluar
float u1 = 0, u2 = 0;
double p[4], q[4];

void init() {
	glClearColor(1, 1, 1, 1);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-320, 320, -240, 240);
}

void ingresaDatosPantalla() {
	printf("Ingresa los datos del tamanio de la pantalla!\n");
	printf("Ingresa el valor de X min: ");
	scanf_s("%d", &xmin);
	fflush(stdin);
	printf("\nIngresa el valor de X max: ");
	scanf_s("%d", &xmax);
	fflush(stdin);
	printf("\nIngresa el valor de Y min: ");
	scanf_s("%d", &ymin);
	fflush(stdin);
	printf("\nIngresa el valor de Y max: ");
	scanf_s("%d", &ymax);

	printf("(%d, %d), (%d, %d)", xmin, ymin, xmax, ymax);

}

void ingresaDatosLinea() {
	printf("Ingresa los puntos inicial y final de la linea\n");
	printf("Ingresa el valor de x1: ");
	scanf_s("%d", &x1);
	fflush(stdin);
	printf("Ingresa el valor de y1: ");
	scanf_s("%d", &y1);
	fflush(stdin);
	printf("Ingresa el valor de x2: ");
	scanf_s("%d", &x2);
	fflush(stdin);
	printf("Ingresa el valor de y2: ");
	scanf_s("%d", &y2);
	fflush(stdin);
}

void recortar(int x1, int y1, int x2, int y2)
{
	int dx = x2 - x1, dy = y2 - y1, i;
	double t;
	p[0] = -dx; q[0] = x1 - xmin;
	p[1] = dx; q[1] = xmax - x1;
	p[2] = -dy; q[2] = y1 - ymin;
	p[3] = dy; q[3] = ymax - y1;

	for (i = 0; i < 4; i++)
	{
		if (p[i] == 0 && q[i] < 0)
			return;
		if (p[i] < 0)
		{
			t = (q[i]) / (p[i]); 
			if (t > u1 && t < u2)
			{
				u1 = t;
			}
		}
		else if (p[i] > 0)
		{
			t = (q[i]) / (p[i]);  
			if (t > u1 && t < u2)
			{
				u2 = t;
			}
		}
	}
	if (u1 < u2)
	{
		x1 = x1 + u1 * (x2 - x1);
		y1 = y1 + u1 * (y2 - y1);
		x2 = x1 + u2 * (x2 - x1);
		y2 = y1 + u2 * (y2 - y1);
		glBegin(GL_LINES);
		glVertex2i(x1, y1);
		glVertex2i(x2, y2);
		glEnd();
		glFlush();
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2i(x1, y1);
	glVertex2i(x2, y2);
	glEnd();
	glFlush();
}
void myKey(unsigned char key, int x, int y)
{
	glClear(GL_COLOR_BUFFER_BIT);
	if (key == 'c')
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glFlush();
		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_LINES);
		glVertex2i(xmin, ymin);
		glVertex2i(xmin, ymax);
		glVertex2i(xmin, ymax);
		glVertex2i(xmax, ymax);
		glVertex2i(xmax, ymax);
		glVertex2i(xmax, ymin);
		glVertex2i(xmax, ymin);
		glVertex2i(xmin, ymin);
		glEnd();
		glFlush();
		recortar(::x1, y2, x2, y1);
	}


}
int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Algoritmo Liang-Basrky 2019-1");
	ingresaDatosPantalla();
	ingresaDatosLinea();
	glutDisplayFunc(display);
	glutKeyboardFunc(myKey);
	init();
	glutMainLoop();
	return 0;
}
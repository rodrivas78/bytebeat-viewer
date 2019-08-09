//*   
//* Bytebeat Viewer  by  Rodrigo G. Rivas (rodrivas78)
//* This application generate visualizations for "bytebeats" ("one liners" or small programs
//* that produce interesting sound and musical results). When plotted, many of 
//* them result in fractals. So I thought it appropriate to call them "sound fractals" too. For more 
//* information on Bytebeats, I recommend the website (link below) of Ville-Matias Heikkiläem 
//* (a.k.a. Viznut), the discoverer of this method.
//*  http://countercomplex.blogspot.com/2011/10/algorithmic-symphonies-from-one-line-of.html
//*


#define GLUT_DISABLE_ATEXIT_HACK 
#include <stdlib.h>
#include <glut.h>
#include <cstring>
#include<iostream>
using namespace std;

int x;
int k;
double zoom = 2; 
char c;

void mouseClick(int, int, int, int);

	void Draw() 
	{

glClear(GL_COLOR_BUFFER_BIT);
glColor3f(1.0, 0.0, 0.0);

	for(k=0;k<=100000;k++)  
	{				
		// Some interesting Bytebeats "formulas"
		// I put a '*2' at the end of some just to scale the images better. 
		
		c=putchar((k*5&k>>7)|(k*3&k>>10))*2; 
		//c=putchar(k&k>>3|k>2);
		//c=putchar(k*(((k>>12)|(k>>8))&(63&(k>>4))))*2;  
		//c=putchar(k*(42&k>>10))*2;   //42 melody
		//c=putchar(k*(42&k>>10));
		//c=putchar(k*(((k>>12)|(k>>8))&(63&(k>>4))))*2;
		//c=putchar(k&k>>8)*2;  //Triangulo de Sirpinski
		//c=putchar(sin(k)-(k&k>>7))*2;  //Fractal invertido
		//c=putchar(k*9&k>>4|k*5&k>>7|k*3&k/1024)*2;
		//c=putchar(((k>>9))&((k>>1))|(1|(49&k<<2))&(k<<1))*2;
		//c=putchar((k>>(k>>5*(k>>13)%8))|(k>>4));
		
		
	glColor3f(0.5, 0.4, 1.0); //blue 
	glPointSize(1);
	glVertex2f(k/30,c+1000);	
	
	glColor3f(2.1, 3.0, 0.0); //yellow
	glBegin(GL_POINTS);
    glVertex2f(k/30,c+400);

    } 
	glScalef(zoom, zoom, 1.0f);	
	
glEnd();  
glFlush();
}
	
	
void update()
{    	 				
glutPostRedisplay();      
}


void Initialize() 
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);    
	//a = 1000.0*zoom;   //width / Escala do view  / tamanho das linhas e colunas // Original->500.0
	//b = 1000.0*zoom;   //height / Tamanho do view // Original->500.0	
}

void mouseClick(int btn, int state, int x, int y) {
  if (state == GLUT_DOWN) {
    switch(btn) {
    case GLUT_LEFT_BUTTON:
		//Aproxima
      cout << "left click at: (" << x << ", " << y << ")\n";
	  zoom -= 0.5;
	  break;
    case GLUT_RIGHT_BUTTON:
		//Afasta
      cout << "right click at: (" << x << ", " << y << ")\n";
	  zoom += 0.5;
      break;
    case GLUT_MIDDLE_BUTTON:
      cout << "middle click at: (" << x << ", " << y << ")\n";
      break;
    case 3:  //mouse wheel scrolls
      cout << "mouse wheel scroll up\n";
      break;   
     default:
     break;
    }
  }
  
 glutPostRedisplay(); 
}

 void reshape(int w, int h)
{
    glViewport(0, 0, 3000.0, 3000.0); // representam quantas colunas e linhas haverao na janela
    glMatrixMode(GL_PROJECTION);
	//glMatrixMode(GL_FLAT);  //tanto GL_FLAT quanto PROJECTION funciona
    glLoadIdentity();
	gluOrtho2D(0.0, 3000.0*zoom, 0.0, 3000.0*zoom); //Define a origem dos espaços e o tamanho de cada célula
}


int main(int iArgc, char** cppArgv) {
	glutInit(&iArgc, cppArgv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1200, 1000);
	glutInitWindowPosition(40, 50);
	glutCreateWindow("Bytebeat Viewer");
	glutMouseFunc(mouseClick);
	Initialize();
	glutDisplayFunc(Draw);
	glutIdleFunc(update);
    glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}

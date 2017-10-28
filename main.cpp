#include <iostream>
#include <GL/glut.h>

using namespace std;

float xc = 100, yc = 100;
float armRX = 100, armRy = 100;
float armLX = 100, armLy = 100;
float legRX = 100, legRy = 100;
float legLX = 100, legLy = 100;
float torsoX = 100, torsoY = 100;

int timeraL = 0;
int timeraR = 0;
int timerlR = 0;
int timerlL = 0;

float delta = 0.8;


void Timer(int i){
    glutPostRedisplay();
    glutTimerFunc(3,Timer,0);
}

void init(){
    glClearColor(0.0,0.0,0.0,1.0);

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,200.0,0.0,150.0);
}

void plot_point(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(xc+x, yc+y);
    glVertex2i(xc+x, yc-y);
    glVertex2i(xc+y, yc+x);
    glVertex2i(xc+y, yc-x);
    glVertex2i(xc-x, yc-y);
    glVertex2i(xc-y, yc-x);
    glVertex2i(xc-x, yc+y);
    glVertex2i(xc-y, yc+x);
    glEnd();
}

void bresenham_circle(int r)
{
    int x=0,y=r;
    float pk=(5.0/4.0)-r;

    /* Plot the points */
    /* Plot the first point */
    plot_point(x,y);
    int k;
    /* Find all vertices till x=y */
    while(x < y)
    {
        x = x + 1;
        if(pk < 0)
            pk = pk + 2*x+1;
        else
        {
            y = y - 1;
            pk = pk + 2*(x - y) + 1;
        }
        plot_point(x,y);
    }
}

void body(){
    glBegin(GL_LINES);
    glVertex2f(torsoX,torsoY-10);
    glVertex2f(torsoX,torsoY-50);

    glColor3f(0,1,0);
    glVertex2f(armRX,torsoY-20);
    glVertex2f(armRX+30,armRy-20);

    glColor3f(0,0,1);

    glVertex2f(armLX,torsoY-20);
    glVertex2f(armLX-30,armLy-20);

    glColor3f(1,1,1);

    glVertex2f(torsoX,torsoY-50);
    glVertex2f(legRX+30,legRy-70);

    glVertex2f(torsoX,torsoY-50);
    glVertex2f(legLX-30,legLy-70);
    glEnd();

    glutSwapBuffers();
}

void saludarR(int i){
    armRy += delta;
    if(armRy >= 110){
        delta = -0.8;
    }
    if(armRy <= 90){
        delta = 0.8;
    }
    glutPostRedisplay();
//    if(timeraR != 0){
//        glutTimerFunc(timeraR,saludarR,0);
//    }
}

void saludarL(int i){
    armLy += delta;
    if(armLy >= 110){
        delta = -0.8;
    }
    if(armLy <= 90){
        delta = 0.8;
    }
    glutPostRedisplay();
//    if(timeraL != 0){
//        glutTimerFunc(timeraL,saludarL,0);
//    }
}

void caminarF(int i){
    legRX -= delta;

    legLX += delta;
    if(legLX >= 125){
        delta = -0.8;
    }
    if(legLX <= 95){
        delta = 0.8;
    }
    glutPostRedisplay();
//    if(timerlR != 0){
//        glutTimerFunc(timerlR,caminarF,0);
//    }
}

void kbFunc(GLubyte key, GLint xMouse, GLint yMouse){
    cout << key << endl;
    switch (key){
        case 'w':
            if(timerlR == 0){
                timerlR = 30;
                caminarF(0);
            }else{
                timerlR = 0;
            }
            break;
        case 'a':
            if(timeraR == 0){
                timeraR = 30;
                saludarR(0);
            }else{
                timeraR = 0;
            }
            break;
        case 's':
            break;
        case 'd':
            if(timeraL == 0){
                timeraL = 30;
                saludarL(0);
            }else{
                timeraL = 0;
            }
            break;
        default:
            timerlR = 0;
            timeraL = 0;
            timeraR = 0;
            timerlL = 0;
            delta = 0.8;

            armLy = 100;
            armLX = 100;
            armRy = 100;
            armLX = 100;

            legLX = 100;
            legLy = 100;
            legRy = 100;
            legRX = 100;
            break;
    }
}

void displayFunc(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,0.0,0.0);
    glPointSize(3);
    bresenham_circle(10);
    body();
}

void display(){
    bresenham_circle(10);
}



void Initialize(){
    glClearColor(0,0,0,0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,1,0,1,-1,1);
}

int main(int argc,char** argv) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(420,420);
    glutCreateWindow("Animacion");

    init();
    glutDisplayFunc(displayFunc);
    glutKeyboardFunc(kbFunc);

    Timer(0);

    glutMainLoop();
    return 0;
}
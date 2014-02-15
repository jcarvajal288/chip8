#include <GL/freeglut.h>

void drawPixel(const int x, const int flipped_y)
{
    // openGL puts the origin at the lower left, so we need to switch
    // the y coordinate around to put it at the upper left
    int y = 32 - flipped_y;
    glBegin(GL_QUADS);
        glVertex2i(x, y);
        glVertex2i(x, y-1);
        glVertex2i(x+1, y-1);
        glVertex2i(x+1, y);
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawPixel(0,0);
    drawPixel(63,31);
    glFlush();
}

void init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 64.0, 0.0, 32.0);
    glMatrixMode(GL_MODELVIEW);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor3f(0.0, 1.0, 0.0);
    //glPointSize(10.0);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 320);
    glutCreateWindow("Chip 8");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
}
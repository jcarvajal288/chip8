#include "Screen.hpp"

static void RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
}

void Screen::initWindow(int argc, char** argv) const
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(posX, posY);
    glutCreateWindow(title.c_str());
    glutDisplayFunc(RenderSceneCB);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glPointSize(pixelWidth);

    glutMainLoop();

    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
}

void drawPixel(const int x, const int y) const
{

}

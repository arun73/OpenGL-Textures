#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <SOIL/SOIL.h>

#define TEXTURE_PATH "tux.png"

GLuint texture;

void init();
void display();
GLuint LoadTextureRAW(const char * filename, int wrap);

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("OpenGL textures");
    glutDisplayFunc(display);

    init();

    glutMainLoop();

    return 0;
}

void init()
{
    glClearColor(0, 0, 0, 1);
    gluOrtho2D(-2, 2, -2, 2);

    // Enable 2D textures
    glEnable(GL_TEXTURE_2D);

    // Use soil library to load the image
    texture = SOIL_load_OGL_texture
                    (
                        TEXTURE_PATH,
                        SOIL_LOAD_AUTO,
                        SOIL_CREATE_NEW_ID,
                        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
                    );

    // check for an error during the load process
    if(texture == 0)
        printf("SOIL loading error: '%s'\n", SOIL_last_result());
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0, 0, 0, 1);

    glBegin( GL_QUADS );
        glTexCoord2f(0.0,0.0);
        glVertex2d(-1, -1);
        glTexCoord2d(1.0,0.0);
        glVertex2d(1, -1);
        glTexCoord2d(1.0,1.0);
        glVertex2d(1, 1);
        glTexCoord2d(0.0,1.0);
        glVertex2d(-1, 1);
    glEnd();

    glFlush();
}

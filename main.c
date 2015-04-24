#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <SOIL/SOIL.h>

#define TEXURE_PATH "image.raw"
#define WIDTH   256
#define HEIGHT  256

GLuint texture;

void init();
void display();
GLuint LoadTextureRAW(const char *filename, GLfloat wrap_mode);

int main(int argc, char **argv)
{
    // Glut initial setup
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
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

    // Need to enable the type of texture that we need to use
    glEnable(GL_TEXTURE_2D);

    // Load the texture into OpenGL application
    texture = LoadTextureRAW(TEXURE_PATH, GL_REPEAT);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0, 0, 0, 1);

    // Creating a square
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex2d(-1, -1);
    glTexCoord2d(1.0, 0.0);
    glVertex2d(1, -1);
    glTexCoord2d(1.0, 1.0);
    glVertex2d(1, 1);
    glTexCoord2d(0.0, 1.0);
    glVertex2d(-1, 1);
    glEnd();

    glFlush();
    glutSwapBuffers();
}

/*
 * Load a WIDTH x HEIGHT 'raw' image as texture
 * Wrap modes: GL_REPEAT, GL_MIRRORED_REPEAT, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_BORDER
 * Do try out different wrap modes to understand what they exactly mean
 */
GLuint LoadTextureRAW(const char *filename, GLfloat wrap_mode)
{
    GLuint texture;
    GLubyte data[WIDTH * HEIGHT * 3];
    FILE *file;

    // Open raw image file
    file = fopen(filename, "rb");
    if (file == NULL) return 0;

    // Read the texture data
    fread(data, WIDTH * HEIGHT * 3, 1, file);
    fclose(file);

    // Create a single texture object
    glGenTextures(1, &texture);

    // Type of the texture
    glBindTexture(GL_TEXTURE_2D, texture);

    // Select modulate to mix texture with color for shading
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    // Setup the filtering mode
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Setup the wrapping mode
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_mode);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_mode);

    // Build the texture mipmaps
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, WIDTH, HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, data);

    return texture;
}

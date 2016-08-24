/*
 * Sergio Ruiz.
 *
 * TC3022. Computer Graphics Course.
 * Menus example.
 */

#include <OpenGL/gl.h> 						// Mac users put #include <OpenGL/gl.h> See: http://lnx.cx/docs/opengl-in-xcode
#include <OpenGL/glu.h>                     // Mac users put #include <OpenGL/glu.h> and #include <OpenGL/glut.h>
#include <GLUT/GLUT.h>
#include <stdio.h>
#include <math.h>

void processMenu(int val);

// MY STATES:
int shape; //0: TRIANGLE, 1: HEXAGON
// OPENGL STATES:
int mode; // Polygon mode: 0: solid, 1: wireframe.
int primitive; // 0: GL_POINTS, 1: GL_LINES, 2: GL_LINE_STRIP, 3: GL_TRIANGLES, 4: GL_TRIANGLE_STRIP

// VERTEX POSITION:
float vX;
float vY;
float vZ;

// ANGLE IN RADIANS:
float rad;

// COLOR:
float cr;
float cg;
float cb;


void init()
{
    vX = 0.0f;
    vY = 0.0f;
    vZ = 0.0f;
    cr = 0.0f;
    cg = 0.0f;
    cb = 0.0f;
    shape = 0;
    glEnable(GL_DEPTH_TEST);            // Enable check for close and far objects.
    glClearColor(0.0, 0.0, 0.0, 0.0);   // Clear the color state.
    glMatrixMode(GL_MODELVIEW);         // Go to 3D mode.
    glLoadIdentity();                   // Reset 3D view matrix.
}

void display()                          // Called for each frame (about 60 times per second).
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);             // Clear color and depth buffers.
    glLoadIdentity();                                               // Reset 3D view matrix.
    gluLookAt(0.0, 0.0, 4.0,                                        // Where the camera is.
              0.0, 0.0, 0.0,                                        // To where the camera points at.
              0.0, 1.0, 0.0);                                       // "UP" vector.
    
    
    glPointSize(5.0);
    glColor3f(0,1,0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // MODE
    glBegin(GL_POINTS); // PRIMITIVE
    for (int i = 0; i <= 360; i += 360/5) //5 --> SHAPE
    {
        rad = 0.0174533f * (float)i;
        vX = cosf(rad); // #include <math.h>
        vY = -sinf(rad);
        glVertex3f(vX,vY,vZ);
    }
    glEnd();
    
    glutSwapBuffers();                                              // Swap the hidden and visible buffers.
}

void idle()                                                         // Called when drawing is finished.
{
    glutPostRedisplay();                                            // Display again.
}

void reshape(int x, int y)                                          // Called when the window geometry changes.
{
    glMatrixMode(GL_PROJECTION);                                    // Go to 2D mode.
    glLoadIdentity();                                               // Reset the 2D matrix.
    gluPerspective(40.0, (GLdouble)x / (GLdouble)y, 0.5, 20.0);     // Configure the camera lens aperture.
    glMatrixMode(GL_MODELVIEW);                                     // Go to 3D mode.
    glViewport(0, 0, x, y);                                         // Configure the camera frame dimensions.
    gluLookAt(0.0, 0.0, 4.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);
    display();
}

int addMenus()
{
    // These variables store a GLUT-generated ID.
    // For each menu, you need an integer variable.
    // We'll generate 3 variables:
    int mainMenu, subMenu1, subMenu2;
    
    // Step 1: generate IDs for each menu and
    // assign a callback method (processMenu) for each:
    
    mainMenu = glutCreateMenu(processMenu);
    subMenu1 = glutCreateMenu(processMenu);
    subMenu2 = glutCreateMenu(processMenu);
    
    // Step 2: fill the menus.
    // Activate mainMenu, fill it with submenu1 & submenu 2:
    glutSetMenu(mainMenu);
    glutAddSubMenu("SOLID SHAPE", subMenu1);
    glutAddSubMenu("WIREFRAME SHAPE", subMenu2);
    glutAddMenuEntry("GL_POINTS", 21);
    glutAddMenuEntry("GL_LINES", 22);
    glutAddMenuEntry("GL_LINE_STRIP", 23);
    glutAddMenuEntry("GL_TRIANGLES", 24);
    glutAddMenuEntry("GL_TRIANGLE_STRIP", 25);
    
    // Activate and fill subMenu1:
    glutSetMenu(subMenu1);
    glutAddMenuEntry("TRIANGLE", 1);
    glutAddMenuEntry("PENTAGON", 2);
    glutAddMenuEntry("HEXAGON", 3);
    glutAddMenuEntry("RECTANGLE", 4);
    glutAddMenuEntry("RHOMBUS", 5);
    glutAddMenuEntry("CIRCLE", 6);
    // Activate and fill subMenu2:
    glutSetMenu(subMenu2);
    glutAddMenuEntry("TRIANGLE", 7);
    glutAddMenuEntry("PENTAGON", 8);
    glutAddMenuEntry("HEXAGON", 9);
    glutAddMenuEntry("RECTANGLE", 10);
    glutAddMenuEntry("RHOMBUS", 11);
    glutAddMenuEntry("CIRCLE", 12);
    // Step 3: link mainMenu to the mouse wheel:
    glutSetMenu(mainMenu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
    return 0;
}

/*
 Callback to process menus
 */
void processMenu(int val)
{
    // Primitive type: 0: GL_POINTS, 1: GL_LINES, 2: GL_LINE_STRIP, 3: GL_TRIANGLES, 4: GL_TRIANGLE_STRIP
    if (val >= 21 && val <= 25)
    {
        primitive = val - 21;
    }
    // Which shape to draw. 0: triangle, 1: pentagon, 2: hexagon, 3: rectangle, 4: rhombus, 5: circle.
    if (val >= 1 && val <= 6)
    {
        shape = val - 1;
        mode = 0; //SOLID
    }
    if (val >= 7 && val <= 12)
    {
        shape = val - 7;
        mode = 1; // WIREFRAME
    }
    
    glutPostRedisplay();
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);                                          // Init GLUT with command line parameters.
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);       // Use 2 buffers (hidden and visible). Use the depth buffer. Use 3 color channels.
    glutInitWindowSize(800, 800);
    glutCreateWindow(argv[0]);
    
    init();
    glutReshapeFunc(reshape);                                       // Reshape CALLBACK function.
    glutDisplayFunc(display);                                       // Display CALLBACK function.
    glutIdleFunc(idle);                                             // Idle CALLBACK function.
    addMenus();
    
    glutMainLoop();                                                 // Begin graphics program.
    return 0;                                                       // ANSI C requires a return value.
}
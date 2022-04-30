



#include <stdlib.h>

#include <stdio.h>

#include <time.h>

#include <string.h>

#include <GL/glut.h>





/**** Global Declarations and initializations *****/



GLUquadricObj* quadratic;



float t_val = 0.1;

int array_size = 11000; //  number of snow flakes

float snow[11000][2];   //  coordinates of snow flakes 

int j;                  //snow[specifies flake number][0=specifies x coordinate  1=specifies y coordinate]

GLfloat angle = 0.0f;

GLfloat x, y, z;

bool right = true;

int flag = 1;

float l1, l2, l3;



/***** Funtion to output text on screen *****/



void print_bitmap_string(float x, float y, float z, char* s)

{

    int i;

    GLvoid* font_style = GLUT_BITMAP_TIMES_ROMAN_24; // font name

    int len = (int)strlen(s);

    glPushMatrix();

    glRasterPos3f(x, y, z);

    for (i = 0; i < len; i++) {

        glutBitmapCharacter(font_style, s[i]);

    }



    glPopMatrix();

}





/**** Welcome Screen ****/



void welcome_screen()

{

    glClearColor(0.0, 0.0, 0.0, 1.0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);

    char welcome[7][200];

    strcpy_s(welcome[0], "WELCOME");

    strcpy_s(welcome[1], "Christmas Scene Simulation");

    strcpy_s(welcome[2], "");

    strcpy_s(welcome[3], "");

    strcpy_s(welcome[4], "");

    strcpy_s(welcome[5], "Press s to Start  & q to quit the Simulation");

    strcpy_s(welcome[6], "Press d for Description");

    glColor3f(0, 1, 1);

    print_bitmap_string(-1, 3.5, -7, welcome[0]);

    glColor3f(1, 1, 1);

    print_bitmap_string(-2, 2.5, -7, welcome[1]);

    glColor3f(1, 0, 1);

    print_bitmap_string(-6.1, -0.7, -7, welcome[2]);

    glColor3f(.8, 0.5, 1);

    print_bitmap_string(-6.2, -1.3, -7, welcome[3]);

    print_bitmap_string(-6.2, -2, -7, welcome[4]);

    glColor3f(1.0, 1.0, 0.0);

    print_bitmap_string(2.2, -1.3, -7, welcome[5]);

    glColor3f(1.0, 1.0, 0.0);

    print_bitmap_string(2.2, -2, -7, welcome[6]);



}



/***** Description Screen *****/



void descscreen()

{

    glClearColor(1.0, 1.0, 1.0, 1.0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);

    char text[8][200];

    strcpy_s(text[0], "DESCRIPTION");

    strcpy_s(text[1], "This project demonstrates a Christmas Scene Simulation.");

    strcpy_s(text[2], "The project is build using the OpenGL API and the source code is written in C.");

    strcpy_s(text[3], "The prime portion of this project concentrates on demonstration of realistic snowflakes and well animated christmas");

    strcpy_s(text[4], "characters and decorations. The lights of snow covered christmas tree and snowny mountains brings the desktop alive.");

    strcpy_s(text[5], "The movement of the snowman is in loop and need not be controlled by the user. The snowflakes falling feature can be");

    strcpy_s(text[6], "controlled by the user by pressing the 'a' key. The christmas tree is decorated with lights. The christmas presents ");

    strcpy_s(text[7], "have a 3-dimentional outlook and a wrapped cude rendering.");

    glColor3f(1, 0, 0);

    print_bitmap_string(-1, 3.5, -7, text[0]);

    glColor3f(0, 0, 0);

    print_bitmap_string(-8, 2.5, -7, text[1]);

    print_bitmap_string(-8, 2, -7, text[2]);

    print_bitmap_string(-8, 1, -7, text[3]);

    print_bitmap_string(-8, 0.5, -7, text[4]);

    print_bitmap_string(-8, 0, -7, text[5]);

    print_bitmap_string(-8, -0.5, -7, text[6]);

    print_bitmap_string(-8, -1, -7, text[7]);

}



/****** Keyboard Functions *******/



void mKeyboardFunc(unsigned char key, int x, int y) {

    switch (key) {

    case 'a':

    case 'A':

        for (j = 0; j < array_size; j++) {

            snow[j][0] += 0.005;   // moving the snow in x direction

            snow[j][1] -= 0.005;   // moving the snow in y direction

        }

        glutPostRedisplay();

        break;



    case 's':

    case 'S': flag = 2;

        glutPostRedisplay();

        break;



    case 'd':

    case 'D': flag = 3;

        glutPostRedisplay();

        break;



    case 'e':

    case 'E': exit(0);



    case 'w':

    case 'W': flag = 1;

        glutPostRedisplay();

        break;

    case 'q':

        break;



    }

}



/***** Initializing the snow array ******/



void initSnow() {

    int i;

    for (i = 0; i < array_size; i++) {

        int r1 = rand() % 6000;

        int r2 = rand() % 1000;

        while (r2 < 50) {

            r2 = rand() % 1000;

        }

        snow[i][0] = r1 * -0.01;//x co-ordinate

        snow[i][1] = r2 * 0.01;//y co-ordinate

    }

}





/***** Reshape function ******/



void resize(int w, int h) {

    GLdouble size;

    GLdouble aspect;



    /* Use the whole window. */

    glViewport(0, 0, w, h);



    /* We are going to do some 2-D orthographic drawing. */

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();



    GLfloat ar = (GLfloat)w / h;

    gluPerspective(45, ar, 0.1, 100);



    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

}





/***** Function to Draw Snow ******/



void drawSnow() {



    glColor3d(0.95, 0.95, 0.95); // Color of the snow

    srand(time(NULL));



    int i;

    for (i = 0; i < array_size; i++) {

        glPushMatrix();

        glTranslated(snow[i][0], snow[i][1], -4);

        glRotated(65, -1.0, 0.0, 0.8);

        glutSolidCube(0.015);

        glPopMatrix();

        glPushMatrix();

        glTranslated(-snow[i][0], snow[i][1], -4);

        glRotated(65, -1.0, 0.0, 0.8);

        glutSolidCube(0.015);

        glPopMatrix();

    }

}



/******* Funtion for Drawing lights on the tree ******/



void drawLights() {



    // Eight Lights on the tree



    glColor3d(l1 - 0.01, l2, l3);

    glPushMatrix();

    glTranslated(-0.3, 0.5, -5);

    glRotated(65, -1.0, 0.0, 0.8);

    glutSolidCube(0.1);

    glPopMatrix();



    glColor3d(l2, l3 + 0.06, l1);

    glPushMatrix();

    glTranslated(0.3, 0.95, -5);

    glRotated(65, -1.0, 0.0, 0.5);

    glutSolidCube(0.1);

    glPopMatrix();



    glColor3d(l1, l3, l2 - 0.05);

    glPushMatrix();

    glTranslated(0, 1.6, -5);

    glRotated(65, -1.0, 0.0, 0.5);

    glutSolidCube(0.1);

    glPopMatrix();



    glColor3d(l2 - 0.04, l1 + 0.02, l3);

    glPushMatrix();

    glTranslated(0.4, 0.25, -5);

    glRotated(65, -1.0, 0.0, 0.8);

    glutSolidCube(0.1);

    glPopMatrix();



    glColor3d(l3 + 0.02, l1 - 0.08, l2 - 0.06);

    glPushMatrix();

    glTranslated(-0.2, 0.05, -5);

    glRotated(65, -1.0, 0.0, 0.8);

    glutSolidCube(0.1);

    glPopMatrix();



    glColor3d(l3 - 0.04, l2 + 0.07, l1 - 0.07);

    glPushMatrix();

    glTranslated(-0.5, 1, -5);

    glRotated(65, -1.0, 0.0, 0.8);

    glutSolidCube(0.1);

    glPopMatrix();



    glColor3d(l3 + 0.06, l1, l1);

    glPushMatrix();

    glTranslated(-0.1, 1.2, -5);

    glRotated(65, -1.0, 0.0, 0.8);

    glutSolidCube(0.1);

    glPopMatrix();



    glColor3d(l2, l3 + 0.02, l3 - 0.04);

    glPushMatrix();

    glTranslated(0.2, 0.55, -5);

    glRotated(65, -1.0, 0.0, 0.8);

    glutSolidCube(0.1);

    glPopMatrix();

}



/****** Function to Draw Snowman *******/



void drawSnowMan(GLfloat x, GLfloat y, GLfloat z) {



    glColor3f(0.0, 0.0, 0.0);

    glPushMatrix();        // Eyes

    glTranslatef(x, y + 0.8, z + 0.5);

    glutSolidSphere(0.05, 200, 200);

    glPopMatrix();

    glPushMatrix();

    glTranslatef(x + 0.2, y + 0.8, z + 0.5);

    glutSolidSphere(0.05, 200, 200);

    glPopMatrix();



    glColor3d(1, 0, 0);  // Nose

    glPushMatrix();

    glTranslatef(x + 0.1, y + 0.65, z + 0.5);

    glRotatef(-260.0, 1.0, -1.5, 0.0);

    glutSolidCone(0.08, 0.2, 10, 2);

    glPopMatrix();



    glColor3f(1, 1, 1);  // Body Structure

    glPushMatrix();

    glTranslatef(x, y + 0.1, z);

    glutSolidSphere(0.55, 200, 200);

    glPopMatrix();

    glColor3f(1, 1, 1);

    glPushMatrix();

    glTranslatef(x, y - 0.99, z);

    glutSolidSphere(0.95, 200, 200);

    glPopMatrix();

    glColor3f(1, 1, 1);

    glPushMatrix();

    glTranslatef(x, y + 0.7, z);

    glutSolidSphere(0.35, 200, 200);

    glPopMatrix();



}





/***** Function to draw the rotated snowman ******/



void rotatingSnowMan() {

    x = -2.7, y = 0.3, z = -7;

    glPushMatrix();

    glTranslatef(x, y, z);

    glRotatef(angle, 0.0, 0.0, 1.0);

    glTranslatef(-x, -y, -z);

    drawSnowMan(x, y, z);

    glPopMatrix();

}





/****** Function to Draw the Tree ******/



void drawTree() {

    glColor3d(0.1, 0.5, 0.1);  // Tree color



    //Tree Cones

    glPushMatrix();

    glTranslated(0.0, 1.1, -6);

    glRotated(65, -1.0, 0.0, 0.0);

    glutSolidCone(0.85, 1.6, 100, 100);

    glPopMatrix();



    glPushMatrix();

    glTranslated(0.0, 0.6, -6);

    glRotated(65, -1.0, 0.0, 0.0);

    glutSolidCone(0.9, 1.5, 100, 100);

    glPopMatrix();



    glPushMatrix();

    glTranslated(0.0, 0.25, -6);

    glRotated(65, -1.0, 0.0, 0.0);

    glutSolidCone(0.95, 1.5, 100, 100);

    glPopMatrix();



    // Tree base

    glColor3d(0.29, 0.13, 0.13);

    glPushMatrix();

    glTranslated(0.0, -1.15, -6);

    glRotated(65, -1.0, 0.0, 0.0);

    gluCylinder(quadratic, 0.3f, 0.3f, 1.25f, 32, 32);

    glPopMatrix();



    // Tree shadow

    glColor3d(0.6, 0.6, 0.6);

    glPushMatrix();

    glTranslated(0.0, -0.8, -6);

    glRotated(70, -1.0, 0.0, 0.0);

    glutSolidTorus(0.33, 0.60, 200, 200);

    glPopMatrix();

}





/****** Function to Draw the ground/mountains ******/



void drawGround()

{

    //Upper Ground Circle

    glColor3f(0.93, 0.94, 0.94);

    glPushMatrix();

    glTranslatef(-7, -10, -12.5);

    glutSolidSphere(10, 200, 1000);

    glPopMatrix();



    //Middle Ground Circle

    glColor3f(0.96, 0.97, 0.95);

    glPushMatrix();

    glTranslatef(1.5, -10, -10.5);

    glutSolidSphere(10, 200, 1000);

    glPopMatrix();



    //Back Ground Circle

    glColor3f(0.91, 0.92, 0.90);

    glPushMatrix();

    glTranslatef(13, -10, -19.5);

    glutSolidSphere(10, 200, 1000);

    glPopMatrix();



}





/***** Function to Draw Gifts *****/



void drawGifts()

{

    //Gift One

    glColor3f(1, 0, 0);

    glPushMatrix();

    glTranslatef(0, -0.62, -5);

    glRotatef(45, 1, 0, 0);

    glRotatef(45, 0, 1, 0);

    glutSolidCube(0.3);

    glPopMatrix();



    // Gift Two

    glColor3f(1, 1, 0);

    glPushMatrix();

    glTranslatef(0.5, -0.52, -5);

    glRotatef(45, 1, 0, 0);

    glRotatef(45, 0, 1, 0);

    glutSolidCube(0.3);

    glPopMatrix();



    // Gift Three

    glColor3f(0, 1, 0);

    glPushMatrix();

    glTranslatef(0.3, -1.00, -5);

    glRotatef(45, 1, 0, 0);

    glRotatef(45, 0, 1, 0);

    glutSolidCube(0.3);

    glPopMatrix();



    // Gift Four

    glColor3f(0, 1, 1);

    glPushMatrix();

    glTranslatef(-0.4, -0.9, -5);

    glRotatef(45, 1, 0, 0);

    glRotatef(45, 0, 1, 0);

    glutSolidCube(0.3);

    glPopMatrix();

}





/** Draws the border of the gifts **/



void drawGiftsLine() {



    glColor3f(1, 1, 1); // Line Color



    // line for gift one (RED BOX)

    glPushMatrix();

    glLineWidth(2);

    glTranslatef(0, -0.53, -1.03);

    glBegin(GL_LINES);

    glVertex3f(0, 0.082, -2.1);		// origin pt of the box border

    glVertex3f(0, -0.054, -2.1);

    glVertex3f(0, 0.082, -2.1);		// origin pt of the box border

    glVertex3f(0.13, 0.165, -2.1);

    glVertex3f(0, 0.082, -2.1);		// origin pt of the box border

    glVertex3f(-0.13, 0.165, -2.1);

    glEnd();

    glPopMatrix();



    //line for gift two (YELLOW BOX)

    glPushMatrix();

    glLineWidth(2);

    glTranslatef(0.345, -0.453, -1.03);

    glBegin(GL_LINES);

    glVertex3f(0, 0.082, -2.1);		// origin pt of the box border

    glVertex3f(0, -0.054, -2.1);

    glVertex3f(0, 0.082, -2.1);		// origin pt of the box border

    glVertex3f(0.13, 0.165, -2.1);

    glVertex3f(0, 0.082, -2.1);		// origin pt of the box border

    glVertex3f(-0.13, 0.165, -2.1);

    glEnd();

    glPopMatrix();



    //line for gift three (GREEN BOX)

    glPushMatrix();

    glLineWidth(2);

    glTranslatef(0.21, -0.79, -1.03);

    glBegin(GL_LINES);

    glVertex3f(0, 0.082, -2.1);		// origin pt of the box border

    glVertex3f(0, -0.054, -2.1);

    glVertex3f(0, 0.082, -2.1);		// origin pt of the box border

    glVertex3f(0.13, 0.165, -2.1);

    glVertex3f(0, 0.082, -2.1);		// origin pt of the box border

    glVertex3f(-0.13, 0.165, -2.1);

    glEnd();

    glPopMatrix();



    //line for gift three (FIROZI BOX)

    glPushMatrix();

    glLineWidth(2);

    glTranslatef(-0.278, -0.726, -1.03);

    glBegin(GL_LINES);

    glVertex3f(0, 0.082, -2.1);		// origin pt of the box border

    glVertex3f(0, -0.054, -2.1);

    glVertex3f(0, 0.082, -2.1);		// origin pt of the box border

    glVertex3f(0.13, 0.165, -2.1);

    glVertex3f(0, 0.082, -2.1);		// origin pt of the box border

    glVertex3f(-0.13, 0.165, -2.1);

    glEnd();

    glPopMatrix();

}





/****** Display Function *******/



void display(void) {

    glClearColor(0.45, 0.45, 1.0, 1.0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    gluLookAt(0, 0, 1, 0, 0, 0, 0, 1, 0);

    drawGround();

    rotatingSnowMan();

    drawTree();

    drawSnow();

    drawLights();

    drawGiftsLine();

    drawGifts();

}



/****** Idle Function which rotates the snowman ******/



void idle() {



    if (right) {

        angle += 0.9f;

        if (angle > 7.0f)

            right = false;

    }



    if (!right) {

        angle -= 0.9f;

        if (angle < -4.0f)

            right = true;

    }



    srand(time(NULL));

    l1 = ((float)(rand()) / (float)(RAND_MAX));	  // randomizing 

    l2 = ((float)(rand()) / (float)(RAND_MAX)) * 0.99; // color of the 

    l3 = ((float)(rand()) / (float)(RAND_MAX));      // lights



    glutPostRedisplay();



}





/**** Function to set flag value to switch b/w different windows *****/



void scene() {

    if (flag == 1) {

        glutIdleFunc(NULL);		// Flag Value for welcome screen

        welcome_screen();

    }



    if (flag == 2) {



        glutIdleFunc(idle);

        display();			// Flag value for the christmas scene

    }



    if (flag == 3) {

        glutIdleFunc(NULL);

        descscreen();			// Flag Value for the description screen

    }



    glFlush();

}





/******* MAIN FUNCTION *******/



int main(int argc, char* argv[]) {



    // Initializations



    glutInit(&argc, argv);

    glutInitWindowSize(1200, 600); // window size

    glutInitWindowPosition(50, 40); // window position

    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);

    glutCreateWindow("Christmas");



    quadratic = gluNewQuadric();



    glShadeModel(GL_SMOOTH);

    glEnable(GL_DEPTH_TEST); //enabling z-buffer



    // Function Calls



    glutReshapeFunc(resize);

    glutDisplayFunc(scene);

    glDepthFunc(GL_LESS);

    glutFullScreen();			// fullscreen view of the program

    glutKeyboardFunc(mKeyboardFunc);

    initSnow();



    glutMainLoop(); // Initiate the main loop

    return 0;

}

#define FREEGLUT_STATIC
#include <math.h>
#include <GL/freeglut.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>


double pi = 3.1415926;

//time
GLint daytime = 0;


//lighting
int i = 0;
bool enableLight = 1;
bool enableLight1 = false;
GLfloat light0pos[] = { 0.0f, 76.f, 0.f, 0.f };
GLfloat light1pos[] = { 10.0f, -50.0f,-350.0f, 1.f };
GLfloat light0_mat1[] = { 0.3, 0.3, 0.3, 1.f };
GLfloat light0_diff[] = { 0.3, 0.3, 0.3, 0.3 };
const GLfloat an[] = { 30.0f };
GLfloat light1_mat1[] = { 0.6, 0.6, 0.6, 0.5f };
GLfloat light1_diff[] = { 0.6, 0.6, 0.6, 0.5f };
GLfloat light1_spc1[] = { 1.0, 1.0, 1.0, 1.0 };


// Define color
# define white 1.0, 1.0, 1.0
# define SaddleBrown 139.0 / 255.0, 69.0 / 255.0, 19.0 / 255.0 //table
# define Sienna 160.0 / 255.0, 82.0 / 255.0, 45.0 / 255.0 //table
# define LightGoldenrod 238.0 / 255.0, 221.0 / 255.0, 130.0 / 255.0 //teapot
# define yellow 0.93, 0.68, 0.055
# define red 0.65, 0.165, 0.165
# define brown 0.35, 0.15, 0.098
# define darkBrown 0.165, 0.09, 0.059
# define brown 0.35, 0.15, 0.098
# define darkBrown 0.165, 0.09, 0.059
# define Wheat 255.0 / 255.0, 231.0 / 255.0, 186.0 / 255.0
# define Burlywood 222.0 / 255.0, 184.0 / 255.0, 135.0 / 255.0
# define LightYellow2 238.0 / 255.0, 238.0 / 255.0, 209.0 / 255.0
# define LightYellow1 255.0 / 255.0, 255.0 / 255.0, 224.0 / 255.0
# define gold 255.0 / 255.0, 215.0 / 255.0, 0.0 / 255.0

//creation of geometry
double cuboid[8][3];// Set a matrix to record cuboid's vertexes
GLUquadricObj* quadobj;

//wall
GLint wall_thick = 10;
GLint bottom_base = -140;
GLint height = 300;
GLint right_base = -165;
GLint width = 300;
GLint back_base = -220;
GLint length = 450;

//robot
GLfloat robotX = -10, robotY = -10, robotZ = 14, robotmul = 7;

// texture seting
static GLuint wall_night; // Initialize the concrete texture object
static GLuint wall_daytime; // Initialize the brick texture object
static GLuint floor_night;  // Initialize the soil texture object
static GLuint floor_daytime; // Initialize the grass texture object
static GLint imageWidth;
static GLint imageHeight;
static GLint pixelLength;
static GLubyte* pixelData;


//animation values
int time1 = 20; // Declare refresh interval of teapot and robot in ms
int time2 = 60; // Declare refresh interval of clock in ms
int cp = 0; // Set a clock pointer angle parameter to control clock pointers
int clockTime = 0; // Declare the current time


GLfloat teapot_angle = 0;
bool teapot_flag = 1;
bool teapot_clockwise = 1;

GLfloat robot_angle = 0;
bool robot_flag = 1;
bool robot_mode = 1;
int robot_forth_or_back = 0;

// view
int winWidth = 700; // the window width
int winHeight = 600; // the window height
GLdouble frustdum = 120.0f;
GLdouble move_up = 0;
GLdouble move_right = 0;
GLfloat angleX = 0.0;
GLfloat angleY = 0.0;
GLfloat oldX;
GLfloat oldY;

GLfloat obj_mat_ambient[4];
GLfloat obj_mat_diffuse[4];
GLfloat obj_mat_specular[4];
GLfloat obj_mat_emission[4];
GLfloat obj_mat_shininess;

//Declaring functions
void init(void);
void mat(float r, float g, float b);
void light1_lamp(void);
void drawCuboid(double x1, double y1, double z1, double x2, double y2, double z2);
void glRectXplane(int leftY, int leftZ, int rightY, int rightZ, float X);
void glRectYplane(int leftY, int leftZ, int rightY, int rightZ, float X);
void glRectZplane(int leftY, int leftZ, int rightY, int rightZ, float X);

void table(void);
void cabinet(void);
void bed(void);
void lamp(void);
void window(void);
void circle(int x0, int y0, double r, float z);
void calendar(void);
void wall(void);
void clock_on_wall();
void Robot(GLfloat x, GLfloat y, GLfloat z);

GLuint setTexture(const char* fileName);
void floor_texture();
void wall_texture();
void display(void);

void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void motion(int x, int y);
void onTimer1(int Value);
void onTimer2(int Value);
void whenInMainloop();

void menu(int item);
void menuList();


//init the light0(environment light) and material
void init(void) 
{
	// Light 0 Settings

	glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_mat1);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diff);

	quadobj = gluNewQuadric();

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);		//Define Counter-Clockwise as front face
	glEnable(GL_COLOR_MATERIAL);

	//Initialize material properties
	GLfloat no_mat[] = { 0.0,0.0,0.0,1.0 };
	GLfloat mat_diffuse[] = { 0.9,0.9,0.9,1.0 };
	GLfloat mat_specular[] = { 0.3,0.3,0.3,1.0 };
	GLfloat high_shininess[] = { 20.0 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

}

//the material
void mat(float r, float g, float b) {
	GLfloat obj_mat_ambient[] = { r, g, b, 1.0f };
	GLfloat obj_mat_diffuse[] = { r, g, b, 1.0f };
	GLfloat obj_mat_specular[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	GLfloat obj_mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat obj_mat_shininess = 30.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, obj_mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, obj_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, obj_mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, obj_mat_emission);
	glMaterialf(GL_FRONT, GL_SHININESS, obj_mat_shininess);
}

void light1_lamp(void) {
	if (enableLight1)
	{
		glLightfv(GL_LIGHT1, GL_POSITION, light1pos);
		glLightfv(GL_LIGHT1, GL_AMBIENT, light1_mat1);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diff);
		glLightfv(GL_LIGHT1, GL_SPECULAR, light1_spc1);
		glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, an);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT1);
	}
	else
	{
		glDisable(GL_LIGHT1);
	}
}

// drawCuboid() aims to draw a cuboid when given start point and length
void drawCuboid(double x1, double y1, double z1, double x2, double y2, double z2) {
	cuboid[0][0] = x1;
	cuboid[0][1] = y1;
	cuboid[0][2] = z1;

	cuboid[1][0] = x1;
	cuboid[1][1] = y1;
	cuboid[1][2] = z1 + z2;

	cuboid[2][0] = x1 + x2;
	cuboid[2][1] = y1;
	cuboid[2][2] = z1 + z2;

	cuboid[3][0] = x1 + x2;
	cuboid[3][1] = y1;
	cuboid[3][2] = z1;

	// bind the other four vertexes
	for (int m = 0; m < 4; m++) {
		for (int n = 0; n < 3; n++) {
			if (n == 1) {
				cuboid[4 + m][n] = cuboid[m][n] + y2;
			}
			else {
				cuboid[4 + m][n] = cuboid[m][n];
			}
		}
	}


	// Draw the binded cuboid
	// Draw a cuboid's bottom
	glBegin(GL_POLYGON);
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(cuboid[0][0], cuboid[0][1], cuboid[0][2]);
	glVertex3f(cuboid[1][0], cuboid[1][1], cuboid[1][2]);
	glVertex3f(cuboid[2][0], cuboid[2][1], cuboid[2][2]);
	glVertex3f(cuboid[3][0], cuboid[3][1], cuboid[3][2]);
	glEnd();

	// Draw a cuboid's top
	glBegin(GL_POLYGON);
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(cuboid[4][0], cuboid[4][1], cuboid[4][2]);
	glVertex3f(cuboid[5][0], cuboid[5][1], cuboid[5][2]);
	glVertex3f(cuboid[6][0], cuboid[6][1], cuboid[6][2]);
	glVertex3f(cuboid[7][0], cuboid[7][1], cuboid[7][2]);
	glEnd();

	// Draw a cuboid' left side
	glBegin(GL_POLYGON);
	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f(cuboid[0][0], cuboid[0][1], cuboid[0][2]);
	glVertex3f(cuboid[1][0], cuboid[1][1], cuboid[1][2]);
	glVertex3f(cuboid[5][0], cuboid[5][1], cuboid[5][2]);
	glVertex3f(cuboid[4][0], cuboid[4][1], cuboid[4][2]);
	glEnd();

	// Draw a cuboid's right side
	glBegin(GL_POLYGON);
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(cuboid[2][0], cuboid[2][1], cuboid[2][2]);
	glVertex3f(cuboid[3][0], cuboid[3][1], cuboid[3][2]);
	glVertex3f(cuboid[7][0], cuboid[7][1], cuboid[7][2]);
	glVertex3f(cuboid[6][0], cuboid[6][1], cuboid[6][2]);
	glEnd();

	// Draw a cublid's front side
	glBegin(GL_POLYGON);
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(cuboid[5][0], cuboid[5][1], cuboid[5][2]);
	glVertex3f(cuboid[6][0], cuboid[6][1], cuboid[6][2]);
	glVertex3f(cuboid[2][0], cuboid[2][1], cuboid[2][2]);
	glVertex3f(cuboid[1][0], cuboid[1][1], cuboid[1][2]);
	glEnd();

	// Draw a cublid's back side
	glBegin(GL_POLYGON);
	glNormal3f(0.0, 0.0, -1.0);
	glVertex3f(cuboid[0][0], cuboid[0][1], cuboid[0][2]);
	glVertex3f(cuboid[3][0], cuboid[3][1], cuboid[3][2]);
	glVertex3f(cuboid[7][0], cuboid[7][1], cuboid[7][2]);
	glVertex3f(cuboid[4][0], cuboid[4][1], cuboid[4][2]);
	glEnd();
}

//glRectXplane(), glRectYplane() and glRectZplane() aims to draw a rectangle when given the plane and the points
void glRectXplane(int leftY, int leftZ, int rightY, int rightZ, float X) {
	glBegin(GL_POLYGON);
	glVertex3d(X, leftY, leftZ);
	glVertex3d(X, leftY, rightZ);
	glVertex3d(X, rightY, rightZ);
	glVertex3d(X, rightY, leftZ);
	glEnd();
}

void glRectYplane(int leftX, int leftZ, int rightX, int rightZ, float Y) {
	glBegin(GL_POLYGON);
	glVertex3d(leftX, Y, leftZ);
	glVertex3d(rightX, Y, leftZ);
	glVertex3d(rightX, Y, rightZ);
	glVertex3d(leftX, Y, rightZ);
	glEnd();
}

void glRectZplane(int leftX, int leftY, int rightX, int rightY, float Z) {
	glBegin(GL_POLYGON);
	glVertex3d(leftX, leftY, Z);
	glVertex3d(rightX, leftY,Z);
	glVertex3d(rightX, rightY,Z);
	glVertex3d(leftX, rightY,Z);
	glEnd();
}


void table(void) {
	glPushMatrix();
	glTranslatef(right_base + 250, bottom_base + wall_thick, back_base + 200);

	//Four supports
	mat(SaddleBrown);
	

	glPushMatrix();
	glTranslatef(0, 0.f, 100.f);
	glRotatef(-90, 1.f, 0.f, 0.f);
	gluCylinder(quadobj, 2.f, 2.f, 50.f, 20.f, 20.f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.f, 160.f);
	glRotatef(-90, 1.f, 0.f, 0.f);
	gluCylinder(quadobj, 2.f, 2.f, 50.f, 20.f, 20.f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(40, 0.f, 160.f);
	glRotatef(-90, 1.f, 0.f, 0.f);
	gluCylinder(quadobj, 2.f, 2.f, 50.f, 20.f, 20.f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(40, 0.f, 100.f);
	glRotatef(-90, 1.f, 0.f, 0.f);
	gluCylinder(quadobj, 2.f, 2.f, 50.f, 20.f, 20.f);
	glPopMatrix();

	//table body
	mat(Sienna);
	glPushMatrix();
	glTranslatef(20.f, 50.f, 130.f);
	glRotatef(0, 1.f, 0.f, 0.f);
	glScalef(8, 0.5, 12);
	glutSolidCube(10);
	glPopMatrix();


	//Rotate teapot with angle
	glTranslatef(0.f, -40.f, 120.f);
	glRotatef(teapot_angle, 0.f, 1.f, 0.f);

	//a teapot on table
	glPushMatrix();
	glTranslatef(-10.f, 100.f, 0.f);
	glRotatef(-90.f, 0.f, 1.f, 0.f);
	glScalef(100.f, 100.0f, -100.f);
	mat(LightGoldenrod);
	glutSolidTeapot(0.1);
	glPopMatrix();


	glPopMatrix();
}

void cabinet(void) {
	glPushMatrix();
	glTranslatef(40, 0, -100);
	//drawer body
	glPushMatrix();
	mat(brown);
	glTranslatef(8.f, -90.f, 20.5f);
	glRotatef(0, 1.f, 0.f, 0.f);
	glScalef(3, 0.1, 5);
	glutSolidCube(20);
	glPopMatrix();

	//upperlayer
	glPushMatrix();
	mat(darkBrown);
	glTranslatef(8.f, -110.f, 20.f);
	glRotatef(0, 1.f, 0.f, 0.f);
	glScalef(3, 2, 5);
	glutSolidCube(20);
	glPopMatrix();

	// interlayer
	glPushMatrix();
	mat(darkBrown);
	glTranslatef(8.f, -110.f, 20.5f);
	glRotatef(0, 1.f, 0.f, 0.f);
	glScalef(3, 0.1, 5);
	glutSolidCube(20);
	glPopMatrix();


	// Drawer Handle
	mat(white);
	glPushMatrix();
	glTranslatef(8.f, -100.f, 70.f);
	glRotatef(0, 1.f, 0.f, 0.f);
	glScalef(1, 1, 1);
	glutSolidSphere(2, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(8.f, -120.f, 70.f);
	glRotatef(0, 1.f, 0.f, 0.f);
	glScalef(1, 1, 1);
	glutSolidSphere(2, 20, 20);
	glPopMatrix();
	glPopMatrix();
}

void bed(void) {
	glPushMatrix();
	glTranslatef(40, 0, -100);
	//bottom bed
	glPushMatrix();
	glTranslatef(-71.f, -110.f, 80.f);
	glRotatef(0, 1.f, 0.f, 0.f);
	glScalef(5, 1.5, 10);
	mat(Sienna);
	glutSolidCube(20);
	glPopMatrix();

	//upper bed
	glPushMatrix();
	glTranslatef(-71.f, -90.f, 80.f);
	glRotatef(0, 1.f, 0.f, 0.f);
	glScalef(5, 0.5, 10);
	mat(Wheat);
	glutSolidCube(20);
	glPopMatrix();

	//the head of bed
	glPushMatrix();
	glTranslatef(-71.f, -90.f, -20.f);
	glRotatef(0, 1.f, 0.f, 0.f);
	glScalef(5, 4, 2);
	mat(Sienna);
	glutSolidCube(20);
	glPopMatrix();

	//pillow
	glPushMatrix();
	glTranslatef(-71.f, -73.f, 20.f);
	glRotatef(0, 1.f, 0.f, 0.f);
	glScalef(3, 1, 1);
	mat(0.7f, 0.10f, 0.1f);
	glutSolidCube(20);
	glPopMatrix();
	glPopMatrix();
}

//Bed lamp
void lamp(void) {

	glPushMatrix();
	glTranslatef(40, -55, -100);
	glScalef(5, 5, 5);

	
	//lamp pedestal
	mat(red);
	glPushMatrix();
	glTranslatef(0, -6.5, 0);
	glScalef(2, 0.4, 2);
	glutSolidCube(3);
	glPopMatrix();


	//lamp holder
	mat(white);
	glPushMatrix();				
	glTranslatef(0, -10, 0);
	glRotated(-90, 1, 0, 0);
	glScalef(0.8, 0.8, 1);
	gluCylinder(quadobj, 1.f, 0.8f, 10.f, 20.f, 20.f);
	glPopMatrix();

	//lamp light
	mat(yellow);
	glPushMatrix();
	glTranslatef(0, -2.0, 0);
	glRotated(-90, 1, 0, 0);
	glScalef(2.8, 2.8, 0.5);
	gluCylinder(quadobj, 1.f, 0.8f, 10.f, 20.f, 20.f);
	glutSolidCylinder( 0.8f, 10.f, 20.f, 20.f);
	glPopMatrix();

	glPopMatrix();
}

void window(void) {

	//background
	glLineWidth(6);
	for (float i = 105; i < 173; i++)
	{
		glBegin(GL_LINES);
		if (daytime == 0)
		{
			mat(0.7f, 0.7f, 0.7f);
		}
		else
		{
			mat(1.f, 1.f, 1.f);
		}
		glVertex3f(i - 40, 120.0f, -200.0f);
		glVertex3f(i - 40, 60.0f, -200.0f);
		glEnd();
	}

	//frame
	glPushMatrix();
	mat(0.4f, 0.20f, 0.f);
	glLineWidth(6);
	glTranslatef(-40.f, 0.f, 0);
	glBegin(GL_LINES);
	glVertex3f(100, 120.0, -198.f);
	glVertex3f(175, 120.0, -198.f);
	glVertex3f(100, 90.0, -198.f);
	glVertex3f(175, 90.0, -198.f);
	glVertex3f(100, 60.0, -198.f);
	glVertex3f(175, 60.0, -198.f);
	glVertex3f(102, 120.0, -198.f);
	glVertex3f(102, 60.0, -198.f);
	glVertex3f(137, 120.0, -198.f);
	glVertex3f(137, 60.0, -198.f);
	glVertex3f(173, 120.0, -198.f);
	glVertex3f(173, 60.0, -198.f);
	glEnd();
	glPopMatrix();


}

void circle(int x0, int y0, double r, float z)
{
	int x = 0;
	int y = (int)r;
	//第一个点坐标	
	int d = int(3 - 2 * r);
	glBegin(GL_POINTS);
	while (y >= x)		//draw the 1/8 circle
	{
		glVertex3f(x0 + x, y0 + y, z);
		glVertex3f(x0 + y, y0 + x, z);
		glVertex3f(x0 + y, y0 - x, z);
		glVertex3f(x0 + x, y0 - y, z);
		glVertex3f(x0 - x, y0 - y, z);
		glVertex3f(x0 - y, y0 - x, z);
		glVertex3f(x0 - y, y0 + x, z);
		glVertex3f(x0 - x, y0 + y, z);
		if (d < 0)
			d += 2 * x + 3;
		else
		{
			d += 2 * (x - y) + 5;
			y--;
		}
		x++;
	}
	glEnd();
}

void calendar(void) {
	glPushMatrix();
	glTranslatef(90, 0, -100);
	glRotatef(90, 0, 1, 0);
	mat(red);

	glBegin(GL_POLYGON);
	glVertex3f(-85.0, 100.0, -198.f);
	glVertex3f(-15.0, 100.0, -198.f);
	glVertex3f(-15.0, 50.0, -198.f);
	glVertex3f(-85.0, 50.0, -198.f);
	glEnd();


	//smile face
	glLineWidth(1);
	mat(yellow);
	circle(-49, 75, 15.0, -197.2f);
	circle(-49, 75, 22.0, -196.6f);
	circle(-59, 80, 8.0, -196.6f);
	circle(-39, 80, 8.0, -196.6f);


	mat(red);
	glRectZplane(-85, 100, -15, 70, -196.9f);
	glRectZplane(-68, 80.0, -30, 70.0, -196.4f);


	//calendar bottom background 
	mat(0.9, 0.9, 0.9);
	glRectZplane(-85, 0, -15, 50, -199.f);

	//cut-off rule
	glBegin(GL_LINES);
	mat(0.4, 0.4, 0.4);
	for (i = 50; i >= 0; i -= 10) {
		glVertex3f(-85.0, i, -198.f);
		glVertex3f(-15.0, i, -198.f);
	}

	for (i = -15; i >= -85; i -= 10) {
		glVertex3f(i, 50.0, -198.f);
		glVertex3f(i, 0.0, -198.f);
	}
	glEnd();

	glPopMatrix();


}

void wall(void) {

	mat(yellow);


	glPushMatrix();
	glTranslatef(right_base, bottom_base, back_base);
	// Back wall
	drawCuboid(0,0,0, width, height, wall_thick);

	//Right wall
	drawCuboid(0, 0, 0, wall_thick, height, length);
	//Left wall
	drawCuboid(width, 0, 0, wall_thick, height, length);
	//Bottom wall
	drawCuboid(0,0,0, width, wall_thick, length);
	//Top wall
	drawCuboid(0, height, 0, width+ wall_thick, wall_thick, length);
	glPopMatrix();


}

// Draw a clock
void clock_on_wall() {
	glPushMatrix();
	glTranslatef(right_base+150, bottom_base+200, back_base+ wall_thick+3);
	glScalef(0.3, 0.3, 0.3);
	mat(1, 1, 1);

	// Draw the outline of the clock
	glBegin(GL_POLYGON);
	for (int i = 0; i <= 3600; i++) {
		glVertex3f(75 * cos(2 * pi * i / 3600), 75 * sin(2 * pi * i / 3600),0);
	}
	glEnd();

	mat(0, 0, 0);
	glLineWidth(1);
	for (int i = 0; i < 12; i++) {
		glBegin(GL_LINES);
		glVertex3f(65 * cos(2 * pi * i / 12), 65 * sin(2 * pi * i / 12),1);
		glVertex3f(75 * cos(2 * pi * i / 12), 75 * sin(2 * pi * i / 12),1);
		glEnd();
	}


	// Draw a minute hand
	glPushMatrix();
	glRotatef(-cp, 0, 0, 1);
	glLineWidth(1);
	glBegin(GL_LINES);
	glVertex3f(0, 0,1);
	glVertex3f(0, 65,1);
	glEnd();
	glPopMatrix();

	// Draw an hour hand
	glPushMatrix();
	glRotatef(-cp / 12, 0, 0, 1);
	glLineWidth(2);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 1);
	glVertex3f(0, 40, 1);
	glEnd();
	glPopMatrix();
	glPopMatrix();

}

void Robot(GLfloat x, GLfloat y, GLfloat z)
{
	GLUquadricObj* myRobot;
	myRobot = gluNewQuadric();
	gluQuadricNormals(myRobot, GLU_SMOOTH);

	
	glPushMatrix();
	glScaled(robotmul, robotmul, robotmul);
	glTranslatef(x + (robotmul - 7) * 1.5, y + (robotmul - 7) * 1.5, z - (robotmul - 7) * 1.5 -10);
	glRotated(robot_angle, 0, 1, 0);

	//body
	mat(gold);
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	gluCylinder(myRobot, 1, 1, 1.5, 16, 16);
	glPopMatrix();

	//hand1
	mat(yellow);
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslatef(1.5, 0, -0.3);
	glRotatef(-45, 0, 1, 1);
	gluCylinder(myRobot, 0.2, 0.2, 1, 16, 16);
	glPopMatrix();

	//hand2
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslatef(-1.5, 0, -0.3);
	glRotatef(45, 0, 1, 1);
	gluCylinder(myRobot, 0.2, 0.2, 1, 16, 16);
	glPopMatrix();

	//foot1
	mat(yellow);
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslatef(0.5, 0, 1.5);
	gluCylinder(myRobot, 0.2, 0.2, 0.5, 16, 16);
	glPopMatrix();

	//foot2
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslatef(-0.5, 0, 1.5);
	gluCylinder(myRobot, 0.2, 0.2, 0.5, 16, 16);
	glPopMatrix();

	//antenna1
	mat(yellow);
	glPushMatrix();
	glTranslatef(0.7, 1.2, 0);
	glRotatef(90, 3, -1.5, 0);
	gluCylinder(myRobot, 0.1, 0.1, 0.5, 16, 16);
	glPopMatrix();

	//antenna2
	glPushMatrix();
	glTranslatef(-0.7, 1.2, 0);
	glRotatef(90, 3, 1.5, 0);
	gluCylinder(myRobot, 0.1, 0.1, 0.5, 16, 16);
	glPopMatrix();

	//head
	mat(LightYellow1);
	glPushMatrix();
	glutSolidSphere(1, 16, 16);
	glPopMatrix();

	glPopMatrix();

}

// Read image and bind texture
GLuint setTexture(const char* fileName) {
	GLuint lastTextureID = 0, textureID = 0;
	GLubyte* pixeldata = 0;

	// Read in and open an image file
	FILE* file = NULL; // The image file should be placed in the same folder with the source code.
	fopen_s(&file, fileName, "rb"); // read in binary mode
	if (file == 0) {
		return 0;
	}
	// Get the width and height of image
	// Reposition stream position indicator
	// SEEK_SET: Beginning of file
	fseek(file, 0x0012, SEEK_SET);
	fread(&imageWidth, sizeof(imageWidth), 1, file);
	fread(&imageHeight, sizeof(imageHeight), 1, file);
	fseek(file, 54, SEEK_SET);

	// Count the length of in the image by pixel
	// Pixel data consists of three colors red, green and blue
	pixelLength = imageWidth * 3;
	while (pixelLength % 4 != 0) {
		pixelLength++;
	}
	// Pixel data length = width * height
	pixelLength *= imageHeight;
	// Malloc for the image by pixel
	pixeldata = (GLubyte*)malloc(pixelLength); // memory allocation

	// Close file
	if (pixeldata == 0) {
		fclose(file);
		return 0;
	}

	if (fread(pixeldata, pixelLength, 1, file) <= 0) {
		free(pixeldata);
		fclose(file);
		return 0;
	}

	glGenTextures(1, &textureID);
	if (textureID == 0) {
		free(pixeldata);
		fclose(file);
		return 0;
	}

	// Set texture parameters
	GLint last_texture_ID = lastTextureID;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture_ID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0,
		GL_BGR_EXT, GL_UNSIGNED_BYTE, pixeldata);
	glBindTexture(GL_TEXTURE_2D, lastTextureID);
	free(pixeldata);

	return textureID;
}

void floor_texture() {
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	if (daytime == 1) {
		glBindTexture(GL_TEXTURE_2D, floor_daytime);
	}
	else {
		glBindTexture(GL_TEXTURE_2D, floor_night);
	}
	glTranslatef(right_base, bottom_base, back_base);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(0, wall_thick+1, 0);
	glTexCoord2f(0, 1); glVertex3f(width, wall_thick + 1, 0);
	glTexCoord2f(1, 1); glVertex3f(width, wall_thick + 1, length);
	glTexCoord2f(1, 0); glVertex3f(0, wall_thick + 1, length);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//init_customized_texture();
	//glBegin(GL_QUADS);
	// specify the ordinates of checkerboard facing the viewer squarely
	// set the current texture coordinates
	//glTexCoord2f(0.0, 0.0); glVertex3f(right_base, bottom_base + wall_thick+1, back_base);
	//glTexCoord2f(0.0, 1.0); glVertex3f(right_base, bottom_base + wall_thick+1, back_base+length);
	//glTexCoord2f(1.0, 1.0); glVertex3f(right_base+width, bottom_base + wall_thick+1, back_base + length);
	//glTexCoord2f(1.0, 0.0); glVertex3f(right_base + width, bottom_base + wall_thick+1, back_base);
	//glEnd();
	//glDisable(GL_TEXTURE_2D);
}

void wall_texture() {
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	if (daytime == 1) {
		glBindTexture(GL_TEXTURE_2D, wall_daytime);
	}
	else {
		glBindTexture(GL_TEXTURE_2D, wall_night);
	}
	glTranslatef(right_base, bottom_base, back_base);

	// Decorate the back wall
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(0, 0, wall_thick+1);
	glTexCoord2f(0, 1); glVertex3f(0, height, wall_thick + 1);
	glTexCoord2f(1, 1); glVertex3f(width, height, wall_thick + 1);
	glTexCoord2f(1, 0); glVertex3f(width, 0, wall_thick + 1);
	glEnd();

	// Decorate the left wall
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(wall_thick + 1, 0, 0);
	glTexCoord2f(0, 1); glVertex3f(wall_thick + 1, height, 0);
	glTexCoord2f(1, 1); glVertex3f(wall_thick + 1, height, length);
	glTexCoord2f(1, 0); glVertex3f(wall_thick + 1, 0, length);
	glEnd();

	// Decorate the right wall
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(width - 1, 0, 0);
	glTexCoord2f(0, 1); glVertex3f(width  - 1, height, 0);
	glTexCoord2f(1, 1); glVertex3f(width  - 1, height, length);
	glTexCoord2f(1, 0); glVertex3f(width - 1, 0, length);
	glEnd();

	// Decorate the top wall
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(0, height - 1, 0);
	glTexCoord2f(0, 1); glVertex3f(width , height  - 1, 0);
	glTexCoord2f(1, 1); glVertex3f(width , height  - 1, length);
	glTexCoord2f(1, 0); glVertex3f(0, height  -  1, length);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

}

// all the objects will be shown in this function
void display(void)
{
	//Clear the buffer
	glClearColor(0.0, 0.0, 0.0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	light1_lamp();
	glLoadIdentity();
	glPushMatrix();
		glTranslatef(-40, 0, -550);
		glTranslatef(move_right, move_up, 0);
		glRotatef(angleX, 0.0, 1.0, 0.0);
		glRotatef(angleY, 1.0, 0.0, 0.0);
		table();
		cabinet();
		bed();
		lamp();
		clock_on_wall();
		window();
		calendar();
		glTranslatef(40.f, 0.f, 0);
		Robot(robotX, robotY, robotZ);
		wall();
		floor_texture();
		wall_texture();
	glPopMatrix();

	glutSwapBuffers();
	glFlush();

}

void reshape(int w, int h) // Resize the GL Window. w=width, h=height
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void keyboard(unsigned char key, int x, int y) // Handle the keyboard events here
{
	switch (key)
	{
	case '\033':
		exit(0);
		break;

	case '=':
	case '+':
		frustdum = frustdum - 5;
		break;
	case '-':
	case '_':
		frustdum = frustdum + 5;
		break;
	case 's':
	case 'S':
		move_up = move_up + 5;
		break;
	case 'w':
	case 'W':
		move_up = move_up - 5;
		break;
	case 'd':
	case 'D':
		move_right = move_right - 5;
		break;
	case 'a':
	case 'A':
		move_right = move_right + 5;
		break;
	

	case 'o':
	case 'O':
		{
			if (enableLight1 == false)
			{
				enableLight1 = true;
			}
			else
			{
				enableLight1 = false;
			}
		}
		break;

	case 'b':
	case 'B':
		robot_flag = 1- robot_flag;
		break;
	case 'n':
	case 'N':
		robot_mode = 1- robot_mode;
		break;
	case 'm':
	case 'M':
		teapot_flag = 1 - teapot_flag;
		break;
	case ',':
		teapot_clockwise = 1 - teapot_clockwise;
		break;

	//clock
	case 'k':
		time2 -= 10;
		if (time2 < 20) {
			time2 = 20;
		}
		break;
	case 'l':
		time2 += 10;
		if (time2 > 160) {
			time2 = 160;
		}
		break;
	case '0':
		cp = 0;
	
		break;
	case '1':
		cp = 30 * 12;
		break;
	case '2':
		cp = 60 * 12;
		break;
	case '3':
		cp = 90 * 12;
		break;
	case '4':
		cp = 120 * 12;
		break;
	case '5':
		cp = 150 * 12;
		break;
	case '6':
		cp = 180 * 12;
		break;
	case '7':
		cp = 210 * 12;
		break;
	case '8':
		cp = 240 * 12;
		break;
	case '9':
		cp = 270 * 12;
		break;
	case ')'://10
		cp = 300 * 12;
		break;
	case '!'://11
		cp = 330 * 12;
		break;
	case '@'://12
		cp = 360 * 12;
		break;
	case '#'://13
		cp = 390 * 12;
		break;
	case '$'://14
		cp = 420 * 12;
		break;
	case '%'://15
		cp = 450 * 12;
		break;
	case '^'://16
		cp = 480 * 12;
		break;
	case '&'://17
		cp = 510 * 12;
		break;
	case '*'://18
		cp = 540 * 12;
		break;
	case '('://19
		cp = 570 * 12;
		break;
	case 'z'://20
		cp = 600 * 12;
		break;
	case 'x'://21
		cp = 630 * 12;
		break;
	case 'c'://22
		cp = 660 * 12;
		break;
	case 'v'://23
		cp = 690 * 12;
		break;

	}


}

// The mouse() and motion() aims to use mouse to rotate the angle of view
void mouse(int button, int state, int x, int y) {
	if (button = GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			oldX = x + winWidth / 2.0;
			oldY = y + winHeight / 2.0;
		}
	
	}
	

}

void motion(int x, int y) {
	GLint deltaX = oldX - x + winWidth / 2.0;
	GLint deltaY = oldY - y + winHeight / 2.0;
	angleX += 360 * (GLfloat)deltaX / (GLfloat)winWidth;
	angleY += 360 * (GLfloat)deltaY / (GLfloat)winHeight;
	oldX = x + winWidth / 2.0;
	oldY = y + winHeight / 2.0;
	glutPostRedisplay();
}

// Create onTimer1 function to record the time of balloons swinging
void onTimer1(int Value) {
	if (robot_flag == 1) {
		// Increase rotate angle
		if (robot_mode == 1) {
			if (robot_angle >= 360)
				robot_angle = 0;
			robot_angle++;
		}
		else
		{
			if (robot_forth_or_back == 0)
			{
				if (robotZ <= 20)
				{
					robotZ = robotZ + 0.05;
				}
				else
				{
					robot_forth_or_back = 1;
				}
			}
			else
			{
				if (robotZ >= 6)
				{
					robotZ = robotZ - 0.05;
				}
				else
				{
					robot_forth_or_back = 0;
				}
			}
		}
		
	}

	if (teapot_flag == 1) {
		if (teapot_clockwise == 1) {
			if (teapot_angle >= 360)
				teapot_angle = 0;
			teapot_angle++;
		}
		else {
			if (teapot_angle <= -360)
				teapot_angle = 0;
			teapot_angle--;
		}

	}



	glutTimerFunc(time1, onTimer1, 1);
}

// Create onTimer2 function to record time of clock
void onTimer2(int Value) {
	// Increase time
	cp += 30;


	if (cp / 12 % 720 > 180 && cp / 12 % 720 <= 570) {
		daytime = 1;
		
	}
	else
	{
		daytime = 0;
		
	}

	// 5 a.m.- 7a.m.:increase lighting 5 p.m.- 7p.m.:decrease lighting
	if (cp / 12 % 720 > 150 && cp / 12 % 720 <= 210) {
		if (enableLight)
			if (light0_mat1[0] <= 1) {
				for (i = 0; i <= 3; i++) {
					light0_mat1[i] += 0.02;
					light0_diff[i] += 0.02;
				}
				glLightfv(GL_LIGHT0, GL_AMBIENT, light0_mat1);
				glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diff);
				glEnable(GL_LIGHT0);
			}
	}
	else if (cp / 12 % 720 > 510 && cp / 12 % 720 <= 570)
	{
		if (enableLight)
			if (light0_mat1[0] >= 0) {
				for (i = 0; i <= 3; i++) {
					light0_mat1[i] -= 0.02;
					light0_diff[i] -= 0.02;
				}
				glLightfv(GL_LIGHT0, GL_AMBIENT, light0_mat1);
				glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diff);
				glEnable(GL_LIGHT0);
			}
	}
	

	glutTimerFunc(time2, onTimer2, 1);

}

void whenInMainloop()
{
	//	winWidth = w; winHeight = h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Frustum Setting
	glFrustum(-frustdum, frustdum , -frustdum, frustdum, 300., 800.);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Force OpenGL to redraw the current window
	glutPostRedisplay();
}

void menu(int item)
{
	keyboard((unsigned char)item, 0, 0);
}

void menuList() {
	int clockOp, lightOp, zoom, teapotOp, robotOp;

	clockOp = glutCreateMenu(menu);
	glutAddMenuEntry("quicker", 'k');
	glutAddMenuEntry("slower", 'l');
	glutAddMenuEntry("0 o'clock", '0');
	glutAddMenuEntry("1 o'clock", '1');
	glutAddMenuEntry("2 o'clock", '2');
	glutAddMenuEntry("3 o'clock", '3');
	glutAddMenuEntry("4 o'clock", '4');
	glutAddMenuEntry("5 o'clock", '5');
	glutAddMenuEntry("6 o'clock", '6');
	glutAddMenuEntry("7 o'clock", '7');
	glutAddMenuEntry("8 o'clock", '8');
	glutAddMenuEntry("9 o'clock", '9');
	glutAddMenuEntry("10 o'clock", ')');
	glutAddMenuEntry("11 o'clock", '!');
	glutAddMenuEntry("12 o'clock", '@');
	glutAddMenuEntry("13 o'clock", '#');
	glutAddMenuEntry("14 o'clock", '$');
	glutAddMenuEntry("15 o'clock", '%');
	glutAddMenuEntry("16 o'clock", '^');
	glutAddMenuEntry("17 o'clock", '&');
	glutAddMenuEntry("18 o'clock", '*');
	glutAddMenuEntry("19 o'clock", '(');
	glutAddMenuEntry("20 o'clock", 'z');
	glutAddMenuEntry("21 o'clock", 'x');
	glutAddMenuEntry("22 o'clock", 'c');
	glutAddMenuEntry("23 o'clock", 'v');

	lightOp = glutCreateMenu(menu);
	glutAddMenuEntry("open/close the lamp", 'o');
	zoom = glutCreateMenu(menu);
	glutAddMenuEntry("Zoom decreae (-)", '-');
	glutAddMenuEntry("Zoom increase (+)", '+');

	teapotOp = glutCreateMenu(menu);
	glutAddMenuEntry("stop/restart", 'm');
	glutAddMenuEntry("rotate anticlockwise/clockwise", ',');
	robotOp = glutCreateMenu(menu);
	glutAddMenuEntry("stop/restart", 'b');
	glutAddMenuEntry("rotate/forward", 'n');

	glutCreateMenu(menu);
	glutAddMenuEntry("Greeting card Operations", '\0');
	glutAddMenuEntry(" ", '\0'); //space line
	glutAddSubMenu("Clock Operations ", clockOp);
	glutAddSubMenu("Light Operations ", lightOp);
	glutAddSubMenu("Zoom ", zoom);
	glutAddSubMenu("teapot ", teapotOp);
	glutAddSubMenu("robot", robotOp);
	glutAddMenuEntry(" ", '\0');
	glutAddMenuEntry("Quit (Esc)", '\033');
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void main(int argc, char** argv)
{

	/* Initialization of GLUT Library */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	/* Create a window with title specified */
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Room");

	// Add texture information to the object
	wall_night = setTexture("wall_night.bmp");
	wall_daytime = setTexture("wall_daytime.bmp");
	floor_night = setTexture("floor_night.bmp");
	floor_daytime = setTexture("floor_daytime.bmp");
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	init();	// not GLUT call, initialize several parameters
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(whenInMainloop);
	glutTimerFunc(time1, onTimer1, 1);
	glutTimerFunc(time2, onTimer2, 1);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	menuList();
	glutMainLoop();
}
#define GLEW_STATIC
#define FREEGLUT_STATIC

#include <math.h>
#include <GL/freeglut.h>
#include <iostream>

double PI = 3.1415926;

bool timeFlag1 = true; // Set a boolean parameter to control the direction of the swinging balloons
float bp = 0.5; // Set a balloon parameter which could control the size
int ba = 16; // Set a balloon parameter which could control the balloon angles

int time1 = 40; // Declare refresh interval of balloons in ms
int time2 = 40; // Declare refresh interval of clock in ms
int time3 = 40; // Declare refresh interval of balloon in ms
int cp = 0; // Set a clock pointer angle parameter to control clock pointers
int night = 0;// Declare it is night or morning
int building = 0; // 0:FB 1:CB
int clockTime = 0; // Declare the current time

GLint scale = 1;
GLint stepx = 0;
GLint stepy = 0;
GLint width = 800;
GLint height = 500;
GLint groundHeight = 120;
GLint birdx = 0;
GLint birdy = 100;

// declare functions

void whenInMainloop();
void onTimer1(int);
void onTimer2(int);
void onTimer3(int);

void keyboardInput(unsigned char, int, int);
void mouseInput(int button, int state, int x, int y);

void display();
void glArc(double x, double y, double start_angle, double end_angle, double radius, int MODE);
void glCircle(double x, double y, double radius, int MODE);
void glLines(int leftX, int leftY, int rightX, int rightY);
void glRect(int leftX, int leftY, int rightX, int rightY, int MODE);
void glTri(int x1, int y1, int x2, int y2, int x3, int y3, int MODE);
void background();
void fb();
void cb();
void tree1();
void tree2();
void tree3();
void tree4();
void bird();
void drawClock();
void balloon1();
void balloon2();
void balloon3();
void printBitmapString(void* font, const char* s);
int TextOut(float x, float y, const char* cstr);
void greetingText();


void menu(int item);
void menuList();


// Idle callback function
void whenInMainloop() {
	// Force OpenGL to redraw the current window
	if (scale == 0) scale = 1;
	glViewport(stepx, stepy, width * scale, height * scale);//positionx, positiony, width, height
	glutPostRedisplay();
}

// Create onTimer1 function to record the time of balloons swinging
void onTimer1(int Value) {
	if (timeFlag1 == true) {
		// Increase rotate angle
		ba++;
	}
	else if (timeFlag1 == false) {
		// Decrease rotate angle
		ba--;
	}
	if (ba > 15) {
		timeFlag1 = false;
	}
	else if (ba < -15) {
		timeFlag1 = true;
	}
	glutTimerFunc(time1, onTimer1, 1);
}

// Create onTimer2 function to record time of clock
void onTimer2(int Value) {
	// Increase time
	cp += 30;
	if (cp / 12 % 720 > 0 && cp / 12 % 720 <= 30) {
		clockTime = 0;
	}
	else if (cp / 12 % 720 > 30 && cp / 12 % 720 <= 60)
	{
		clockTime = 1;
	}
	else if (cp / 12 % 720 > 60 && cp / 12 % 720 <= 90)
	{
		clockTime = 2;
	}
	else if (cp / 12 % 720 > 90 && cp / 12 % 720 <= 120)
	{
		clockTime = 3;
	}
	else if (cp / 12 % 720 > 120 && cp / 12 % 720 <= 150)
	{
		clockTime = 4;
	}
	else if (cp / 12 % 720 > 150 && cp / 12 % 720 <= 180)
	{
		clockTime = 5;
	}
	else if (cp / 12 % 720 > 180 && cp / 12 % 720 <= 210)
	{
		clockTime = 6;
	}
	else if (cp / 12 % 720 > 210 && cp / 12 % 720 <= 240)
	{
		clockTime = 7;
	}
	else if (cp / 12 % 720 > 240 && cp / 12 % 720 <= 270)
	{
		clockTime = 8;
	}
	else if (cp / 12 % 720 > 270 && cp / 12 % 720 <= 300)
	{
		clockTime = 9;
	}
	else if (cp / 12 % 720 > 300 && cp / 12 % 720 <= 330)
	{
		clockTime = 10;
	}
	else if (cp / 12 % 720 > 330 && cp / 12 % 720 <= 360)
	{
		clockTime = 11;
	}
	else if (cp / 12 % 720 > 360 && cp / 12 % 720 <= 390)
	{
		clockTime = 12;
	}
	else if (cp / 12 % 720 > 390 && cp / 12 % 720 <= 420)
	{
		clockTime = 13;
	}
	else if (cp / 12 % 720 > 420 && cp / 12 % 720 <= 450)
	{
		clockTime = 14;
	}
	else if (cp / 12 % 720 > 450 && cp / 12 % 720 <= 480)
	{
		clockTime = 15;
	}
	else if (cp / 12 % 720 > 480 && cp / 12 % 720 <= 510)
	{
		clockTime = 16;
	}
	else if (cp / 12 % 720 > 510 && cp / 12 % 720 <= 540)
	{
		clockTime = 17;
	}
	else if (cp / 12 % 720 > 540 && cp / 12 % 720 <= 570)
	{
		clockTime = 18;
	}
	else if (cp / 12 % 720 > 570 && cp / 12 % 720 <= 600)
	{
		clockTime = 19;
	}
	else if (cp / 12 % 720 > 600 && cp / 12 % 720 <= 630)
	{
		clockTime = 20;
	}
	else if (cp / 12 % 720 > 630 && cp / 12 % 720 <= 660)
	{
		clockTime = 21;
	}
	else if (cp / 12 % 720 > 660 && cp / 12 % 720 <= 690)
	{
		clockTime = 22;
	}
	else if (cp / 12 % 720 > 690 && cp / 12 % 720 <= 720)
	{
		clockTime = 23;
	}


	if (cp / 12 % 720 > 180 && cp / 12 % 720 <= 570) {
		night = 0;
	}
	else
	{
		night = 1;
	}

	glutTimerFunc(time2, onTimer2, 1);

}

// Create onTimer3 function to fly the bird
void onTimer3(int Value) {
	if (birdx < width) {
		birdx = birdx + 5;
	}
	else {
		birdx = 0;
	}

	glutTimerFunc(time3, onTimer3, 1);
}

// Create keyBoardInput function to adjust buildings, balloons, clock, viewport, zoom in/out
void keyboardInput(unsigned char key, int x, int y) {

	if (key == 'q' || key == 'Q') {
		exit(0);
	}
	//buildings
	else if(key == 'b'|| key == 'B')
	{
		building = 1 - building;
	}
	//balloons
	else if (key == 'n' || key == 'N') {
		bp = bp - 0.1;
	}
	else if (key == 'm' || key == 'M') {
		bp = bp + 0.1;
	}
	//clock
	else if (key == 'k' || key == 'K') {
		time2 -= 10;
		if (time2 < 20) {
			time2 = 20;
		}
	}
	else if (key == 'l' || key == 'L') {
		time2 += 10;
		if (time2 > 160) {
			time2 = 160;
		}
	}
	else if (key == '0') {
		cp = 0;
	}
	else if (key == '1') {
		cp = 30*12;
	}
	else if (key == '2') {
		cp = 60*12;
	}
	else if (key == '3') {
		cp = 90 * 12;
	}
	else if (key == '4') {
		cp = 120 * 12;
	}
	else if (key == '5') {
		cp = 150 * 12;
	}
	else if (key == '6') {
		cp = 180 * 12;
	}
	else if (key == '7') {
		cp = 210 * 12;
	}
	else if (key == '8') {
		cp = 240 * 12;
	}
	else if (key == '9') {
		cp = 270 * 12;
	}
	else if (key == ')') {
		cp = 300 * 12;
	}
	else if (key == '!') {
		cp = 330 * 12;
	}
	else if (key == '@') {
		cp = 360 * 12;
	}
	else if (key == '#') {
		cp = 390 * 12;
	}
	else if (key == '$') {
		cp = 420 * 12;
	}
	else if (key == '%') {
		cp = 450 * 12;
	}
	else if (key == '^') {
		cp = 480 * 12;
	}
	else if (key == '&') {
		cp = 510 * 12;
	}
	else if (key == '*') {
		cp = 540 * 12;
	}
	else if (key == '(') {
		cp = 570 * 12;
	}
	else if (key == 'z') {
		cp = 600 * 12;
	}
	else if (key == 'x') {
		cp = 630 * 12;
	}
	else if (key == 'c') {
		cp = 660 * 12;
	}
	else if (key == 'v') {
		cp = 690 * 12;
	}

	//viewport
	else if (key == 'a' || key == 'A') // move the viewport to the left
			stepx = stepx + 10;
	
	else if (key == 'w' || key == 'W') // move the viewport up
			stepy = stepy - 10;

	else if (key == 'd' || key == 'D') // move the viewport to the right

			stepx = stepx - 10;	
	else if (key == 's' || key == 'S') // move the viewport down
			stepy = stepy + 10;
	//zoom in
	else if (key == '+' || key == '=') // shrink the viewport

		scale++;
	//zoom out
	else if (key == '-' ) // enlarge the viewport
		scale--;


}

// Create keyBoardInput function to make the bird higher
void mouseInput(int button, int state, int x, int y) {

	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) {
		birdy = birdy + 5;
	}
}


void display() {
	if (night == 0) {
		glClearColor(0.52941, 0.80794, 0.98039, 1);//Set Color: LightSkyBlue
	}
	else {
		glClearColor(0.27451, 0.5098, 0.70588, 1);//Set Color: SteelBlue
	}

	glClear(GL_COLOR_BUFFER_BIT);

	background();
	 //Object 1: foundation building
	if (building == 0) {
		glPushMatrix();
		glTranslatef(0, groundHeight, 0);
		glScalef(1, 1, 1);
		fb();
		glPopMatrix();
	}
	else {
		glPushMatrix();
		glTranslatef(100, 10, 0);
		glScalef(1.3, 1.3, 1);
		cb();
		glPopMatrix();
	}
		
		tree1();
		tree2();
		tree3();
		tree4();
		bird();
	// Object 2: Clock
		drawClock();
	// Object 3: "Happy anniversary!" text
		greetingText();
	// Objecct 4: Balloon

	balloon1();
	balloon2();
	balloon3();

	glFlush();//Make sure the previous OpenGL commands execute immediately (rather than waiting in the buffer) 
	glutSwapBuffers();
}

// glArc, glCircle, glLines, glRect, glTri are used to facilitate drawing
void glArc(double x, double y, double start_angle, double end_angle, double radius, int MODE)
{
	glBegin(MODE);
	double delta_angle = PI / 180;
	for (double i = start_angle; i <= end_angle; i += delta_angle)
	{
		double vx = x + radius * cos(i);
		double vy = y + radius * sin(i);
		glVertex2d(vx, vy);
	}
	glEnd();
}
void glCircle(double x, double y, double radius, int MODE)
{
	glArc(x, y, 0, 2 * PI, radius, MODE);
}
void glLines(int leftX, int leftY, int rightX, int rightY) {
	glBegin(GL_LINES);
	glVertex2d(leftX, leftY);
	glVertex2d(rightX, rightY);
	glEnd();
}
void glRect(int leftX, int leftY, int rightX, int rightY, int MODE) {
	glBegin(MODE);
	glVertex2d(leftX, leftY);
	glVertex2d(rightX, leftY);
	glVertex2d(rightX, rightY);
	glVertex2d(leftX, rightY);
	glEnd();
}
void glTri(int x1, int y1, int x2, int y2, int x3, int y3, int MODE) {
	glBegin(MODE);
	glVertex2d(x1, y1);
	glVertex2d(x2, y2);
	glVertex2d(x3, y3);
	glEnd();
}

void background() {

	if (night == 0) {// morning
		// sky
		glColor3f(0.52941, 0.80794, 0.98039);//Set Color: LightSkyBlue
		glRect(0, height, width, groundHeight, GL_POLYGON);
		// ground
		glColor3ub(211, 211, 211);//Set Color: LightGray
		glRect(0, 0, width, groundHeight, GL_POLYGON);

	}
	else {//night
		// sky
		glColor3ub(70, 130, 180);//Set Color: SteelBlue
		glRect(0, height, width, groundHeight, GL_POLYGON);

		// ground
		glColor3ub(105, 105, 105);//Set Color: DimGrey
		glRect(0, 0, width, groundHeight, GL_POLYGON);

	}
}
void fb() {
	int width = glutGet(GLUT_WINDOW_WIDTH);
	int height = glutGet(GLUT_WINDOW_HEIGHT);
	double midbuilding_width = 400; //midbuilding_width + 2 * smallbuilding = width
	double midbuilding_height = 250;
	double smallbuilding_width = 200;
	double smallbuilding_height = 155;
	double widthOfLine = width / 48;
	double window_width = width / 16;
	double window_height = midbuilding_height / 5;
	double middle_convexwall_width = 200;
	double middle_convexwall_height = 400;
	double door_width = 200;
	double door_height = 100;
	double steelbar_width = 200;
	double steelbar_height = 10;
	double protrusion_width = 70;
	double protrusion_height = 15;

	//a whole outline of building: incluing the middle and two small buildings
	glColor3ub(205, 205, 180);// Set color: LightYellow3
	glRect(0, 0, width, midbuilding_height, GL_POLYGON);

	//the vertical lines between windows
	glLineWidth(widthOfLine);
	glColor3ub(205, 205, 180);// Set color: LightYellow3
	for (int i = 1; i < 16; i++) {
		glPushMatrix();
		glTranslatef(i * (width / 16), 0, 0);
		glLines(0, 0, 0, midbuilding_height);
		glPopMatrix();
	}
	//the horizontal lines beteewen windows
	glLineWidth(widthOfLine);
	glColor3ub(255, 222, 173);// Set color: NavajoWhite
	for (int i = 1; i < 6; i++) {
		glPushMatrix();
		glTranslatef(0, i * (midbuilding_height / 5), 0);
		glLines(0, 0, 800, 0);
		glPopMatrix();
	}

	//the concave wall in the middle
	glColor3ub(255, 255, 224);// Set color: LightYellow1
	glRect(width / 2 - middle_convexwall_width / 2, door_height, width / 2 + middle_convexwall_width / 2, midbuilding_height, GL_POLYGON);

	//the concave wall between horizaontal lines
	for (int i = 0; i < 4; i++) {
		glPushMatrix();
		glTranslatef(0, i * (midbuilding_height / 5), 0);
		glLineWidth(width / 240);
		glColor3ub(238, 238, 209);// Set color: LightYellow2
		glLines(0, 0, 800, 0);
		glPopMatrix();
	}

	//windows
	//background of window
	for (int i = 0; i < 8; i++) {
		glPushMatrix();
		glTranslatef(i * (width / 8), 0, 0);
		//left-side window glass
		for (int i = 0; i < 5; i++) {
			glPushMatrix();
			glTranslatef(0, i * (midbuilding_height / 5), 0);
			glColor3ub(255, 255, 255);//Set color: white
			glRect(widthOfLine / 2, window_height - widthOfLine / 2, window_width - widthOfLine / 4, widthOfLine / 2, GL_POLYGON);

			//horizontal lines of window 
			glLineWidth(2);
			glColor3ub(46, 139, 87);//Set color: SeaGreen
			glLines(widthOfLine / 2, window_height - widthOfLine / 2, window_width - widthOfLine / 4, window_height - widthOfLine / 2);
			glLines(widthOfLine / 2, window_height / 5 * 4 - widthOfLine / 2, window_width - widthOfLine / 4, window_height / 5 * 4 - widthOfLine / 2);
			glLines(window_width - widthOfLine / 4, window_height / 5 + widthOfLine / 2, widthOfLine / 2, window_height / 5 + widthOfLine / 2);
			glLines(window_width - widthOfLine / 4, widthOfLine / 2, widthOfLine / 2, widthOfLine / 2);

			//vertical lines of window 
			glLines(widthOfLine / 2, widthOfLine / 2, widthOfLine / 2, window_height - widthOfLine / 2);
			glLines(widthOfLine / 2 + window_width / 5, widthOfLine / 2, widthOfLine / 2 + window_width / 5, window_height - widthOfLine / 2);
			glLines(window_width / 5 * 4 - widthOfLine / 4, window_height - widthOfLine / 2, window_width / 5 * 4 - widthOfLine / 4, widthOfLine / 2);
			glLines(window_width - widthOfLine / 4, window_height - widthOfLine / 2, window_width - widthOfLine / 4, widthOfLine / 2);
			glPopMatrix();
		}
		//right-side window glass
		for (int i = 0; i < 5; i++) {
			glPushMatrix();
			glTranslatef(window_width, i * (midbuilding_height / 5), 0);
			glColor3f(1, 1, 1);
			glRect(widthOfLine / 4, window_height - widthOfLine / 2, window_width - widthOfLine / 2, widthOfLine / 2, GL_POLYGON);
			glBegin(GL_POLYGON);
			glVertex2f(widthOfLine / 4, window_height - widthOfLine / 2);
			glVertex2f(window_width - widthOfLine / 2, window_height - widthOfLine / 2);
			glVertex2f(window_width - widthOfLine / 2, widthOfLine / 2);
			glVertex2f(widthOfLine / 4, widthOfLine / 2);
			glEnd();

			//horizontal lines of the window
			glLineWidth(2);
			glColor3ub(46, 139, 87);// Set color: SeaGreen
			glLines(widthOfLine / 4, window_height - widthOfLine / 2, window_width - widthOfLine / 2, window_height - widthOfLine / 2);
			glLines(widthOfLine / 4, window_height / 5 * 4 - widthOfLine / 2, window_width - widthOfLine / 2, window_height / 5 * 4 - widthOfLine / 2);
			glLines(window_width - widthOfLine / 2, window_height / 5 + widthOfLine / 2, widthOfLine / 4, window_height / 5 + widthOfLine / 2);
			glLines(window_width - widthOfLine / 2, widthOfLine / 2, widthOfLine / 4, widthOfLine / 2);

			//vertical lines of the window
			glLines(widthOfLine / 4, widthOfLine / 2, widthOfLine / 4, window_height - widthOfLine / 2);
			glLines(widthOfLine / 4 + window_width / 5, widthOfLine / 2, widthOfLine / 4 + window_width / 5, window_height - widthOfLine / 2);
			glLines(window_width / 5 * 4 - widthOfLine / 2, window_height - widthOfLine / 2, window_width / 5 * 4 - widthOfLine / 2, widthOfLine / 2);
			glLines(window_width - widthOfLine / 2, window_height - widthOfLine / 2, window_width - widthOfLine / 2, widthOfLine / 2);
			glPopMatrix();
		}
		glPopMatrix();
	}

	//roof of the door
	glColor3ub(0, 100, 0);// Set color: DarkGreen
	glRect(width / 2 - door_width / 2 - 5, door_height, width / 2 + door_width / 2, door_height - 20, GL_POLYGON);
	//pillars of the door
	glColor3ub(205, 198, 115);// Set color: Khaki3
	glRect(width / 2 - door_width / 2 + 10, 0, width / 2 - door_width / 2 + 35, door_height - 20, GL_POLYGON);
	glRect(width / 2 + door_width / 2 - 10, 0, width / 2 + door_width / 2 - 35, door_height - 20, GL_POLYGON);

	//background of door
	glColor3ub(255, 255, 224);// Set color: LightYellow1
	glRect(width / 2 - door_width / 2 + 37, 0, width / 2 + door_width / 2 - 35, door_height - 20, GL_POLYGON);


	//roof
	//steel bars
	glColor3f(1, 1, 1);
	glBegin(GL_LINE_STRIP);
	glVertex2f(width / 2 - steelbar_width / 2, midbuilding_height + widthOfLine / 2);
	glVertex2f(width / 2 - steelbar_width / 2, midbuilding_height + widthOfLine / 2 + steelbar_height);
	glVertex2f(width / 2 + steelbar_width / 2, midbuilding_height + widthOfLine / 2 + steelbar_height);
	glVertex2f(width / 2 + steelbar_width / 2, midbuilding_height + widthOfLine / 2);
	glEnd();

	for (int i = 0; i < 8; i++) {
		glPushMatrix();
		glTranslatef(i * steelbar_width / 8, 0, 0);
		glColor3ub(238, 238, 209);// Set color: LightYellow2
		glLines(width / 2 - steelbar_width / 2, midbuilding_height + widthOfLine / 2, width / 2 - steelbar_width / 2, midbuilding_height + widthOfLine / 2 + steelbar_height);
		glPopMatrix();
	}
	//Protusion of roof
	glColor3f(1, 1, 1);
	glRect(width / 2 - steelbar_width / 2 - protrusion_width - 10, midbuilding_height + widthOfLine / 2, width / 2 - steelbar_width / 2 - 10, midbuilding_height + widthOfLine / 2 + protrusion_height, GL_POLYGON);

	glColor3f(1, 1, 1);
	glRect(width / 2 + steelbar_width / 2 + protrusion_width + 10, midbuilding_height + widthOfLine / 2, width / 2 + steelbar_width / 2 + 10, midbuilding_height + widthOfLine / 2 + protrusion_height, GL_POLYGON);

	//delete the extra space to create the right and left building
	if (night == 0) {
		glColor3f(0.52941, 0.80794, 0.98039);
	}
	else {
		glColor3ub(70, 130, 180);//Set Color: SteelBlue
	}
	glRect(-widthOfLine, midbuilding_height + widthOfLine, smallbuilding_width, smallbuilding_height, GL_POLYGON);
	if (night == 0) {
		glColor3f(0.52941, 0.80794, 0.98039);
	}
	else {
		glColor3ub(70, 130, 180);//Set Color: SteelBlue
	}
	glRect(width - smallbuilding_width, midbuilding_height + widthOfLine, width + widthOfLine, smallbuilding_height, GL_POLYGON);



}
void cb() {
	// concave wall
	glColor3ub(102, 153, 153);
	glRect(60, 270, 220, 160, GL_POLYGON);

	// brace
	glColor3ub(0, 51, 51);
	glRect(70, 130, 210, 112, GL_POLYGON);
	glColor3ub(70, 0, 0);
	glTri(20, 85, 40, 113, 40, 85, GL_POLYGON);
	glRect(40, 113, 230, 85, GL_POLYGON);
	glRect(20, 85, 230, 70, GL_POLYGON);
	glTri(230, 115, 230, 70, 245, 70, GL_POLYGON);

	// cube
	glColor3ub(102, 51, 51);
	glRect(50, 315, 90, 195, GL_POLYGON);
	glTri(90, 315, 90, 280, 95, 280, GL_POLYGON);
	glRect(90, 280, 115, 195, GL_POLYGON);
	glRect(110, 315, 230, 280, GL_POLYGON);
	glRect(115, 280, 230, 250, GL_POLYGON);
	glTri(115, 195, 115, 270, 135, 270, GL_POLYGON);
	glRect(160, 270, 230, 195, GL_POLYGON);
	glRect(50, 170, 230, 120, GL_POLYGON);
	glTri(65, 170, 125, 185, 125, 170, GL_POLYGON);
	glRect(125, 185, 230, 170, GL_POLYGON);

	// lines
	glColor3ub(153, 0, 0);
	glRect(52, 305, 87, 303, GL_POLYGON);
	glRect(52, 295, 90, 293, GL_POLYGON);
	glRect(52, 285, 93, 283, GL_POLYGON);
	glRect(52, 295, 90, 293, GL_POLYGON);
	glRect(112, 305, 197, 303, GL_POLYGON);
	glRect(133, 285, 227, 283, GL_POLYGON);
	glRect(115, 295, 227, 293, GL_POLYGON);
	glRect(52, 275, 227, 273, GL_POLYGON);
	glRect(62, 265, 100, 263, GL_POLYGON);
	glRect(72, 255, 110, 253, GL_POLYGON);
	glRect(52, 245, 95, 243, GL_POLYGON);
	glRect(52, 235, 123, 233, GL_POLYGON);
	glRect(52, 225, 110, 223, GL_POLYGON);
	glRect(72, 215, 119, 213, GL_POLYGON);
	glRect(52, 205, 117, 203, GL_POLYGON);
	glRect(182, 265, 228, 263, GL_POLYGON);
	glRect(202, 255, 228, 253, GL_POLYGON);
	glRect(162, 245, 218, 243, GL_POLYGON);
	glRect(172, 235, 208, 233, GL_POLYGON);
	glRect(162, 225, 178, 223, GL_POLYGON);
	glRect(182, 215, 218, 213, GL_POLYGON);
	glRect(162, 205, 228, 203, GL_POLYGON);
	glRect(115, 178, 228, 176, GL_POLYGON);
	glRect(90, 170, 228, 168, GL_POLYGON);
	glRect(72, 162, 228, 160, GL_POLYGON);
	glRect(52, 154, 188, 152, GL_POLYGON);
	glRect(62, 146, 158, 144, GL_POLYGON);
	glRect(100, 138, 208, 136, GL_POLYGON);
	glRect(52, 130, 228, 128, GL_POLYGON);

	glColor3ub(103, 0, 0);
	glRect(33, 102, 234, 98, GL_POLYGON);
	glRect(22, 88, 238, 84, GL_POLYGON);
	glRect(21, 74, 242, 70, GL_POLYGON);
}


// trees
void tree1() {
	glPushMatrix();
	glTranslatef(100, 50, 0);
	glScalef(2.5, 3, 1);

	// leaf
	glColor3ub(34, 139, 34);//forest green
	glLineWidth(10);
	glTri(3, 53, 13, 40, -7, 40, GL_TRIANGLES);
	glTri(3, 43, 18, 28, -12, 28, GL_TRIANGLES);
	glTri(3, 33, 13, 20, -7, 20, GL_TRIANGLES);
	glTri(3, 23, 18, 10, -12, 10, GL_TRIANGLES);

	// bole
	glColor3ub(184, 134, 11); //Set color: DarkGoldenrod
	glRect(5, 10, 0, 0, GL_POLYGON);
	glPopMatrix();
}
void tree2() {
	glPushMatrix();
	glTranslatef(200, 100, 0);
	glScalef(2.5, 3, 1);
	// leaf
	glColor3ub(34, 139, 34);//forest green
	glLineWidth(10);
	glTri(3, 53, 13, 40, -7, 40, GL_TRIANGLES);
	glTri(3, 43, 18, 28, -12, 28, GL_TRIANGLES);
	glTri(3, 33, 13, 20, -7, 20, GL_TRIANGLES);
	glTri(3, 23, 18, 10, -12, 10, GL_TRIANGLES);
	// bole
	glColor3ub(184, 134, 11); //Set color: DarkGoldenrod
	glRect(5, 10, 0, 0, GL_POLYGON);
	glPopMatrix();
}
void tree3() {
	glPushMatrix();
	glTranslatef(width - 200, 100, 0);
	glScalef(2.5, 3, 1);
	// leaf
	glColor3ub(34, 139, 34);//forest green
	glLineWidth(10);
	glTri(3, 53, 13, 40, -7, 40, GL_TRIANGLES);
	glTri(3, 43, 18, 28, -12, 28, GL_TRIANGLES);
	glTri(3, 33, 13, 20, -7, 20, GL_TRIANGLES);
	glTri(3, 23, 18, 10, -12, 10, GL_TRIANGLES);

	// bole
	glColor3ub(184, 134, 11); //Set color: DarkGoldenrod
	glRect(5, 10, 0, 0, GL_POLYGON);
	glPopMatrix();
}
void tree4() {
	glPushMatrix();
	glTranslatef(width - 100, 50, 0);
	glScalef(2.5, 3, 1);
	// leaf
	glColor3ub(34, 139, 34);//forest green
	glLineWidth(10);
	glTri(3, 53, 13, 40, -7, 40, GL_TRIANGLES);
	glTri(3, 43, 18, 28, -12, 28, GL_TRIANGLES);
	glTri(3, 33, 13, 20, -7, 20, GL_TRIANGLES);
	glTri(3, 23, 18, 10, -12, 10, GL_TRIANGLES);

	// bole
	glColor3ub(184, 134, 11); //Set color: DarkGoldenrod
	glRect(5, 10, 0, 0, GL_POLYGON);
	glPopMatrix();
}
// bird
void bird() {
	//head
	glColor3f(1, 1, 0);
	glCircle(100 + birdx, 100 + birdy, 10, GL_POLYGON);
	//eye
	glColor3f(1, 1, 1);
	glCircle(birdx + 105, birdy + 101, 5, GL_POLYGON);
	glColor3f(0, 0, 0);
	glCircle(birdx + 106, birdy + 101, 1, GL_POLYGON);
	//body
	glColor3f(1, 1, 0);
	glCircle(birdx + 70, birdy + 100, 10, GL_POLYGON);
	glRect(birdx + 70, birdy + 110, 95 + birdx, 90 + birdy, GL_POLYGON);
	//wings
	glTri(birdx + 80, birdy + 104, birdx + 75, birdy + 120, birdx + 90, birdy + 120, GL_POLYGON);
	glTri(birdx + 80, birdy + 104, birdx + 75, birdy + 80, birdx + 90, birdy + 80, GL_POLYGON);
	//mouth
	glTri(birdx + 110, birdy + 103, birdx + 110, birdy + 95, birdx + 120, birdy + 95, GL_POLYGON);
	//tail
	glTri(birdx + 50, birdy + 95, birdx + 50, birdy + 105, birdx + 65, birdy + 100, GL_POLYGON);
}

// Draw a clock
void drawClock() {
	glPushMatrix();
	glTranslatef(675, 400, 0);
	glColor3f(1, 1, 1);

	// Draw the outline of the clock
	glBegin(GL_POLYGON);
	for (int i = 0; i <= 3600; i++) {
		glVertex2f(75 * cos(2 * PI * i / 3600), 75 * sin(2 * PI * i / 3600));
	}
	glEnd();

	glColor3f(0, 0, 0);
	glLineWidth(2);
	for (int i = 0; i < 12; i++) {
		glBegin(GL_LINES);
		glVertex2f(65 * cos(2 * PI * i / 12), 65 * sin(2 * PI * i / 12));
		glVertex2f(75 * cos(2 * PI * i / 12), 75 * sin(2 * PI * i / 12));
		glEnd();
	}
	glPopMatrix();

	// Draw a minute hand
	glPushMatrix();
	glTranslatef(675, 400, 0);
	glRotatef(-cp, 0, 0, 1);
	glLineWidth(2);
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(0, 65);
	glEnd();
	glPopMatrix();

	// Draw an hour hand
	glPushMatrix();
	glTranslatef(675, 400, 0);
	glRotatef(-cp / 12, 0, 0, 1);

	glLineWidth(4);
	glLines(0, 0, 0, 40);
	glPopMatrix();

}

// Draw some Balloons
void balloon1() {
	glPushMatrix();
	glTranslatef(525, 100, 0);
	glRotatef(ba, 0, 0, 1);
	
	// line
	glColor3f(1, 1, 1);
	glLineWidth(2);
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(0, 175 * bp);
	glEnd();

	// sphere
	glColor3ub(255, 106, 106); //Set color: IndianRed1
	glBegin(GL_POLYGON);
	for (int i = 0; i <= 360; i++) {
		glVertex2f(30 * cos(2 * PI * i / 360) * bp, (225 + 50 * sin(2 * PI * i / 360)) * bp);
	}
	glEnd();
	glPopMatrix();

}

void balloon2() {
	glPushMatrix();
	glTranslatef(525, 100, 0);
	glRotatef(20 + ba, 0, 0, 1);
	// line
	glColor3f(1, 1, 1);
	glLineWidth(2);
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(0, 175 * bp);
	glEnd();
	// sphere
	glColor3ub(255, 106, 106); //Set color: IndianRed1
	glBegin(GL_POLYGON);
	for (int i = 0; i <= 360; i++) {
		glVertex2f(30 * cos(2 * PI * i / 360) * bp, (225 + 50 * sin(2 * PI * i / 360)) * bp);
	}
	glEnd();
	glPopMatrix();

}

void balloon3() {
	glPushMatrix();
	glTranslatef(525, 100, 0);
	glRotatef(-20 + ba, 0, 0, 1);
	// line
	glColor3ub(240, 248, 255);
	glLineWidth(2);
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(0, 175 * bp);
	glEnd();
	// sphere
	glColor3ub(255, 106, 106); //Set color: IndianRed1
	glBegin(GL_POLYGON);
	for (int i = 0; i <= 360; i++) {
		glVertex2f(30 * cos(2 * PI * i / 360) * bp, (225 + 50 * sin(2 * PI * i / 360)) * bp);
	}
	glEnd();
	glPopMatrix();

}
// Create printBitmapString and Textout function to print out the text
void printBitmapString(void* font, const char* s) {
	if (s && strlen(s)) {
		while (*s) {
			glutBitmapCharacter(font, *s);
			s++;
		}
	}
}
int TextOut(float x, float y, const char* cstr) {
	glRasterPos2f(x, y);
	printBitmapString(GLUT_BITMAP_HELVETICA_18, cstr);
	return 1;
}
void greetingText() {
	glColor3f(1, 1, 1);
	switch (clockTime)
	{
	case 0:TextOut(230, 430, "Happy Anniversary! It is 0 o'clock.");
		break;
	case 1:TextOut(230, 430, "Happy Anniversary! It is 1 o'clock.");
		break;
	case 2:TextOut(230, 430, "Happy Anniversary! It is 2 o'clock.");
		break;
	case 3:TextOut(230, 430, "Happy Anniversary! It is 3 o'clock.");
		break;
	case 4:TextOut(230, 430, "Happy Anniversary! It is 4 o'clock.");
		break;
	case 5:TextOut(230, 430, "Happy Anniversary! It is 5 o'clock.");
		break;
	case 6:TextOut(230, 430, "Happy Anniversary! It is 6 o'clock.");
		break;
	case 7:TextOut(230, 430, "Happy Anniversary! It is 7 o'clock.");
		break;
	case 8:TextOut(230, 430, "Happy Anniversary! It is 8 o'clock.");
		break;
	case 9:TextOut(230, 430, "Happy Anniversary! It is 9 o'clock.");
		break;
	case 10:TextOut(230, 430, "Happy Anniversary! It is 10 o'clock.");
		break;
	case 11:TextOut(230, 430, "Happy Anniversary! It is 11 o'clock.");
		break;
	case 12:TextOut(230, 430, "Happy Anniversary! It is 12 o'clock.");
		break;
	case 13:TextOut(230, 430, "Happy Anniversary! It is 13 o'clock.");
		break;
	case 14:TextOut(230, 430, "Happy Anniversary! It is 14 o'clock.");
		break;
	case 15:TextOut(230, 430, "Happy Anniversary! It is 15 o'clock.");
		break;
	case 16:TextOut(230, 430, "Happy Anniversary! It is 16 o'clock.");
		break;
	case 17:TextOut(230, 430, "Happy Anniversary! It is 17 o'clock.");
		break;
	case 18:TextOut(230, 430, "Happy Anniversary! It is 18 o'clock.");
		break;
	case 19:TextOut(230, 430, "Happy Anniversary! It is 19 o'clock.");
		break;
	case 20:TextOut(230, 430, "Happy Anniversary! It is 20 o'clock.");
		break;
	case 21:TextOut(230, 430, "Happy Anniversary! It is 21 o'clock.");
		break;
	case 22:TextOut(230, 430, "Happy Anniversary! It is 22 o'clock.");
		break;
	case 23:TextOut(230, 430, "Happy Anniversary! It is 23 o'clock.");
		break;
	default:TextOut(230, 430, "Happy Anniversary!");
		break;
	}

}

// 'Reshape' function is called when the window shape change event occurs
void Reshape(int w, int h) {
	//glViewport(stepx, stepy, width * scale, height * scale);//positionx, positiony, width, height
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT));//display area left right down top
}

// mouse and keyboard can control the display altogether
void menu(int item) 
{
	keyboardInput((unsigned char)item, 0, 0);
}
void menuList() {
	int clockOp, balloonOp, zoom;

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
	
	balloonOp = glutCreateMenu(menu);
	glutAddMenuEntry("larger", 'm');
	glutAddMenuEntry("smaller", 'n');
	zoom = glutCreateMenu(menu);
	glutAddMenuEntry("Zoom decrease (-)", '-');
	glutAddMenuEntry("Zoom increase (+)", '+');
	glutCreateMenu(menu);
	glutAddMenuEntry("Greeting card Operations", '\0');
	glutAddMenuEntry(" ", '\0');
	glutAddSubMenu("Clock Operations ", clockOp);
	glutAddSubMenu("Balloon Operations ", balloonOp);
	glutAddSubMenu("Zoom ", zoom);
	glutAddMenuEntry(" ", '\0');
	glutAddMenuEntry("Change building (b)", 'b');
	glutAddMenuEntry(" ", '\0');
	glutAddMenuEntry("Quit (Esc)", 'q');
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}
// The main function
int main(int argc, char** argv) {
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	// Set the Dimensions
	glutInitWindowSize(800, 500);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Greeting Card");

	glutDisplayFunc(display);

	glutReshapeFunc(Reshape);
	glutIdleFunc(whenInMainloop);
	glutTimerFunc(time1, onTimer1, 1);
	glutTimerFunc(time2, onTimer2, 1);
	glutTimerFunc(time3, onTimer3, 1);
	glutKeyboardFunc(keyboardInput);
	glutMouseFunc(mouseInput);
	menuList();
	glutMainLoop();
}
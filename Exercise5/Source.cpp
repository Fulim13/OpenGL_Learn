#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")

#define WINDOW_TITLE "OpenGL Window"

//bridge controller
float speed = 0.0, bspeed = 0.0;

//projection
float tx = 0, tz = -3, tSpeed = 0.1; // Translate for modelview (x and z axis movement for camera)
float ty = 0, ySpeed = 0.1;           // Camera up/down movement (y axis)
float cameraSpeed = 0.1;              // General camera movement speed
float cameraAngleX = 0, cameraAngleY = 0;  // Camera rotation (X and Y axis rotation)
float ONear = 1, OFar = 20;         // Ortho near far
float PNear = 1, PFar = 30;           // Perspective near far
boolean isOrtho = true;               // Is ortho view flag

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) {
			PostQuitMessage(0);
		}
		else if (wParam == 'N') {
			speed = +0.1;
		}
		else if (wParam == 'M') {
			speed = -0.1;
		}
		else if (wParam == 'W') {         // Move camera forward
			tz -= cameraSpeed;
		}
		else if (wParam == 'S') {         // Move camera backward
			tz += cameraSpeed;
		}
		else if (wParam == VK_UP) {       // Move camera up (on Y-axis)
			ty -= ySpeed;
		}
		else if (wParam == VK_DOWN) {     // Move camera down (on Y-axis)
			ty += ySpeed;
		}
		else if (wParam == VK_LEFT) {     // Move camera left (on X-axis)
			tx += tSpeed;
		}
		else if (wParam == VK_RIGHT) {    // Move camera right (on X-axis)
			tx -= tSpeed;
		}
		else if (wParam == 'A') {         // Rotate camera around X-axis (counterclockwise)
			cameraAngleX += 1.0f;
		}
		else if (wParam == 'D') {         // Rotate camera around X-axis (clockwise)
			cameraAngleX -= 1.0f;
		}
		else if (wParam == 'Q') {         // Rotate camera around Y-axis (counterclockwise)
			cameraAngleY += 1.0f;
		}
		else if (wParam == 'E') {         // Rotate camera around Y-axis (clockwise)
			cameraAngleY -= 1.0f;
		}
		else if (wParam == 'O') {         // Switch to Orthographic projection
			isOrtho = true;
		}
		else if (wParam == 'P') {         // Switch to Perspective projection
			isOrtho = false;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	int n = ChoosePixelFormat(hdc, &pfd);

	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void projection() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (isOrtho) {
		glOrtho(-1, 1, -1, 1, ONear, OFar);  
	}
	else {
		gluPerspective(45.0f, 1.0f, PNear, PFar); 
	}

	glTranslatef(tx, ty, tz);

	glRotatef(cameraAngleY, 0, 1, 0);  
	glRotatef(cameraAngleX, 1, 0, 0);  

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void drawCube(float sx, float sy, float sz) {
	glBegin(GL_QUADS);
	//Face 1: Front
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, sz);
	glVertex3f(sx, 0.0, sz);
	glVertex3f(sx, 0.0, 0.0);

	//Face 2: Right
	glVertex3f(sx, 0.0, 0.0);
	glVertex3f(sx, sy, 0.0);
	glVertex3f(sx, sy, sz);
	glVertex3f(sx, 0.0, sz);

	//Face 3: Top
	glVertex3f(sx, 0.0, sz);
	glVertex3f(0.0, 0.0, sz);
	glVertex3f(0.0, sy, sz);
	glVertex3f(sx, sy, sz);

	//Face 4: Behind
	glVertex3f(sx, sy, sz);
	glVertex3f(sx, sy, 0.0);
	glVertex3f(0.0, sy, 0.0);
	glVertex3f(0.0, sy, sz);

	//Face 5: Left
	glVertex3f(0.0, sy, sz);
	glVertex3f(0.0, 0.0, sz);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, sy, 0.0);

	//Face 6: Bottom
	glVertex3f(0.0, sy, 0.0);
	glVertex3f(sx, sy, 0.0);
	glVertex3f(sx, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glEnd();
}

void drawCube2(float sx, float sy, float sz) {
	glBegin(GL_QUADS);
	//Face 1: Front
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, sz);
	glVertex3f(sx, 0.0, sz);
	glVertex3f(sx, 0.0, 0.0);

	//Face 2: Right
	glVertex3f(sx, 0.0, 0.0);
	glVertex3f(sx, sy, 0.0);
	glVertex3f(sx, sy, sz);
	glVertex3f(sx, 0.0, sz);

	//Face 3: Top
	glVertex3f(sx, 0.0, sz);
	glVertex3f(0.0, 0.0, sz);
	glVertex3f(0.0, sy, sz);
	glVertex3f(sx, sy, sz);

	//Face 4: Behind
	glVertex3f(sx, sy, sz);
	glVertex3f(sx, sy, 0.0);
	glVertex3f(0.0, sy, 0.0);
	glVertex3f(0.0, sy, sz);

	//Face 5: Left
	glVertex3f(0.0, sy, sz);
	glVertex3f(0.0, 0.0, sz);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, sy, 0.0);

	//Face 6: Bottom
	glVertex3f(0.0, sy, 0.0);
	glVertex3f(sx, sy, 0.0);
	glVertex3f(sx, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glEnd();
}

void drawPyramid(float sz) {
	glBegin(GL_QUADS);
	// Face 1 : Bottom
	glVertex3f(0.0, 0.0, sz);
	glVertex3f(sz, 0.0, sz);
	glVertex3f(sz, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);

	// Face 2 & 3 & 4 & 5
	glVertex3f(sz / 2, sz, sz / 2);
	glVertex3f(0.0f, 0.0f, sz);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(sz / 2, sz, sz / 2);

	glVertex3f(sz / 2, sz, sz / 2);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(sz, 0.0, 0.0);
	glVertex3f(sz / 2, sz, sz / 2);

	glVertex3f(sz / 2, sz, sz / 2);
	glVertex3f(sz, 0.0, 0.0);
	glVertex3f(sz, 0.0, sz);
	glVertex3f(sz / 2, sz, sz / 2);

	glVertex3f(sz / 2, sz, sz / 2);
	glVertex3f(sz, 0.0, sz);
	glVertex3f(0.0, 0.0, sz);
	glVertex3f(sz / 2, sz, sz / 2);
	glEnd();
}

void drawSphere(double radius, double slices, double stacks) {
	GLUquadricObj* sphere = NULL;
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluSphere(sphere, radius, slices, stacks);
	gluDeleteQuadric(sphere);
}

void drawCylinder(float topRadius, float baseRadius, double height, double slices, double stacks) {
	glRotatef(90, 0.0, 1.0, 0.0);
	GLUquadricObj* cylinder = NULL;
	cylinder = gluNewQuadric();
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluCylinder(cylinder, topRadius, baseRadius, height, slices, stacks);
	gluDeleteQuadric(cylinder);
}


void display()
{
	glClearColor(0.5255f, 0.6196f, 0.7490f, 0.0);  // Sky blue background
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	// Orthographic view & Perspective view
	projection();

	// Background
	glPushMatrix();
	drawSphere(35, 50, 50);  // Sky sphere
	glPopMatrix();

	// Left tower base 
	glPushMatrix();
	glColor3f(0.3490f, 0.2500f, 0.2235f);
	glTranslatef(-0.55, -0.5, -0.05);
	drawCube(0.3, 0.1, 0.3);
	glPopMatrix();

	// Right tower base 
	glPushMatrix();
	glColor3f(0.3490f, 0.2500f, 0.2235f);
	glTranslatef(0.25, -0.5, -0.05);
	drawCube(0.3, 0.1, 0.3);
	glPopMatrix();

	// Left tower
	glPushMatrix();
	glColor3f(0.4039f, 0.2500f, 0.1333f);
	glTranslatef(-0.5, -0.4, 0.0);
	drawCube(0.2, 0.7, 0.2);
	glPopMatrix();

	// Right tower
	glPushMatrix();
	glColor3f(0.4039f, 0.2500f, 0.1333f);
	glTranslatef(0.3, -0.4, 0.0);
	drawCube(0.2, 0.7, 0.2);
	glPopMatrix();

	// Top left tower 
	glPushMatrix();
	glColor3f(0.5059f, 0.1451f, 0.6000f);
	glTranslatef(-0.50, 0.3, 0);
	drawPyramid(0.2);
	glPopMatrix();

	// Top right tower 
	glPushMatrix();
	glColor3f(0.5059f, 0.1451f, 0.6000f);
	glTranslatef(0.30, 0.3,0);
	drawPyramid(0.2);
	glPopMatrix();

	// Left tower hole 1
	// Surrounding cubes around left tower
	glPushMatrix();
	glColor3f(0.7f, 0.5f, 0.3f);
	glTranslatef(-0.55, -0.4, -0.05);
	drawCube(0.05, 0.8, 0.05);
	glPopMatrix();

	// Pyramid for Surrounding cubes around left tower
	glPushMatrix();
	glColor3f(0.5059f, 0.1451f, 0.6000f);
	glTranslatef(-0.55, 0.4, -0.05);
	drawPyramid(0.05);
	glPopMatrix();

	// Left tower hole 2
	// Surrounding cubes around left tower
	glPushMatrix();
	glColor3f(0.7f, 0.5f, 0.3f);
	glTranslatef(-0.30, -0.4, -0.05);
	drawCube(0.05, 0.8, 0.05);
	glPopMatrix();

	// Pyramid for Surrounding cubes around left tower
	glPushMatrix();
	glColor3f(0.5059f, 0.1451f, 0.6000f);
	glTranslatef(-0.30, 0.4, -0.05);
	drawPyramid(0.05);
	glPopMatrix();

	// Left tower hole 3
	// Surrounding cubes around left tower
	glPushMatrix();
	glColor3f(0.7f, 0.5f, 0.3f);
	glTranslatef(-0.55, -0.4, 0.2);
	drawCube(0.05, 0.8, 0.05);
	glPopMatrix();

	// Pyramid for Surrounding cubes around left tower
	glPushMatrix();
	glColor3f(0.5059f, 0.1451f, 0.6000f);
	glTranslatef(-0.55, 0.4, 0.2);
	drawPyramid(0.05);
	glPopMatrix();

	// Left tower hole 4
	// Surrounding cubes around left tower
	glPushMatrix();
	glColor3f(0.7f, 0.5f, 0.3f);  
	glTranslatef(-0.30, -0.4, 0.2);
	drawCube(0.05, 0.8, 0.05);
	glPopMatrix();

	// Pyramid for Surrounding cubes around left tower
	glPushMatrix();
	glColor3f(0.5059f, 0.1451f, 0.6000f);
	glTranslatef(-0.30, 0.4, 0.2);
	drawPyramid(0.05);
	glPopMatrix();

	// Right tower hole 1
	// Surrounding cubes around Right tower
	glPushMatrix();
	glColor3f(0.7f, 0.5f, 0.3f);  // Cube color
	glTranslatef(0.25, -0.4, -0.05);
	drawCube(0.05, 0.8, 0.05);
	glPopMatrix();

	// Pyramid for Surrounding cubes around Right tower
	glPushMatrix();
	glColor3f(0.5059f, 0.1451f, 0.6000f);
	glTranslatef(0.25, 0.4, -0.05);
	drawPyramid(0.05);
	glPopMatrix();

	// Right tower hole 2
	// Surrounding cubes around Right tower
	glPushMatrix();
	glColor3f(0.7f, 0.5f, 0.3f);  // Cube color
	glTranslatef(0.50, -0.4, -0.05);
	drawCube(0.05, 0.8, 0.05);
	glPopMatrix();

	// Pyramid for Surrounding cubes around Right tower
	glPushMatrix();
	glColor3f(0.5059f, 0.1451f, 0.6000f);
	glTranslatef(0.50, 0.4, -0.05);
	drawPyramid(0.05);
	glPopMatrix();

	// Right tower hole 3
	// Surrounding cubes around Right tower
	glPushMatrix();
	glColor3f(0.7f, 0.5f, 0.3f);  // Cube color
	glTranslatef(0.25, -0.4, 0.2);
	drawCube(0.05, 0.8, 0.05);
	glPopMatrix();

	// Pyramid for Surrounding cubes around Right tower
	glPushMatrix();
	glColor3f(0.5059f, 0.1451f, 0.6000f);
	glTranslatef(0.25, 0.4, 0.2);
	drawPyramid(0.05);
	glPopMatrix();

	// Right tower hole 4
	// Surrounding cubes around Right tower
	glPushMatrix();
	glColor3f(0.7f, 0.5f, 0.3f);  // Cube color
	glTranslatef(0.50, -0.4, 0.2);
	drawCube(0.05, 0.8, 0.05);
	glPopMatrix();

	// Pyramid for Surrounding cubes around left tower
	glPushMatrix();
	glColor3f(0.5059f, 0.1451f, 0.6000f);
	glTranslatef(0.50, 0.4, 0.2);
	drawPyramid(0.05);
	glPopMatrix();

	// Left extra bridge
	glPushMatrix();
	glColor3f(0.3490f, 0.2500f, 0.2235f);
	glTranslatef(-1.0, -0.3, 0.0);
	drawCube(0.5, 0.05, 0.2);
	glPopMatrix();

	// Right extra bridge
	glPushMatrix();
	glColor3f(0.3490f, 0.2500f, 0.2235f);
	glTranslatef(0.5, -0.3, 0.0);
	drawCube(0.5, 0.05, 0.2);
	glPopMatrix();

	// Sky bridge 
	glPushMatrix();
	glColor3f(0.3490f, 0.2500f, 0.2235f);
	glTranslatef(-0.3, 0.15, 0.02);
	drawCube(0.6, 0.05, 0.16);
	glPopMatrix();

	// Bridge controller
	glPushMatrix();
	bspeed = bspeed + speed;
	if (bspeed >= 50) {
		bspeed = 50;
	}
	else if (bspeed <= 0) {
		bspeed = 0;
	}

	// Left control bridge
	glPushMatrix();
	glColor3f(0.3490f, 0.2500f, 0.2235f);
	glTranslatef(-0.3, -0.3, 0.0);
	glRotatef(bspeed, 0.0, 0.0, 1.0);
	drawCube(0.3, 0.05, 0.2);
	glPopMatrix();

	// Right control bridge
	glPushMatrix();
	glColor3f(0.3490f, 0.2500f, 0.2235f);
	glTranslatef(0.3, -0.3, 0.0);
	glRotatef(-bspeed, 0.0, 0.0, 1.0);
	drawCube(-0.3, 0.05, 0.2);
	glPopMatrix();

	glPopMatrix();

	// Left bridge back holder - black
	glPushMatrix();
	glColor3f(0.3490f, 0.2500f, 0.2235f);
	glTranslatef(0.45, 0.15, 0.02);
	glRotatef(-45, 0.0, 0.0, 1.0);
	drawCylinder(0.015, 0.015, 0.6, 20, 20);
	glPopMatrix();

	// Left bridge front holder - black
	glPushMatrix();
	glColor3f(0.3490f, 0.2500f, 0.2235f);
	glTranslatef(0.45, 0.15, 0.18);
	glRotatef(-45, 0.0, 0.0, 1.0);
	drawCylinder(0.015, 0.015, 0.6, 20, 20);
	glPopMatrix();

	// Right bridge back holder - black
	glPushMatrix();
	glColor3f(0.3490f, 0.2500f, 0.2235f);
	glTranslatef(-0.9, -0.29, 0.02);
	glRotatef(45, 0.0, 0.0, 1.0);
	drawCylinder(0.015, 0.015, 0.6, 20, 20);
	glPopMatrix();

	// Right bridge front holder - black
	glPushMatrix();
	glColor3f(0.3490f, 0.2500f, 0.2235f);
	glTranslatef(-0.9, -0.29, 0.18);
	glRotatef(45, 0.0, 0.0, 1.0);
	drawCylinder(0.015, 0.015, 0.6, 20, 20);
	glPopMatrix();

	// Left tower hole - white (same as tower for symmetry)
	glPushMatrix();
	glColor3f(0.3490f, 0.2500f, 0.2235f);
	glTranslatef(0.299, -0.3, 0.02);
	drawCube2(0.202, 0.2, 0.16);
	glPopMatrix();

	// Right tower hole - white (same as tower for symmetry)
	glPushMatrix();
	glColor3f(0.3490f, 0.2500f, 0.2235f);
	glTranslatef(-0.501, -0.3, 0.02);
	drawCube2(0.202, 0.2, 0.16);
	glPopMatrix();
}


//--------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
		NULL, NULL, wc.hInstance, NULL);

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		display();

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------
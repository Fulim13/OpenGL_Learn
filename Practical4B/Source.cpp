#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h> 
#include <cmath>
#include <iostream>

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "glu32.lib")


#define WINDOW_TITLE "OpenGL Window"

#define PI 3.14159265359

using namespace std;

int questionToShow = 1;

//cude variables
float cubeX = 0.0f;
float cubeY = 0.0f;
float cubeZ = 0.0f;

float cubeRotX = 0.0f;
float cubeRotY = 0.0f;
float cubeRotZ = 0.0f;

float movementSpeed = 0.05;
float rotationSpeed = 1.0f; // rotation not use radian, use degree

GLUquadricObj* sphere = NULL;
GLUquadricObj* cylinder = NULL;
int slices = 5;
int stacks = 5;

float speed = 0.0;

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam) {
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;

		case VK_UP:
			slices++;
			break;
		case VK_DOWN:
			slices--;
			break;
		case VK_LEFT:
			stacks--;
			break;
		case VK_RIGHT:
			stacks++;
			break;

		case VK_NUMPAD8:
			cubeZ += movementSpeed;
			break;
		case VK_NUMPAD2:
			cubeZ -= movementSpeed;
			break;
		case VK_NUMPAD4:
			cubeX -= movementSpeed;
			break;
		case VK_NUMPAD6:
			cubeX += movementSpeed;
			break;
		case VK_NUMPAD7:
			cubeY += movementSpeed;
			break;
		case VK_NUMPAD1:
			cubeY -= movementSpeed;
			break;

		case 'T':
			// Rotate on X axis
			cubeRotX += rotationSpeed;
			cout << "RotX: " << cubeRotX << endl;
			break;
		case 'Y':
			// Rotate on X axis
			cubeRotX -= rotationSpeed;
			break;
		case 'U':
			// Rotate on Y axis
			cubeRotY -= rotationSpeed;
			break;
		case 'I':
			// Rotate on Y axis
			cubeRotY += rotationSpeed;
			break;
		case 'O':
			// Rotate on Z axis
			cubeRotZ += rotationSpeed;
			break;
		case 'P':
			// Rotate on Z axis
			cubeRotZ -= rotationSpeed;
			break;

		case 0x31:	// 1 key is pressed
			questionToShow = 1;
			break;
		case 0x32:	// 2 key is pressed
			questionToShow = 2;
			break;
		case 0x33:	// 3 key is pressed
			questionToShow = 3;
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

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

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------

void drawSphere() {
	sphere = gluNewQuadric();
	//https://registry.khronos.org/OpenGL-Refpages/gl2.1/xhtml/gluQuadricDrawStyle.xml
	gluQuadricDrawStyle(sphere, GLU_LINE);
	glColor3f(0.0f, 0.0f, 1.0f);
	gluSphere(sphere, 0.5, slices, stacks);
}

void drawCylinder() {
	// Cylinder is not face on the middle, is face the front of the top part (the sharp part)
	cylinder = gluNewQuadric();
	gluQuadricDrawStyle(cylinder, GLU_LINE);
	glColor3f(0.0f, 0.0f, 1.0f);
	// gluCylinder(GLUquadric obj*, baseRadius, topRadius, height,slices, stacks);
	// gluCylinder(cylinder, 0.2, 0.2, 0.6, slices, stacks);
	gluCylinder(cylinder, 0.01, 0.4, 0.6, slices, stacks);
}

void drawCream(double r) {
	GLUquadricObj* sphere = NULL;
	sphere = gluNewQuadric();
	glColor3f(1.0f, 1.0f, 1.0f);
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricTexture(sphere, true);
	gluSphere(sphere, r, 30, 30);
	gluDeleteQuadric(sphere);
}

void drawCornOutline(double tr, double br, double h) {
	glPushMatrix();
	glRotatef(90, 1.0, 0.0, 0.0); // Align cone with the Z-axis
	GLUquadricObj* cylinder = NULL;
	cylinder = gluNewQuadric();
	glColor3f(.62f, .39f, .10f);
	gluQuadricDrawStyle(cylinder, GLU_LINE); // Set draw style to outline
	gluCylinder(cylinder, tr, br, h, 35, 35); // Draw the outline cone
	gluDeleteQuadric(cylinder); // Clean up
	glPopMatrix();
}

void drawCorn(double tr, double br, double h) {
	glRotatef(90, 1.0, 0.0, 0.0);
	GLUquadricObj* cylinder = NULL;
	cylinder = gluNewQuadric();
	glColor3f(.82f, .49f, .18f);
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluQuadricTexture(cylinder, true);
	gluCylinder(cylinder, tr, br, h, 20, 20);
	gluDeleteQuadric(cylinder);
}

void drawBiskut(double tr, double br, double h) {
	glRotatef(90, 1.0, 0.0, 0.0);
	GLUquadricObj* cylinder = NULL;
	cylinder = gluNewQuadric();
	glColor3f(.48f, .25f, .0f);
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluQuadricTexture(cylinder, true);
	gluCylinder(cylinder, tr, br, h, 20, 20);
	gluDeleteQuadric(cylinder);
}

void drawCherry(double r) {
	GLUquadricObj* sphere = NULL;
	sphere = gluNewQuadric();
	glColor3f(0.8235, 0.0392, 0.1804);
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricTexture(sphere, true);
	gluSphere(sphere, r, 10, 10);
	gluDeleteQuadric(sphere);
}

void drawcherryStick(double tr, double br, double h) {
	glRotatef(80, 1.0, 0.0, 0.0);
	GLUquadricObj* cylinder = NULL;
	cylinder = gluNewQuadric();
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluQuadricTexture(cylinder, true);
	gluCylinder(cylinder, tr, br, h, 20, 20);
	gluDeleteQuadric(cylinder);
}

void display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	switch (questionToShow) {
		// Sphere
		case 1:
			glLoadIdentity();

			glTranslatef(cubeX, cubeY, cubeZ);
			glRotatef(cubeRotX, 1.0f, 0.0f, 0.0f);
			glRotatef(cubeRotY, 0.0f, 1.0f, 0.0f);
			glRotatef(cubeRotZ, 0.0f, 0.0f, 1.0f);
			drawSphere();
			break;

		// Cylinder
		case 2:
			glLoadIdentity();

			glTranslatef(cubeX, cubeY, cubeZ);
			glRotatef(cubeRotX, 1.0f, 0.0f, 0.0f);
			glRotatef(cubeRotY, 0.0f, 1.0f, 0.0f);
			glRotatef(cubeRotZ, 0.0f, 0.0f, 1.0f);
			drawCylinder();
			break;
		case 3:
			glPushMatrix();
			glLoadIdentity();
			glRotatef(-20, 1.0, 0.0, 0.0);

			glPushMatrix();
			speed = speed + 0.05;
			glRotatef(speed, 0.0, 1.0, 0.0);

			glPushMatrix();
			drawCorn(0.2, 0.0, 0.8);
			glPushMatrix();
				glRotatef(-90, 1.0, 0.0, 0.0);
				drawCornOutline(0.2, 0.0, 0.8);
			glPopMatrix();
			glPopMatrix();

			glPushMatrix();
			drawCream(0.18);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(0.0, 0.25, 0.0);
			drawCream(0.18);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(0.1, 0.55, 0.0);
			drawBiskut(0.02, 0.02, 0.4);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(0.13, 0.58, 0.0);
			drawBiskut(0.02, 0.02, 0.4);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(-0.08, 0.43, 0.0);
			drawCherry(0.06);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(-0.08, 0.55, 0.0);
			drawcherryStick(0.005, 0.005, 0.3);
			glPopMatrix();

			glPopMatrix();
			glPopMatrix();
			break;
		}



}
//--------------------------------------------------------------------
// change it main -> console
// WINAPI WinMain -> graphic
int main(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
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
		CW_USEDEFAULT, CW_USEDEFAULT, 600, 600,
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

	glEnable(GL_DEPTH_TEST);
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
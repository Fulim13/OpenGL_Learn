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

//rotation variables
float rotX = 0.0f;
float rotY = 0.0f;
float rotZ = 0.0f;

float rotationSpeed = 3.0f; // rotation not use radian, use degree

float speed = 0.0;
BITMAP BMP;
HBITMAP hBMP = NULL;

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

		case 'T':
			// Rotate on X axis
			rotX += rotationSpeed;
			cout << "rotX: " << rotX << endl;
			break;
		case 'Y':
			// Rotate on X axis
			rotX -= rotationSpeed;
			break;
		case 'U':
			// Rotate on Y axis
			rotY -= rotationSpeed;
			break;
		case 'I':
			// Rotate on Y axis
			rotY += rotationSpeed;
			break;
		case 'O':
			// Rotate on Z axis
			rotZ += rotationSpeed;
			break;
		case 'P':
			// Rotate on Z axis
			rotZ -= rotationSpeed;
			break;

		case 0x31:	// 1 key is pressed
			questionToShow = 1;
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

GLuint loadTexture(LPCSTR filename) {
	GLuint texture = 0;

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	HBITMAP hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), filename, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);

	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	DeleteObject(hBMP);

	return texture;
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

	GLuint textureArr[7];

	glPushMatrix();
	glLoadIdentity();
	glRotatef(-20, 1.0, 0.0, 0.0);

	glPushMatrix();

	// Automatically rotate
	//speed = speed + 0.05;
	//glRotatef(speed, 0.0, 1.0, 0.0);

	glRotatef(rotX, 1.0f, 0.0f, 0.0f);
	glRotatef(rotY, 0.0f, 1.0f, 0.0f);
	glRotatef(rotZ, 0.0f, 0.0f, 1.0f);

	glPushMatrix();
	textureArr[0] = loadTexture("corn.bmp");
	drawCorn(0.2, 0.0, 0.8);
	glDeleteTextures(1, &textureArr[0]);
	glPopMatrix();

	glPushMatrix();
	textureArr[1] = loadTexture("chocolate.bmp");
	drawCream(0.18);
	glDeleteTextures(1, &textureArr[1]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.25, 0.0);
	textureArr[2] = loadTexture("vanilla.bmp");
	drawCream(0.18);
	glDeleteTextures(1, &textureArr[2]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.1, 0.55, 0.0);
	textureArr[3] = loadTexture("biscuit2.bmp");
	drawBiskut(0.02, 0.02, 0.4);
	glDeleteTextures(1, &textureArr[3]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.13, 0.58, 0.0);
	textureArr[4] = loadTexture("biscuit1.bmp");
	drawBiskut(0.02, 0.02, 0.4);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.08, 0.43, 0.0);
	textureArr[5] = loadTexture("cherry.bmp");
	drawCherry(0.06);
	glDeleteTextures(1, &textureArr[5]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.08, 0.55, 0.0);
	textureArr[6] = loadTexture("cherrystick.bmp");
	drawcherryStick(0.005, 0.005, 0.3);
	glDeleteTextures(1, &textureArr[6]);
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();
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
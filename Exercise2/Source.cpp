#include <Windows.h>
#include <gl/GL.h>
#include <cmath>

#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "OpenGL Window"

#define PI 3.14159265359

float r = 1.0f;
float g = 1.0f;
float b = 1.0f;

float quadPosX = 0.0f;
float quadPosY = 0.0f;
float quadPosZ = 0.0f;
int questionToShow = 1;

float angle = 0.0f;
float radius = 0.5f;

float scaleVal = 0;
bool scaleReset = true;
float scaleSpeed = .005;

// Color variables
float rStar = 1.0f, gStar = 1.0f, bStar = 0.0f;
float colorIncrement = 0.01f;

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
			quadPosY += 0.1f;
			break;
		case VK_DOWN:
			quadPosY -= 0.1f;
			break;
		case VK_LEFT:
			quadPosX -= 0.1f;
			break;
		case VK_RIGHT:
			quadPosX += 0.1f;
			break;
		case 0x52:
			r += 1.0f;
			g = .0f;
			b = .0f;
			break;
		case 0x47:
			g += 1.0f;
			r = .0f;
			b = .0f;
			break;
		case 0x42:
			b += 1.0f;
			g = .0f;
			r = .0f;
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
		case 0x34:	// 4 key is pressed
			questionToShow = 4;
			break;
		case VK_SPACE:
			quadPosX = 0.0f;
			quadPosY = 0.0f;
			quadPosZ = 0.0f;
			r = 1.0f;
			g = 1.0f;
			b = 1.0f;
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

void q1() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(quadPosX, quadPosY, quadPosZ);
	glBegin(GL_QUADS);					//Begin to draw quads
	glColor3f(r, g, b);
	glVertex2d(-0.5, -0.5);			//P1
	glVertex2d(-0.5, 0.5);			//P2
	glVertex2d(0.5, 0.5);			//P3
	glVertex2d(0.5, -0.5); 			//P4	
	glEnd();
}

void q2() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	float x = 0.0f, y = 0.0f, radius = 0.5f;
	int numPoints = 5;

	// Set the color (automatically updated)
		glColor3f(rStar, gStar, bStar);

	// Update the color values
	rStar += colorIncrement;
	if (rStar > 1.0f || rStar < 0.0f) colorIncrement = -colorIncrement; // Reverse direction for R

	gStar += colorIncrement * 0.8f;
	if (gStar > 1.0f || gStar < 0.0f) colorIncrement = -colorIncrement; // Reverse direction for G

	bStar += colorIncrement * 0.6f;
	if (bStar > 1.0f || bStar < 0.0f) colorIncrement = -colorIncrement; // Reverse direction for B
	// Calculate the angle for each point of the star
	float angleStep = 2 * PI / numPoints;
	float innerRadius = radius / 2.5f;  // The inner radius (for the star's inward points)

	glBegin(GL_TRIANGLES);

	for (int i = 0; i < numPoints; ++i) {
		// Outer point (the points of the star)
		float x1 = x + radius * cos(i * angleStep);
		float y1 = y + radius * sin(i * angleStep);

		// Inner point (the points of the inner part of the star)
		float x2 = x + innerRadius * cos(i * angleStep + angleStep / 2);
		float y2 = y + innerRadius * sin(i * angleStep + angleStep / 2);

		// Next outer point
		float x3 = x + radius * cos((i + 1) * angleStep);
		float y3 = y + radius * sin((i + 1) * angleStep);

		// Draw the triangle
		glVertex2f(x, y);  // Center of the star
		glVertex2f(x1, y1); // Outer point
		glVertex2f(x2, y2); // Inner point

		glVertex2f(x, y);  // Center of the star
		glVertex2f(x2, y2); // Inner point
		glVertex2f(x3, y3); // Next outer point
	}

	glEnd();
}

void q3() {
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();  // Reset the modelview matrix

	// Calculate the new position for circular motion
	float transX = radius * cos(angle);  // X-coordinate based on cosine
	float transY = radius * sin(angle);  // Y-coordinate based on sine

	// Increment the angle for counter-clockwise motion
	angle += 0.05f;  // Adjust increment for speed; smaller value = slower motion

	// Reset angle to prevent overflow (optional)
	if (angle >= 2 * PI) {
		angle -= 2 * PI;
	}

	// Apply translation (move the object to the new position)
	glTranslatef(transX, transY, 0.0f);

	// Apply rotation (rotate around the center of the object)
	glRotatef(angle * (180.0f / PI), 0.0f, 0.0f, 1.0f);

	// Draw the square
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0f);  // Set color to green

	glVertex2f(-0.03f, 0.03f);  // Top-left
	glVertex2f(0.03f, 0.03f);   // Top-right
	glVertex2f(0.03f, -0.03f);  // Bottom-right
	glVertex2f(-0.03f, -0.03f); // Bottom-left

	glEnd();
}

void q4() {
	glLoadIdentity();

	// Reset scaling if switching back to this view
	if (scaleReset) {
		scaleVal = 1.0f;   // Reset scaling factor
		scaleReset = false; // Disable reset until view changes
	}

	scaleVal += scaleSpeed;

	glScalef(scaleVal, scaleVal, 0);

	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);

	glVertex2f(-.15, .15);
	glVertex2f(.15, .15);
	glVertex2f(.15, -.15);
	glVertex2f(-.15, -.15);
	glEnd();
}



void display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //clear the color of the screen to black
	glClear(GL_COLOR_BUFFER_BIT); //Clear the color buffer
	switch (questionToShow) {
	case 1:
		q1();
		break;
	case 2:
		q2();
		break;
	case 3:
		q3();
		break;
	case 4:
		q4();
		break;
	}



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
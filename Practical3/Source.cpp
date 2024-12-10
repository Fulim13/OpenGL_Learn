
#include <Windows.h>
#include <gl/GL.h>
#include <math.h>

#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "OpenGL Window"

float r = 1.0f;
float g = 1.0f;
float b = 1.0f;

float quadPosX = 0.0f;
float quadPosY = 0.0f;
float quadPosZ = 0.0f;
float quadPosX2 = 0.0f;
float quadPosY2 = 0.0f;
float quadPosZ2 = 0.0f;
float quadPosX3 = 0.0f;
float quadPosY3 = 0.0f;
float quadPosZ3 = 0.0f;
int questionToShow = 3;

float x = 0.0, y = 0.0;						// Origin of circle
float radius = 0.2;							// Radius of circle
float angle = 0.0;							// Angle of circle (in radian)
float x2 = 0.0, y2 = 0.0;					// Point on circle
const double PI = 3.14159265;				// Value of PI
float noOfTriangle = 30;					// Number of triangle to draw circle

float spinnerAngle = 0.0f;


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

			case VK_NUMPAD8:
				quadPosY2 += 0.1f;
				break;
			case VK_NUMPAD2:
				quadPosY2 -= 0.1f;
				break;
			case VK_NUMPAD4:
				quadPosX2 -= 0.1f;
				break;
			case VK_NUMPAD6:
				quadPosX2 += 0.1f;
				break;

			case 0x57: // 'W'
				quadPosY3 += 0.1f;
				break;
			case 0x53: // 'S'
				quadPosY3 -= 0.1f;
				break;
			case 0x41: // 'A'
				quadPosX3 -= 0.1f;
				break;
			case 0x44: // 'D'
				quadPosX3 += 0.1f;
				break;

			case 0x52: // 'R'
				r += 1.0f;
				g = .0f;
				b = .0f;
				break;
			case 0x47: // 'G'
				g += 1.0f;
				r = .0f;
				b = .0f;
				break;
			case 0x42: // 'B'
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

			case VK_SPACE:
				quadPosX = 0.0f;
				quadPosY = 0.0f;
				quadPosZ = 0.0f;
				break;

			case 'Z':
				spinnerAngle += 1.0f;
				break;
			case 'X':
				spinnerAngle -= 1.0f;
				break;
			case 'C':
				spinnerAngle = 0.0f;
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

void drawCircle(){
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);		// Red
	glVertex2f(x, y);					// Draw the origin of the circle
	for (angle = 0; angle <= 2 * PI; angle += (2 * PI) / noOfTriangle) {
		x2 = x + radius * cos(angle);	// Calculate the x component
		y2 = y + radius * sin(angle);	// Calculate the y component
		glVertex2f(x2, y2);				// Draw the point on the circle
	}
	glEnd();
}

void drawCloud() {
	glPushMatrix();
		glTranslatef(0.2f, 0.0f, 0.0f);
		glScalef(0.5f, 0.5f, 1.0f);
		drawCircle();
	glPopMatrix();

	glPushMatrix();	
		glTranslatef(-0.2f, 0.0f, 0.0f);
		glScalef(0.45f, 0.45f, 1.0f);
		drawCircle();
	glPopMatrix();

	glPushMatrix();
		drawCircle();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.1f, 0.13f, 0.0f);
		glScalef(0.4f, 0.4f, 1.0f);
		drawCircle();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-0.1f, 0.13f, 0.0f);
		glScalef(0.4f, 0.4f, 1.0f);
		drawCircle();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.2f, 0.07f, 0.0f);
		glScalef(0.4f, 0.4f, 1.0f);
		drawCircle();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-0.2f, 0.07f, 0.0f);
		glScalef(0.4f, 0.4f, 1.0f);
		drawCircle();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.15f, -0.1f, 0.0f);
		glScalef(0.4f, 0.4f, 1.0f);
		drawCircle();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-0.15f, -0.1f, 0.0f);
		glScalef(0.4f, 0.4f, 1.0f);
		drawCircle();
	glPopMatrix();

}

void drawTriangle(float r, float g, float b) {
	glBegin(GL_TRIANGLES);
		glColor3f(r, g, b);		// Green
		glVertex2f(0.0, 0.5);
		glVertex2f(0.5, -0.5);
		glVertex2f(-0.5, -0.5);
	glEnd();
}

void drawBuilding() {
	glColor3f(.95f, .82f, .74f);

	glBegin(GL_QUADS);
	glVertex2f(-.1, .3f);
	glVertex2f(.1f, .3f);
	glVertex2f(.25f, -.7f);
	glVertex2f(-.25f, -.7f);
	glEnd();

	glPushMatrix();
	glRotatef(spinnerAngle, 0.0f, 0.0f, 1.0f); // Rotate the spinner
	glColor3f(0.72f, 0.45f, 0.2f);
	

	glPushMatrix();
		glTranslatef(-.1f, .0f, .0f);
		glRotatef(-45.0f, .0f, .0f, 1.0f);
		glBegin(GL_QUADS);
		glVertex2f(-0.75f, 0.3f);
		glVertex2f(0.55f, 0.3f);
		glVertex2f(0.55f, 0.2f);
		glVertex2f(-0.75f, 0.2f);
		glEnd();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(.1f, .0f, .0f);
		glRotatef(45.0f, .0f, .0f, 1.0f);
		glBegin(GL_QUADS);
		glVertex2f(-0.55f, 0.3f);
		glVertex2f(0.75f, 0.3f);
		glVertex2f(0.75f, 0.2f);
		glVertex2f(-0.55f, 0.2f);
		glEnd();
	glPopMatrix();

	glPushMatrix();
		glBegin(GL_QUADS);
		glVertex2f(-0.65f, 0.3f);
		glVertex2f(0.65f, 0.3f);
		glVertex2f(0.65f, 0.2f);
		glVertex2f(-0.65f, 0.2f);
		glEnd();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(.25f, .2f, .0f);
		glRotatef(90.0f, .0f, .0f, 1.0f);
		glBegin(GL_QUADS);
		glVertex2f(-0.65f, 0.3f);
		glVertex2f(0.65f, 0.3f);
		glVertex2f(0.65f, 0.2f);
		glVertex2f(-0.65f, 0.2f);
		glEnd();
	glPopMatrix();

	glPopMatrix();

}



void drawMountain(float r, float g, float b) {
	drawTriangle(r, g, b);
}


void drawSun() {

}

void drawBackground() {
	// Draw the blue sky
	glColor3f(0.529f, 0.808f, 0.922f); // Sky blue color
	glBegin(GL_QUADS);
	glVertex2f(-1.0f, 1.0f);  // Top left
	glVertex2f(1.0f, 1.0f);  // Top right
	glVertex2f(1.0f, -0.2f); // Bottom right
	glVertex2f(-1.0f, -0.2f); // Bottom left
	glEnd();

	// Draw the green ground
	glColor3f(0.0f, 0.6f, 0.0f); // Green color
	glBegin(GL_QUADS);
	glVertex2f(-1.0f, -1.0f); // Bottom left
	glVertex2f(1.0f, -1.0f); // Bottom right
	glVertex2f(1.0f, -0.2f); // Top right
	glVertex2f(-1.0f, -0.2f); // Top left
	glEnd();
}

void drawWindMill() {
	drawBackground();

	glPushMatrix();
		glTranslatef(-0.4f, 0.1f, 0.0f);
		glScalef(0.8f, 0.6f, 1.0f);
		drawMountain(0.4f, 0.3f, 0.2f);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-0.8f, 0.0f, 0.0f);
		glScalef(0.6f, 0.4f, 1.0f);
		drawMountain(0.6f, 0.6f, 0.6f);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-0.1f, 0.0f, 0.0f);
		glScalef(0.6f, 0.4f, 1.0f);
		drawMountain(0.4f, 0.5f, 0.3f);
	glPopMatrix();


	glPushMatrix();
		glTranslatef(0.6f, 0.8f, 0.0f);
		glScaled(0.5, 0.5, 1.0);
		drawCloud();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.2f, 0.5f, 0.0f);
		glScaled(0.5, 0.5, 1.0);
		drawCloud();
	glPopMatrix();


	glPushMatrix();
		glTranslatef(-0.4f, 0.8f, 0.0f);
		glScaled(0.5, 0.5, 1.0);
		drawCloud();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-0.8f, 0.5f, 0.0f);
		glScaled(0.5, 0.5, 1.0);
		drawCloud();
	glPopMatrix();

	glPushMatrix();
		drawBuilding();
	glPopMatrix();
}

void display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); 
	glClear(GL_COLOR_BUFFER_BIT);
	switch (questionToShow) {
		case 1:
			glLoadIdentity();
			glPushMatrix();
				glTranslatef(quadPosX3, quadPosY3, quadPosZ3); // Move Both Quads (Parent) with W, A, S, D //Parent can affect both children, but children can't affect parent
				glPushMatrix();
					glTranslatef(quadPosX, quadPosY, quadPosZ); // Move First Quad (Child) with Arrow Keys
					glBegin(GL_QUADS);
						glColor3f(.0f, .0f, 1.0f);		// Blue
						glVertex2d(-0.5, 0.5);
						glVertex2d(0.0, 0.5);
						glVertex2d(0.0, -0.5);
						glVertex2d(-0.5, -0.5);
					glEnd();
				glPopMatrix();

				glPushMatrix();
					glTranslatef(quadPosX2, quadPosY2, quadPosZ2); // Move Second Quad (Child) with Numpad 8, 4, 5, 6
					glBegin(GL_QUADS);
						glColor3f(1.0f, .0f, .0f);		// Red	
						glVertex2d(0.0, 0.5);
						glVertex2d(0.5, 0.5);
						glVertex2d(0.5, -0.5);
						glVertex2d(0.0, -0.5);
					glEnd();
				glPopMatrix();
			glPopMatrix();
			break;
		case 2:
			glLoadIdentity();
			glPushMatrix();
				glTranslatef(quadPosX, quadPosY, quadPosZ);
				glBegin(GL_QUADS);
					glColor3f(1.0f, .0f, .0f);			// Red
					glVertex2d(0.0, 0.1);
					glVertex2d(0.5, 0.1);
					glVertex2d(0.5, -0.1);
					glVertex2d(0.0, -0.1);
				glEnd();
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-quadPosX, -quadPosY, quadPosZ);
					glBegin(GL_QUADS);
					glColor3f(1.0f, .0f, .0f);			// Red
					glVertex2d(0.0, 0.1);
					glVertex2d(0.5, 0.1);
					glVertex2d(0.5, -0.1);
					glVertex2d(0.0, -0.1);
					glEnd();
			glPopMatrix();
			break;
		case 3:
			glLoadIdentity();
			drawWindMill();
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
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <cmath>
#include <iostream>

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")

#define WINDOW_TITLE "OpenGL Window"

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

float upperArmRotateZ = 0.0f;
float wholeArmRotateZ = 0.0f;

// Camera Properties
float cameraModifier = 0.2f;

float cameraX = 0.0f;
float cameraY = 0.0f;
float cameraZ = 0.0f;
float cameraSpeed = 0.1f;

// Light Properties
GLUquadricObj* sphere = NULL;
GLfloat light_position2[] = { .0f, .0f, .0f };
float lightSpeed = .1f;

// HOW TO LET OPEN GL TO KNOW THE NORMAL OF A SURFACE

// TEXTURE VARIABLES
GLuint texture = 0;	// Texture Name
BITMAP BMP;			// Bitmap Structure
HBITMAP hBMP = NULL;	// Handle to Bitmap

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
			light_position2[1] += lightSpeed;
			break;
		case VK_DOWN:
			light_position2[1] -= lightSpeed;
			break;
		case VK_LEFT:
			light_position2[0] -= lightSpeed;
			break;
		case VK_RIGHT:
			light_position2[0] += lightSpeed;
			break;
		case 'K':
			light_position2[2] += lightSpeed;
			break;
		case 'L':
			light_position2[2] -= lightSpeed;
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

			// Moving the Camera
		case 'Z':
			cameraZ += cameraSpeed;
			break;
		case 'X':
			cameraZ -= cameraSpeed;
			break;
		case 'C':
			cameraX -= cameraSpeed;
			break;
		case 'V':
			cameraX += cameraSpeed;
			break;
		case 'B':
			cameraY -= cameraSpeed;
			break;
		case 'N':
			cameraY += cameraSpeed;
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

void cube() {
	GLfloat cyDiffColor[] = { 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, cyDiffColor);

	GLfloat cyAmbColor[] = { 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, cyAmbColor);

	glTranslatef(cubeX, cubeY, cubeZ);
	glRotatef(cubeRotX, 1.0f, 0.0f, 0.0f);
	glRotatef(cubeRotY, 0.0f, 1.0f, 0.0f);
	glRotatef(cubeRotZ, 0.0f, 0.0f, 1.0f);

	glBegin(GL_QUADS); // front
	glColor3f(1, 0, 0); // red
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.0f, 0.5f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(0.5f, 1.0f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glEnd();


	glBegin(GL_QUADS); // right
	glColor3f(0, 1, 0); //green
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glEnd();

	glBegin(GL_QUADS); // back
	glColor3f(0, 0, 1); //blue
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glEnd();

	glBegin(GL_QUADS); // left
	glColor3f(1, 0, 1); // purple
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glEnd();

	glBegin(GL_QUADS); // top
	glColor3f(1, 1, 0); // yellow
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glEnd();

	glBegin(GL_QUADS); // bottom
	glColor3f(0, 1, 1); // cyan
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glEnd();
}

void pyramid() {
	glTranslatef(cubeX, cubeY, cubeZ);
	glRotatef(cubeRotX, 1.0f, 0.0f, 0.0f);
	glRotatef(cubeRotY, 0.0f, 1.0f, 0.0f);
	glRotatef(cubeRotZ, 0.0f, 0.0f, 1.0f);

	glBegin(GL_LINE_LOOP); //back
	glColor3f(1, 1, 1); //white
	//glColor3f(0, 0, 1); //blue
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();

	glBegin(GL_LINE_LOOP); //front
	//glColor3f(1, 1, 0); //yellow
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();

	glBegin(GL_LINE_LOOP); //left
	//glColor3f(1, 0, 0); //red
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();

	glBegin(GL_LINE_LOOP); //right
	//glColor3f(0, 1, 0); //green
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();

	glBegin(GL_LINE_LOOP); // bottom
	//glColor3f(0, 1, 1); // cyan
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glEnd();
}

void display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Modify Camera
	//glMatrixMode(GL_PROJECTION); 
	//glLoadIdentity(); 

	//gluPerspective(30, 1, 0.3, 10.0f);

	//// translate only affect the projection, not the model
	//glTranslatef(cameraX, cameraY, cameraZ);

	//glMatrixMode(GL_MODELVIEW); // switch matrix state to modify object

	//glPushMatrix();
	//	glTranslatef(light_position2[0], light_position2[1], light_position2[2]);
	//	sphere = gluNewQuadric();
	//	glColor3f(1.0f, .0f, .0f);
	//	gluSphere(sphere, .05, 50, 25);
	//glPopMatrix();

	//glEnable(GL_LIGHTING);

	//GLfloat light_position[] = { .0f, 1.0f, .0f };
	//glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	//GLfloat light_ambient[] = { .5f, .5f, .5f };
	//glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	//glEnable(GL_LIGHT0);

	//glLightfv(GL_LIGHT1, GL_POSITION, light_position2);
	//GLfloat light_diff[] = { 1.0f, .0f, .0f };
	//glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diff);
	//glEnable(GL_LIGHT1);

	switch (questionToShow) {
	case 1:
		glLoadIdentity();
		cube();
		break;
	case 2:
		glLoadIdentity();
		pyramid();
		break;
	}
}


void InitializeTextures() {
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	HBITMAP hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"Box.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
}

void CleanUpTextures() {
	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
}

//--------------------------------------------------------------------
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

	// Enable 3D Depth Test
	glEnable(GL_DEPTH_TEST);

	// Modify Camera (Fixed Camera)
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	// glOrtho(left, right, bottom, top, near, far);
	// since the near is 0, and the object is also in z = 0 , we are inside the object, so the object size cut down by 2
	// glOrtho(-5, 5, -5, 5, -1, 10); 
	//
	//glOrtho(cameraLeft, cameraRight, cameraBottom, cameraTop, cameraNear, cameraFar);

	//--------------------------------
	//	End initialization
	//--------------------------------

	// Initialize Textures
	InitializeTextures();

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

	CleanUpTextures();

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
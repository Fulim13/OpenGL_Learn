#include <Windows.h>
#include <gl/GL.h>
#include <math.h>
#include <gl/GLU.h>

#pragma comment (lib, "OpenGL32.lib")ba
#pragma comment (lib, "GLU32.lib") 

#define WINDOW_TITLE "OpenGL Window"

float r = 0.0f;
float pi = 3.14159;

int questionToShow = 1;

// cube variables
float cubeX = 0.0f;
float cubeY = 0.0f;
float cubeZ = 0.0f;

float cubeRotX = 0.0f;
float cubeRotY = 0.0f;
float cubeRotZ = 0.0f;

float coneX = 0.0f;
float coneY = -0.9f;
float coneZ = 0.0f;

float coneRotX = 0.0f;
float coneRotY = -0.6f;
float coneRotZ = 0.0f;

float movementSpeed = 0.01;
float rotationSpeed = 10;

GLUquadricObj* sphere = NULL;
GLUquadricObj* cylinder = NULL;
int slices = 50;
int stacks = 10;

float camLeft = -2;
float camRight = 2;
float camBottom = -2;
float camTop = 2;
float camNear = -2;
float camFar = 2;
float camModifier = 0.2;
float camX = 0.0;
float camY = 0.0;
float camZ = -5;
float camSpeed = 0.2;

float lightPos0[] = { 0,1,0 };
float lightAmb0[] = { 0.1,0.1,0.1 }; //white
float lightPos1[] = { 1,1,0 };
float lightDiff1[] = { 1,0,0 }; //red
float light1MoveSpeed = 0.1;

bool isSphere = true;
bool isLight = true;


float iceCream1DiffCol[] = { 1.0f, 1.0f, 0.93f };
float iceCream1AmbCol[] = { 1.0f, 1.0f, 0.93f };

// capture id and close the window
LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		
		case 'W':
			lightPos1[1] += light1MoveSpeed;
			break;
		case 'A':
			lightPos1[0] -= light1MoveSpeed;
			break;
		case 'S':
			lightPos1[1] -= light1MoveSpeed;
			break;
		case 'D':
			lightPos1[0] += light1MoveSpeed;
			break;
		case 'Q':
			lightPos1[2] -= light1MoveSpeed;
			break;
		case 'E':
			lightPos1[2] += light1MoveSpeed;
			break;

		case VK_UP:
			cubeRotX += rotationSpeed;
			cubeRotY += rotationSpeed;
			cubeRotZ += rotationSpeed;
			break;
		case VK_DOWN:
			cubeRotX -= rotationSpeed;
			cubeRotY -= rotationSpeed;
			cubeRotZ -= rotationSpeed;
			break;

		case VK_SPACE:
			isLight = !isLight;
			break;
		case 'O':
			//camBottom -= camModifier;
			isSphere = true;
			break;
		case 'P':
			//camBottom -= camModifier;
			isSphere = false;
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

		case 'F':
			cubeRotX += rotationSpeed;
			break;
		case 'G':
			cubeRotX -= rotationSpeed;
			break;
		case 'H':
			cubeRotY += rotationSpeed;
			break;
		case 'J':
			cubeRotY -= rotationSpeed;
			break;
		case 'K':
			cubeRotZ += rotationSpeed;
			break;
		case 'L':
			cubeRotZ -= rotationSpeed;
			break;


		case 0x31: // key '1' is pressed
			questionToShow = 1;
			break;
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

void drawPyramid() {
	glPushMatrix();

	//front
	glBegin(GL_TRIANGLES);
	glNormal3f(0.0f, 0, 1.0f);
	glVertex3f(0.0f, 0.5f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glEnd();

	//right
	glBegin(GL_TRIANGLES);
	glNormal3f(0.5f, 0, 0);
	glNormal3f(1, 0, 0);
	glVertex3f(0.0f, 0.5f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);

	//back
	glBegin(GL_TRIANGLES);
	glNormal3f(0.0f, 0, -1.0f);
	glVertex3f(0.0f, 0.5f, 0.0f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, -0.5f);

	//left
	glBegin(GL_TRIANGLES);
	glNormal3f(-1, 0, 0);
	glVertex3f(0.0f, 0.5f, 0.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glEnd();

	//Bottom
	glBegin(GL_QUADS);
	glNormal3f(0, -1, 0);
	glVertex3f(-0.5, -0.5, 0.5f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glEnd();
	glPopMatrix();
}

void drawSphere() {
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	glColor3f(2.0f, 1.0f, 0.93f);
	gluSphere(sphere, 0.5f, 100, 100);
}

void setupLight()
{
	if (isLight) {
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);

		// Red diffuse light
		float diffuseLight[] = { 1.0f, 1.0f, 1.0f };  // Red color
		float ambientLight[] = { 0.2f, 0.2f, 0.2f };  // Soft ambient light
		float specularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // White specular

		glLightfv(GL_LIGHT0, GL_POSITION, lightPos1);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
		//glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);

		// Draw a small sphere to represent light position
		glPushMatrix();
		glDisable(GL_LIGHTING);  // Disable lighting for light source visualization
		glTranslatef(lightPos1[0], lightPos1[1], lightPos1[2]);
		glColor3f(1, 0, 0);  // white color for light source
		GLUquadric* lightSphere = gluNewQuadric();
		gluSphere(lightSphere, 0.05, 50, 50);
		gluDeleteQuadric(lightSphere);
		glEnable(GL_LIGHTING);
		glPopMatrix();
	}
	else {
		glDisable(GL_LIGHTING);
	}
}

void display()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30, 1, 0.2, 10.0f);
	glTranslatef(camX, camY, camZ);

	glMatrixMode(GL_MODELVIEW);

	switch (questionToShow)
	{
	case 1:
		glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();

		glTranslatef(cubeX, cubeY, cubeZ);
		glRotatef(cubeRotX, 1.0f, 0.0f, 0.0f);
		glRotatef(cubeRotY, 0.0f, 1.0f, 0.0f);
		glRotatef(cubeRotZ, 0.0f, 0.0f, 1.0f);

		setupLight();

		if (isSphere) {
			drawSphere();
		}
		else {
			drawPyramid();
		}

		break;
	default:
		break;
	}



}
//------------------------------------------------------------------------------------------

/*
HINSTANCE hInst		- ID number(program) : when instance shape need to use
HINSTNACE hPrevInst - got sercuity prob but still in lib
LPSTR vmflineparam	- to acpt like '--debug' after a cmd to use to do other things
int nCmdShow		- style flag, how the window appear like fullscreen or windowed
*/

/* Call out console to show variable or something :
* int main(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR vmflineparam, int nCmdShow)
*/


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR vmflineparam, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));		 // fill all the space in the variable with '0'

	// Specify how the class will be
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL); // samge result with 'hInst'
	wc.lpfnWndProc = WindowProcedure;		 // "long pointer function window procedure" - 
	wc.lpszClassName = WINDOW_TITLE;			 // Class Name/Title
	wc.style = CS_HREDRAW | CS_VREDRAW;	// <horizontal> | <vertical>

	// Create class when execute; else return false to close it
	if (!RegisterClassEx(&wc)) return false;

	// Create window 
	HWND hWnd = CreateWindow(	// HWND - handler of window
		WINDOW_TITLE,			// Class Name
		WINDOW_TITLE,			// Window Name
		WS_OVERLAPPEDWINDOW,	// Style
		CW_USEDEFAULT,			// x - location of spawn window
		CW_USEDEFAULT,			// y - location of spawn window
		800,					// width
		800,					// height
		NULL,					// Parent
		NULL,					// Menu in window upper like - File, Edit, View, Help
		wc.hInstance,			// ID
		NULL);					// Not Important

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
	glEnable(GL_DEPTH_TEST);



	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	// infinite loop - for instant refreshing
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) // see message from window os like input from user
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		display();

		SwapBuffers(hdc); // swap buffer to let gpu draw something at back
	}

	// delete class
	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	// close window
	return true;
}
//--------------------------------------------------------------------
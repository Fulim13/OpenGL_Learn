#include <Windows.h>	// window class
#include <gl/GL.h>		// openGL class
#include <math.h>		// math class

#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "Practical Exercise 1"

int questionNumber = 1;	//Question number

float x=0.0, y=0.0;							//Origin of circle
float radius = 0.2;							//Radius of circle
float angle = 0.0;							//Angle of circle
float x2=0.0, y2=0.0;						//Point on circle
const double PI = 3.14159265358979323846;	//Value of PI
float noOfTriangle = 30;					//Number of triangle to draw circle


LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) PostQuitMessage(0);
		if (wParam == 0x31) //press key '1'
			questionNumber = 1;
		if (wParam == 0x32) //press key '2'
			questionNumber = 2;
		if (wParam == 0x33) //press key '3'
			questionNumber = 3;
		if (wParam == 0x34) //press key '4'
			questionNumber = 4;
		if (wParam == 0x35) //press key '5'
			questionNumber = 5;
		if (wParam == 0x36) //press key '6'
			questionNumber = 6;
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

void drawOutline() {
	glLineWidth(5.0);					//Set line width to 5
	glBegin(GL_LINE_LOOP);				//Begin to draw outline
		glColor3f(0.0f, 0.0f, 1.0f);	//Set color to blue
		glVertex2d(-0.5, -0.5);			//P1
		glVertex2d(-0.5, 0.5);			//P2
		glVertex2d(0.5, 0.5);			//P3
		glVertex2d(0.5, -0.5); 			//P4	
	glEnd();
}

void pahangFlag() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	// clear background screen to black
	glClear(GL_COLOR_BUFFER_BIT);			// clear the color buffer

	glBegin(GL_QUADS);					//Begin to draw quads
		glColor3f(1.0f, 1.0f, 1.0f);	//Set color to white
		glVertex2d(-0.5, 0.0);			//P1
		glVertex2d(-0.5, 0.5);			//P2
		glVertex2d(0.5, 0.5);			//P3
		glVertex2d(0.5, 0.0); 			//P4	
	glEnd();

	glBegin(GL_QUADS);					//Begin to draw quads
		glColor3f(0.0f, 0.0f, 0.0f);	//Set color to black
		glVertex2d(-0.5, -0.5);			//P1
		glVertex2d(-0.5, 0.0);			//P2
		glVertex2d(0.5, 0.0);			//P3
		glVertex2d(0.5, -0.5); 			//P4	
	glEnd();

	drawOutline();
}

void n9Flag() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	// clear background screen to black
	glClear(GL_COLOR_BUFFER_BIT);			// clear the color buffer

	glBegin(GL_QUADS);					//Begin to draw quads
		glColor3f(1.0f, 1.0f, 0.0f);	//Set color to yellow
		glVertex2d(-0.5, -0.5);			//P1
		glVertex2d(-0.5, 0.5);			//P2
		glVertex2d(0.5, 0.5);			//P3
		glVertex2d(0.5, -0.5); 			//P4
	glEnd();

	glBegin(GL_TRIANGLES);				//Begin to draw triangles
		glColor3f(0.0f, 0.0f, 0.0f);	//Set color to black
		glVertex2d(-0.5, 0.0);			//P1
		glVertex2d(-0.5, 0.5);			//P2
		glVertex2d(0.0, 0.0);			//P3
	glEnd();

	glBegin(GL_TRIANGLES);				//Begin to draw triangles
		glColor3f(1.0f, 0.0f, 0.0f);	//Set color to red
		glVertex2d(-0.5, 0.5);			//P1
		glVertex2d(0.0, 0.5);			//P2
		glVertex2d(0.0, 0.0);			//P3
	glEnd();
}

void englandFlag() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	// clear background screen to black
	glClear(GL_COLOR_BUFFER_BIT);			// clear the color buffer

	glBegin(GL_QUADS);					//Begin to draw quads
		glColor3f(1.0f, 1.0f, 1.0f);	//Set color to white
		glVertex2d(-0.5, -0.5);			//P1
		glVertex2d(-0.5, 0.5);			//P2
		glVertex2d(0.5, 0.5);			//P3
		glVertex2d(0.5, -0.5); 			//P4
	glEnd();

	glBegin(GL_QUADS);				//Begin to draw quads
		glColor3f(1.0f, 0.0f, 0.0f);	//Set color to red
		glVertex2d(-0.5, -0.1);			//P1
		glVertex2d(-0.5, 0.1);			//P2
		glVertex2d(0.5, 0.1);			//P3
		glVertex2d(0.5, -0.1);			//P4
	glEnd();

	glBegin(GL_QUADS);				//Begin to draw quads
		glColor3f(1.0f, 0.0f, 0.0f);	//Set color to red
		glVertex2d(-0.1, -0.5);			//P1
		glVertex2d(-0.1, 0.5);			//P2
		glVertex2d(0.1, 0.5);			//P3
		glVertex2d(0.1, -0.5);			//P4
	glEnd();
}

void scotlandFlag() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	// clear background screen to black
	glClear(GL_COLOR_BUFFER_BIT);			// clear the color buffer

	glBegin(GL_QUADS);					//Begin to draw quads
		glColor3f(0.0f, 0.0f, 1.0f);	//Set color to blue
		glVertex2d(-0.5, -0.5);			//P1
		glVertex2d(-0.5, 0.5);			//P2
		glVertex2d(0.5, 0.5);			//P3
		glVertex2d(0.5, -0.5); 			//P4
	glEnd();

	glBegin(GL_QUADS);					//Begin to draw quads
		glColor3f(1.0f, 1.0f, 1.0f);    // Set color to white
		glVertex2d(0.4, -0.5);          // P1
		glVertex2d(-0.5, 0.4);          // P2
		glVertex2d(-0.4, 0.5);          // P3
		glVertex2d(0.5, -0.4);          // P4
	glEnd();

	glBegin(GL_QUADS);
		glColor3f(1.0f, 1.0f, 1.0f);    // Set color to white
		glVertex2d(-0.5, -0.4);         // P1
		glVertex2d(0.4, 0.5);           // P2
		glVertex2d(0.5, 0.4);           // P3
		glVertex2d(-0.4, -0.5);         // P4
	glEnd();

	glBegin(GL_TRIANGLES);				//Begin to draw triangles
		glColor3f(1.0f, 1.0f, 1.0f);	//Set color to white
		glVertex2d(-0.5, -0.5);			//P1
		glVertex2d(-0.5, -0.4);			//P2
		glVertex2d(-0.4, -0.5);			//P3
	glEnd();

	glBegin(GL_TRIANGLES);				//Begin to draw triangles
		glColor3f(1.0f, 1.0f, 1.0f);	//Set color to white
		glVertex2d(-0.5, 0.4);			//P1
		glVertex2d(-0.5, 0.5);			//P2
		glVertex2d(-0.4, 0.5);			//P3
	glEnd();

	glBegin(GL_TRIANGLES);				//Begin to draw triangles
		glColor3f(1.0f, 1.0f, 1.0f);	//Set color to white
		glVertex2d(0.4, 0.5);			//P1
		glVertex2d(0.5, 0.5);			//P2
		glVertex2d(0.5, 0.4);			//P3
	glEnd();

	glBegin(GL_TRIANGLES);				//Begin to draw triangles
		glColor3f(1.0f, 1.0f, 1.0f);	//Set color to white
		glVertex2d(0.4, -0.5);			//P1
		glVertex2d(0.5, -0.4);			//P2
		glVertex2d(0.5, -0.5);			//P3
	glEnd();
}

void japanFlag() {


	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	// clear background screen to black
	glClear(GL_COLOR_BUFFER_BIT);			// clear the color buffer		
	
	glBegin(GL_QUADS);					//Begin to draw quads
		glColor3f(1.0f, 1.0f, 1.0f);	//Set color to white
		glVertex2d(-0.5, -0.5);			//P1
		glVertex2d(-0.5, 0.5);			//P2
		glVertex2d(0.5, 0.5);			//P3
		glVertex2d(0.5, -0.5); 			//P4	
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 0.0f, 0.0f);			//Set color to red
		glVertex2f(x, y);					// draw the origin of the circle
		for (angle = 0; angle <= 2 * PI; angle += (2*PI)/ noOfTriangle) {
			x2 = x + radius * cos(angle);	// calculate the x component
			y2 = y + radius * sin(angle);	// calculate the y component
			glVertex2f(x2, y2);				// draw the point on the circle
		}
	glEnd();

	drawOutline();
}

void japanFlagWithoutFills() {


	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	// clear background screen to black
	glClear(GL_COLOR_BUFFER_BIT);			// clear the color buffer		

	glBegin(GL_QUADS);					//Begin to draw quads
		glColor3f(1.0f, 1.0f, 1.0f);	//Set color to white
		glVertex2d(-0.5, -0.5);			//P1
		glVertex2d(-0.5, 0.5);			//P2
		glVertex2d(0.5, 0.5);			//P3
		glVertex2d(0.5, -0.5); 			//P4	
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3f(1.0f, 0.0f, 0.0f);		//Set color to red

	//NOTE: move the origin
	float x = 0.5, y = 0.5;

	//NOTE: no need to draw the origin for circle without fill
	// glVertex2f(x, y);				// draw the origin of the circle
	for (angle = PI; angle <= 2 * PI; angle += PI / noOfTriangle) {

	//NOTE: Changing the angle to draw the circle
	//for (angle = 0; angle <= PI; angle += PI / noOfTriangle) {
	//for (angle = 0; angle <= 2 * PI; angle += (2 * PI) / noOfTriangle) {
		x2 = x + radius * cos(angle);	// calculate the x component
		y2 = y + radius * sin(angle);	// calculate the y component
		glVertex2f(x2, y2);				// draw the point on the circle
	}
	glEnd();

	drawOutline();
}

void display()
{
	switch (questionNumber) {
		case 1:
			pahangFlag();
			break;
		case 2:
			n9Flag();
			break;
		case 3:
			englandFlag();
			break;
		case 4:
			scotlandFlag();
			break;
		case 5:
			japanFlag();
			break;
		case 6:
			japanFlagWithoutFills();
			break;
		default:
			pahangFlag();
			break;
	}
}
//--------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR cmdlineparam, int nCmdShow)
{
	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL); 
	wc.lpfnWndProc = WindowProcedure;  

	wc.lpszClassName = WINDOW_TITLE;		
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE,
		WINDOW_TITLE,
		WS_OVERLAPPEDWINDOW, 
		CW_USEDEFAULT,  
		CW_USEDEFAULT,
		800, 
		800,
		NULL, 
		NULL, 
		wc.hInstance,
		NULL);

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
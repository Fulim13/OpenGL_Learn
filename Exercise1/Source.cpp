#include <Windows.h>	// window class
#include <gl/GL.h>		// openGL class
#include <math.h>		// math class

#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "Practical Exercise 1"

int questionNumber = 1;	//Question number

float x = 0.0, y = 0.0;						// Origin of circle
float radius = 0.2;							// Radius of circle
float angle = 0.0;							// Angle of circle (in radian)
float x2 = 0.0, y2 = 0.0;					// Point on circle
const double PI = 3.14159265;				// Value of PI
float noOfTriangle = 30;					// Number of triangle to draw circle


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
		if (wParam == 0x37) //press key '7'
			questionNumber = 7;
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
	glLineWidth(2.0);						// Set line width to 2
	glBegin(GL_LINE_LOOP);				
		glColor3f(0.0f, 0.0f, 1.0f);		// Blue
		glVertex2d(-0.7, -0.4);			
		glVertex2d(-0.7, 0.4);			
		glVertex2d(0.7, 0.4);			
		glVertex2d(0.7, -0.4); 			
	glEnd();
}

void pahangFlag() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	// Clear background screen to black
	glClear(GL_COLOR_BUFFER_BIT);			// Clear the color buffer

	glBegin(GL_QUADS);					
		glColor3f(1.0f, 1.0f, 1.0f);		// White
		glVertex2d(-0.7, 0.0);			
		glVertex2d(-0.7, 0.4);			
		glVertex2d(0.7, 0.4);			
		glVertex2d(0.7, 0.0); 			

		glColor3f(0.0f, 0.0f, 0.0f);		// Black
		glVertex2d(-0.7, -0.7);			
		glVertex2d(-0.7, 0.0);			
		glVertex2d(0.7, 0.0);			
		glVertex2d(0.7, -0.4); 			
	glEnd();

	drawOutline();
}

void n9Flag() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	
	glClear(GL_COLOR_BUFFER_BIT);			

	glBegin(GL_QUADS);					
		glColor3f(1.0f, 1.0f, 0.0f);		// Yellow
		glVertex2d(-0.7, -0.4);			
		glVertex2d(-0.7, 0.4);			
		glVertex2d(0.7, 0.4);			
		glVertex2d(0.7, -0.4); 			
	glEnd();

	glBegin(GL_TRIANGLES);				
		glColor3f(1.0f, 0.0f, 0.0f);		// Red
		glVertex2d(-0.7, 0.0);			
		glVertex2d(-0.7, 0.4);			
		glVertex2d(0.0, 0.4);			

		glColor3f(0.0f, 0.0f, 0.0f);		// Black
		glVertex2d(-0.7, 0.0);			
		glVertex2d(0.0, 0.4);			
		glVertex2d(0.0, 0.0);			
	glEnd();
}

void englandFlag() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	
	glClear(GL_COLOR_BUFFER_BIT);			

	glBegin(GL_QUADS);					
		glColor3f(1.0f, 1.0f, 1.0f);		// White
		glVertex2d(-0.7, -0.4);			
		glVertex2d(-0.7, 0.4);			
		glVertex2d(0.7, 0.4);			
		glVertex2d(0.7, -0.4); 			
	glEnd();

	glBegin(GL_QUADS);				
		glColor3f(1.0f, 0.0f, 0.0f);		// Red
		glVertex2d(-0.7, -0.1);			
		glVertex2d(-0.7, 0.1);			
		glVertex2d(0.7, 0.1);			
		glVertex2d(0.7, -0.1);			
				
		glVertex2d(-0.1, -0.4);		
		glVertex2d(-0.1, 0.4);		
		glVertex2d(0.1, 0.4);			
		glVertex2d(0.1, -0.4);			
	glEnd();
}

void scotlandFlag() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	
	glClear(GL_COLOR_BUFFER_BIT);			

	glBegin(GL_QUADS);						
		glColor3f(0.0f, 0.0f, 1.0f);		// Blue
		glVertex2d(-0.7, -0.4);				
		glVertex2d(-0.7, 0.4);				
		glVertex2d(0.7, 0.4);				
		glVertex2d(0.7, -0.4);				
	glEnd();

	glBegin(GL_QUADS);						
		glColor3f(1.0f, 1.0f, 1.0f);		// White
		glVertex2d(0.55, -0.4);              
		glVertex2d(-0.7, 0.3);              
		glVertex2d(-0.55, 0.4);              
		glVertex2d(0.7, -0.3);              

		glVertex2d(-0.7, -0.3);            
		glVertex2d(0.55, 0.4);               
		glVertex2d(0.7, 0.3);               
		glVertex2d(-0.55, -0.4);            
	glEnd();

	glBegin(GL_TRIANGLES);					
		glColor3f(1.0f, 1.0f, 1.0f);		// White
		glVertex2d(-0.7, -0.4);				
		glVertex2d(-0.7, -0.3);				
		glVertex2d(-0.55, -0.4);				

		glVertex2d(-0.7, 0.3);				
		glVertex2d(-0.7, 0.4);				
		glVertex2d(-0.55, 0.4);				

		glVertex2d(0.55, 0.4);				
		glVertex2d(0.7, 0.4);				
		glVertex2d(0.7, 0.3);				

		glColor3f(1.0f, 1.0f, 1.0f);		
		glVertex2d(0.55, -0.4);				
		glVertex2d(0.7, -0.3);				
		glVertex2d(0.7, -0.4);				
	glEnd();
}

void japanFlag() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	
	glClear(GL_COLOR_BUFFER_BIT);			
	
	glBegin(GL_QUADS);					
		glColor3f(1.0f, 1.0f, 1.0f);		// White
		glVertex2d(-0.7, -0.4);				
		glVertex2d(-0.7, 0.4);				
		glVertex2d(0.7, 0.4);				
		glVertex2d(0.7, -0.4);				
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
		glColor3f(1.0f, 0.0f, 0.0f);		// Red
		glVertex2f(x, y);					// Draw the origin of the circle
		for (angle = 0; angle <= 2 * PI; angle += (2*PI)/ noOfTriangle) {
			x2 = x + radius * cos(angle);	// Calculate the x component
			y2 = y + radius * sin(angle);	// Calculate the y component
			glVertex2f(x2, y2);				// Draw the point on the circle
		}
	glEnd();

	drawOutline();
}

void japanFlagWithoutFills() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	
	glClear(GL_COLOR_BUFFER_BIT);			

	glBegin(GL_QUADS);					
		glColor3f(1.0f, 1.0f, 1.0f);		// White
		glVertex2d(-0.5, -0.5);			
		glVertex2d(-0.5, 0.5);			
		glVertex2d(0.5, 0.5);			
		glVertex2d(0.5, -0.5); 			
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3f(1.0f, 0.0f, 0.0f);			// Red

	//NOTE: Move the origin
	float x = 0.5, y = 0.5;

	//NOTE: No need to draw the origin for Circle without fill
	// glVertex2f(x, y);				// draw the origin of the circle
	for (angle = PI; angle <= 2 * PI; angle += PI / noOfTriangle) {			// Half circle with the flat side on top
	//NOTE: Changing the angle to draw the circle
	//for (angle = 0; angle <= PI; angle += PI / noOfTriangle) {			// Half circle with the flat side on bottom
	//for (angle = 0; angle <= 2 * PI; angle += (2 * PI) / noOfTriangle) {	// Full circle
		x2 = x + radius * cos(angle);	// Calculate the x component
		y2 = y + radius * sin(angle);	// Calculate the y component
		glVertex2f(x2, y2);				// Draw the point on the circle
	}
	glEnd();

	drawOutline();
}

void smileFace() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	
	glClear(GL_COLOR_BUFFER_BIT);			

	// Background
	glBegin(GL_QUADS);						
		glColor3f(1.0f, 1.0f, 1.0f);			// White
		glVertex2d(1.0, 1.0);              
		glVertex2d(-1.0, 1.0);              
		glVertex2d(-1.0, -1.0);             
		glVertex2d(1.0, -1.0);              
	glEnd();
	
	// Head
	glBegin(GL_TRIANGLE_FAN);
		glColor3f(1.0f, 1.0f, 0.0f);			// Yellow
		glVertex2f(x, y);					
		for (angle = 0; angle <= PI; angle += PI / noOfTriangle) {
			x2 = x + radius * cos(angle);	
			y2 = y + radius * sin(angle);	
			glVertex2f(x2, y2);				
		}
	glEnd();

	// Face and Body
	glBegin(GL_QUADS);						
		glColor3f(1.0f, 1.0f, 0.0f);			// Yellow
		glVertex2d(0.2, .0);              
		glVertex2d(-0.2, .0);              
		glVertex2d(-0.2, -.8);              
		glVertex2d(0.2, -.8);              
	glEnd();

	// Spectacles
	glBegin(GL_QUADS);						
		glColor3f(.0f, .0f, .0f);				// Black
		glVertex2d(0.2, .0);              
		glVertex2d(-0.2, .0);              
		glVertex2d(-0.2, -.1);              
		glVertex2d(0.2, -.1);              
	glEnd();

	// Eyes
	glBegin(GL_TRIANGLE_FAN);
		glColor3f(1.0f, 1.0f, 1.0f);			// White
		float x= -.07, y = -.05;
		glVertex2f(x, y);					
		for (angle = 0; angle < 2 * PI; angle += (2 * PI) / noOfTriangle) {
			x2 = x + 0.07 * cos(angle);	
			y2 = y + 0.07 * sin(angle);	
			glVertex2f(x2, y2);				
		}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
		glColor3f(1.0f, 1.0f, 1.0f);			// White
		x = .07, y = -.05;
		glVertex2f(x, y);					
		for (angle = 0; angle < 2 * PI; angle += (2 * PI) / noOfTriangle) {
			x2 = x + 0.07 * cos(angle);	
			y2 = y + 0.07 * sin(angle);	
			glVertex2f(x2, y2);				
		}
	glEnd();

	// Retina
	glBegin(GL_TRIANGLE_FAN);
		glColor3f(0.0f, 0.0f, 0.0f);			// Black
		x = .07, y = -.05;
		glVertex2f(x, y);					
		for (angle = 0; angle < 2 * PI; angle += (2 * PI) / noOfTriangle) {
			x2 = x + 0.05 * cos(angle);	
			y2 = y + 0.05 * sin(angle);	
			glVertex2f(x2, y2);				
		}
	glEnd();


	glBegin(GL_TRIANGLE_FAN);
		glColor3f(0.0f, 0.0f, 0.0f);			// Black
		x = -.07, y = -.05;
		glVertex2f(x, y);					
		for (angle = 0; angle < 2 * PI; angle += (2 * PI) / noOfTriangle) {
			x2 = x + 0.05 * cos(angle);	
			y2 = y + 0.05 * sin(angle);	
			glVertex2f(x2, y2);				
		}
	glEnd();

	// Spectacles Frame/Shape
	glBegin(GL_LINE_LOOP);
		glColor3f(0.0f, 0.0f, 0.0f);			// Black
		x = -.07, y = -.05;
		for (angle = 0; angle < 2 * PI; angle += (2 * PI) / noOfTriangle) {
			x2 = x + 0.07 * cos(angle);	
			y2 = y + 0.07 * sin(angle);	
			glVertex2f(x2, y2);				
		}
	glEnd();

	glBegin(GL_LINE_LOOP);
		glColor3f(0.0f, 0.0f, 0.0f);			// Black
		x = .07, y = -.05;
		for (angle = 0; angle < 2 * PI; angle += (2 * PI) / noOfTriangle) {
			x2 = x + 0.07 * cos(angle);	
			y2 = y + 0.07 * sin(angle);	
			glVertex2f(x2, y2);				
		}
	glEnd();

	// Smile
	glBegin(GL_LINE_LOOP);
		glColor3f(0.0f, 0.0f, 0.0f);			// Black
		x = 0, y = -.2;
		for (angle = PI; angle < 2 * PI; angle += (2 * PI) / noOfTriangle) {
			x2 = x + 0.07 * cos(angle);	
			y2 = y + 0.07 * sin(angle);	
			glVertex2f(x2, y2);				
		}
	glEnd();

	// Hand
	glBegin(GL_QUADS);						
		glColor3f(1.0f, 1.0f, 0.0f);			// Yellow
		glVertex2d(-0.2, -.5);              
		glVertex2d(-0.2, -.45);              
		glVertex2d(-0.4, -.45);              
		glVertex2d(-0.4, -.5);              
	glEnd();

	glBegin(GL_QUADS);						
		glColor3f(1.0f, 1.0f, 0.0f);			// Yellow
		glVertex2d(0.2, -.5);              
		glVertex2d(0.2, -.45);              
		glVertex2d(0.4, -.45);              
		glVertex2d(0.4, -.5);              
	glEnd();

	// Shirt
	glBegin(GL_QUADS);						
		glColor3f(0.0f, 0.0f, 1.0f);			// Blue
		glVertex2d(0.2, -.4);              
		glVertex2d(-0.2, -.4);              
		glVertex2d(-0.2, -.45);              
		glVertex2d(0.2, -.45);              
	glEnd();

	glBegin(GL_QUADS);						
		glColor3f(0.0f, 0.0f, 1.0f);			// Blue    
		glVertex2d(0.1, -.45);              
		glVertex2d(-0.1, -.45);              
		glVertex2d(-0.1, -.6);              
		glVertex2d(0.1, -.6);              
	glEnd();

	glBegin(GL_QUADS);						
		glColor3f(0.0f, 0.0f, 1.0f);			// Blue
		glVertex2d(0.2, -.6);              
		glVertex2d(-0.2, -.6);              
		glVertex2d(-0.2, -.8);              
		glVertex2d(0.2, -.8);              
	glEnd();
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
		case 7:
			smileFace();
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
		600, 
		600,
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
#include <Windows.h>
#include <gl/GL.h>

#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "OpenGL Window"

float r = 1.0f;
float g = 1.0f;
float b = 1.0f;

float quadPosX = 0.0f;
float quadPosY = 0.0f;
float quadPosZ = 0.0f;

int questionToShow = 1;

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam) {
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

		case 0x52:	// R key is pressed
			r += 1.0f;
			g = .0f;
			b = .0f;
			break;
		case 0x47:	// G key is pressed
			g += 1.0f;
			r = .0f;
			b = .0f;
			break;
		case 0x42:	// B key is pressed
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

void display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); 
	glClear(GL_COLOR_BUFFER_BIT);
	switch (questionToShow) {
		// See the Difference between Translate + Rotate and Rotate + Translate
		// Translate + Rotate: Color of Triangle is Red, Green, Blue
		// Rotate + Translate: Color of Triangle is Green, Green, Green
		case 1:
			glLoadIdentity();

			glLineWidth(5.0f);

			// Transformation see in reverse order (Translate first then rotate)
			glRotatef(30, 0.0f, 0.0f, 1.0f);
			glTranslatef(0.5f, 0.0f, 0.0f);

			// Triangle
			glBegin(GL_POLYGON);	
				glColor3f(1, 0, 0);		// Red
				glVertex2f(-.5, 0);		

				glColor3f(0, 1, 0);		// Green
				glVertex2f(0, .5);		

				glColor3f(0, 0, 1);		//Blue
				glVertex2f(.5, 0);		
			glEnd();


			glLoadIdentity();

			glLineWidth(5.0f);		

			// Transformation see in reverse order (Rotate first then translate)
			glTranslatef(0.5f, 0.0f, 0.0f);
			glRotatef(30, 0.0f, 0.0f, 1.0f);

			// Triangle
			glBegin(GL_POLYGON);	
				glColor3f(0, 1, 0);		// Green
				glVertex2f(-.5, 0);		
				glVertex2f(0, .5);		
				glVertex2f(.5, 0);		
			glEnd();

			break;

		// A movable square with color changing capability
		// Use arrow keys to move the square
		// Use R, G, B keys to change the color of the square
		case 2:
			glLoadIdentity();

			glTranslatef(quadPosX, quadPosY, quadPosZ);

			glBegin(GL_QUADS);					
				glColor3f(r, g, b);	
				glVertex2d(-0.5, -0.5);			
				glVertex2d(-0.5, 0.5);			
				glVertex2d(0.5, 0.5);			
				glVertex2d(0.5, -0.5);
			glEnd();
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
// preprocessor for library
#include <Windows.h>
#include <gl/GL.h>

// link to OpenGL library (Window Specific)
#pragma comment (lib, "OpenGL32.lib")

// Constant Title
#define WINDOW_TITLE "OpenGL Window"

float r = 0.0f;

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) PostQuitMessage(0);
		if (wParam == VK_UP) r += 0.5;
		// if (wParam == VK_UP) // DO SOMETHING
		// if (wParam == VK_LEFT) // MOVE TO THE LEFT(0);
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
	glClearColor(r, 0.0f, 0.0f, 0.0f); //clear the color of the screen to red
	glClear(GL_COLOR_BUFFER_BIT); //Clear the color buffer
	
	//glPointSize(10.0f);	//Set point size

	glLineWidth(5.0f);		//Set line width

	glBegin(GL_POLYGON);	//Begin to draw line
	glColor3f(1, 0, 0);		// RED
	glVertex2f(-.5, 0);		// P1
	glColor3f(0, 1, 0);		//GREEN
	glVertex2f(0, .5);		//P2
	glColor3f(0, 0, 1);		//Blue
	glVertex2f(.5, 0);		//P3
	glEnd();
}
//--------------------------------------------------------------------

// hInst: process (instance) id number for the window (provided by OS)
// hPrevInst: id number of father window, (one window inside another window) - obsolete
// cmdlineparam: command line parameter
// if (cmdlineparam == "--incognito") { //do something}
// if (cmdlineparam == "--debug") { //do something}
// nCmdShow: style of start up window (full-screen, display location)
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR cmdlineparam, int nCmdShow)
{
	// In normal situation, we write main and Class Program (inside Class, we have window code to display window), and we use Class in main then compile to executable
	// Microsoft don't want to give source code, we write main for create the window, and compile it to executable, then during runtime, it will create the winodw on memory

	// Create Datastructure wc with type Window Class Extended
	WNDCLASSEX wc;

	// Find the address of wc that created (wc), all of the memory of wc will fill in with zero
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = hInst; // GetModuleHandle(NULL); // get id number
	wc.lpfnWndProc = WindowProcedure;  //Window Procedure function, receive msg from the user, if user want to quick, the window procedure capture the message and close the window
	
	// if have unresolved externals, it means the a piece of code in the program is external to the project, the project cannot solve the program because it does not understand the code
	// lpszClassName and WINDOW_TITLE are different string, so causing external error, the solution is to use Multi-Byte Character Set
	wc.lpszClassName = WINDOW_TITLE;		// Name of the Window Class
	wc.style = CS_HREDRAW | CS_VREDRAW; //Style of the Window

	// take the information above to register the class, if cannot Register Window class, close the program
	if (!RegisterClassEx(&wc)) return false;

	// Handle of Window
	HWND hWnd = CreateWindow(WINDOW_TITLE,
		"Valorant 2.0", // Untitle - Notepad
		WS_OVERLAPPEDWINDOW, // Can two window overlap
		CW_USEDEFAULT,  //x 
		CW_USEDEFAULT,  //y
		800, //width 
		800, //height
		NULL, //parent window
		NULL, // menu (resource menu) - like File Edit View in above
		wc.hInstance, // instance id
		NULL);

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context (what draw in the window)
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------

	// Draw Window
	ShowWindow(hWnd, nCmdShow);

	// create message
	MSG msg;

	// fill with zeros
	ZeroMemory(&msg, sizeof(msg));

	// Window - Event-Driven program
	// when event happens, then Window behave
	// when you do cin>>, you program stop
	// in open gl, the code run infitely loop, repeat 10000 time in sec
	while (true)
	{
		// Peek the message from os (ask os, do you have message for me)
		// if player press up arrow, OS will create the message 
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);

			// Send the message to WindowProcedure > msg
			DispatchMessage(&msg);
		}

		display();

		// front buffer display the screen, back buffer draw, back buffer finish drawing swap with front buffer
		SwapBuffers(hdc);
	}

	// Delete the class, shut down the program
	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------
#include <Windows.h>
#include <gl/GL.h>
#include <cmath>
#include <iostream>

#pragma comment (lib, "OpenGL32.lib")


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
float lowerArmRotateZ = 0.0f;
float wholeArmRotateZ = 0.0f;

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
					upperArmRotateZ += rotationSpeed;
					break;
				case VK_DOWN:
					upperArmRotateZ -= rotationSpeed;
					break;
				case VK_LEFT:
					wholeArmRotateZ += rotationSpeed;
					break;
				case VK_RIGHT:
					wholeArmRotateZ -= rotationSpeed;
					break;
				case 'W':
					lowerArmRotateZ += rotationSpeed;
					break;
				case 'S':
					lowerArmRotateZ -= rotationSpeed;
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

void cube() {
	glTranslatef(cubeX, cubeY, cubeZ);
	glRotatef(cubeRotX, 1.0f, 0.0f, 0.0f);
	glRotatef(cubeRotY, 0.0f, 1.0f, 0.0f);
	glRotatef(cubeRotZ, 0.0f, 0.0f, 1.0f);

	glBegin(GL_QUADS); // front
		glColor3f(1, 0, 0); // red
		glVertex3f(-0.5f, 0.5f, -0.5f);
		glVertex3f(-0.5f, -0.5f, -0.5f);
		glVertex3f(0.5f, -0.5f, -0.5f);
		glVertex3f(0.5f, 0.5f, -0.5f);
	glEnd();

	glBegin(GL_QUADS); // right
		glColor3f(0, 1, 0); //green
		glVertex3f(0.5f, 0.5f, 0.5f);
		glVertex3f(0.5f, -0.5f, 0.5f);
		glVertex3f(0.5f, -0.5f, -0.5f);
		glVertex3f(0.5f, 0.5f, -0.5f);
	glEnd();

	glBegin(GL_QUADS); // back
		glColor3f(0, 0, 1); //blue
		glVertex3f(0.5f, 0.5f, 0.5f);
		glVertex3f(0.5f, -0.5f, 0.5f);
		glVertex3f(-0.5f, -0.5f, 0.5f);
		glVertex3f(-0.5f, 0.5f, 0.5f);
	glEnd();

	glBegin(GL_QUADS); // left
		glColor3f(1, 0, 1); // purple
		glVertex3f(-0.5f, -0.5f, -0.5f);
		glVertex3f(-0.5f, 0.5f, -0.5f);
		glVertex3f(-0.5f, 0.5f, 0.5f);
		glVertex3f(-0.5f, -0.5f, 0.5f);
	glEnd();

	glBegin(GL_QUADS); // top
		glColor3f(1, 1, 0); // yellow
		glVertex3f(-0.5f, 0.5f, 0.5f);
		glVertex3f(0.5f, 0.5f, 0.5f);
		glVertex3f(0.5f, 0.5f, -0.5f);
		glVertex3f(-0.5f, 0.5f, -0.5f);
	glEnd();

	glBegin(GL_QUADS); // bottom
		glColor3f(0, 1, 1); // cyan
		glVertex3f(0.5f, -0.5f, 0.5f);
		glVertex3f(-0.5f, -0.5f, 0.5f);
		glVertex3f(-0.5f, -0.5f, -0.5f);
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

void drawLineCube(float v1_top_left_front[3], float v2_bottom_left_front[3],
	float v3_bottom_right_front[3], float v4_top_right_front[3],
	float v5_top_left_back[3], float v6_bottom_left_back[3],
	float v7_bottom_right_back[3], float v8_top_right_back[3]) {

	glBegin(GL_LINE_LOOP); // front
	glColor3f(1, 1, 1);		// white
	//glColor3f(1, 0, 0); // red
	glVertex3f(v1_top_left_front[0], v1_top_left_front[1], v1_top_left_front[2]);
	glVertex3f(v2_bottom_left_front[0], v2_bottom_left_front[1], v2_bottom_left_front[2]);
	glVertex3f(v3_bottom_right_front[0], v3_bottom_right_front[1], v3_bottom_right_front[2]);
	glVertex3f(v4_top_right_front[0], v4_top_right_front[1], v4_top_right_front[2]);
	glEnd();

	glBegin(GL_LINE_LOOP); // right
	//glColor3f(0, 1, 0); //green
	glVertex3f(v4_top_right_front[0], v4_top_right_front[1], v4_top_right_front[2]);
	glVertex3f(v3_bottom_right_front[0], v3_bottom_right_front[1], v3_bottom_right_front[2]);
	glVertex3f(v7_bottom_right_back[0], v7_bottom_right_back[1], v7_bottom_right_back[2]);
	glVertex3f(v8_top_right_back[0], v8_top_right_back[1], v8_top_right_back[2]);
	glEnd();

	glBegin(GL_LINE_LOOP); // back
	//glColor3f(0, 0, 1); //blue
	glVertex3f(v5_top_left_back[0], v5_top_left_back[1], v5_top_left_back[2]);
	glVertex3f(v6_bottom_left_back[0], v6_bottom_left_back[1], v6_bottom_left_back[2]);
	glVertex3f(v7_bottom_right_back[0], v7_bottom_right_back[1], v7_bottom_right_back[2]);
	glVertex3f(v8_top_right_back[0], v8_top_right_back[1], v8_top_right_back[2]);
	glEnd();

	glBegin(GL_LINE_LOOP); // left
	//glColor3f(1, 0, 1); // purple
	glVertex3f(v2_bottom_left_front[0], v2_bottom_left_front[1], v2_bottom_left_front[2]);
	glVertex3f(v1_top_left_front[0], v1_top_left_front[1], v1_top_left_front[2]);
	glVertex3f(v5_top_left_back[0], v5_top_left_back[1], v5_top_left_back[2]);
	glVertex3f(v6_bottom_left_back[0], v6_bottom_left_back[1], v6_bottom_left_back[2]);
	glEnd();

	glBegin(GL_LINE_LOOP); // top
	//glColor3f(1, 1, 0); // yellow
	glVertex3f(v1_top_left_front[0], v1_top_left_front[1], v1_top_left_front[2]);
	glVertex3f(v4_top_right_front[0], v4_top_right_front[1], v4_top_right_front[2]);
	glVertex3f(v8_top_right_back[0], v8_top_right_back[1], v8_top_right_back[2]);
	glVertex3f(v5_top_left_back[0], v5_top_left_back[1], v5_top_left_back[2]);
	glEnd();

	glBegin(GL_LINE_LOOP); // bottom
	//glColor3f(0, 1, 1); // cyan
	glVertex3f(v3_bottom_right_front[0], v3_bottom_right_front[1], v3_bottom_right_front[2]);
	glVertex3f(v2_bottom_left_front[0], v2_bottom_left_front[1], v2_bottom_left_front[2]);
	glVertex3f(v6_bottom_left_back[0], v6_bottom_left_back[1], v6_bottom_left_back[2]);
	glVertex3f(v7_bottom_right_back[0], v7_bottom_right_back[1], v7_bottom_right_back[2]);
	glEnd();
}

void arm() {
	// Define the vertices of the cube
	float v1[3] = { -0.5f, 0.2f, -0.1f };
	float v2[3] = { -0.5f, 0.0f, -0.1f };
	float v3[3] = { 0.0f, 0.0f, -0.1f };
	float v4[3] = { 0.0f, 0.2f, -0.1f };
	float v5[3] = { -0.5f, 0.2f, 0.1f };
	float v6[3] = { -0.5f, 0.0f, 0.1f };
	float v7[3] = { 0.0f, 0.0f, 0.1f };
	float v8[3] = { 0.0f, 0.2f, 0.1f };

	drawLineCube(v1, v2, v3, v4, v5, v6, v7, v8);
}

void display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	switch (questionToShow) {
	case 1:
		glLoadIdentity();
		cube();
		break;
	case 2:
		glLoadIdentity();
		pyramid();
		break;
	case 3:
		glLoadIdentity();
		glPushMatrix();
			glTranslatef(cubeX, cubeY, cubeZ);
			glRotatef(cubeRotX, 1.0f, 0.0f, 0.0f);
			glRotatef(cubeRotY, 0.0f, 1.0f, 0.0f);
			glRotatef(wholeArmRotateZ, 0.0f, 0.0f, 1.0f);
				glPushMatrix();
					glRotatef(upperArmRotateZ, 0.0f, 0.0f, 1.0f);
					arm();
				glPopMatrix();

				glPushMatrix();
					glRotatef(lowerArmRotateZ, 0.0f, 0.0f, 1.0f);
					glTranslatef(0.5f, 0.0f, 0.0f);
					arm();
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
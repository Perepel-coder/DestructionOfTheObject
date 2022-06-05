#pragma once
#define MAX_PARTICLES 500
#define QUBE_ID 100     // ID ������� ��� ����
#define SPHERE_ID   101     // ID ������� ��� �����
#define PYRAMID_ID   102     // ID ������� ��� ��������
#define QUBE 0
#define SPHERE 1
#define PYRAMID 2
#include <windows.h>
#include <fstream>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <C:\Users\���\Desktop\�����\program C++\��������_1\Project\Project\glaux.h>
#include <cmath>
#include <random>
#include <ctime>
#include "Geometry.h"
#include "Camera.h"
#include "Texture.h"
#include "Terrain.h"
#include "Timer.h"
#include "Particles.h"
#include "Output.h"
#include "Figures.h"
// ��������� ��������� �� ������� ��� ��������� ������� ��������� ������
typedef void (APIENTRY* PFNGLFOGCOORDFEXTPROC) (GLfloat coord);
void SetFogCoord(float depth, float height); // // ������������� �������� ����� ��� ������� ������� � ��������� ��������
int DrawGLScene(GLvoid);
void keyboard();
extern bool  keys[600];
extern HGLRC  hRC;              // ���������� �������� ����������
extern HDC  hDC;              // ��������� �������� ���������� GDI
extern HWND  hWnd;              // ����� ����� �������� ���������� ����
extern HINSTANCE  hInstance;              // ����� ����� �������� ���������� ����������
extern bool  fullscreen;
extern bool  active;
extern int camera_width;
extern int camera_height;
extern LPARAM Mouse_lParam;
extern int g_DetailScale;
extern GLfloat LightAmbient[4];
extern GLfloat LightDiffuse[4];
extern GLfloat LightPosition[4];
extern PFNGLFOGCOORDFEXTPROC glFogCoordfEXT;
extern bool start;				// ������ �������� �������
extern bool explosion;			// ������ �����
extern int ID;
extern bool f;
extern bool grid_;
extern bool BEGIN;
extern bool BEGIN_TEXTURE;
int RetrieveObjectID(int x, int y);
/////////////////////////////////////////////
GLvoid KillGLWindow(GLvoid);
BOOL CreateGLWindow(LPCWSTR title, int width, int height, int bits, bool fullscreenflag);
void Window();
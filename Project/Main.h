#pragma once
#define MAX_PARTICLES 500
#define QUBE_ID 100     // ID обьекта для Куба
#define SPHERE_ID   101     // ID обьекта для Сферы
#define PYRAMID_ID   102     // ID обьекта для Пирамиды
#define QUBE 0
#define SPHERE 1
#define PYRAMID 2
#include <windows.h>
#include <fstream>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <C:\Users\днс\Desktop\Прога\program C++\Курсовой_1\Project\Project\glaux.h>
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
// Обьявляем указатель на функцию для установки позиции обьемного тумана
typedef void (APIENTRY* PFNGLFOGCOORDFEXTPROC) (GLfloat coord);
void SetFogCoord(float depth, float height); // // Устанавливает обьемный туман для текущей вершины с указанной глубиной
int DrawGLScene(GLvoid);
void keyboard();
extern bool  keys[600];
extern HGLRC  hRC;              // Постоянный контекст рендеринга
extern HDC  hDC;              // Приватный контекст устройства GDI
extern HWND  hWnd;              // Здесь будет хранится дескриптор окна
extern HINSTANCE  hInstance;              // Здесь будет хранится дескриптор приложения
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
extern bool start;				// запуск процесса падения
extern bool explosion;			// запуск взрыа
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
#include "Main.h"
#pragma once
#define MAP_SIZE    1024 // Размер нашей карты высот
#define STEP_SIZE	16	// Ширина и высота каждого составляющего карту квадрата
#define HEIGHT_RATIO    1.5f    // Отношение, с которым Y изменяется относительно X и Z
int Height(BYTE* pHeightMap, int X, int Y);	// Загружает .raw файл в переменную с передаваемой длинной
int Height_for_camera(BYTE* pHeightMap, int X, int Y); // проверка для камеры (чтобы не проваливаться под пол)
void LoadRawFile(LPSTR strName, int nSize, BYTE* pHeightMap);	// Конвертирует данные карты высот в примитивы и отрисовывает их на экран
// Конвертирует данные карты высот в примитивы и отрисовывает их на экран 
void RenderHeightMap(BYTE pHeightMap[]);
extern BYTE g_HeightMap[MAP_SIZE * MAP_SIZE];

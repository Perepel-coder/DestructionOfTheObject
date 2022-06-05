#include "Main.h"
#pragma once
#define MAP_SIZE    1024 // ������ ����� ����� �����
#define STEP_SIZE	16	// ������ � ������ ������� ������������� ����� ��������
#define HEIGHT_RATIO    1.5f    // ���������, � ������� Y ���������� ������������ X � Z
int Height(BYTE* pHeightMap, int X, int Y);	// ��������� .raw ���� � ���������� � ������������ �������
int Height_for_camera(BYTE* pHeightMap, int X, int Y); // �������� ��� ������ (����� �� ������������� ��� ���)
void LoadRawFile(LPSTR strName, int nSize, BYTE* pHeightMap);	// ������������ ������ ����� ����� � ��������� � ������������ �� �� �����
// ������������ ������ ����� ����� � ��������� � ������������ �� �� ����� 
void RenderHeightMap(BYTE pHeightMap[]);
extern BYTE g_HeightMap[MAP_SIZE * MAP_SIZE];

#include "pch.h"
#include "Main.h"
using namespace std;
#pragma warning(disable : 4996)
extern bool g_bDetail; // ���������/���������� ���������� �������
// ������� �������� �������� ��������� �������� 
extern int g_DetailScale;
// ������������� ���������� ���������� ����������� �� ������ X � Z
void SetTextureCoord(float x, float z) {
	//// ��� ����� ���������� ���������� ���������� ��� ������� �������. ����� 
	//// ������� ���, ������ ���� ������� X & Y, � ����� �� �� MAP_SIZE ����� �����������. 
	//// �������, ��� �������������, ��� ����� ����� ����� ����� �� �������, ��� � ��������.
	//glTexCoord2f(x / MAP_SIZE, -z / MAP_SIZE);
	float u = x / (float)MAP_SIZE;
	float v = -z / (float)MAP_SIZE;
	// ������ �������� ��������� ������� �� ����� ������������ 
	// glMultiTexCoord2fARB (). ��� �������� ��� ������� u/v ���������� 
	// ��� ������ ���������� �����, ��� ��� �� ���������� ���������������������. 
	// ��������� �� ����� ������������ ���������� ������� ��� �������� 
	// ��������� ��������, ������ �������� �� �� u/v ���������� 
	// ��� ����� �������.
	// ��������� ���������� �������� �����������
	glMultiTexCoord2fARB(GL_TEXTURE0_ARB, u, v);
	// ��������� ���������� ��������� �������� 
	glMultiTexCoord2fARB(GL_TEXTURE1_ARB, u, v);
}
// �-� ������������ ��� ���������� ����� ����� �����.
// ��� ������ � ��������� ������ ����� ���������, ��� �� �� �������
// �� ������� �������, ��� ��� ��������, ��� ����� �� ���������. 
// ����� ������� X � Y ����� � �������� (MAX_SIZE � 1).
int Height_for_camera(BYTE* pHeightMap, int X, int Y) {
	int x = X % MAP_SIZE;   // �������� ��� X 
	int y = Y % MAP_SIZE;   // �������� ��� Y
	if (!pHeightMap) { return 0; }	// ��������, ��� �������� � ����������� �������u
	int size = MAP_SIZE * MAP_SIZE;
	if ((x + (y * MAP_SIZE)) >= size || (x + (y * MAP_SIZE)) < 0) {
		return -1;
	}
	else {
		return pHeightMap[x + (y * MAP_SIZE)];  // ����� ������ ������� �������
	}
}
int Height(BYTE* pHeightMap, int X, int Y) {
	int x = X % MAP_SIZE;   // �������� ��� X 
	int y = Y % MAP_SIZE;   // �������� ��� Y
	if (!pHeightMap) { return 0; }	// ��������, ��� �������� � ����������� �������u
	// ���� ��� ����� ������� ��������� � 2�-������. 
	// �� ����� ������������ �������: index = (x + (y * arrayWidth) ). 
	// ��� ������, ��� �� ���������� 2�-������[x][y], 
	// ����� �� ����� ���������������. ������, ���� ������ ������, 
	// ����� ������ ��� ����� �������.
	return pHeightMap[x + (y * MAP_SIZE)];  // ����� ������ ������� �������
}
// ������������� �������� �������� �������, � ����������� �� ������ � ������	(����������)
void SetVertexColor(BYTE* pHeightMap, int x, int y) {
	if (!pHeightMap) return;     // ��������, ��� ������ �����
	// ����� �� ������������� ���� �������, ����������� �� ������� � ������.
	// �������� �� 0 �� 1.0 �������� �������� ������ �� 256.0f.
	float fColor = -0.15f + (Height(pHeightMap, x, y) / 256.0f);
	// �������� ������ ������� �������� �� ������� ������� 
	glColor3f(0, fColor, 0);
}
// ������ ����� �����, ��� ��������� ���������
// ������ ��� ����� �������������� �������� ����������� � ��������� 
// ���������. ����� ������� �� ����������, ��� ����� ��������� ������� 
// ARB-����������. ������, GL_COMBINE_ARB, ��������� ��� ������������� 
// ��������� ��������, ������, GL_RGB_SCALE_ARB, ��������� ��� 
// ����������� ����� ������ ��������, ����� ��� �� ��������� ������. 
// ��� ��������� �������� ��� ���� ��������� � ��������� �������. 
// GL_RGB_SCALE_ARB ����� ��������� �������� ������ 1, 2 ��� 4. 2 ��������
// ������ ���������, 4 ��� ������� ����. 
// ����� ������� ������� ��������� ��������, ����������� ����������
// �������. ����� �� ������ � ����� ���������� ������, �� ����� 
// �������������� �� ���������� ��������� ��������.
void RenderHeightMap(BYTE pHeightMap[]) {
	int X = 0, Y = 0;       // ���������� ��� ������ �� �������
	int x, y, z;            // ���������� ��� ������
	bool Z = false; int i = 0;
	bool bSwitchSides = false;
	if (!pHeightMap) return;     // ��������, ��� ������ �����
	glActiveTextureARB(GL_TEXTURE0_ARB);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Terrain[0]);
	// ���� �������� ��������� ��������, ����������� ������ ������:
	if (g_bDetail) {
		// ���������� ��������� ��������
		glActiveTextureARB(GL_TEXTURE1_ARB);
		glEnable(GL_TEXTURE_2D);
		// �������� ����� ���������� � ����������� ����� (�������� �2�).
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_ARB);
		glTexEnvi(GL_TEXTURE_ENV, GL_RGB_SCALE_ARB, 2);
		// ������ ��������� �������� 
		glBindTexture(GL_TEXTURE_2D, Detail[0]);
		// ������ ������ � ���������� �������. ��� �������� ��� �������� 
		// ������� ��������� ��������.
		glMatrixMode(GL_TEXTURE);
		// ���������� ������� � ��������� ������� �������� scale
		glLoadIdentity();
		glScalef((float)g_DetailScale, (float)g_DetailScale, 1);
		// ������� �� ���������� ������� 
		glMatrixMode(GL_MODELVIEW);
	}
	glBegin(GL_TRIANGLE_STRIP);
	for (X = 0; X < MAP_SIZE; X += STEP_SIZE) {
		// ���������, ����� �� ��������� � ��������������� ������� 
		if (bSwitchSides) {
			// �������� ����� ����������� ��� �������� X. 
			// �������� � MAP_SIZE � ��� �� 0.
			for (Y = MAP_SIZE; Y > 0; Y -= STEP_SIZE) {
				// �������� (X, Y, Z) �������� ��� ������ ����� ������� 
				x = X;
				y = Height(pHeightMap, X, Y);
				z = Y;
				// ������������� �����-�� ������ ���� �������
				SetFogCoord(g_FogDepth, (float)y);
				// ���������� ���������� ��� ������� 
				SetTextureCoord((float)x, (float)z);
				glVertex3i(x, y, z);
				// �������� (X, Y, Z) ��� ������ ������ ������� 
				x = X + STEP_SIZE;
				y = Height(pHeightMap, X + STEP_SIZE, Y);
				z = Y;
				// ������������� �����-�� ������ ���� �������
				SetFogCoord(g_FogDepth, (float)y);
				// ������������� ���������� ���������� � �������� ������� 
				SetTextureCoord((float)x, (float)z);
				glVertex3i(x, y, z);
			}
		}
		else {
			// �������� ����� ����������� ��� �������� X. 
			// �������� � 0 � ��� �� MAP_SIZE.
			for (Y = 0; Y < MAP_SIZE; Y += STEP_SIZE) {
				// �������� (X, Y, Z) ��� ������ ������ �������
				x = X + STEP_SIZE;
				y = Height(pHeightMap, X + STEP_SIZE, Y);
				z = Y;
				// ������������� �����-�� ������ ���� �������
				SetFogCoord(g_FogDepth, (float)y);
				// ������������� ���������� ���������� � �������� ������� 
				SetTextureCoord((float)x, (float)z);
				glVertex3i(x, y, z);
				// �������� (X, Y, Z) �������� ��� ������ ����� ������� 
				x = X;
				y = Height(pHeightMap, X, Y);
				z = Y;
				// ������������� �����-�� ������ ���� �������
				SetFogCoord(g_FogDepth, (float)y);
				// ������������� ���������� ���������� � �������� ������� 
				SetTextureCoord((float)x, (float)z);
				glVertex3i(x, y, z);
			}
		}
		bSwitchSides = !bSwitchSides;
	}
	glEnd();
	//glBegin(GL_QUADS);
	//for (X = 0; X < MAP_SIZE; X += STEP_SIZE) {
	//	for (Y = 0; Y < MAP_SIZE; Y += STEP_SIZE) {
	//		// �������� X,Y,Z ��� ������ ����� ������� 
	//		x = X; y = Height(pHeightMap, X, Y ); z = Y;
	//		SetFogCoord(g_FogDepth, y);
	//		SetTextureCoord(x, z);
	//		glVertex3i(x, y, z);    // �������� ��� ������� ��� ������� � OpenGL
	//		// �������� (X, Y, Z) ��� ������� ����� ������� 
	//		x = X; y = Height(pHeightMap, X, Y + STEP_SIZE ); z = Y + STEP_SIZE ;
	//		SetFogCoord(g_FogDepth, y);
	//		SetTextureCoord(x, z);
	//		glVertex3i(x, y, z);    // ������
	//		x = X + STEP_SIZE; y = Height(pHeightMap, X + STEP_SIZE, Y + STEP_SIZE); z = Y + STEP_SIZE;
	//		SetFogCoord(g_FogDepth, y);
	//		SetTextureCoord(x, z);
	//		glVertex3i(x, y, z);    // ������
	//		x = X + STEP_SIZE; y = Height(pHeightMap, X + STEP_SIZE, Y); z = Y;
	//		SetFogCoord(g_FogDepth, y);
	//		SetTextureCoord(x, z);
	//		glVertex3i(x, y, z);    // ������������
	//	}
	//}
	//glEnd();
	glActiveTextureARB(GL_TEXTURE1_ARB); glDisable(GL_TEXTURE_2D);
	glActiveTextureARB(GL_TEXTURE0_ARB); glDisable(GL_TEXTURE_2D);
}
//   ��������� .raw ���� � ������ ����. ������ �������� � �������� ������.
void LoadRawFile(LPSTR strName, int nSize, BYTE* pHeightMap) {
	FILE* pFile = NULL;
	// ������� ���� ��� ��������� ������ 
	pFile = fopen(strName, "rb");
	// ���������, ��������� �� �������� ���� 
	if (pFile == NULL) { // ������� ������ � ������������� ������� 
		MessageBox(NULL, L"���� �� ��������!", L"Error", MB_OK);
		return;
	}
	fread(pHeightMap, 1, nSize, pFile);
	int result = ferror(pFile);
	if (result) {
		MessageBox(NULL, L"���������� ������� ������!", L"Error", MB_OK);
	}
	fclose(pFile);
}
// ������� �� ����� ��, ��� �� �������: 
// 1) ������� ������ ����� ����� �� ����� .raw. ��� ������, ��� ��� � .raw ������ ��� ������� ����������, ������ ���� �����������. 
// 2) ����� ��������� ����� �����, ��� ����� ������� � �� �����.
// ��� ���� �� ������� ������, �� ������ �������� �������� � ������������� �������� (STEP_SIZE).
// ����������� �� ����� �����, ������ ��� �������� � �����. 
// ������ ������� ��������� ���������� ������� � ������ ������� �������� �����.
//////////////////////////////////
// ������������� �������� ����� ��� ������� ������� � ��������� ��������
void SetFogCoord(float depth, float height) {
	// ������� ��������� ������� ������ � ������ ������� �������. ���� ������ 
	// ������ �������, ��� ��� ���� ������� �� ���������� (0), �� ���� ������ 
	// ���� �������, ������������ �������� ������. ��������� ����� ������� 
	// �����, ������������ � glFogCoordfEXT (), ������� ������ ������, ��� ����� 
	// ������� ������� �� ������, ����� ������� ��� �������� �������������. 
	// ����� ����� ������ ������ ������, ��� �����.
	float fogY = 0;
	// ��������, �� ������ �� ������ �������, ��� �������� �������
	if (height > depth) fogY = 0; // ����� ��������� ������� ������ ��� ������� ������� 
	else fogY = -(height - depth);
	// ��������� ���������� ������ ��� ���� �������, ��������� ��������� �� �������-���������� 
	glFogCoordfEXT(fogY);
}

#include "pch.h"
#include "Main.h"
VECTOR SkyBox[24];
enum figure { QUAD };
bool f = false;
bool grid_ = false;
void grid() {
    if (grid_) {
        
        for (float i = 10; i <= 1000; i += 50) {
            glBegin(GL_LINES);
            // ��� � 
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex3f(13, 190, i);
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex3f(973, 190, i);
            // ��� Z 
            glColor3f(0.0f, 1.0f, 0.0f);
            glVertex3f(i, 190, 10);
            glColor3f(0.0f, 1.0f, 0.0f);
            glVertex3f(i, 190, 1000);
            glEnd();
        }
        glBegin(GL_LINES);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(500, 0, 500);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(500, 1000, 500);
        glEnd();
    }
    glColor3f(1.0f, 1.0f, 1.0f);
}
void pack_in_box(VECTOR* Box, int figure, float x, float y, float z, float width, float height, float length) {
    if (figure == QUAD) {
        x = x - width / 2;
        y = y - height / 2;
        z = z - length / 2;
        SkyBox[0] = { x + width, y,z }; SkyBox[1] = { x + width, y + height, z };
        SkyBox[2] = { x, y + height, z }; SkyBox[3] = { x, y, z };
        SkyBox[4] = { x, y,z + length }; SkyBox[5] = { x, y + height, z + length };
        SkyBox[6] = { x + width, y + height, z + length }; SkyBox[7] = { x + width, y, z + length };
        SkyBox[8] = { x, y, z }; SkyBox[9] = { x, y, z + length };
        SkyBox[10] = { x + width, y, z + length }; SkyBox[11] = { x + width, y,z };
        SkyBox[12] = { x + width, y + height, z }; SkyBox[13] = { x + width, y + height, z + length };
        SkyBox[14] = { x, y + height, z + length }; SkyBox[15] = { x, y + height, z };
        SkyBox[16] = { x, y + height,z }; SkyBox[17] = { x, y + height,z + length };
        SkyBox[18] = { x, y,z + length }; SkyBox[19] = { x, y,z };
        SkyBox[20] = { x + width, y, z }; SkyBox[21] = { x + width, y, z + length };
        SkyBox[22] = { x + width, y + height, z + length }; SkyBox[23] = { x + width, y + height, z };
    }
}
void CreateSkyBox(float x, float y, float z, float width, float height, float length) {
    glEnable(GL_TEXTURE_2D);		// ���������� ��������� ��������
    // ������ �������� � � ������ ������� ����
    // ������������� ����� � x/y/z 
    x = x - width / 2;
    y = y - height / 2;
    z = z - length / 2;
    //LightPosition[0] = x - width; LightPosition[1] = y + height; LightPosition[2] = z - length; LightPosition[3] = 0.0f;
    // ������ �������� � ������ �������
    glBindTexture(GL_TEXTURE_2D, Back[0]);
    glBegin(GL_QUADS);
    // ���������� ���������� � ������� ������ ������� 
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
    glEnd();
    // �������� �������� � �������� �������
    glBindTexture(GL_TEXTURE_2D, Front[0]);
    glBegin(GL_QUADS);
    // ���������� ���������� � ������� �������� ������� 
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z + length);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z + length);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z + length);
    glEnd();
    // ������ �������� �� ������ �������
    glBindTexture(GL_TEXTURE_2D, Bottom[0]);
    glBegin(GL_QUADS);
    // ���������� ���������� � ������� ������ ������� 
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y, z + length);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y, z + length);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z);
    glEnd();
    // ������� �������� �� ������� �������
    glBindTexture(GL_TEXTURE_2D, Top[0]);
    glBegin(GL_QUADS);
    // ���������� ���������� � ������� ������� �������
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y + height, z + length);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y + height, z + length);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z);
    glEnd();
    // ����� �������� �� ����� �������
    glBindTexture(GL_TEXTURE_2D, Left[0]);
    glBegin(GL_QUADS);
    // ���������� ���������� � ������� 
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z + length);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z + length);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);
    glEnd();
    // �������� ������ �������
    glBindTexture(GL_TEXTURE_2D, Right[0]);
    glBegin(GL_QUADS);
    // ���������� ���������� � �������
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z + length);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}
int DrawGLScene(GLvoid)                // ����� ����� ����������� ��� ����������
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);      // �������� ����� � ����� �������
    glLoadIdentity();              // �������� ������� �������
    pack_in_box(SkyBox, QUAD, 500, 0, 500, 4000, 4000, 4000);
    ///////////////////////////////////////////
    g_Camera.CheckCameraCollision_q(SkyBox, 24);
    g_Camera.Look();    // ���� ������
    glInitNames();  // ��� ������� ������� ������ ���, ��� ��� ����� �������� �� �� ����� �� ������ ID
    ////////////////////////////////////
    // ���������� ��� ������ ������� 
    static float beginTime = GetTickCount() * 0.001f;
    static float endTime = beginTime;
    static float dt = 0.0f;
    //Delta Time � �����, ��������� � �������� �����
    ////////////////////////////// ���������
    //////////////////////////////////////////
    grid();                                         // �����
    RenderHeightMap(g_HeightMap);                   // �������� �����
    CreateSkyBox(500, 0, 500, 4000, 4000, 4000);    //�������� �������� 
    if (!explosion) {
        parameter.Draw();
    }
    if (explosion) {;
        if (!f) {
            f = true;
            float x, y, z; int count;
            parameter.access(&x, &y, &z, &count);  // count = count / 2;
            dyn.init(VECTOR(x, y + count * 2, z), count);
        }
        if (LockFrameRate) {
            beginTime = GetTickCount() * 0.001f;    // �������� ����� ������ �����
            dt = beginTime - endTime;   // �������� dt
            // ���������� � �������� ��� �������:
            for (int i = 0; i < dyn.amount; i++) {
                dyn.draw_particles(i);
                dyn.process(dt, i);
            }
            // ������� �����, ��������� � ����� �����
            endTime = GetTickCount() * 0.001f;
        }
    }
    // �������� ������� ������� ������ 
    VECTOR  vPos = g_Camera.mv_position;
    VECTOR  vNewPos = vPos;
    // ��������� ������ ������ ��� ������� ������� x/z, � ���������� 10, 
    // ����� ������ �� ���� ����� �� ����.
    int result = Height_for_camera(g_HeightMap, (int)vPos.x, (int)vPos.z) + 10;
    if ((vPos.y < result + 10)) {
        // ��������� ����� ������� ������ = ������ ����������� + 10
        vNewPos.y = (float)(result + 10);
        // ������� ������� ������, ������� � �����
        float temp = vNewPos.y - vPos.y;
        //  �������� � ������� ������� ��� ������� 
        VECTOR  vView = g_Camera.mv_view;
        vView.y += temp;
        // ��������� ������ � ����� �������
        g_Camera.PositionCamera(vNewPos.x, vNewPos.y, vNewPos.z, vView.x, vView.y, vView.z, 0, 1, 0);
    }
    SwapBuffers(hDC);    // ������ ����� (������� �����������)
    return true;                // ���������� ������ �������
}
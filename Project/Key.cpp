#include "pch.h"
#include "Main.h"
BOOL light;      // ���� ��� / ����
BOOL lp;         // L ������?
BOOL gp;
BOOL GRID;
BOOL strafe;
Output data;
void keyboard() {
    // ������
    g_Camera.Update(speed);
    if (keys['G'] && !gp) // ������� 'G' ������ � �� ������������?
    {
        gp = TRUE;      // gp ��������� TRUE    (������������)
        GRID = !GRID; // ������������ ����� TRUE/FALSE
        if (!GRID)               // ���� �� ����
        {
            grid_ = false;  // ������ �����
        }
        else                      // � ��������� ������
        {
            grid_ = true;   // ��������� �����
        }
    }
    if (!keys['G']) // ������� 'G' ������?
    {
        gp = FALSE;      // ���� ���, �� lp ����� FALSE (�� ������������)
    }
    // ���� ���/����
    if (keys['L'] && !lp) // ������� 'L' ������ � �� ������������?
    {
        lp = TRUE;      // lp ��������� TRUE    (������������)
        light = !light; // ������������ ����� TRUE/FALSE
        if (!light)               // ���� �� ����
        {
            glDisable(GL_LIGHTING);  // ������ ���������
        }
        else                      // � ��������� ������
        {
            glEnable(GL_LIGHTING);   // ��������� ���������
        }
    }
    if (!keys['L']) // ������� 'L' ������?
    {
        lp = FALSE;      // ���� ���, �� lp ����� FALSE (�� ������������)
    }
    // ������ �� 3 ����
    /*if (keys[VK_RIGHT]) {                             (� ���� ����� ������ �� ����� (��, ����))
        g_Camera.RotateAroundPoint(g_Camera.mv_view, speed, 0, 1, 0);
    }
    if (keys[VK_LEFT]) {
        g_Camera.RotateAroundPoint(g_Camera.mv_view, -speed, 0, 1, 0);
    }*/
    // ���������� �����
    if (keys['Z']) {
        //ShowCursor(false);              // ������ ��������� ����� (������� �����! ������ ��������!)
        g_Camera.SetViewByMouse();
    }
    // ���� � ��������� 
    if (keys['Q']) {
        // �������� �������� scale.
        // �������� ������� �������� �� 2, ���� ��� �� ��������� 128.
        g_DetailScale = (g_DetailScale * 2) % 128;
        // ���� ��������=0, ������ ��� 1 
        if (g_DetailScale == 0) { g_DetailScale = 1; }
    }
    // ����������� �������� ������ ������ ��� ������ ��������� +/- .
    if (keys[VK_ADD]) {
        g_FogDepth += 0.1f;        // ����������� ������
        if (g_FogDepth > 150) g_FogDepth = 150;      // �� �� ����� 200 
    }
    if (keys[VK_SUBTRACT]) {
        g_FogDepth -= 0.1f;
        if (g_FogDepth < 0) g_FogDepth = 0;  // �� ����� 0 
    }
    //////// ������ ������� /////////////
    if (keys[VK_SPACE]) {
        start = true;
        parameter.output(&data);
    }
}
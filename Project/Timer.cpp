#include "pch.h"
#include "Main.h"
bool LockFrameRate(int frame_rate) {
    static float lastTime = 0.0f;
    // ������� ����� � ��������: 
    float currentTime = GetTickCount() * 0.001f;
    // �������� ��������� � ����������� ����� �����. 
    // ���� ������ ����������, ���������� true.
    if ((currentTime - lastTime) > (1.0f / frame_rate)) {
        // ������� ��������� ����� 
        lastTime = currentTime;
        return true;
    }
    return false;
}
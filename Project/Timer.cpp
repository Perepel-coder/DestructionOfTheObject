#include "pch.h"
#include "Main.h"
bool LockFrameRate(int frame_rate) {
    static float lastTime = 0.0f;
    // Текущее время в секундах: 
    float currentTime = GetTickCount() * 0.001f;
    // Получаем прошедшее с предыдущего кадра время. 
    // Если прошло достаточно, возвращаем true.
    if ((currentTime - lastTime) > (1.0f / frame_rate)) {
        // Сбросим последнее время 
        lastTime = currentTime;
        return true;
    }
    return false;
}
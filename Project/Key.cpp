#include "pch.h"
#include "Main.h"
BOOL light;      // Свет ВКЛ / ВЫКЛ
BOOL lp;         // L нажата?
BOOL gp;
BOOL GRID;
BOOL strafe;
Output data;
void keyboard() {
    // стрейф
    g_Camera.Update(speed);
    if (keys['G'] && !gp) // Клавиша 'G' нажата и не удерживается?
    {
        gp = TRUE;      // gp присвоили TRUE    (удерживается)
        GRID = !GRID; // Переключение сетки TRUE/FALSE
        if (!GRID)               // Если не свет
        {
            grid_ = false;  // Запрет сетки
        }
        else                      // В противном случае
        {
            grid_ = true;   // Разрешить сетку
        }
    }
    if (!keys['G']) // Клавиша 'G' Отжата?
    {
        gp = FALSE;      // Если так, то lp равно FALSE (не удерживается)
    }
    // свет вкл/выкл
    if (keys['L'] && !lp) // Клавиша 'L' нажата и не удерживается?
    {
        lp = TRUE;      // lp присвоили TRUE    (удерживается)
        light = !light; // Переключение света TRUE/FALSE
        if (!light)               // Если не свет
        {
            glDisable(GL_LIGHTING);  // Запрет освещения
        }
        else                      // В противном случае
        {
            glEnable(GL_LIGHTING);   // Разрешить освещение
        }
    }
    if (!keys['L']) // Клавиша 'L' Отжата?
    {
        lp = FALSE;      // Если так, то lp равно FALSE (не удерживается)
    }
    // взгляд от 3 лица
    /*if (keys[VK_RIGHT]) {                             (в этой проге вообще не нужен (фу, бяка))
        g_Camera.RotateAroundPoint(g_Camera.mv_view, speed, 0, 1, 0);
    }
    if (keys[VK_LEFT]) {
        g_Camera.RotateAroundPoint(g_Camera.mv_view, -speed, 0, 1, 0);
    }*/
    // управление мышью
    if (keys['Z']) {
        //ShowCursor(false);              // Скрыть указатель мышки (помыслы чисты! нечего скрывать!)
        g_Camera.SetViewByMouse();
    }
    // игра с тектурами 
    if (keys['Q']) {
        // Изменяем значение scale.
        // Умножаем текущее значение на 2, пока оно не достигнет 128.
        g_DetailScale = (g_DetailScale * 2) % 128;
        // Если значение=0, делаем его 1 
        if (g_DetailScale == 0) { g_DetailScale = 1; }
    }
    // возможность изменять высоту тумана над землей клавишами +/- .
    if (keys[VK_ADD]) {
        g_FogDepth += 0.1f;        // Увеличиваем высоту
        if (g_FogDepth > 150) g_FogDepth = 150;      // Но не более 200 
    }
    if (keys[VK_SUBTRACT]) {
        g_FogDepth -= 0.1f;
        if (g_FogDepth < 0) g_FogDepth = 0;  // Не менее 0 
    }
    //////// ЗАПУСК ПАДЕНИЯ /////////////
    if (keys[VK_SPACE]) {
        start = true;
        parameter.output(&data);
    }
}
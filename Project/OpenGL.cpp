#include "pch.h"
#include "Main.h"
// Расширение: указатель на функцию, устанавливающую глубину тумана для вершины
PFNGLFOGCOORDFEXTPROC glFogCoordfEXT = NULL;
// В начале файла включим мультитекстурирование; добавим прототипы нужных 
// функций и некоторые переменные
PFNGLMULTITEXCOORD2FARBPROC     glMultiTexCoord2fARB = NULL;
PFNGLACTIVETEXTUREARBPROC       glActiveTextureARB = NULL;
// Данные карты высот 
BYTE g_HeightMap[MAP_SIZE * MAP_SIZE];
bool g_bRenderMode = true; // Класс камеры
float g_FogDepth = 0.0f;    // глубина тумана
bool g_bDetail = true;  // Вкл/выкл детальную текстуру
int g_DetailScale = 20; // Текущее scale-значение для текстурной матрицы
HGLRC  hRC = NULL;              // Постоянный контекст рендеринга
HDC  hDC = NULL;              // Приватный контекст устройства GDI
HWND  hWnd = NULL;              // Здесь будет хранится дескриптор окна
HINSTANCE  hInstance;              // Здесь будет хранится дескриптор приложения
int camera_width;
int camera_height;
LPARAM Mouse_lParam;
bool BEGIN = false;
bool BEGIN_TEXTURE = false;
bool  keys[600];                // Массив, используемый для операций с клавиатурой
bool  active = true;                // Флаг активности окна, установленный в true по умолчанию
bool  fullscreen = false;              // Флаг режима окна, установленный в полноэкранный по умолчанию
GLfloat LightAmbient[] = { 0.9f, 0.9f, 0.9f, 1.0f }; // Значения фонового света
GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // Значения диффузного света
GLfloat LightPosition[] = { 0.0f, 1000.0f, 0.0f, 1.0f };     // Позиция света
LRESULT  CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);        // Прототип функции WndProc
GLvoid ReSizeGLScene(GLsizei width, GLsizei height)        // Изменить размер и инициализировать окно GL
{
    if (height == 0)              // Предотвращение деления на ноль
    {
        height = 1;
    }
    camera_height = height;
    camera_width = width;
    glViewport(0, 0, width, height);          // Сброс текущей области вывода
    glMatrixMode(GL_PROJECTION);            // Выбор матрицы проекций
    glLoadIdentity();              // Сброс матрицы проекции
    // Вычисление соотношения геометрических размеров для окна
    gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 10, 10000.0f);
    //gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, .5f, 150.0f);
    glMatrixMode(GL_MODELVIEW);            // Выбор матрицы вида модели
    glLoadIdentity();              // Сброс матрицы вида модели
}
int InitGL(GLvoid)                // Все установки касаемо OpenGL происходят здесь  (+ я сюда пихаю все, что надо инициализировать)
{
    LoadGLTextures();			// Загрузка текстур
    LoadRawFile((LPSTR)"Terrain.raw", MAP_SIZE * MAP_SIZE, g_HeightMap);
    // Устанавливаем камеру 
    g_Camera.PositionCamera(-1450.0f, 1950.0f, -264.9f, 521.0f, 521.0f, 521.0f, 0.0f, 1.0f, 0.0f);
    g_Camera.SetCameraRadius(50);
    //????????????????
    glActiveTextureARB = (PFNGLACTIVETEXTUREARBPROC)wglGetProcAddress("glActiveTextureARB");
    glMultiTexCoord2fARB = (PFNGLMULTITEXCOORD2FARBPROC)wglGetProcAddress("glMultiTexCoord2fARB");
    // Нужно убедится, что текущая версия OpenGL на машине поддерживает мультитекстурирование:
    if (!glActiveTextureARB || !glMultiTexCoord2fARB) {
        // Выводим ошибку и выходим
        MessageBox(hWnd, L"Не поддерживается мультитекстурирование!", L"ERROR", MB_OK);
        PostQuitMessage(0);
    }
    // Нужно проверить, поддерживает ли видеокарта хардварный туман.
    // Получаем указатель на функцию нужного расширения 
    glFogCoordfEXT = (PFNGLFOGCOORDFEXTPROC)wglGetProcAddress("glFogCoordfEXT");
    if (!glFogCoordfEXT) {
        // Выводим ошибку и выходим
        MessageBox(hWnd, L"Не поддерживается хардровый туман!", L"ERROR", MB_OK);
        PostQuitMessage(0);
    }
    // Установим цвет тумана 
    float fogColor[4] = { 0.6f, 0.5f, 0.6f, 1.0f };
    glEnable(GL_FOG);               // Вкл. туман
    glFogi(GL_FOG_MODE, GL_LINEAR);         // Устанавливаем режим в GL_LINEAR
    glFogfv(GL_FOG_COLOR, fogColor);        // Передаём OpenGL цвет тумана
    glFogf(GL_FOG_START, 0.0f);          // Начальное значение глубины — 0
    glFogf(GL_FOG_END, 50.0f);           // Конечное — 50
    // Теперь сообщаем OpenGL, что используем расширение для обьемного тумана glFogCoordEXT ()
    glFogi(GL_FOG_COORDINATE_SOURCE_EXT, GL_FOG_COORDINATE_EXT);
    glShadeModel(GL_SMOOTH);            // Разрешить плавное цветовое сглаживание
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);          // Очистка экрана в черный цвет
    glClearDepth(1.0f);              // Разрешить очистку буфера глубины
    glEnable(GL_DEPTH_TEST);            // Разрешить тест глубины
    glDepthFunc(GL_LEQUAL);            // Тип теста глубины
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);      // Улучшение в вычислении перспективы
    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);    // Установка Фонового Света
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);    // Установка Диффузного Света
    glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);   // Позиция света
    glEnable(GL_LIGHT1); // Разрешение источника света номер один
    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    return true;                // Инициализация прошла успешно
}
GLvoid KillGLWindow(GLvoid)              // Корректное разрушение окна
{
    if (fullscreen)              // Мы в полноэкранном режиме?

    {
        ChangeDisplaySettings(NULL, 0);        // Если да, то переключаемся обратно в оконный режим
        ShowCursor(true);            // Показать курсор мышки
    }
    if (hRC)                // Существует ли Контекст Рендеринга?
    {
        if (!wglMakeCurrent(NULL, NULL))        // Возможно ли освободить RC и DC?
        {
            MessageBox(NULL, L"Release Of DC And RC Failed.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
        }
        if (!wglDeleteContext(hRC))        // Возможно ли удалить RC?
        {
            MessageBox(NULL, L"Release Rendering Context Failed.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
        }
        hRC = NULL;              // Установить RC в NULL
    }
    if (hDC && !ReleaseDC(hWnd, hDC))          // Возможно ли уничтожить DC?
    {
        MessageBox(NULL, L"Release Device Context Failed.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
        hDC = NULL;                // Установить DC в NULL
    }
    if (hWnd && !DestroyWindow(hWnd))            // Возможно ли уничтожить окно?
    {
        MessageBox(NULL, L"Could Not Release hWnd.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
        hWnd = NULL;                // Установить hWnd в NULL
    }
    if (!UnregisterClass(L"OpenGL", hInstance))        // Возможно ли разрегистрировать класс
    {
        MessageBox(NULL, L"Could Not Unregister Class.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
        hInstance = NULL;                // Установить hInstance в NULL
    }
}
BOOL CreateGLWindow(LPCWSTR title, int width, int height, int bits, bool fullscreenflag)
{
    GLuint PixelFormat;              // Хранит результат после поиска
    WNDCLASS  wc;                // Структура класса окна
    DWORD    dwExStyle;              // Расширенный стиль окна
    DWORD    dwStyle;              // Обычный стиль окна
    RECT WindowRect;                // Grabs Rectangle Upper Left / Lower Right Values
    WindowRect.left = (long)0;              // Установить левую составляющую в 0
    WindowRect.right = (long)width;              // Установить правую составляющую в Width
    WindowRect.top = (long)0;                // Установить верхнюю составляющую в 0
    WindowRect.bottom = (long)height;              // Установить нижнюю составляющую в Height
    fullscreen = fullscreenflag;              // Устанавливаем значение глобальной переменной fullscreen
    hInstance = GetModuleHandle(NULL);        // Считаем дескриптор нашего приложения
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;      // Перерисуем при перемещении и создаём скрытый DC
    wc.lpfnWndProc = (WNDPROC)WndProc;          // Процедура обработки сообщений
    wc.cbClsExtra = 0;              // Нет дополнительной информации для окна
    wc.cbWndExtra = 0;              // Нет дополнительной информации для окна
    wc.hInstance = hInstance;            // Устанавливаем дескриптор
    wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);        // Загружаем иконку по умолчанию
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);        // Загружаем указатель мышки
    wc.hbrBackground = NULL;              // Фон не требуется для GL
    wc.lpszMenuName = NULL;              // Меню в окне не будет
    wc.lpszClassName = L"OpenGL";            // Устанавливаем имя классу
    if (!RegisterClass(&wc))              // Пытаемся зарегистрировать класс окна
    {
        MessageBox(NULL, L"Failed To Register The Window Class.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
        return false;                // Выход и возвращение функцией значения false
    }
    if (fullscreen)                // Полноэкранный режим?
    {
        DEVMODE dmScreenSettings;            // Режим устройства
        memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));    // Очистка для хранения установок
        dmScreenSettings.dmSize = sizeof(dmScreenSettings);      // Размер структуры Devmode
        dmScreenSettings.dmPelsWidth = width;        // Ширина экрана
        dmScreenSettings.dmPelsHeight = height;        // Высота экрана
        dmScreenSettings.dmBitsPerPel = bits;        // Глубина цвета
        dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;// Режим Пикселя
        // Пытаемся установить выбранный режим и получить результат.  Примечание: CDS_FULLSCREEN убирает панель управления.
        if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
        {
            // Если переключение в полноэкранный режим невозможно, будет предложено два варианта: оконный режим или выход.
            if (MessageBox(NULL, L"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?",
                L"NeHe GL", MB_YESNO | MB_ICONEXCLAMATION) == IDYES) {
                fullscreen = false;          // Выбор оконного режима (fullscreen = false)
            }
            else
            {
                // Выскакивающее окно, сообщающее пользователю о закрытие окна.
                MessageBox(NULL, L"Program Will Now Close.", L"ERROR", MB_OK | MB_ICONSTOP);
                return false;            // Выход и возвращение функцией false
            }
        }
    }
    //ShowCursor(false);              // Скрыть указатель мышки
    if (fullscreen)                  // Мы остались в полноэкранном режиме?
    {
        ShowCursor(false);              // Скрыть указатель мышки
        dwExStyle = WS_EX_APPWINDOW;          // Расширенный стиль окна
        dwStyle = WS_POPUP;            // Обычный стиль окна
    }
    else
    {
        dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;      // Расширенный стиль окна
        dwStyle = WS_OVERLAPPEDWINDOW;        // Обычный стиль окна
    }
    AdjustWindowRectEx(&WindowRect, dwStyle, false, dwExStyle);      // Подбирает окну подходящие размеры
    if (!(hWnd = CreateWindowEx(dwExStyle,          // Расширенный стиль для окна
        L"OpenGL",          // Имя класса
        title,            // Заголовок окна
        WS_CLIPSIBLINGS |        // Требуемый стиль для окна
        WS_CLIPCHILDREN |        // Требуемый стиль для окна
        dwStyle,          // Выбираемые стили для окна
        0, 0,            // Позиция окна
        WindowRect.right - WindowRect.left,    // Вычисление подходящей ширины
        WindowRect.bottom - WindowRect.top,    // Вычисление подходящей высоты
        NULL,            // Нет родительского
        NULL,            // Нет меню
        hInstance,          // Дескриптор приложения
        NULL)))          // Не передаём ничего до WM_CREATE (???)
    {
        KillGLWindow();                // Восстановить экран
        MessageBox(NULL, L"Window Creation Error.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
        return false;                // Вернуть false
    }
    static  PIXELFORMATDESCRIPTOR pfd =            // pfd сообщает Windows каким будет вывод на экран каждого пикселя
    {
      sizeof(PIXELFORMATDESCRIPTOR),            // Размер дескриптора данного формата пикселей
      1,                  // Номер версии
      PFD_DRAW_TO_WINDOW |              // Формат для Окна
      PFD_SUPPORT_OPENGL |              // Формат для OpenGL
      PFD_DOUBLEBUFFER,              // Формат для двойного буфера
      PFD_TYPE_RGBA,                // Требуется RGBA формат
      (BYTE)bits,                  // Выбирается бит глубины цвета
      0, 0, 0, 0, 0, 0,              // Игнорирование цветовых битов
      0,                  // Нет буфера прозрачности
      0,                  // Сдвиговый бит игнорируется
      0,                  // Нет буфера накопления
      0, 0, 0, 0,                // Биты накопления игнорируются
      32,                  // 32 битный Z-буфер (буфер глубины)
      0,                  // Нет буфера трафарета
      0,                  // Нет вспомогательных буферов
      PFD_MAIN_PLANE,                // Главный слой рисования
      0,                  // Зарезервировано
      0, 0, 0                  // Маски слоя игнорируются
    };
    if (!(hDC = GetDC(hWnd)))              // Можем ли мы получить Контекст Устройства?
    {
        KillGLWindow();                // Восстановить экран
        MessageBox(NULL, L"Can't Create A GL Device Context.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
        return false;                // Вернуть false
    }
    if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))        // Найден ли подходящий формат пикселя?
    {
        KillGLWindow();                // Восстановить экран
        MessageBox(NULL, L"Can't Find A Suitable PixelFormat.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
        return false;                // Вернуть false
    }
    if (!SetPixelFormat(hDC, PixelFormat, &pfd))          // Возможно ли установить Формат Пикселя?
    {
        KillGLWindow();                // Восстановить экран
        MessageBox(NULL, L"Can't Set The PixelFormat.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
        return false;                // Вернуть false
    }
    if (!(hRC = wglCreateContext(hDC)))          // Возможно ли установить Контекст Рендеринга?
    {
        KillGLWindow();                // Восстановить экран
        MessageBox(NULL, L"Can't Create A GL Rendering Context.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
        return false;                // Вернуть false
    }
    if (!wglMakeCurrent(hDC, hRC))            // Попробовать активировать Контекст Рендеринга
    {
        KillGLWindow();                // Восстановить экран
        MessageBox(NULL, L"Can't Activate The GL Rendering Context.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
        return false;                // Вернуть false
    }
    ShowWindow(hWnd, SW_SHOW);              // Показать окно
    SetForegroundWindow(hWnd);              // Слегка повысим приоритет
    SetFocus(hWnd);                // Установить фокус клавиатуры на наше окно
    ReSizeGLScene(width, height);              // Настроим перспективу для нашего OpenGL экрана.
    if (!InitGL())                  // Инициализация только что созданного окна
    {
        KillGLWindow();                // Восстановить экран
        MessageBox(NULL, L"Initialization Failed.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
        return false;                // Вернуть false
    }
    return true;                  // Всё в порядке!
}
LRESULT CALLBACK WndProc(HWND  hWnd,            // Дескриптор нужного окна
    UINT  uMsg,            // Сообщение для этого окна
    WPARAM  wParam,            // Дополнительная информация
    LPARAM  lParam)            // Дополнительная информация
{
    Mouse_lParam = lParam;
    switch (uMsg)                // Проверка сообщения для окна
    {
    case WM_ACTIVATE:            // Проверка сообщения активности окна
    {
        if (!HIWORD(wParam))          // Проверить состояние минимизации
        {
            active = true;          // Программа активна
        }
        else
        {
            active = false;          // Программа теперь не активна
        }
        return 0;            // Возвращаемся в цикл обработки сообщений
    }
    case WM_SYSCOMMAND:            // Перехватываем системную команду
    {
        switch (wParam)            // Останавливаем системный вызов
        {
        case SC_SCREENSAVE:        // Пытается ли запустится скринсейвер?
        case SC_MONITORPOWER:        // Пытается ли монитор перейти в режим сбережения энергии?
            return 0;          // Предотвращаем это
        }
        break;              // Выход
    }
    case WM_CLOSE:              // Мы получили сообщение о закрытие?
    {
        PostQuitMessage(0);          // Отправить сообщение о выходе
        return 0;            // Вернуться назад
    }
    case WM_KEYDOWN:            // Была ли нажата кнопка?
    {
        keys[wParam] = true;          // Если так, мы присваиваем этой ячейке true
        return 0;            // Возвращаемся
    }
    case WM_KEYUP:              // Была ли отпущена клавиша?
    {
        keys[wParam] = false;          //  Если так, мы присваиваем этой ячейке false
        return 0;            // Возвращаемся
    }
    case WM_SIZE:              // Изменены размеры OpenGL окна
    {
        ReSizeGLScene(LOWORD(lParam), HIWORD(lParam));  // Младшее слово=Width, старшее слово=Height
        return 0;            // Возвращаемся
    }
    case WM_LBUTTONDOWN:
    {
        parameter.Mouse_click_L();
        return 0;
    }
    case WM_RBUTTONDOWN:
    {
        parameter.Mouse_click_R();
        return 0;
    }
    case WM_MOUSEWHEEL:
        if ((short)HIWORD(wParam) > 0) {
            parameter.Rotation_Wheel(true);
        }
        else {
            parameter.Rotation_Wheel(false);
        }
    }
    // пересылаем все необработанные сообщения DefWindowProc
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
void Window() {
    MSG  msg;              // Структура для хранения сообщения Windows
    BOOL  done = false;            // Логическая переменная для выхода из цикла
    // Создать наше OpenGL окно
    CreateGLWindow(L"Сцена", 1024, 768, 32, fullscreen);
    while (!done)                // Цикл продолжается, пока done не равно true
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))    // Есть ли в очереди какое-нибудь сообщение?
        {
            if (msg.message == WM_QUIT)        // Мы поучили сообщение о выходе?
            {
                start = false;
                explosion = false;
                f = false;
                BEGIN = false;
                BEGIN_TEXTURE = false;
                parameter.destruct();
                data.destruct();
                Texture = -1;
                done = true;          // Если так, done=true
                // ПОЧИСТИТЬ ВСЕ МАССИВЫ, СТРУКТУРЫ И Т.Д.
            }
            else              // Если нет, обрабатывает сообщения
            {
                TranslateMessage(&msg);        // Переводим сообщение
                DispatchMessage(&msg);        // Отсылаем сообщение
            }
        }
        else                // Если нет сообщений
        {
            // Прорисовываем сцену.
            if (active)          // Активна ли программа?
            {
                keyboard();
                DrawGLScene();        // Рисуем сцену
                //SwapBuffers(hDC);    // Меняем буфер (двойная буферизация)
            }
            if (keys[VK_ESCAPE])          // Была ли нажата ESC
            {
                keys[VK_ESCAPE] = false;        // Если так, меняем значение ячейки массива на false
                KillGLWindow();          // Разрушаем текущее окно
                fullscreen = !fullscreen;      // Переключаем режим
                // Пересоздаём наше OpenGL окно
                CreateGLWindow(L"Сцена", 1024, 768, 32, fullscreen);
            }
        }
    }
    // Shutdown
    KillGLWindow();                // Разрушаем окно
}
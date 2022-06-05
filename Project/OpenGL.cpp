#include "pch.h"
#include "Main.h"
// ����������: ��������� �� �������, ��������������� ������� ������ ��� �������
PFNGLFOGCOORDFEXTPROC glFogCoordfEXT = NULL;
// � ������ ����� ������� ���������������������; ������� ��������� ������ 
// ������� � ��������� ����������
PFNGLMULTITEXCOORD2FARBPROC     glMultiTexCoord2fARB = NULL;
PFNGLACTIVETEXTUREARBPROC       glActiveTextureARB = NULL;
// ������ ����� ����� 
BYTE g_HeightMap[MAP_SIZE * MAP_SIZE];
bool g_bRenderMode = true; // ����� ������
float g_FogDepth = 0.0f;    // ������� ������
bool g_bDetail = true;  // ���/���� ��������� ��������
int g_DetailScale = 20; // ������� scale-�������� ��� ���������� �������
HGLRC  hRC = NULL;              // ���������� �������� ����������
HDC  hDC = NULL;              // ��������� �������� ���������� GDI
HWND  hWnd = NULL;              // ����� ����� �������� ���������� ����
HINSTANCE  hInstance;              // ����� ����� �������� ���������� ����������
int camera_width;
int camera_height;
LPARAM Mouse_lParam;
bool BEGIN = false;
bool BEGIN_TEXTURE = false;
bool  keys[600];                // ������, ������������ ��� �������� � �����������
bool  active = true;                // ���� ���������� ����, ������������� � true �� ���������
bool  fullscreen = false;              // ���� ������ ����, ������������� � ������������� �� ���������
GLfloat LightAmbient[] = { 0.9f, 0.9f, 0.9f, 1.0f }; // �������� �������� �����
GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // �������� ���������� �����
GLfloat LightPosition[] = { 0.0f, 1000.0f, 0.0f, 1.0f };     // ������� �����
LRESULT  CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);        // �������� ������� WndProc
GLvoid ReSizeGLScene(GLsizei width, GLsizei height)        // �������� ������ � ���������������� ���� GL
{
    if (height == 0)              // �������������� ������� �� ����
    {
        height = 1;
    }
    camera_height = height;
    camera_width = width;
    glViewport(0, 0, width, height);          // ����� ������� ������� ������
    glMatrixMode(GL_PROJECTION);            // ����� ������� ��������
    glLoadIdentity();              // ����� ������� ��������
    // ���������� ����������� �������������� �������� ��� ����
    gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 10, 10000.0f);
    //gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, .5f, 150.0f);
    glMatrixMode(GL_MODELVIEW);            // ����� ������� ���� ������
    glLoadIdentity();              // ����� ������� ���� ������
}
int InitGL(GLvoid)                // ��� ��������� ������� OpenGL ���������� �����  (+ � ���� ����� ���, ��� ���� ����������������)
{
    LoadGLTextures();			// �������� �������
    LoadRawFile((LPSTR)"Terrain.raw", MAP_SIZE * MAP_SIZE, g_HeightMap);
    // ������������� ������ 
    g_Camera.PositionCamera(-1450.0f, 1950.0f, -264.9f, 521.0f, 521.0f, 521.0f, 0.0f, 1.0f, 0.0f);
    g_Camera.SetCameraRadius(50);
    //????????????????
    glActiveTextureARB = (PFNGLACTIVETEXTUREARBPROC)wglGetProcAddress("glActiveTextureARB");
    glMultiTexCoord2fARB = (PFNGLMULTITEXCOORD2FARBPROC)wglGetProcAddress("glMultiTexCoord2fARB");
    // ����� ��������, ��� ������� ������ OpenGL �� ������ ������������ ���������������������:
    if (!glActiveTextureARB || !glMultiTexCoord2fARB) {
        // ������� ������ � �������
        MessageBox(hWnd, L"�� �������������� ���������������������!", L"ERROR", MB_OK);
        PostQuitMessage(0);
    }
    // ����� ���������, ������������ �� ���������� ���������� �����.
    // �������� ��������� �� ������� ������� ���������� 
    glFogCoordfEXT = (PFNGLFOGCOORDFEXTPROC)wglGetProcAddress("glFogCoordfEXT");
    if (!glFogCoordfEXT) {
        // ������� ������ � �������
        MessageBox(hWnd, L"�� �������������� ��������� �����!", L"ERROR", MB_OK);
        PostQuitMessage(0);
    }
    // ��������� ���� ������ 
    float fogColor[4] = { 0.6f, 0.5f, 0.6f, 1.0f };
    glEnable(GL_FOG);               // ���. �����
    glFogi(GL_FOG_MODE, GL_LINEAR);         // ������������� ����� � GL_LINEAR
    glFogfv(GL_FOG_COLOR, fogColor);        // ������� OpenGL ���� ������
    glFogf(GL_FOG_START, 0.0f);          // ��������� �������� ������� � 0
    glFogf(GL_FOG_END, 50.0f);           // �������� � 50
    // ������ �������� OpenGL, ��� ���������� ���������� ��� ��������� ������ glFogCoordEXT ()
    glFogi(GL_FOG_COORDINATE_SOURCE_EXT, GL_FOG_COORDINATE_EXT);
    glShadeModel(GL_SMOOTH);            // ��������� ������� �������� �����������
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);          // ������� ������ � ������ ����
    glClearDepth(1.0f);              // ��������� ������� ������ �������
    glEnable(GL_DEPTH_TEST);            // ��������� ���� �������
    glDepthFunc(GL_LEQUAL);            // ��� ����� �������
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);      // ��������� � ���������� �����������
    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);    // ��������� �������� �����
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);    // ��������� ���������� �����
    glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);   // ������� �����
    glEnable(GL_LIGHT1); // ���������� ��������� ����� ����� ����
    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    return true;                // ������������� ������ �������
}
GLvoid KillGLWindow(GLvoid)              // ���������� ���������� ����
{
    if (fullscreen)              // �� � ������������� ������?

    {
        ChangeDisplaySettings(NULL, 0);        // ���� ��, �� ������������� ������� � ������� �����
        ShowCursor(true);            // �������� ������ �����
    }
    if (hRC)                // ���������� �� �������� ����������?
    {
        if (!wglMakeCurrent(NULL, NULL))        // �������� �� ���������� RC � DC?
        {
            MessageBox(NULL, L"Release Of DC And RC Failed.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
        }
        if (!wglDeleteContext(hRC))        // �������� �� ������� RC?
        {
            MessageBox(NULL, L"Release Rendering Context Failed.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
        }
        hRC = NULL;              // ���������� RC � NULL
    }
    if (hDC && !ReleaseDC(hWnd, hDC))          // �������� �� ���������� DC?
    {
        MessageBox(NULL, L"Release Device Context Failed.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
        hDC = NULL;                // ���������� DC � NULL
    }
    if (hWnd && !DestroyWindow(hWnd))            // �������� �� ���������� ����?
    {
        MessageBox(NULL, L"Could Not Release hWnd.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
        hWnd = NULL;                // ���������� hWnd � NULL
    }
    if (!UnregisterClass(L"OpenGL", hInstance))        // �������� �� ����������������� �����
    {
        MessageBox(NULL, L"Could Not Unregister Class.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
        hInstance = NULL;                // ���������� hInstance � NULL
    }
}
BOOL CreateGLWindow(LPCWSTR title, int width, int height, int bits, bool fullscreenflag)
{
    GLuint PixelFormat;              // ������ ��������� ����� ������
    WNDCLASS  wc;                // ��������� ������ ����
    DWORD    dwExStyle;              // ����������� ����� ����
    DWORD    dwStyle;              // ������� ����� ����
    RECT WindowRect;                // Grabs Rectangle Upper Left / Lower Right Values
    WindowRect.left = (long)0;              // ���������� ����� ������������ � 0
    WindowRect.right = (long)width;              // ���������� ������ ������������ � Width
    WindowRect.top = (long)0;                // ���������� ������� ������������ � 0
    WindowRect.bottom = (long)height;              // ���������� ������ ������������ � Height
    fullscreen = fullscreenflag;              // ������������� �������� ���������� ���������� fullscreen
    hInstance = GetModuleHandle(NULL);        // ������� ���������� ������ ����������
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;      // ���������� ��� ����������� � ������ ������� DC
    wc.lpfnWndProc = (WNDPROC)WndProc;          // ��������� ��������� ���������
    wc.cbClsExtra = 0;              // ��� �������������� ���������� ��� ����
    wc.cbWndExtra = 0;              // ��� �������������� ���������� ��� ����
    wc.hInstance = hInstance;            // ������������� ����������
    wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);        // ��������� ������ �� ���������
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);        // ��������� ��������� �����
    wc.hbrBackground = NULL;              // ��� �� ��������� ��� GL
    wc.lpszMenuName = NULL;              // ���� � ���� �� �����
    wc.lpszClassName = L"OpenGL";            // ������������� ��� ������
    if (!RegisterClass(&wc))              // �������� ���������������� ����� ����
    {
        MessageBox(NULL, L"Failed To Register The Window Class.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
        return false;                // ����� � ����������� �������� �������� false
    }
    if (fullscreen)                // ������������� �����?
    {
        DEVMODE dmScreenSettings;            // ����� ����������
        memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));    // ������� ��� �������� ���������
        dmScreenSettings.dmSize = sizeof(dmScreenSettings);      // ������ ��������� Devmode
        dmScreenSettings.dmPelsWidth = width;        // ������ ������
        dmScreenSettings.dmPelsHeight = height;        // ������ ������
        dmScreenSettings.dmBitsPerPel = bits;        // ������� �����
        dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;// ����� �������
        // �������� ���������� ��������� ����� � �������� ���������.  ����������: CDS_FULLSCREEN ������� ������ ����������.
        if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
        {
            // ���� ������������ � ������������� ����� ����������, ����� ���������� ��� ��������: ������� ����� ��� �����.
            if (MessageBox(NULL, L"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?",
                L"NeHe GL", MB_YESNO | MB_ICONEXCLAMATION) == IDYES) {
                fullscreen = false;          // ����� �������� ������ (fullscreen = false)
            }
            else
            {
                // ������������� ����, ���������� ������������ � �������� ����.
                MessageBox(NULL, L"Program Will Now Close.", L"ERROR", MB_OK | MB_ICONSTOP);
                return false;            // ����� � ����������� �������� false
            }
        }
    }
    //ShowCursor(false);              // ������ ��������� �����
    if (fullscreen)                  // �� �������� � ������������� ������?
    {
        ShowCursor(false);              // ������ ��������� �����
        dwExStyle = WS_EX_APPWINDOW;          // ����������� ����� ����
        dwStyle = WS_POPUP;            // ������� ����� ����
    }
    else
    {
        dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;      // ����������� ����� ����
        dwStyle = WS_OVERLAPPEDWINDOW;        // ������� ����� ����
    }
    AdjustWindowRectEx(&WindowRect, dwStyle, false, dwExStyle);      // ��������� ���� ���������� �������
    if (!(hWnd = CreateWindowEx(dwExStyle,          // ����������� ����� ��� ����
        L"OpenGL",          // ��� ������
        title,            // ��������� ����
        WS_CLIPSIBLINGS |        // ��������� ����� ��� ����
        WS_CLIPCHILDREN |        // ��������� ����� ��� ����
        dwStyle,          // ���������� ����� ��� ����
        0, 0,            // ������� ����
        WindowRect.right - WindowRect.left,    // ���������� ���������� ������
        WindowRect.bottom - WindowRect.top,    // ���������� ���������� ������
        NULL,            // ��� �������������
        NULL,            // ��� ����
        hInstance,          // ���������� ����������
        NULL)))          // �� ������� ������ �� WM_CREATE (???)
    {
        KillGLWindow();                // ������������ �����
        MessageBox(NULL, L"Window Creation Error.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
        return false;                // ������� false
    }
    static  PIXELFORMATDESCRIPTOR pfd =            // pfd �������� Windows ����� ����� ����� �� ����� ������� �������
    {
      sizeof(PIXELFORMATDESCRIPTOR),            // ������ ����������� ������� ������� ��������
      1,                  // ����� ������
      PFD_DRAW_TO_WINDOW |              // ������ ��� ����
      PFD_SUPPORT_OPENGL |              // ������ ��� OpenGL
      PFD_DOUBLEBUFFER,              // ������ ��� �������� ������
      PFD_TYPE_RGBA,                // ��������� RGBA ������
      (BYTE)bits,                  // ���������� ��� ������� �����
      0, 0, 0, 0, 0, 0,              // ������������� �������� �����
      0,                  // ��� ������ ������������
      0,                  // ��������� ��� ������������
      0,                  // ��� ������ ����������
      0, 0, 0, 0,                // ���� ���������� ������������
      32,                  // 32 ������ Z-����� (����� �������)
      0,                  // ��� ������ ���������
      0,                  // ��� ��������������� �������
      PFD_MAIN_PLANE,                // ������� ���� ���������
      0,                  // ���������������
      0, 0, 0                  // ����� ���� ������������
    };
    if (!(hDC = GetDC(hWnd)))              // ����� �� �� �������� �������� ����������?
    {
        KillGLWindow();                // ������������ �����
        MessageBox(NULL, L"Can't Create A GL Device Context.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
        return false;                // ������� false
    }
    if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))        // ������ �� ���������� ������ �������?
    {
        KillGLWindow();                // ������������ �����
        MessageBox(NULL, L"Can't Find A Suitable PixelFormat.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
        return false;                // ������� false
    }
    if (!SetPixelFormat(hDC, PixelFormat, &pfd))          // �������� �� ���������� ������ �������?
    {
        KillGLWindow();                // ������������ �����
        MessageBox(NULL, L"Can't Set The PixelFormat.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
        return false;                // ������� false
    }
    if (!(hRC = wglCreateContext(hDC)))          // �������� �� ���������� �������� ����������?
    {
        KillGLWindow();                // ������������ �����
        MessageBox(NULL, L"Can't Create A GL Rendering Context.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
        return false;                // ������� false
    }
    if (!wglMakeCurrent(hDC, hRC))            // ����������� ������������ �������� ����������
    {
        KillGLWindow();                // ������������ �����
        MessageBox(NULL, L"Can't Activate The GL Rendering Context.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
        return false;                // ������� false
    }
    ShowWindow(hWnd, SW_SHOW);              // �������� ����
    SetForegroundWindow(hWnd);              // ������ ������� ���������
    SetFocus(hWnd);                // ���������� ����� ���������� �� ���� ����
    ReSizeGLScene(width, height);              // �������� ����������� ��� ������ OpenGL ������.
    if (!InitGL())                  // ������������� ������ ��� ���������� ����
    {
        KillGLWindow();                // ������������ �����
        MessageBox(NULL, L"Initialization Failed.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
        return false;                // ������� false
    }
    return true;                  // �� � �������!
}
LRESULT CALLBACK WndProc(HWND  hWnd,            // ���������� ������� ����
    UINT  uMsg,            // ��������� ��� ����� ����
    WPARAM  wParam,            // �������������� ����������
    LPARAM  lParam)            // �������������� ����������
{
    Mouse_lParam = lParam;
    switch (uMsg)                // �������� ��������� ��� ����
    {
    case WM_ACTIVATE:            // �������� ��������� ���������� ����
    {
        if (!HIWORD(wParam))          // ��������� ��������� �����������
        {
            active = true;          // ��������� �������
        }
        else
        {
            active = false;          // ��������� ������ �� �������
        }
        return 0;            // ������������ � ���� ��������� ���������
    }
    case WM_SYSCOMMAND:            // ������������� ��������� �������
    {
        switch (wParam)            // ������������� ��������� �����
        {
        case SC_SCREENSAVE:        // �������� �� ���������� �����������?
        case SC_MONITORPOWER:        // �������� �� ������� ������� � ����� ���������� �������?
            return 0;          // ������������� ���
        }
        break;              // �����
    }
    case WM_CLOSE:              // �� �������� ��������� � ��������?
    {
        PostQuitMessage(0);          // ��������� ��������� � ������
        return 0;            // ��������� �����
    }
    case WM_KEYDOWN:            // ���� �� ������ ������?
    {
        keys[wParam] = true;          // ���� ���, �� ����������� ���� ������ true
        return 0;            // ������������
    }
    case WM_KEYUP:              // ���� �� �������� �������?
    {
        keys[wParam] = false;          //  ���� ���, �� ����������� ���� ������ false
        return 0;            // ������������
    }
    case WM_SIZE:              // �������� ������� OpenGL ����
    {
        ReSizeGLScene(LOWORD(lParam), HIWORD(lParam));  // ������� �����=Width, ������� �����=Height
        return 0;            // ������������
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
    // ���������� ��� �������������� ��������� DefWindowProc
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
void Window() {
    MSG  msg;              // ��������� ��� �������� ��������� Windows
    BOOL  done = false;            // ���������� ���������� ��� ������ �� �����
    // ������� ���� OpenGL ����
    CreateGLWindow(L"�����", 1024, 768, 32, fullscreen);
    while (!done)                // ���� ������������, ���� done �� ����� true
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))    // ���� �� � ������� �����-������ ���������?
        {
            if (msg.message == WM_QUIT)        // �� ������� ��������� � ������?
            {
                start = false;
                explosion = false;
                f = false;
                BEGIN = false;
                BEGIN_TEXTURE = false;
                parameter.destruct();
                data.destruct();
                Texture = -1;
                done = true;          // ���� ���, done=true
                // ��������� ��� �������, ��������� � �.�.
            }
            else              // ���� ���, ������������ ���������
            {
                TranslateMessage(&msg);        // ��������� ���������
                DispatchMessage(&msg);        // �������� ���������
            }
        }
        else                // ���� ��� ���������
        {
            // ������������� �����.
            if (active)          // ������� �� ���������?
            {
                keyboard();
                DrawGLScene();        // ������ �����
                //SwapBuffers(hDC);    // ������ ����� (������� �����������)
            }
            if (keys[VK_ESCAPE])          // ���� �� ������ ESC
            {
                keys[VK_ESCAPE] = false;        // ���� ���, ������ �������� ������ ������� �� false
                KillGLWindow();          // ��������� ������� ����
                fullscreen = !fullscreen;      // ����������� �����
                // ���������� ���� OpenGL ����
                CreateGLWindow(L"�����", 1024, 768, 32, fullscreen);
            }
        }
    }
    // Shutdown
    KillGLWindow();                // ��������� ����
}
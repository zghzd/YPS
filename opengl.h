#pragma comment(lib, "user32.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "gdi32.lib")
#include <windows.h>
#include <GL/gl.h>
#include <iostream>
#include <tchar.h>

struct GLWin32Context {
    HWND hwnd;
    HDC hdc;
    HGLRC hglrc;
};

LRESULT CALLBACK GLWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    if (message == WM_CLOSE) {
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

bool CreateOpenGLWindow(GLWin32Context& ctx, int width, int height, const char* title) {
    std::cerr << "正在创建窗口" << std::endl;
    WNDCLASSA wc = {};
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = GLWndProc;
    wc.hInstance = GetModuleHandleA(nullptr);
    wc.lpszClassName = "OpenGLWindowClass";
    RegisterClassA(&wc);

    ctx.hwnd = CreateWindowA(
        wc.lpszClassName,
        title,
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, width, height,
        nullptr, nullptr, wc.hInstance, nullptr
    );
    if (!ctx.hwnd) return false;

    ctx.hdc = GetDC(ctx.hwnd);

    PIXELFORMATDESCRIPTOR pfd = {};
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    int pf = ChoosePixelFormat(ctx.hdc, &pfd);
    if (pf == 0) return false;
    if (!SetPixelFormat(ctx.hdc, pf, &pfd)) return false;

    ctx.hglrc = wglCreateContext(ctx.hdc);
    if (!ctx.hglrc) return false;
    wglMakeCurrent(ctx.hdc, ctx.hglrc);

    return true;
}

void DestroyOpenGLWindow(GLWin32Context& ctx) {
    if (ctx.hglrc) {
        wglMakeCurrent(nullptr, nullptr);
        wglDeleteContext(ctx.hglrc);
    }
    if (ctx.hwnd && ctx.hdc) {
        ReleaseDC(ctx.hwnd, ctx.hdc);
        DestroyWindow(ctx.hwnd);
    }
    ctx.hwnd = nullptr;
    ctx.hdc = nullptr;
    ctx.hglrc = nullptr;
}

void RenderOpenGL(GLWin32Context& ctx) {
    RECT rect;
    GetClientRect(ctx.hwnd, &rect);
    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;
    glViewport(0, 0, width, height);

    glClearColor(0.9f, 0.3f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
    glColor3f(1, 0, 0); glVertex2f(-0.5f, -0.5f);
    glColor3f(0, 1, 0); glVertex2f(0.5f, -0.5f);
    glColor3f(0, 0, 1); glVertex2f(0.0f, 0.5f);
    glEnd();

    SwapBuffers(ctx.hdc);
}

void MessageLoop(GLWin32Context& ctx, int frames = 300) {
    MSG msg;
    int count = 0;
    while (count++ < frames) {
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT)
                return;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        RenderOpenGL(ctx);
        Sleep(16);
    }
}

void _opengl(std::string __date) {
    _log(__date + ".log", "D", "0000-0001", "应用程序主线程OpenGL", "OpenGL渲染：60fps\t1300帧");
    std::cerr << "OpenGL渲染：60fps\t1300帧" << std::endl;
    GLWin32Context ctx = {};
    if (!CreateOpenGLWindow(ctx, 640, 480, "Win32 OpenGL")) {
        std::cerr << "无法创建OpenGL窗口" << std::endl;
        return;
    }
    _log(__date + ".log", "D", "0000-0001", "应用程序主线程OpenGL", "渲染");
    std::cerr << "渲染" << std::endl;
    MessageLoop(ctx, 1300);
    _log(__date + ".log", "D", "0000-0001", "应用程序主线程OpenGL", "渲染结束");
    std::cerr << "渲染结束" << std::endl;
    DestroyOpenGLWindow(ctx);
}
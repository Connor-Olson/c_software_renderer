/* Windows API Window Reference: http://www.winprog.org/tutorial/simple_window.html */

#include <windows.h>

#define INITIAL_WINDOW_WIDTH 700
#define INITIAL_WINDOW_HEIGHT 500

/* Name of the window class to-be registered with the system. */
const char g_szClassName[] = "RendererWindowClass";

/* The Window Procedure: Handles incoming messages from the message loop (msg),
 * associated with the handle for the window (hwnd). */
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    /* Switch statement for handling user input.
     * By default, sends the input to the Default Windows Procedure,
     * otherwise, explicitly handles the input (msg) */
    switch (msg)
    {
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

/* Program entrance: registers the window, invokes it's creation, and starts the
 * window procedure and message loop. */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    /* Initialize the WINDCLASSEX Structure (wc / Window Class) */
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 1;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    /* Attempt to register the window class with the system */
    if (!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!",
                   MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    /* Create the window using the registered window class
     * Reference: https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-createwindowexw */
    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_szClassName,
        "Renderer",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        INITIAL_WINDOW_WIDTH,
        INITIAL_WINDOW_HEIGHT,
        NULL, NULL, hInstance, NULL);

    /* Exit if the window handler being created was not initialized properly */
    if (hwnd == NULL)
    {
        MessageBox(
            NULL,
            "Window Creation Failed!",
            "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    /* Show the window on the screen */
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    /* Windows API Window message loop that handles and returns
     * user input associated with the window. */
    while (GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}
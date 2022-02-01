#include <Windows.h>

LRESULT CALLBACK WindowProc(
    HWND   hwnd,
    UINT   uMsg,
    WPARAM wParam,
    LPARAM lParam
) {
    LRESULT Result = 0;
    switch (uMsg)
    {
    case WM_SIZE:
        OutputDebugStringA("WM_SIZE\n");
        break;

    case WM_DESTROY:
        OutputDebugStringA("WM_DESTROY\n");
        break;

    case WM_CLOSE:
        OutputDebugStringA("WM_CLOSE\n");
        break;

    case WM_ACTIVATEAPP:
        OutputDebugStringA("WM_ACTIVATEAPP\n");
        break;

    case WM_PAINT: {
        PAINTSTRUCT Paint;
        HDC DeviceContext = BeginPaint(hwnd, &Paint);
        int X = Paint.rcPaint.left;
        int Y = Paint.rcPaint.top;
        int Height = Paint.rcPaint.bottom - Paint.rcPaint.top;
        int Width = Paint.rcPaint.right - Paint.rcPaint.left;
        PatBlt(DeviceContext, X, Y, Width, Height, WHITENESS);
        EndPaint(hwnd, &Paint);

    }break;

    default:
        Result = DefWindowProc(hwnd, uMsg, wParam, lParam);
        break;
    }
    return Result;
}

// Entry point into windows for applications.
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    PSTR lpCmdLine, INT nCmdShow) {


    WNDCLASS WindowClass = {};
    WindowClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
    WindowClass.lpfnWndProc = WindowProc;
    WindowClass.hInstance = hInstance;
    // WindowClass.hIcon;
    WindowClass.lpszClassName = "HandmadeHeroWindowClass";

    if (RegisterClass(&WindowClass)) {
        HWND WindowHandle = CreateWindowEx(
            0,
            WindowClass.lpszClassName,
            "Handmade Hero",
            WS_OVERLAPPEDWINDOW | WS_VISIBLE,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            0,
            0,
            hInstance,
            0
        );
        if (WindowHandle) {
            for (;;) {
                MSG Message;
                BOOL MessageResult = GetMessage(&Message, 0, 0, 0);
                if (MessageResult > 0) {
                    TranslateMessage(&Message);
                    DispatchMessage(&Message);
                }
                else {
                    break;
                }
            }
        }
        else {
            // Error Handaling
        }
    }
    else {
        // Error Handaling
    }

    return 0;
}
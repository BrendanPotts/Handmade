#include <Windows.h>
#define local_function static 
#define local_persist static 
#define global_var static 


global_var bool Running;

local_function void win32ResizeDIBSection(int Width, int Height) {

}
local_function void win32UpdateWindow(HWND hwnd, int X, int Y, int Width, int Height) {

}


LRESULT CALLBACK win32WindowCallback(
    HWND   hwnd,
    UINT   uMsg,
    WPARAM wParam,
    LPARAM lParam
) {
    LRESULT Result = 0;
    switch (uMsg)
    {

    case WM_SIZE: {
        RECT ClientRect;
        GetClientRect(hwnd, &ClientRect);
        int Height = ClientRect.bottom - ClientRect.top;
        int Width = ClientRect.right - ClientRect.left;
        win32ResizeDIBSection(Width, Height);

    }break;

    case WM_CLOSE:
        Running = false;
        break;


    case WM_ACTIVATEAPP:
        OutputDebugStringA("WM_ACTIVATEAPP\n");
        break;

    case WM_DESTROY:
        Running = false;
        break;

    case WM_PAINT: {
        PAINTSTRUCT Paint;
        HDC DeviceContext = BeginPaint(hwnd, &Paint);
        int X = Paint.rcPaint.left;
        int Y = Paint.rcPaint.top;
        int Height = Paint.rcPaint.bottom - Paint.rcPaint.top;
        int Width = Paint.rcPaint.right - Paint.rcPaint.left;
        local_persist DWORD Operation = WHITENESS;
        win32UpdateWindow(hwnd, X, Y, Width, Height);
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
    WindowClass.lpfnWndProc = win32WindowCallback;
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
            Running = true;
            while (Running)
            {
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
    }
    else {
        // Error Handaling
    }

    return 0;
}
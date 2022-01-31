#include <Windows.h>

// Entry point into windows for applications.
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    PSTR lpCmdLine, INT nCmdShow)
{
    MessageBoxA(NULL, "Hello World!!", "Handmade", MB_OK | MB_ICONINFORMATION);
    return 0;
}
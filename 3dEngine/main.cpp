#include <iostream>
#include <windows.h>
#include <thread>
#include <chrono>

#include "headers/graphing_algorithms.h"
#include "headers/graphing_structs.h"

const int width = 512;
const int height = 512;

HDC contextHandle;

long moving = 0;

COLORREF color = RGB(0xff, 0x0, 0x0);

long long count = 0;

bool bIncrease = true;
void paintWindow(HWND &windowHandle)
{
    RECT rect;
    if (GetWindowRect(windowHandle, &rect))
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
//        std::cout << ++count << std::endl;
        if (bIncrease)
        {
            if (moving >= (100))
            {bIncrease = false;}
            else{moving++;}
        }
        else
        {
            if (moving <= 0){bIncrease = true;}
            else{moving--;}
        }

        COLORREF buffer[height*width]={0};

        POINT midPoint{width / 2, height / 2};

        graphing_structs::Vec2d a(-2 * 38, 2 * 38, midPoint);
        graphing_structs::Vec2d b(2 * 38, 2 * 38, midPoint);
        graphing_structs::Vec2d c(-2 * 38, -2 * 38, midPoint);
        graphing_structs::Vec2d d(2 * 38, -2 * 38, midPoint);

        graphing_algorithms::bresenhamLine(a, b, buffer, height, width, color);
        graphing_algorithms::bresenhamLine(b, c, buffer, height, width, color);
        graphing_algorithms::bresenhamLine(c, a, buffer, height, width, color);

        graphing_algorithms::bresenhamLine(d, b, buffer, height, width, color);
        graphing_algorithms::bresenhamLine(b, c, buffer, height, width, color);
        graphing_algorithms::bresenhamLine(c, d, buffer, height, width, color);

        graphing_algorithms::paintBorder(buffer, RGB(0xff,0xff,0xff), height, width);

        HBITMAP map = CreateBitmap(
                width,
                height,
                1,
                8*4,
                buffer
        );

        HDC src = CreateCompatibleDC(contextHandle); // TMP context handle
        SelectObject(src, map);
        BitBlt(contextHandle,
               10,
               10,
               512,
               512,
               src,
               0,
               0,
               SRCCOPY);

        DeleteObject(map);
        DeleteDC(src);
    }
}

LRESULT CALLBACK windowProcess(HWND windowHandle, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_CLOSE: // X
            DestroyWindow(windowHandle); return 0;
        case WM_DESTROY:
            PostQuitMessage(0); return 0;
        case WM_PAINT:
            paintWindow(windowHandle); return 0;
        default:
            return DefWindowProc(windowHandle, msg, wParam, lParam);
    }
}

int main() {
    // Registering the window class.
    WNDCLASSA windowInfoStruct =
            {
                    0, windowProcess, 0, 0, nullptr,
                    LoadIcon(nullptr, IDI_APPLICATION),
                    LoadCursor(nullptr, IDC_ARROW),
                    reinterpret_cast<HBRUSH>(GetStockObject(BLACK_BRUSH)),
                    nullptr, // No menu
                "ExampleWindowClass"
            };

    ATOM windowClass = RegisterClassA(&windowInfoStruct);
    if (!windowClass)
    {
        std::cout << "Could not create window class";
        exit(1);
    }

    // Creating the window.
    HWND windowHandle = CreateWindowA(
            MAKEINTATOM(windowClass),
            "3DEngine",             // Window title.
            WS_OVERLAPPEDWINDOW,    // Adds title bar and thick borders.
            CW_USEDEFAULT, CW_USEDEFAULT, 640, 480,
            nullptr,
            nullptr,
            GetModuleHandle(nullptr),
            nullptr
    );
    if (!windowHandle)
    {
        std::cout << GetLastError() << std::endl;
        std::cout << "Failed to create window.";
        exit(1);
    }

    // Make window visible.
    ShowWindow(windowHandle, SW_SHOWMAXIMIZED);

    contextHandle = GetDC(windowHandle);
    // Event loop.
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam; // IDK
}

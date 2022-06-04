#include <iostream>
#include <windows.h>
#include <cmath>
#include <thread>
#include <chrono>

const int BACKGROUND_COLOR = BLACK_BRUSH;

double incrementOrDecrement(double num)
{
    if (num < 0)
    {
        return --num;
    }
    else if (num > 0)
    {
        return ++num;
    }
}

void drawLineBetweenPoints(HDC &deviceContextHandle, COLORREF &color, POINT* origin, POINT* endPoint)
{
    for (int p = 0; p < 2; p++)
    {
        double deltaX = endPoint->x - origin->x;
        double deltaY = endPoint->y - origin->y;
        double slope;
        if (deltaX != 0)
        {
           slope = deltaY/deltaX;
        }
        else
        {
            slope = origin->y;
        }
        if (deltaX > 0)
        {
            double originalSlope = slope;
            double yToMove = 0.00f;
            double xToMove = 0.00f;

            double xMoved;
            double yMoved;

            bool keepGoing = true;
            while(keepGoing)
            {
                if (abs(slope) > 1) // If more y per x.
                {
                    if (round(yToMove) == 0) // If rounded yToMove == 0,
                    {
                        yToMove+=round(slope); // Give another order.
                    }
                    else // If there are pending move orders for y.
                    {
                        if (slope < 0) // If orders are for decrement.
                        {
                            xMoved--;
                            yToMove++;
                        }
                        else // If orders are for increment.
                        {
                            xMoved++;
                            yToMove--;
                        }
                    }
                }
                if (abs(slope) < 1) // If more x per y.
                {
                    if (round(xToMove) == 0)
                    {
                        if (slope < 0) // If orders are for decrement.
                        {
                            xMoved--;
                            yToMove++;
                        }
                        else // If orders are for increment.
                        {
                            xMoved++;
                            yToMove--;
                        }
                        xToMove+=round(1/slope);
                    }
                    else
                    {
                        if (slope < )
                    }
                }
                SetPixel(deviceContextHandle, (int)round(origin->x + xMoved), (int)round(origin->y + yMoved), color);

//                if (abs((int)round(slope*i)) > 1)
//                {
//                    yPerX = abs((int)round(slope*i));
//                    std::cout << "oo";
//                }
//                if (round(originalSlope) != 0)
//                {
//                    if ()
//                    SetPixel(deviceContextHandle, origin->x+totalIncrementInX, (int)round(slope*i), color);
//                    totalIncrementInX+=
//                }
//                else {
//                    SetPixel(deviceContextHandle, i, (int)round(origin->y+totalIncrementInY), color);
//                    totalIncrementInY+=slope;
//                }
////                if (i%2==0)
////                {
////                    std::this_thread::sleep_for(std::chrono::milliseconds(1));
////                }
            }
            break;
        }
        else if (deltaX < 0)
        {
            POINT* tmp = origin;
            origin = endPoint;
            endPoint = tmp;
        }
        else
        {
            break;
        }
    }
}

void paintWindow(HWND windowHandle)
{
    RECT rect;
    if (GetWindowRect(windowHandle, &rect))
    {
        COLORREF colors[] = {
                RGB(0xFF, 0, 0),
                RGB(0, 0xFF, 0),
                RGB(0, 0, 0xFF)
        };
        PAINTSTRUCT paintStruct;
        HDC deviceContextHandle = BeginPaint(windowHandle, &paintStruct);
        int moveItBy = 100;
        POINT origin{10+moveItBy,10+moveItBy};
        POINT dest{100+moveItBy,200+moveItBy};
        POINT dest2{1000+moveItBy, 50+moveItBy};

        SetPixel(deviceContextHandle, origin.x, origin.y, colors[1]);
        SetPixel(deviceContextHandle, dest.x, dest.y, colors[2]);
        SetPixel(deviceContextHandle, dest2.x, dest2.y, colors[0]);

        drawLineBetweenPoints(deviceContextHandle, colors[0], &origin, &dest);
        drawLineBetweenPoints(deviceContextHandle, colors[1], &dest, &dest2);
        drawLineBetweenPoints(deviceContextHandle, colors[2], &dest2, &origin);
    }
}

LRESULT CALLBACK windowProcess(HWND windowHandle, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_KEYDOWN: // X button.
        case WM_CLOSE:
            DestroyWindow(windowHandle); std::cout << "CLOSE"; return 0;
        case WM_DESTROY:
            PostQuitMessage(0); std::cout << "DESTROY"; return 0;
        case WM_PAINT:
            paintWindow(windowHandle); std::cout << "PAINT"; return 0;
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
                static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH)),
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
    HWND windowHandler = CreateWindowA(
            MAKEINTATOM(windowClass),
            "3DEngine",             // Window title.
            WS_OVERLAPPEDWINDOW,    // Adds title bar and thick borders.
            CW_USEDEFAULT, CW_USEDEFAULT, 640, 480,
            nullptr,
            nullptr,
            GetModuleHandle(nullptr),
            nullptr
    );
    if (!windowHandler)
    {
        std::cout << GetLastError() << std::endl;
        std::cout << "Failed to create window.";
        exit(1);
    }

    // Make window visible.
    ShowWindow(windowHandler, SW_SHOWMAXIMIZED);

    // Event loop.
    MSG msg;
    while (GetMessage(&msg, 0, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

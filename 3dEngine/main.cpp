#include <iostream>
#include <windows.h>
#include <cmath>
#include <thread>
#include <chrono>
#include <vector>
#include "headers/grapher.h"

int BACKGROUND_COLOR = BLACK_BRUSH;

int moveItBy = 100;

POINT one{moveItBy+0,moveItBy+0};
POINT two{moveItBy+100,moveItBy+200};
POINT three{moveItBy+200,moveItBy+100};

const int width = 512;
const int height = 512;

HDC contextHandle;

long moving = 0;

COLORREF colors[] = {
        RGB(0xFF, 0, 0),
        RGB(0, 0xFF, 0),
        RGB(0, 0, 0xFF)
};

std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
std::chrono::system_clock::time_point lastFrame = std::chrono::system_clock::now();

COLORREF color = RGB(0xff, 0x0, 0x0);

// Bresenham line algorithm.
void bresenhamLine(POINT p1, POINT p2, COLORREF* buf)
{
    int x,y,dx,dy,dx1,dy1,px,py,xe,ye,i;
    dx=p2.x-p1.x;dy=p2.y-p1.y;
    dx1=abs(dx);dy1=abs(dy);
    px=2*dy1-dx1;py=2*dx1-dy1;
    if(dy1<=dx1)
    {
        if(dx>=0){x=p1.x;y=p1.y;xe=p2.x;}
        else{x=p2.x;y=p2.y;xe=p1.x;}
        buf[y*height+x]=color;
        for(i=0;x<xe;i++)
        {
            color++;
            x=x+1;
            if(px<0){px=px+2*dy1;}
            else
            {
                if((dx<0&&dy<0)||(dx>0&&dy>0)){y=y+1;}
                else{y=y-1;}
                px=px+2*(dy1-dx1);
            }
            buf[y*height+x]=color;
        }
    }
    else
    {
        if(dy>=0){x=p1.x;y=p1.y;ye=p2.y;}
        else{x=p2.x;y=p2.y;ye=p1.y;}
        buf[y*height+x]=color;
        for(i=0;y<ye;i++)
        {
            color++;
            y=y+1;
            if(py<=0){py=py+2*dx1;}
            else
            {
                if((dx<0&&dy<0)||(dx>0&&dy>0)){x=x+1;}
                else{x=x-1;}
                py=py+2*(dx1-dy1);
            }
            buf[y*height+x]=color;
        }
    }
}

struct vec2d
{
    float x,y;
    vec2d(float x, float y) : x(x), y(y) {}
    POINT getAsPoint() const
    {
        return POINT{(long)x, (long)y};
    }
};

struct vec3d
{
    float x,y,z;
    vec3d(float _x, float _y, float _z, float midHeight, float midWidth) : z(_z) {
        x = _x+midWidth;
        y = _y+midHeight;
    }
    [[nodiscard]] POINT getAs2d() const
    {
        return POINT{(long)x,(long)y};
    }
};

bool bIncrease = true;
void paintWindow(HWND &windowHandle)
{
    RECT rect;
    if (GetWindowRect(windowHandle, &rect))
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
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

//        COLORREF buf[height][width] = {{0}};

//        auto* buffer = new COLORREF[height*width];

        COLORREF buffer[height*width]={0};

//        auto** buf = new COLORREF*[height];
//        for (int i = 0; i < height; i++)
//        {
//            buf[i] = new COLORREF[width];
//        }
//        Grapher grapher = Grapher(color, width, height);

        // Cube

//        std::cout << buffer[131072];

        vec2d midPoint{(float)width/2, (float)height/2};

        vec3d a{150,100,50, midPoint.y, midPoint.x};
        vec3d b{-150,100,50, midPoint.y, midPoint.x};
        vec3d c{150,-100,50, midPoint.y, midPoint.x};
        vec3d d{-150,-100,50, midPoint.y, midPoint.x};

        vec3d e{200,75,-100, midPoint.y, midPoint.x};
        vec3d f{-75,75,-100, midPoint.y, midPoint.x};
        vec3d g{200,-120,-100, midPoint.y, midPoint.x};
        vec3d h{-75,-120,-100, midPoint.y, midPoint.x};

        // AB, CD, EF, GH, AC, BD, EG, FH, AE, CG, BF, DH
        bresenhamLine(a.getAs2d(), b.getAs2d(), buffer);
        bresenhamLine(c.getAs2d(), d.getAs2d(), buffer);
        bresenhamLine(e.getAs2d(), f.getAs2d(), buffer);
        bresenhamLine(g.getAs2d(), h.getAs2d(), buffer);
        bresenhamLine(a.getAs2d(), c.getAs2d(), buffer);
        bresenhamLine(b.getAs2d(), d.getAs2d(), buffer);
        bresenhamLine(e.getAs2d(), g.getAs2d(), buffer);
        bresenhamLine(f.getAs2d(), h.getAs2d(), buffer);
        bresenhamLine(a.getAs2d(), e.getAs2d(), buffer);
        bresenhamLine(c.getAs2d(), g.getAs2d(), buffer);
        bresenhamLine(b.getAs2d(), f.getAs2d(), buffer);
        bresenhamLine(d.getAs2d(), h.getAs2d(), buffer);

        for (int i = 0; i < width; i++)
        {
            buffer[(width-1)*height+i] = RGB(0,0,0xFF);
            buffer[i] = RGB(0,0,0xFF);
        }

        for (int i = 0; i < height; i++)
        {
            buffer[i*width] = RGB(0,0,0xFF);
            buffer[i*width-1] = RGB(0,0,0xFF);
        }

        vec2d topLeft{0,0};
        vec2d topRight{width-1,0};
        vec2d bottomLeft{0, height-1};
        vec2d bottomRight{width-1, height-1};

//        bresenhamLine(topLeft.getAsPoint(), d.getAs2d(), buffer); // D
//        bresenhamLine(a.getAs2d(), bottomRight.getAsPoint(), buffer);
//        bresenhamLine(topRight.getAsPoint(), c.getAs2d(), buffer);
//        bresenhamLine(bottomLeft.getAsPoint(), b.getAs2d(), buffer);


//        POINT p1 = {100+moving,100+moving};
//        POINT p2 = {200-moving,200-moving};
//        POINT p3 = {300+moving,50+moving};

//        grapher.drawLineBetweenPoints(p1, p2, contextHandle);
//        bresenhamLine(p1, p2, buffer);
//        bresenhamLine(p2, p3, buffer);
//        bresenhamLine(p1, p3, buffer);

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

//        SetPixel(contextHandle, topLeft.x, topLeft.y, RGB(0x0,0x0,0xFF));
//        SetPixel(contextHandle, topRight.x, topRight.y, RGB(0x0,0x0,0xFF));
//        SetPixel(contextHandle, bottomLeft.x, bottomLeft.y, RGB(0x0,0x0,0xFF));
//        SetPixel(contextHandle, bottomRight.x, bottomRight.y, RGB(0x0,0x0,0xFF));

//        for (int i = 0; i < height; i++)
//        {
//            delete [] buf[i];
//        }
//        delete [] buf;
    }
}

LRESULT CALLBACK windowProcess(HWND windowHandle, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
//        case WM_KEYDOWN: // X button.
        case WM_CLOSE:
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

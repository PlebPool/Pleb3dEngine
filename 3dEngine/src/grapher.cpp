//
// Created by mattias.wegblad on 2022-06-05.
//

#include "../headers/grapher.h"
#include "../headers/graph_algorithms.h"


Grapher::Grapher(COLORREF color, int width, int height) : _color(color), _height(height), _width(width)
{
//    _buf = new COLORREF*[_height]{nullptr};
//    for (int i = 0; i < _height; i++)
//    {
//        _buf[i] = new COLORREF[width]{0};
//    }
}

void Grapher::flush(HDC &deviceContext)
{
    for (int i = 0; i < _width; i++)
    {
        _buf[i][0] = RGB(0,0,0xFF);
        _buf[i][_width-1] = RGB(0,0,0xFF);
    }

    for (int i = 0; i < _height; i++)
    {
        _buf[0][i] = RGB(0,0,0xFF);
        _buf[_height-1][i] = RGB(0,0,0xFF);
    }

    HBITMAP map = CreateBitmap(
            _width,
            _height,
            1,
            8*4,
            _buf
    );

    HDC src = CreateCompatibleDC(deviceContext); // TMP context handle
    SelectObject(src, map);
    BitBlt(deviceContext,
           0,
           0,
           _width,
           _height,
           src,
           0,
           0,
           SRCCOPY);

    DeleteObject(map);
    DeleteDC(src);
}

void Grapher::drawLineBetweenPoints(POINT &p1, POINT &p2, HDC &deviceContext)
{
    graph_algorithms::bresenhamLine(p1, p2, _buf, _color);
    flush(deviceContext);
}

Grapher::~Grapher() {
    for (int i = 0; i < _height; i++){delete [] _buf[i];}
    delete [] _buf;
}

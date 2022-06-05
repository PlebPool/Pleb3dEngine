//
// Created by mattias.wegblad on 2022-06-05.
//

#ifndef INC_3DENGINE_GRAPHER_H
#define INC_3DENGINE_GRAPHER_H
#include <windows.h>

class Grapher {
private:
    COLORREF _color;
    COLORREF _buf[512][512]={{0}};
    int _width;
    int _height;
public:
    Grapher(COLORREF color, int width, int height);
    void drawLineBetweenPoints(POINT &p1, POINT &p2, HDC &deviceContext);

    virtual ~Grapher();

private:
    void flush(HDC &deviceContext);
};


#endif //INC_3DENGINE_GRAPHER_H

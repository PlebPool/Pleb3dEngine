//
// Created by mattias.wegblad on 2022-06-05.
//

#ifndef INC_3DENGINE_GRAPHER_H
#define INC_3DENGINE_GRAPHER_H
#include <windows.h>

class Grapher {
private:
    COLORREF color;
    COLORREF** buf;
public:
    Grapher(COLORREF color, COLORREF **buf);
    void drawLineBetweenPoints(POINT &p1, POINT &p2, HDC deviceContext);
};


#endif //INC_3DENGINE_GRAPHER_H

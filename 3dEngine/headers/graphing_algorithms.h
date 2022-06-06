//
// Created by matti on 2022-06-06.
//

#ifndef INC_3DENGINE_GRAPHING_ALGORITHMS_H
#define INC_3DENGINE_GRAPHING_ALGORITHMS_H
#include "graphing_structs.h"
#include <windows.h>

namespace graphing_algorithms
{
    void bresenhamLine(graphing_structs::Vec2d &p1, graphing_structs::Vec2d &p2, COLORREF* buf, int height, int width, COLORREF &color);
    void paintBorder(COLORREF* buf, COLORREF color, int height, int width);
    void visualizeTriangle(graphing_structs::Triangle triangleData, COLORREF* buf, int height, int width, COLORREF &color);
};

#endif //INC_3DENGINE_GRAPHING_ALGORITHMS_H

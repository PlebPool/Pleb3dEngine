//
// Created by mattias.wegblad on 2022-06-05.
//

#include "../headers/grapher.h"
#include "../headers/graph_algorithms.h"

Grapher::Grapher(COLORREF color, COLORREF **buf) : color(color), buf(buf) {}

void flush()
{

}

void Grapher::drawLineBetweenPoints(POINT &p1, POINT &p2, HDC deviceContext)
{
    graph_algorithms::bresenhamLine(p1, p2, buf, color);

}

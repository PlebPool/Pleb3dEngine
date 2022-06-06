//
// Created by matti on 2022-06-06.
//

#ifndef INC_3DENGINE_GRAPHING_STRUCTS_H
#define INC_3DENGINE_GRAPHING_STRUCTS_H
#include <windows.h>
#include <vector>

namespace graphing_structs
{
    struct Vec2d
    {
        float x,y;
        Vec2d(float _x, float _y, POINT &midPoint);
    };
    struct Vec3d
    {
        float x,y,z;
        Vec3d(float _x, float _y, float _z, POINT &midPoint);
        [[nodiscard]] Vec2d getAsPoint(POINT &midPoint) const;
    };
    struct Triangle
    {
        Vec3d vectors[3];
    };
    struct PolygonMesh
    {
        std::vector<Triangle> trianglePolygons;
    };
};


#endif //INC_3DENGINE_GRAPHING_STRUCTS_H

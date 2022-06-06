//
// Created by matti on 2022-06-06.
//

#include "../headers/graphing_structs.h"

graphing_structs::Vec2d::Vec2d(float _x, float _y, POINT &midPoint)
{
    x = _x+(float)midPoint.x;
    y = _y+(float)midPoint.y;
}

graphing_structs::Vec3d::Vec3d(float _x, float _y, float _z, POINT &midPoint) : z(_z)
{
    x = _x+(float)midPoint.x;
    y = _y+(float)midPoint.y;
}

[[nodiscard]] graphing_structs::Vec2d graphing_structs::Vec3d::getAsPoint(POINT &midPoint) const
{
    return {x,y, midPoint};
}
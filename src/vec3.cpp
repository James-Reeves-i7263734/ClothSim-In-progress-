#include "vec3.h"

Vec3 operator*(float _scaleFactor, const Vec3 & _rhs)
{
    return _rhs * _scaleFactor;
}

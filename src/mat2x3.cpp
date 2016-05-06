#include "mat2x3.h"
#include "vec3.h"

#include <cstring>

Mat2x3::Mat2x3(float a0, float a1, float a2, float a3, float a4, float a5)
{
    entries[0] = a0;
    entries[1] = a1;
    entries[2] = a2;
    entries[3] = a3;
    entries[4] = a4;
    entries[5] = a5;
}

Mat2x3::Mat2x3(const Mat2x3 &_value)
{
    memcpy(entries, _value.entries, 6*sizeof(float));
}

Mat2x3::Mat2x3(const float *_value)
{
    memcpy(entries, _value,6*sizeof(float));
}

void Mat2x3::SetEntry(int _position, float _value)
{
    if(_position >= 0 && _position <= 5)
    {
        entries[_position] = _value;
    }
}

float Mat2x3::GetEntry(int _position) const
{
    if(_position >= 0 && _position <= 5)
    {
        return entries[_position];
    }
    return 0.0f;
}

Mat2x3 Mat2x3::operator+(const Mat2x3 & _value) const
{
    return Mat2x3(entries[0] + _value.entries[0],
            entries[1] + _value.entries[1],
            entries[2] + _value.entries[2],
            entries[3] + _value.entries[3],
            entries[4] + _value.entries[4],
            entries[5] + _value.entries[5]);

}

Mat2x3 Mat2x3::operator -(const Mat2x3 & _value) const
{
    return Mat2x3(entries[0] - _value.entries[0],
            entries[1] - _value.entries[1],
            entries[2] - _value.entries[2],
            entries[3] - _value.entries[3],
            entries[4] - _value.entries[4],
            entries[5] - _value.entries[5]);

}

Mat2x3 Mat2x3::operator*(const float _value) const
{
    return Mat2x3(entries[0] * _value,
            entries[1] * _value,
            entries[2] * _value,
            entries[3] * _value,
            entries[4] * _value,
            entries[5] * _value);
}

Mat2x3 Mat2x3::operator/(const float _value) const
{
    if (_value == 0.0f || _value == 1.0f)
    {
        return (*this);
    }

    float temp = 1 / _value;

    return (*this) * temp;
}

void Mat2x3::operator+=(const Mat2x3 & _value)
{
    (*this) = (*this) + _value;
}


Vec3 Mat2x3::operator*(const Vec3 _value) const
{
    return Vec3(entries[0] * _value.x + entries[2] * _value.y + entries[4] * _value.z,
            entries[1] * _value.x + entries[3] * _value.y + entries[5] * _value.z,
            0.0f);
}

void Mat2x3::Transpose(void)
{
    *this = GetTranspose();
}

Mat2x3 Mat2x3::GetTranspose(void) const
{
    return Mat2x3(entries[0], entries[3],
                  entries[1], entries[4],
                  entries[2], entries[5]);
}

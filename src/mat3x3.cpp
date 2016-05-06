#include "mat3x3.h"
#include "vec3.h"

#include <cstring>

Mat3x3::Mat3x3(float a0, float a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8)
{
    entries[0] = a0;
    entries[1] = a1;
    entries[2] = a2;
    entries[3] = a3;
    entries[4] = a4;
    entries[5] = a5;
    entries[6] = a6;
    entries[7] = a7;
    entries[8] = a8;
}

Mat3x3::Mat3x3(const Mat3x3 &_value)
{
    memcpy(entries, _value.entries, 9*sizeof(float));
}

Mat3x3::Mat3x3(const float *_value)
{
    memcpy(entries, _value, 9*sizeof(float));
}

void Mat3x3::SetEntry(int _position, float _value)
{
    if(_position >= 0 && _position <= 8)
    {
        entries[_position] = _value;
    }
}

float Mat3x3::GetEntry(int _position) const
{
    if(_position >= 0 && _position <= 8)
    {
        return entries[_position];
    }
    return 0.0f;
}

Mat3x3 Mat3x3::operator+(const Mat3x3 & _value) const
{
    return Mat3x3(entries[0] + _value.entries[0],
            entries[1] + _value.entries[1],
            entries[2] + _value.entries[2],
            entries[3] + _value.entries[3],
            entries[4] + _value.entries[4],
            entries[5] + _value.entries[5],
            entries[6] + _value.entries[6],
            entries[7] + _value.entries[7],
            entries[8] + _value.entries[8]);

}

Mat3x3 Mat3x3::operator -(const Mat3x3 & _value) const
{
    return Mat3x3(entries[0] - _value.entries[0],
            entries[1] - _value.entries[1],
            entries[2] - _value.entries[2],
            entries[3] - _value.entries[3],
            entries[4] - _value.entries[4],
            entries[5] - _value.entries[5],
            entries[6] - _value.entries[6],
            entries[7] - _value.entries[7],
            entries[8] - _value.entries[8]);

}

Mat3x3 Mat3x3::operator*(const float _value) const
{
    return Mat3x3(entries[0] * _value,
            entries[1] * _value,
            entries[2] * _value,
            entries[3] * _value,
            entries[4] * _value,
            entries[5] * _value,
            entries[6] * _value,
            entries[7] * _value,
            entries[8] * _value);
}

Mat3x3 Mat3x3::operator/(const float _value) const
{
    if (_value == 0.0f || _value == 1.0f)
    {
        return (*this);
    }

    float temp = 1 / _value;

    return (*this) * temp;
}

void Mat3x3::operator+=(const Mat3x3 & _value)
{
    (*this) = (*this) + _value;
}


Vec3 Mat3x3::operator*(const Vec3 _value) const
{
    return Vec3(entries[0] * _value.x + entries[3] * _value.y + entries[6] * _value.z,
            entries[1] * _value.x + entries[4] * _value.y + entries[7] * _value.z,
            entries[2] * _value.x + entries[5] * _value.y + entries[8] * _value.z);
}

Mat3x3& Mat3x3::operator =(const Mat3x3& _value)
{
    entries[0] = _value.entries[0];
    entries[1] = _value.entries[1];
    entries[2] = _value.entries[2];
    entries[3] = _value.entries[3];
    entries[4] = _value.entries[4];
    entries[5] = _value.entries[5];
    entries[6] = _value.entries[6];
    entries[7] = _value.entries[7];
    entries[8] = _value.entries[8];

    return *this;

}

void Mat3x3::Invert(void)
{
    *this = GetInverse();
}

Mat3x3 Mat3x3::GetInverse(void) const
{

}





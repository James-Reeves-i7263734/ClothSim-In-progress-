#ifndef VEC3
#define VEC3

//--------------------------------------------
// A simple Vec3 class
// Handmade because ngl stopped working
// on home computer
//--------------------------------------------

#include <iostream>
#include <math.h>
#include <complex>
#include <GL/gl.h>
#include <glm/mat3x3.hpp>

typedef GLfloat PRECISION;
typedef PRECISION Real;

class Vec3
{

public:

    float x, y, z;

public:

    Vec3() { x = y = z = 0; }

    Vec3(const float * rhs) : x(*rhs), y(*rhs+1), z(*(rhs+2)) {}

    Vec3(float _xValue, float _yValue, float _zValue)
    {

        x = _xValue;
        y = _yValue;
        z = _zValue;

    }

    void set(const float &_xValue, const float &_yValue, const float &_zValue)
    {

        x = _xValue;
        y = _yValue;
        z = _zValue;

    }

    float getX() const { return x; }
    float getY() const { return y; }
    float getZ() const { return z; }

    void setX(const float &_xValue) { z = _xValue; }
    void setY(const float &_yValue) { z = _yValue; }
    void setZ(const float &_zValue) { z = _zValue; }

    void zero()
    {

        x = y = z = 0;

    }

    void normalise()
    {

        float magnitude = sqrt((x * x) + (y * y) + (z * z));

        if(magnitude != 0)
        {
            x /= magnitude;
            y /= magnitude;
            z /= magnitude;
            //return Vec3(x / magnitude, y / magnitude, y / magnitude);
        }

    }

    static float dot(const Vec3 &_vec1, const Vec3 &_vec2)
    {

        return _vec1.x * _vec2.x + _vec1.y * _vec2.y + _vec1.z * _vec2.z;

    }

    float dot(const Vec3 &_vec) const
    {

        return x * _vec.x + y * _vec.y + z * _vec.z;

    }

    static Vec3 cross(const Vec3 &_vec1, const Vec3 &_vec2)
    {

        return Vec3(_vec1.y * _vec2.z - _vec1.z * _vec2.y, _vec1.z * _vec2.x - _vec1.x * _vec2.z, _vec1.x * _vec2.y - _vec1.y * _vec2.x);

    }

    void addX(float _value) { x += _value; }
    void addY(float _value) { y += _value; }
    void addZ(float _value) { z += _value; }

    static float length(const Vec3 &_vec1, const Vec3 &_vec2)
    {
        float dx = _vec2.x - _vec1.x;
        float dy = _vec2.y - _vec1.y;
        float dz = _vec2.z - _vec1.z;

        return sqrt((dx * dx) + (dy * dy) + (dz * dz));
    }

    void Display()
    {
        std::cout << "X: " << x << "\t Y: " << y << "\t Z: " << z << std::endl;
    }

    Vec3 operator+(const Vec3 &_vector) const
    {
        return Vec3(x + _vector.x, y + _vector.y, z + _vector.z);
    }

    void operator+=(const Vec3 &_vector)
    {
        x += _vector.x;
        y += _vector.y;
        z += _vector.z;
    }

    void operator-=(const Vec3 &_vector)
    {
        x -= _vector.x;
        y -= _vector.y;
        z -= _vector.z;
    }

    void operator/=(const Vec3 &_vector)
    {
        x /= _vector.x;
        y /= _vector.y;
        z /= _vector.z;
    }

    Vec3 operator-(const Vec3 &_vector) const
    {
        return Vec3(x - _vector.x, y - _vector.y, z - _vector.z);
    }

    Vec3 operator-(const float _value) const
    {
        return Vec3(x - _value, y - _value, z - _value);
    }

    Vec3 operator*(const Vec3 &_vector) const
    {
        return Vec3(x * _vector.x, y * _vector.y, z * _vector.z);
    }

    Vec3 operator*(const float _value) const
    {
        return Vec3(x * _value, y * _value, z * _value);
    }

    Vec3 operator/(const float _value) const
    {
        return Vec3(x / _value, y / _value, z / _value);
    }

    Vec3 operator-() const
    {
        return Vec3(-x, -y, -z);
    }

    bool operator!=(const Vec3 &_vec) const
    {
        if(x != _vec.x || y != _vec.y || z != _vec.z)
        {
            return true;
        }
    }

    bool operator>= (const Vec3 &_vec) const
    {
        if(x >= _vec.x || y >= _vec.y || z >= _vec.z)
        {
            return true;
        }
    }

    /*Vec3 operator * (const glm::mat3x3 _matrix) const
    {
        Vec3 col_1(x * _matrix[0], y * _matrix[1], z * _matrix[2]);
        Vec3 col_2(x * _matrix[3], y * _matrix[4], z * _matrix[5]);
        Vec3 col_3(x * _matrix[6], y * _matrix[7], z * _matrix[8]);

        return Vec3(col_1, col_2, col_3);

    }*/


};

#endif // VEC3


///-----------------------------------------------------------------------------
/// Code based on code created by:
/// Paul Baker, 2006
/// "www.paulsprojects.net"
/// BSD Licence "http://www.paulsprojects.net/NewBSDLicence.txt"
/// ----------------------------------------------------------------------------


#ifndef MAT3X3
#define MAT3X3

#include "vec3.h"

class Mat3x3
{

public:
    Mat3x3();
    Mat3x3( float a0, float a1, float a2,
            float a3, float a4, float a5,
            float a6, float a7, float a8);

    Mat3x3(const float * _value);

    Mat3x3(const Mat3x3 &_value);
    ~Mat3x3() {}

    void SetEntry(int _position, float _value);
    float GetEntry(int _position) const;

    //Binary Operators
    Mat3x3 operator+(const Mat3x3 & _value) const;
    Mat3x3 operator-(const Mat3x3 & _value) const;
    //Mat3x3 operator*(const Mat3x3 & _value) const;
    Mat3x3 operator*(const float _value) const;
    Vec3 operator*(const Vec3 _value) const;
    Mat3x3 operator/(const float _value) const;

    void operator += (const Mat3x3 & _value);
    Mat3x3& operator = (const Mat3x3& _mat);

    //Misc Methods
    void Invert(void);
    Mat3x3 GetInverse(void) const;

    float entries[9];

};

#endif // MAT3X3


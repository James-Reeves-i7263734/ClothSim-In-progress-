//------------------------------------------------------
///Code is almost identical to Mat3x3
/// See the Mat3x3.h for the referencing
//------------------------------------------------------

#ifndef MAT2X3
#define MAT2X3

#include "vec3.h"

class Mat2x3
{

public:
    Mat2x3();
    Mat2x3( float a0, float a1, float a2,
            float a3, float a4, float a5);

    Mat2x3(const float * _value);

    Mat2x3(const Mat2x3 &_value);
    ~Mat2x3() {}

    void SetEntry(int _position, float _value);
    float GetEntry(int _position) const;

    //Binary Operators
    Mat2x3 operator+(const Mat2x3 & _value) const;
    Mat2x3 operator-(const Mat2x3 & _value) const;
    //Mat3x3 operator*(const Mat3x3 & _value) const;
    Mat2x3 operator*(const float _value) const;
    Vec3 operator*(const Vec3 _value) const;
    Mat2x3 operator/(const float _value) const;

    void operator += (const Mat2x3 & _value);

    //Misc Methods
    void Transpose(void);
    Mat2x3 GetTranspose() const ;

    float entries[6];

};

#endif // MAT2X3


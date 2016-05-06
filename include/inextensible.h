#ifndef INEXTENSIBLE
#define INEXTENSIBLE

///--------------------------------------------------------------------------
/// Based on the paper:
/// "Efficient Simulation of Inextensible Cloth", R. Goldenthal, et al.,
/// ACM Transactions on Graphics (Proceedings of SIGGRAPH 2007), Volume 26
/// [Accessed 2016]
/// http://www.cs.columbia.edu/cg/ESIC/esic.html
///--------------------------------------------------------------------------

#include "vec3.h"
#include "particle.h"
#include "spring.h"
#include "constants.h"
#include "mat3x3.h"
#include "mat2x3.h"

#include <iostream>
#include <vector>

class Inextensible
{

public:

    ///Inextensible cloth calculations
    /// @brief Uses the Fast Projection Method
    /// @brief outlined in the paper
    Inextensible(Particle *_a, Particle *_b);
    ~Inextensible();

    Vec3& getStart() {return m_startPoint;}
    Vec3& getEnd() {return m_endPoint;}
    Vec3& getVelocity() {return m_velocity;}

    Vec3 constraintGradient(Particle *_a, Particle *_b);
    Vec3 iterationVector(Particle *_a, Particle *_b);

    Mat3x3 massMatrix(Mat3x3 _matrix, Particle *_a, Particle *_b);

private:

    Particle *m_a;
    Particle *m_b;

    Vec3 m_startPoint;
    Vec3 m_endPoint;

    Vec3 m_currentPosition;
    Vec3 m_velocity;
    Vec3 m_halfPointPos;
    Vec3 m_intervalPos;
    Vec3 m_extensibility;
    Vec3 m_increment;

    Vec3 m_ABDistance;

    int m_iteration;

    float m_timeStep;
    float m_length;
    float m_scaling;

    //Mass matrix
    Mat3x3 m_matrix{0,0,0,0,0,0,0,0,0};


};

#endif // INEXTENSIBLE

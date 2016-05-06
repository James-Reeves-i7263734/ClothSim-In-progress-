#include "inextensible.h"
//#include "mat3x3.h"

Vec3 Inextensible::constraintGradient(Particle *_a, Particle *_b)
{

    m_a = _a;
    m_b = _b;

    Vec3 Pa = m_a->returnPos();
    Vec3 Pb = m_b->returnPos();
    Vec3 val = (Pb - Pa) * 2.0f;

    Vec3 constraint = val / REST_LENGTH;

    return constraint;


}

Vec3 Inextensible::iterationVector(Particle *_a, Particle *_b)
{

    m_a = _a;
    m_b = _b;

    Vec3 l;
    Vec3 Pa = m_a->returnPos();
    Vec3 Pb = m_b->returnPos();
    Vec3 PbPa = Pb - Pa;

    Vec3 vector = ((PbPa * PbPa) / REST_LENGTH) - REST_LENGTH;

    return vector;

}

Mat3x3 Inextensible::massMatrix(Mat3x3 _matrix, Particle *_a, Particle *_b)
{

    m_a = _a;
    m_b = _b;

    //Symmetrical Matrix
    Mat3x3 M{m_a->m_mass,0,0,0,0,0,0,0,m_b->m_mass};
    M = _matrix;

    //Set up Mass Matrices
    Mat3x3 MM1{0,0,0,0,0,0,0,0,0};
    Mat3x3 MM2{0,0,0,0,0,0,0,0,0};
    Mat3x3 MFinal{0,0,0,0,0,0,0,0,0};


    //Coordinate Vector of the Particle
    Vec3 q_1 = m_a->returnPos();
    Vec3 q_2 = m_b->returnPos();

    //Time derivative of q
    Vec3 d_q1 = q_1 * m_velocity;
    Vec3 d_q2 = q_2 * m_velocity;

    Vec3 d_q1Half = d_q1 / 2.0f;
    Vec3 d_q2Half = d_q2 / 2.0f;

    MM1 = M;
    MM1 * d_q1Half;
    MM1 * d_q1;

    MM2 = M;
    MM2 * d_q2Half;
    MM2 * d_q2;
    //MM2 = (M * (d_q2 / 2)) * d_q2;

    MFinal = MM1 + MM2;

    return MFinal;

}


Inextensible::Inextensible(Particle *_a, Particle *_b)
{

    m_a = _a;
    m_b = _b;

    m_startPoint = m_a->returnPos();
    m_endPoint = m_b->returnPos();
    m_halfPointPos = m_endPoint - m_startPoint / 2;

    m_iteration = 0;
    m_timeStep = 10.0f;

    //Used to represent the outcome of equation 7 from the paper
    Vec3 AuxillaryVariable;

    Vec3 length;
    m_length = length.length(m_startPoint, m_endPoint);

    m_velocity = (m_a->getVelocity() + m_b->getVelocity()) / 2.0f;

    while(m_currentPosition >= m_halfPointPos && m_currentPosition != m_endPoint)
    {
        //
        float timeStepSqrd = m_timeStep * m_timeStep;

        Vec3 AuxVariPart_1 = massMatrix(m_matrix,m_a,m_b) * constraintGradient(m_a,m_b);
        Vec3 AuxVariPart_2 = AuxVariPart_1 * iterationVector(m_a,m_b);
        AuxillaryVariable = AuxVariPart_2 * timeStepSqrd;

        Vec3 incrementPart = massMatrix(m_matrix, m_a, m_b) * (constraintGradient(m_a, m_b) * -timeStepSqrd);
        m_increment = incrementPart * AuxillaryVariable;

        Vec3 newPos = m_currentPosition + m_increment;
        m_currentPosition = newPos;

        ++m_iteration;
    }

    m_velocity = ((m_currentPosition - m_startPoint) * (m_timeStep * 0.5f));

}






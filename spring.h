#ifndef SPRING
#define SPRING

#include "vec3.h"
#include "particle.h"
#include "constants.h"

class Spring
{

public:

    int m_a;
    int m_b;

    float m_springTension;
    float m_constant;
    float m_restLength;

    Spring();
    ~Spring();


};

#endif // SPRING


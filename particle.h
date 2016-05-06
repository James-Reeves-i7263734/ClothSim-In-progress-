#ifndef PARTICLE
#define PARTICLE

#include "vec3.h"
//#include <glm/vec3.hpp>

class Particle
{

public:

    Particle(Vec3 _position);
    Particle();
    ~Particle();

    Vec3& returnPos() {return m_position;}
    Vec3& getVelocity() {return m_velocity;}
    Vec3& getNormal() {return m_normal;}

    float& getMass() {return m_mass;}

    Vec3 m_position;
    Vec3 m_velocity;
    Vec3 m_normal;

    bool m_isMoveable;

    float m_mass;

};

#endif // PARTICLE


#include "particle.h"

Particle::Particle(Vec3 _position)
{

    m_position = _position;
    m_velocity = Vec3(0,0,0);
    m_mass = 0;
    m_isMoveable = true;

}

Particle::Particle()
{

}

Particle::~Particle(){}

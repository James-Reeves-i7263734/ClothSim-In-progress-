#ifndef CLOTH
#define CLOTH

///-----------------------------------------------------------
///
/// Cloth Simulation code based on work done by
/// Paul Baker, 2006.
/// Website: www.paulsproject.net
///
///-----------------------------------------------------------

//#include <QtGui/QWindow>
//#include <QtGui/QOpenGLFunctions>
//#include <QtGui/QGuiApplication>
//#include <QtGui/QMatrix4x4>
//#include <QtGui/QOpenGLShaderProgram>
//#include <QtGui/QScreen>

#include <GL/gl.h>
#include <GL/glut.h>

#include <iostream>
#include <sys/time.h>
#include <vector>

#include "particle.h"
#include "spring.h"
#include "vec3.h"
#include "constants.h"
#include "inextensible.h"

class Cloth
{

public:

    Cloth();
    ~Cloth();

    //Set up GL
    bool Init(int _argc, char **_argv);

    //Handle window resize
    static void GLResize(int _w, int _h);

    //Set up variables
    bool SimInit();

    //Reset cloth
    void resetCloth();

    void UpdateFrame();

    void draw();

    void render(double _currentTime, double _totalTime);

    double& getCurrentTime() {return m_currentTime;}
    double& getTimeElapsed() {return m_timeElapsed;}

    void drawTri(Particle *_p1, Particle *_p2, Particle *_p3);

    Particle* getParticle(int _x, int _y)
    {
        return &currentParticle[_y * CLOTHSIZE + _x];
    }
    /*Particle getPart(int x, int y)
    {
        return part_1.at(x * CLOTHSIZE + y);
    }*/

private:

    //Function for keeping track of time
    double m_startTime;
    double m_currentTime;
    double m_timeElapsed;

    //Set gravity
    Vec3 m_gravity;

    //Set Mass
    float m_mass;

    //Set up Array of Particles
    int numParticles;
    std::vector<Particle>part_1;
    std::vector<Particle>part_2;

    //Vector iterators
    std::vector<Particle>::iterator currentParticle;
    std::vector<Particle>::iterator nextParticle;

    //Set up Array of Spring
    int numSprings;
    std::vector<Spring>connections;
    std::vector<Spring>::iterator currentConnection;


};



#endif // CLOTH


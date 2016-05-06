#include "cloth.h"

Cloth::Cloth()
{

    m_gravity = Vec3(0.0f,-0.98f,0.0f);
    m_mass = 0.01f;

    struct timeval time;
    gettimeofday(&time, NULL);
    m_startTime = (time.tv_usec * 10);

}

bool Cloth::Init(int _argc, char** _argv)
{

    glutInit(&_argc, _argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(720, 486);
    glutCreateWindow("Inextensible Cloth Simulation");
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glClearColor(0.7f, 0.0f, 1.0f, 1.0f);

    return true;

}

void Cloth::GLResize(int _w, int _h)
{

    glViewport(0, 0, _w, _h);
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluPerspective(45.0, (double)_w / (double) _h, 1.0, 200.0);

}

void Cloth::drawTri(Particle *_p1, Particle *_p2, Particle *_p3)
{

    glNormal3fv((GLfloat *) &(_p1->getNormal()));
    glVertex3fv((GLfloat *) &(_p1->returnPos()));

    glNormal3fv((GLfloat *) &(_p2->m_normal));
    glVertex3fv((GLfloat *) &(_p2->returnPos()));

    glNormal3fv((GLfloat *) &(_p3->m_normal));
    glVertex3fv((GLfloat *) &(_p3->returnPos()));

}


bool Cloth::SimInit()
{

    //Set number of particles
    numParticles = CLOTHSIZE * CLOTHSIZE;

    //Set number of springs

    //Set the horizontal and vertical springs, except for bottom and right edges. Also known as structural springs
    numSprings = (CLOTHSIZE - 1) * CLOTHSIZE * 2;

    //Set the diagonal springs. Also known as Shear springs
    //This connects the top-left to the bottom-right (and vice versa) corner of each pair of triangles
    numSprings += (CLOTHSIZE - 1) * (CLOTHSIZE - 1) * 2;

    //Set every second particle together. Used to allow for bending
    numSprings += (CLOTHSIZE - 2) * CLOTHSIZE * 2;

    part_1.resize(numParticles);
    part_2.resize(numSprings);

    resetCloth();

    //part_1 = new Particle[numParticles];
    //part_2 = new Particle[numParticles];
    //connections = new Spring[numSprings];

    return true;

}

void Cloth::resetCloth()
{

    //Add particles to arrays and set values
    for(int x = 0; x < CLOTHSIZE; ++x)
    {
        for(int y = 0; y < CLOTHSIZE; ++y)
        {
            part_1[x * CLOTHSIZE + y].m_position.set(float(y) - float(CLOTHSIZE - 1)/2, 0.0f, float(x) - float(CLOTHSIZE-1) / 2);
            part_2[x * CLOTHSIZE + y].m_position.set(float(y) - float(CLOTHSIZE - 1)/2, 0.0f, float(x) - float(CLOTHSIZE-1) / 2);
            //part_1[x * CLOTHSIZE + y].m_velocity.zero();
            part_1[x * CLOTHSIZE + y].m_mass = m_mass;
            part_2[x * CLOTHSIZE + y].m_mass = m_mass;
        }
    }

    //Set top right and top left corners to fixed - in both arrays
    part_1[0].m_isMoveable = false;
    part_1[CLOTHSIZE - 1].m_isMoveable = false;

    part_2[0].m_isMoveable = false;
    part_2[CLOTHSIZE - 1].m_isMoveable = false;

    //Set current and next particle
    currentParticle = part_1.begin();
    nextParticle = part_2.begin();

    //Set up spring array
    currentConnection = connections.begin();

    //Set up the horizontal structural springs
    for(int i = 0; i < CLOTHSIZE; ++i)
    {
        for(int j = 0; j < CLOTHSIZE; ++j)
        {
            currentConnection->m_a = i * CLOTHSIZE + j;
            currentConnection->m_b = i * CLOTHSIZE + (j+1);

            currentConnection->m_constant = SPRINGCONSTANT;
            currentConnection->m_restLength = REST_LENGTH;

            ++currentConnection;
        }
    }

    //Set up the vertical structural springs
    for(int i = 0; i < CLOTHSIZE; ++i)
    {
        for(int j = 0; j < CLOTHSIZE; ++j)
        {
            currentConnection->m_a = i * CLOTHSIZE + j;
            currentConnection->m_b = (i+1) * CLOTHSIZE + j;

            currentConnection->m_constant = SPRINGCONSTANT;
            currentConnection->m_restLength = REST_LENGTH;

            ++currentConnection;
        }
    }

    //Set up the right-hand shear springs
    for(int i = 0; i < CLOTHSIZE; ++i)
    {
        for(int j = 0; j < CLOTHSIZE; ++j)
        {
            currentConnection->m_a = i * CLOTHSIZE + j;
            currentConnection->m_b = (i+1) * CLOTHSIZE + (j+1);

            currentConnection->m_constant = SPRINGCONSTANT;
            currentConnection->m_restLength = REST_LENGTH*sqrt(2.0f);

            ++currentConnection;
        }
    }

    //Set up the left-hand shear springs
    for(int i = 0; i < CLOTHSIZE; ++i)
    {
        for(int j = 0; j < CLOTHSIZE; ++j)
        {
            currentConnection->m_a = i * CLOTHSIZE + j;
            currentConnection->m_b = (i+1) * CLOTHSIZE + (j-1);

            currentConnection->m_constant = SPRINGCONSTANT;
            currentConnection->m_restLength = REST_LENGTH*sqrt(2.0f);

            ++currentConnection;
        }
    }

    //Set up the horizontal bending springs
    for(int i = 0; i < CLOTHSIZE; ++i)
    {
        for(int j = 0; j < CLOTHSIZE; ++j)
        {
            currentConnection->m_a = i * CLOTHSIZE + j;
            currentConnection->m_b = i * CLOTHSIZE + (j+2);

            currentConnection->m_constant = SPRINGCONSTANT;
            currentConnection->m_restLength = REST_LENGTH*2;

            ++currentConnection;
        }
    }

    //Set up the vertical bending springs
    for(int i = 0; i < CLOTHSIZE; ++i)
    {
        for(int j = 0; j < CLOTHSIZE; ++j)
        {
            currentConnection->m_a = i * CLOTHSIZE + j;
            currentConnection->m_b = (i+2) * CLOTHSIZE + j;

            currentConnection->m_constant = SPRINGCONSTANT;
            currentConnection->m_restLength = REST_LENGTH*2;

            ++currentConnection;
        }
    }

}

void Cloth::UpdateFrame()
{
    //Get and Set current time and time passed
    struct timeval time;
    gettimeofday(&time, NULL);
    m_currentTime = (time.tv_usec * 10);
    m_timeElapsed = m_currentTime - m_startTime;
    m_startTime = m_currentTime;

    //Physics updates
    //Updates approx every 10ms
    static double lastUpdate = 0.0;
    lastUpdate += m_timeElapsed;

    bool madeUpdate = false;

    while(lastUpdate>10.0)
    {
        lastUpdate-= 10.0;
        float secondsPassed = 0.01f;
        madeUpdate = true;

        //Calculate the springs
        for(int i = 0; i < numSprings; ++i)
        {
            float length;
            Vec3 partDistance;
            length = partDistance.length(currentParticle[connections[i].m_a].returnPos(), currentParticle[connections[i].m_b].returnPos());

            float extension = length - connections[i].m_restLength;

            connections[i].m_springTension = connections[i].m_constant * extension / connections[i].m_restLength;

        }

        //Calculate the particles
        for(int i = 0; i < numParticles; ++i)
        {

            if(currentParticle[i].m_isMoveable == false)
            {
                nextParticle[i].m_position = currentParticle[i].m_position;
            }
            else
            {
                Vec3 force = m_gravity;

                for (int j = 0; j < numSprings; ++j)
                {
                    if(connections[j].m_a == i)
                    {
                        Vec3 tension = currentParticle[connections[j].m_b].returnPos() - currentParticle->returnPos();

                        tension.normalise();

                        force += tension * connections[j].m_springTension;
                    }

                    if(connections[j].m_b == i)
                    {
                        Vec3 tension = currentParticle[connections[j].m_a].returnPos() - currentParticle->returnPos();

                        tension.normalise();

                        force +=  tension * connections[j].m_springTension;
                    }
                }

                Vec3 acceleration = force / currentParticle[i].m_mass;

                nextParticle[i].m_velocity = (currentParticle[i].m_velocity + acceleration * (float)secondsPassed) * DAMPING;

                nextParticle[i].m_position = currentParticle[i].returnPos() + (nextParticle[i].m_velocity + currentParticle[i].m_velocity) * (float)secondsPassed/2.0f;

            }

        }

        //Particle * temp = currentParticle;
        //currentParticle = nextParticle;
        //nextParticle = currentParticle;
    }

    if(madeUpdate == true)
    {
        for(int i = 0; i < numParticles; ++i)
        {
            currentParticle[i].m_normal.zero();
        }

        for(int i = 0; i < CLOTHSIZE-1; ++i)
        {
            for(int j = 0; j < CLOTHSIZE-1; ++j)
            {
                Vec3 & part0 = currentParticle[i * CLOTHSIZE + j].m_position;
                Vec3 & part1 = currentParticle[i * CLOTHSIZE + j+1].m_position;
                Vec3 & part2 = currentParticle[(i+1) * CLOTHSIZE + j].m_position;
                Vec3 & part3 = currentParticle[(i+1) * CLOTHSIZE + j+1].m_position;

                Vec3 & norm0 = currentParticle[i * CLOTHSIZE + j].m_normal;
                Vec3 & norm1 = currentParticle[i * CLOTHSIZE + j+1].m_normal;
                Vec3 & norm2 = currentParticle[(i+1) * CLOTHSIZE + j].m_normal;
                Vec3 & norm3 = currentParticle[(i+1) * CLOTHSIZE + j+1].m_normal;

                Vec3 partNormal = (part1 - part0).cross(part2, part0);

                norm0 += partNormal;
                norm1 += partNormal;
                norm2 += partNormal;

                partNormal = (part1 - part2).cross(part3, part2);

                norm1 += partNormal;
                norm2 += partNormal;
                norm3 += partNormal;
            }
        }

        for(int i = 0; i < numParticles; ++i)
        {
            currentParticle[i].m_normal.normalise();
        }
    }

    render(m_currentTime, m_timeElapsed);

}

void Cloth::render(double _currentTime, double _totalTime)
{

}

void Cloth::draw()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glTranslatef(0.0, 0.0, -20.0);

    //Draw cloth
    glEnable(GL_LIGHTING);
    //glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, glColor3f(0.8f, 0.0f, 1.0f));
    //glMaterialfv(GL_FRONT, GL_DIFFUSE, COLOR(0.8f, 0.0f, 1.0f));
    //glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, COLOR(1.0f, 1.0f, 0.0f));
    glBegin(GL_TRIANGLES);
    {
        for(int i = 0; i < CLOTHSIZE; ++i)
        {
            for(int j = 0; j < CLOTHSIZE; ++j)
            {
                /*glNormal3fv((GLfloat *) &currentParticle[i * CLOTHSIZE + j].m_normal);
                glVertex3fv((GLfloat *) &currentParticle[i * CLOTHSIZE + j].m_position);
                glNormal3fv((GLfloat *) &currentParticle[i * CLOTHSIZE + j+1].m_normal);
                glVertex3fv((GLfloat *) &currentParticle[i * CLOTHSIZE + j+1].m_position);
                glNormal3fv((GLfloat *) &currentParticle[(i+1) * CLOTHSIZE + j].m_normal);
                glVertex3fv((GLfloat *) &currentParticle[(i+1) * CLOTHSIZE + j].m_position);

                glNormal3fv((GLfloat *) &currentParticle[(i+1) * CLOTHSIZE + j].m_normal);
                glVertex3fv((GLfloat *) &currentParticle[(i+1) * CLOTHSIZE + j].m_position);
                glNormal3fv((GLfloat *) &currentParticle[i * CLOTHSIZE + j+1].m_normal);
                glVertex3fv((GLfloat *) &currentParticle[i * CLOTHSIZE + j+1].m_position);
                glNormal3fv((GLfloat *) &currentParticle[(i+1) * CLOTHSIZE + j+1].m_normal);
                glVertex3fv((GLfloat *) &currentParticle[(i+1) * CLOTHSIZE + j+1].m_position);*/

                drawTri(getParticle(i,j), getParticle(i,j+1), getParticle(i+1,j));
                drawTri(getParticle(i,j), getParticle(i,j+1), getParticle(i+1,j+1));

            }
        }
    }
    glEnd();
    glDisable(GL_LIGHTING);
    glutSwapBuffers();

}

int main(int _argc, char **_argv)
{
    //QGuiApplication clothSim(_argc, _argv);
    //return clothSim.exec();

    Cloth * cloth;

    cloth->Init(_argc, _argv);

    cloth->draw();
    //glutDisplayFunc(cloth->draw());
    glutReshapeFunc(cloth->GLResize);

    if(!cloth->SimInit())
    {
        std::cout << "simInit faled" << std::endl;
        std::cerr << "failed" << std::endl;
        return false;
    }

    cloth->UpdateFrame();

    glutMainLoop();
    return EXIT_SUCCESS;
}


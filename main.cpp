#include "cloth.h"
#include "particle.h"
#include "spring.h"
#include "vec3.h"
#include "constants.h"
#include "clothglwindow.h"

/*Cloth * cloth;

int main(int _argc, char **_argv)
{
    //QGuiApplication clothSim(_argc, _argv);
    //return clothSim.exec();

    cloth->Init(_argc, _argv);

    cloth->draw();
    //glutDisplayFunc(cloth->draw);
    glutReshapeFunc(cloth->GLResize);

    glutMainLoop();
    return EXIT_SUCCESS;
}*/


//--------------------------------------------------------
//
// Basic QtOpenGl code borrowed from:
// http://doc.qt.io/qt-5/qtgui-openglwindow-main-cpp.html
//
//--------------------------------------------------------


/*#include "clothglwindow.h"
#include "cloth.h"
#include "particle.h"*/

/*

#include <QtGui/QGuiApplication>
#include <QtGui/QMatrix4x4>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QScreen>

#include <QtCore/qmath.h>
#include <vector>

Cloth * cloth;


class TriangleWindow : public clothglwindow
{
public:

    TriangleWindow();

    void initialize() Q_DECL_OVERRIDE;
    void render() Q_DECL_OVERRIDE;

private:

    GLuint m_posAttr;
    GLuint m_colAttr;
    GLuint m_matrixUniform;

    QOpenGLShaderProgram *m_program;
    int m_frame;
};

TriangleWindow::TriangleWindow()
    : m_program(0), m_frame(0)
{

}

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);

    QSurfaceFormat format;
    format.setSamples(16);

    TriangleWindow window;
    window.setFormat(format);
    window.resize(1024,640);
    window.show();

    window.setAnimating(true);

    return app.exec();
}

void TriangleWindow::initialize()
{
    m_program = new QOpenGLShaderProgram(this);
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, "vertexShader.vert");
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, "fragShader.frag");
    m_program->link();
    m_posAttr = m_program->attributeLocation("posAttr");
    m_colAttr = m_program->attributeLocation("colAttr");
    m_matrixUniform = m_program->uniformLocation("matrix");
}

void TriangleWindow::render()
{
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_program->bind();

    QMatrix4x4 matrix;
    matrix.perspective(60.0f, 4.0f/3.0f, 0.1f, 100.0f);
    matrix.translate(-10,8,-30);
    //matrix.rotate(10,0,1,0);
    //matrix.rotate(100.0f * m_frame / screen()->refreshRate(), 0,1,0);

    m_program->setUniformValue(m_matrixUniform, matrix);

    //std::vector<Particle> particles = cloth_test.getMPart();


    //double currentTime = m_frame * 10.0;
    //double timeElapsed = cloth->getTimeElapsed();

    //cloth->render(currentTime,timeElapsed );


    /*Vec3 gravity(0,-0.01,0);
    cloth_test.AddForce(gravity*TIME_STEP);
    Vec3 wind(1,0,0);
    cloth_test.windForce(wind*TIME_STEP);
    cloth_test.calculateCloth();
    cloth_test.drawCloth();*/

    //GLfloat vertices[] = {};
        /*0.0f, 0.707f,
        -0.5f, -0.5f,
        0.5f, -0.5f*/

    /*glBegin(GL_TRIANGLES);
    for(std::vector<Particle>::iterator it = particles.begin(); it != particles.end(); ++it)
    {
        for (int i = 0; i < cloth_test.clothWidth()-1; ++i)
        {
            for (int j = 0; j < cloth_test.clothWidth()-1; ++j)
            {

                Vec3 colour(0,0,0);

                if(i%2)
                {
                    colour = Vec3(0.5f, 0.5f, 0.05f);
                }
                else
                {
                    colour = Vec3(0.0f,0.0f,0.0f);
                }

                cloth_test.drawTri(cloth_test.getParticle(i+1,j), cloth_test.getParticle(i,j), cloth_test.getParticle(i,j+1), colour);
                cloth_test.drawTri(cloth_test.getParticle(i+1,j+1), cloth_test.getParticle(i+1,j), cloth_test.getParticle(i,j+1), colour);
            }
        }
    }
    glEnd();*//*



    /*GLfloat colors[] = {
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f
    };

    //glVertexAttribPointer(m_posAttr, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, colors);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawArrays(GL_TRIANGLES, 0, particles.size());

    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

    m_program->release();

    ++m_frame;
}
*/

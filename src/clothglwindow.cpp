//-----------------------------------------------------------------
//
// Basic QtOpenGL code borrowed from:
// http://doc.qt.io/qt-5/qtgui-openglwindow-openglwindow-cpp.html
//
//-----------------------------------------------------------------


#include "clothglwindow.h"

#include <QtCore/QCoreApplication>
#include <QtGui/QOpenGLPaintDevice>
#include <QtGui/QPainter>

clothglwindow::clothglwindow(QWindow *parent)
    : QWindow(parent), m_update_pending(false), m_animating(false)
    , m_context(0), m_device(0)
{
    setSurfaceType(QWindow::OpenGLSurface);
}

clothglwindow::~clothglwindow()
{
    delete m_device;
}

void clothglwindow::render(QPainter *painter)
{
    Q_UNUSED(painter);
}

void clothglwindow::initialize() {}

void clothglwindow::render()
{
    if (!m_device)
    {
        m_device = new QOpenGLPaintDevice;
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    m_device->setSize(size());
    QPainter painter(m_device);
    render(&painter);
}

void clothglwindow::renderLater()
{
    if (!m_update_pending)
    {
        m_update_pending = true;
        QCoreApplication::postEvent(this, new QEvent(QEvent::UpdateRequest));
    }
}

bool clothglwindow::event(QEvent *event)
{
    switch (event->type())
    {
    case QEvent::UpdateRequest:
        m_update_pending = false;
        renderNow();
        return true;
    default:
        return QWindow::event(event);
    }
}

void clothglwindow::exposeEvent(QExposeEvent *event)
{
    Q_UNUSED(event);

    if(isExposed())
    {
        renderNow();
    }
}

void clothglwindow::renderNow()
{
    if(!isExposed())
    {
        return;
    }

    bool needsInitialize = false;

    if (!m_context)
    {
        m_context =  new QOpenGLContext(this);
        m_context->setFormat(requestedFormat());
        m_context->create();

        needsInitialize = true;
    }

    m_context->makeCurrent(this);

    if(needsInitialize)
    {
        initializeOpenGLFunctions();
        initialize();
    }

    render();

    m_context->swapBuffers(this);

    if (m_animating)
    {
        renderLater();
    }
}

void clothglwindow::setAnimating(bool animating)
{
    m_animating = animating;

    if(animating)
    {
        renderLater();
    }
}


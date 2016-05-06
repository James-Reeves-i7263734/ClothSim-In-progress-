//-----------------------------------------------------------------
//
// Basic QtOpenGL code borrowed from:
// http://doc.qt.io/qt-5/qtgui-openglwindow-openglwindow-h.html
//
//-----------------------------------------------------------------


#ifndef CLOTHGLWINDOW_H
#define CLOTHGLWINDOW_H

#include <QtGui/QWindow>
#include <QtGui/QOpenGLFunctions>

class QPainter;
class QOpenGLContext;
class QOpenGLPaintDevice;

class clothglwindow : public QWindow, protected QOpenGLFunctions
{
    Q_OBJECT

public:

    explicit clothglwindow(QWindow *parent = 0);
    ~clothglwindow();

    virtual void render(QPainter *painter);
    virtual void render();

    virtual void initialize();

    void setAnimating(bool animating);

public slots:

    void renderLater();
    void renderNow();

protected:

    bool event(QEvent *event) Q_DECL_OVERRIDE;

    void exposeEvent(QExposeEvent *event) Q_DECL_OVERRIDE;

private:

    bool m_update_pending;
    bool m_animating;

    QOpenGLContext *m_context;
    QOpenGLPaintDevice *m_device;

};

#endif // CLOTHGLWINDOW_H

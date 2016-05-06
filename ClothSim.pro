TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += qt core opengl
LIBS += -lglut -lGLU -lGL

isEqual(QT_MAJOR_VERSION, 5) {
        cache()
        DEFINES +=QT5BUILD
}

SOURCES += \
    particle.cpp \
    spring.cpp \
    cloth.cpp \
    vec3.cpp \
    #main.cpp \
    #clothglwindow.cpp
    inextensible.cpp \
    mat3x3.cpp \
    mat2x3.cpp

HEADERS += \
    cloth.h \
    particle.h \
    spring.h \
    vec3.h \
    constants.h \
    #clothglwindow.h
    inextensible.h \
    mat3x3.h \
    mat2x3.h

DISTFILES += \
    fragshader.frag \
    vertexshader.vert



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
    src/particle.cpp \
    src/spring.cpp \
    src/cloth.cpp \
    src/vec3.cpp \
    #main.cpp \
    #src/clothglwindow.cpp
    src/inextensible.cpp \
    src/mat3x3.cpp \
    src/mat2x3.cpp

HEADERS += \
    include/cloth.h \
    include/particle.h \
    include/spring.h \
    include/vec3.h \
    include/constants.h \
    #include/clothglwindow.h
    include/inextensible.h \
    include/mat3x3.h \
    include/mat2x3.h

DISTFILES += \
    fragshader.frag \
    vertexshader.vert

INCLUDEPATH += include



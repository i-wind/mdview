
QT          += core gui webkit

TARGET      = mdview
TEMPLATE    = app

MOC_DIR     = .obj
OBJECTS_DIR = .obj
RCC_DIR     = .obj
UI_DIR      = .obj

INCLUDEPATH += src sundown

SOURCES     += src/mdview.cpp \
    src/mainwindow.cpp \
    sundown/markdown.c \
    sundown/buffer.c \
    sundown/autolink.c \
    sundown/stack.c \
    sundown/html.c \
    sundown/houdini_html_e.c \
    sundown/houdini_href_e.c

HEADERS     += src/mainwindow.h \
    sundown/markdown.h \
    sundown/buffer.h \
    sundown/autolink.h \
    sundown/stack.h \
    sundown/html.h \
    sundown/houdini.h

RESOURCES   += mdview.qrc

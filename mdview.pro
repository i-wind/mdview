
QT        += core gui webkit

TARGET    = mdview
TEMPLATE  = app

MOC_DIR     = .obj
OBJECTS_DIR = .obj
RCC_DIR     = .obj

SOURCES   += main.cpp \
        mainwindow.cpp

HEADERS   += mainwindow.h

RESOURCES += mdview.qrc
UI_DIR      = .obj

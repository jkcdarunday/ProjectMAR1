#-------------------------------------------------
#
# Project created by QtCreator 2015-05-12T18:02:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CMSC132ProjectMAR1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    assemblyparser.cpp \
    registers.cpp \
    syntaxhighlighter.cpp \
    memory.cpp

HEADERS  += mainwindow.h \
    assemblyparser.h \
    registers.h \
    mapper.h \
    syntaxhighlighter.h \
    memory.h

FORMS    += mainwindow.ui

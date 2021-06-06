#-------------------------------------------------
#
# Project created by QtCreator 2018-02-28T19:07:34
#
#-------------------------------------------------

QT       += core gui sql

QTPLUGIN += QSQLMYSQL

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BrigadaOnline
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    bancodados.cpp \
    cadastrousers.cpp \
    log.cpp \
    planilhaexcel.cpp \
    worker.cpp \
    conexaobd.cpp \
    usuario.cpp \
    delegateocorrencias.cpp

HEADERS += \
        mainwindow.h \
    bancodados.h \
    cadastrousers.h \
    log.h \
    planilhaexcel.h \
    worker.h \
    conexaobd.h \
    usuario.h \
    delegateocorrencias.h

FORMS += \
        mainwindow.ui \
    cadastrousers.ui

INCLUDEPATH = $$PWD\libxl-3.8.2.0\include_cpp

LIBS += $$PWD\libxl-3.8.2.0\lib\libxl.lib

DISTFILES +=

RESOURCES +=


TEMPLATE = app

QT += core gui openglwidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 -03

CFLAGS += -Wall -Wextra -Werror

INCLUDEPATH += $$PWD/include $$PWD/src

SOURCES += \
    source/imageview/imageview.cc \
    source/view/view.cc \
    source/view/strategy.cc \
    source/facade/facade.cc \
    source/model/model_parser.cc \
    source/model/model.cc \
    source/main.cc \
    source/model/command.cc \
    source/controller/controller.cc \

HEADERS += \
    source/facade/facade.h \
    source/view/strategy.h \
    source/model/model.h \
    source/model/model_parser.h \
    source/model/command.h \
    source/controller/controller.h \
    source/imageview/imageview.h \
    source/view/view.h \
    source/include/gif.h \
    source/include/viewer.h \

FORMS += \
    source/mainwindow.ui

RESOURCES = resource/resource.qrc

TRANSLATIONS += \
    resource/3DViewer_ru_RU.ts

CONFIG += lrelease
CONFIG += embed_translations

OBJECTS_DIR = ./obj
MOC_DIR = moc
DESTDIR = ../

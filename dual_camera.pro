#-------------------------------------------------
#
# Project created by QtCreator 2014-01-15T08:40:35
#
#-------------------------------------------------

QT       += core gui widgets

lessThan(QT_MAJOR_VERSION, 4): QT += threads

TEMPLATE = app
TARGET = build/$$CONFIG_RD/dual_camera

OBJECTS_DIR = obj/$$CONFIG_RD
MOC_DIR = $$OBJECTS_DIR/MOC
UI_DIR  = $$OBJECTS_DIR/UI
RCC_DIR = $$OBJECTS_DIR/RCC

CONFIG += $$CONFIG_RD

PLATFORM = am57xx-evm

LIBS += -ljpeg -ldrm_omap -ldrm -lticmem

INCLUDEPATH += $(SDK_PATH_TARGET)/usr/include/libdrm $(SDK_PATH_TARGET)/usr/include/omap

SOURCES += src/main.cpp src/mainwindow.cpp src/jpeg.c src/loopback.c src/cmem_buf.c
HEADERS  += src/mainwindow.h  src/jpeg.h  src/loopback.h src/cmem_buf.h
FORMS    += src/mainwindow.ui

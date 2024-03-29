QT += testlib
QT += gui
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_testharness.cpp

HEADERS += \
    GapBuffer.h \
    IntVector.h

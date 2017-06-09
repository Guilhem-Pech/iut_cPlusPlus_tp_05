TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -static

SOURCES += main.cpp \
    TestTypesBase.cpp

HEADERS += \
    typesbase.hpp \
    C2LinksGenIsA.hpp

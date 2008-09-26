SOURCES += worms.cpp \
           main.cpp
HEADERS += worms.h
TEMPLATE = app
CONFIG += warn_on \
	  thread \
          qt
TARGET = ../bin/worms
RESOURCES = application.qrc

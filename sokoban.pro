qtopia_project(qtopia app)
TARGET=sokoban
CONFIG+=qtopia_main no_quicklaunch

HEADERS = src/sokoban.h \
		  src/playfield.h \
		  src/map.h \
		  src/internalcollections.h \
		  src/levelcollection.h \
		  src/leveldialog.h \
		  src/imagedata.h
SOURCES = src/main.cpp \
		  src/sokoban.cpp \
		  src/playfield.cpp \
		  src/map.cpp \
		  src/internalcollections.cpp \
		  src/levelcollection.cpp \
		  src/leveldialog.cpp \
		  src/imagedata.cpp

help.source=help
help.files=sokoban*
help.hint=help
INSTALLS+=help

desktop.files=sokoban.desktop
desktop.path=/apps/Games
desktop.hint=desktop
INSTALLS+=desktop

pics.files=pics/*
pics.path=/pics/sokoban
pics.hints=pics
INSTALLS+=pics

pkg.desc=Another Sokoban Game
pkg.version=0.0.1
pkg.maintainer=Luxi Liu (luxi.liu@gmail.com)
pkg.license=GPL
pkg.domain=trusted

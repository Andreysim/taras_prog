TEMPLATE = app

TARGET = taras_program

QT = core gui widgets

CONFIG += precompile_header c++17
CONFIG -= debug_and_release debug_and_release_target testcase_targets

CONFIG(debug, debug|release) {
    CONFIG -= release
    TARGET = $${TARGET}d
    CONFIGURATION = Debug
} else {
    CONFIG -= debug
    CONFIG *= release
    CONFIGURATION = Release
}

PRECOMPILED_HEADER = src/pch.h

INCLUDEPATH += \
	$$(QTDIR)/include \
	$$(QTDIR)/include/QtCore \
	$$(QTDIR)/include/QtGui \
	$$(QTDIR)/include/QtWidgets
	
HEADERS = \
	src/Data.h \
	src/DataInputWidget.h \
	src/Emoticon.h \
	src/EvalValue.h \
	src/FilterOptions.h \
	src/FiltersWidget.h \
	src/HistoryWidget.h \
	src/HistoryWindow.h \
	src/MainWindow.h \
	src/pch.h \
	src/ResultWidget.h \
	src/StringUtil.h \
	src/ValueDisplayWidget.h

SOURCES = \
	src/Data.cpp \
	src/DataInputWidget.cpp \
	src/Emoticon.cpp \
	src/EvalValue.cpp \
	src/FiltersWidget.cpp \
	src/HistoryWidget.cpp \
	src/HistoryWindow.cpp \
	src/main.cpp \
	src/MainWindow.cpp \
	src/pch.cpp \
	src/ResultWidget.cpp \
	src/StringUtil.cpp \
	src/ValueDisplayWidget.cpp

RESOURCES = res/Resources.qrc

OBJECTS_DIR = ./GeneratedFiles/$$CONFIGURATION/obj
MOC_DIR = ./GeneratedFiles/$$CONFIGURATION/moc
RCC_DIR = ./GeneratedFiles/$$CONFIGURATION/rcc
UI_DIR = ./GeneratedFiles/$$CONFIGURATION/ui
DESTDIR = bin

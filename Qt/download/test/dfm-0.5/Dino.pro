#-------------------------------------------------
#
# Project created by QtCreator 2011-11-25T17:37:53
#
#-------------------------------------------------
QT       += core gui network
TARGET = Dino
TEMPLATE = app
#CONFIG += static
CONFIG += release warn_off thread
DEPENDPATH += . \
    configdialog \
    highlighters \
    hexedit \
    hexedit/QHexEdit
INCLUDEPATH += . \
    configdialog \
    highlighters \
    hexedit \
    hexedit/QHexEdit
TRANSLATIONS = translations/Dino_de.ts \
                translations/Dino_ru.ts \
                translations/Dino_sr_RS.ts \
                translations/Dino_sr_BA.ts \
                translations/Dino_es_VE.ts \
                translations/Dino_xx_xx.ts
OBJECTS_DIR = build
MOC_DIR = build
#QMAKE_LFLAGS += -static
SOURCES += main.cpp\
        mainwindow.cpp \
    contextmenu.cpp \
    infodlg.cpp \
    tabbar.cpp \
    icondlg.cpp \
    progressdlg.cpp \
    texteditor.cpp \
    highlighters/highlighter_cpp.cpp \
    customactionsdlg.cpp \
    dlistview.cpp \
    desktopapp.cpp \
    dutils.cpp \
    configdialog/configdialog.cpp \
    configdialog/pages.cpp \
    hexedit/Hmainwindow.cpp \
    hexedit/optionsdialog.cpp \
    hexedit/searchdialog.cpp \
    hexedit/QHexEdit/commands.cpp \
    hexedit/QHexEdit/qhexedit.cpp \
    hexedit/QHexEdit/xbytearray.cpp \
    hexedit/QHexEdit/qhexedit_p.cpp \
    dfilesystemmodel.cpp \
    dnetwork.cpp \
    dfileengine.cpp



HEADERS  += mainwindow.h \
    contextmenu.h \
    infodlg.h \
    tabbar.h \
    icondlg.h \
    progressdlg.h \
    texteditor.h \
    highlighters/highlighter_cpp.h \
    customactionsdlg.h \
    dlistview.h \
    desktopapp.h \
    dutils.h \
    configdialog/configdialog.h \
    configdialog/pages.h \
    hexedit/Hmainwindow.h \
    hexedit/optionsdialog.h \
    hexedit/searchdialog.h \
    hexedit/QHexEdit/commands.h \
    hexedit/QHexEdit/xbytearray.h \
    hexedit/QHexEdit/qhexedit.h \
    hexedit/QHexEdit/qhexedit_p.h \
    dfilesystemmodel.h \
    dnetwork.h \
    dfileengine.h




FORMS    += \
    mainwindow.ui \
    hexedit/optionsdialog.ui \
    hexedit/searchdialog.ui

RESOURCES += \
    files.qrc \
    configdialog/configdialog.qrc

OTHER_FILES += \
    TODO \
    AUTHORS \
    CHANGELOG \
    dino.desktop



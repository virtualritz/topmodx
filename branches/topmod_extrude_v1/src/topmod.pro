
# main stuff
QT += opengl \
    xml
CONFIG += qt \
    debug \
    warn_off \
    link_prl

# Fenghui: disable pg option
QMAKE_CXXFLAGS_DEBUG += -pg
QMAKE_CXXFLAGS += -fpermissive
QMAKE_LFLAGS_DEBUG += -pg

TEMPLATE = app
MOC_DIR = tmp
OBJECTS_DIR = tmp
UI_DIR = tmp
RCC_DIR = tmp

# TopModd will be the name for the debug version,
# and TopMod will be the release version
CONFIG(debug, debug|release) { 
	TARGET = TopModd # -$${VERSION}
	DESTDIR = ../bin/debug/
}
else { 
	TARGET = TopMod # -$${VERSION}
	DESTDIR = ../bin/release/
}

DEPENDPATH += include \
    vecmat \
    dlflcore \
    dlflaux \
    arcball
INCLUDEPATH += include \
    vecmat \
    arcball \
    dlflcore \
    dlflaux \
    arcball

# Operating System Specific Tasks - OS/X
macx { 
    DEFINES *= MACX    
    # mac icon when not using a custom info.plist file
    ICON = topmod.icns
    
    # either compile the mac version as an app bundle or a console app
    # tell it to load a custom info.plist file here
    QMAKE_INFO_PLIST = Info.plist
    MACOSX_DEPLOYMENT_TARGET = 10.2
    
    # compile release + universal binary
    CONFIG += x86 \
        ppc
    
    QMAKE_LFLAGS += -L../lib
    LIBS += -lvecmat \
        -ldlflcore \
        -ldlflaux \
        -larcball \
        -framework \
        CoreFoundation
    
    INCLUDEPATH += /usr/include
    QMAKE_LFLAGS += -L/usr/lib
}

# Operating System Specific Tasks - Linux
else:unix { 
    # dave - testing the macx / linux / win32 define
    DEFINES *= UNIX
    QMAKE_LFLAGS += -L../lib
    LIBS += -lvecmat \
        -ldlflcore \
        -ldlflaux \
        -larcball
    DEFINES *= LINUX
}

# Operating System Specific Tasks - Windows
else:win32 { 
    # dave - testing the macx / linux / win32 define
    DEFINES *= WIN32
    
    # application icon windows
    RC_FILE = topmod.rc
    INCLUDEPATH += ../lib
    QMAKE_LFLAGS += -L../lib
    LIBS += -lvecmat \
        -ldlflcore \
        -ldlflaux \
        -larcball
}

# Input
HEADERS += \
		tools/insert_edge_tool.h \
    tools/topmod_tool.h \
    tools/cubical_extrude_tool.h \
    GLWidget.h \
    TopMod.h \
    MainWindow.h \
    GeometryRenderer.h \
    #DLFLLighting.h \
    BasicsMode.h \
    DLFLSelection.h \
    Viewport.h \
    DLFLRenderer.h \
    include/BaseObject.h \
    include/Constants.h \
    include/Inlines.h \
    include/StreamIO.h \
    include/Color.h \
    include/Grid.h \
    include/Texture.h \
    include/Transform.h \
    include/AmbientLight.h \
    include/Light.h \
    include/PointLight.h \
    include/SpotLight.h \
    include/Camera3.h \
	vecmat/Matrix4x4.h
	
SOURCES += tools/insert_edge_tool.cc \
		tools/cubical_extrude_tool.cc \
    tools/topmod_tool.cc \
    GLWidget.cc \
    TopMod.cc \
    main.cc \
    MainWindow.cc \
    MainWindowCallbacks.cc \
    GeometryRenderer.cc \
    BasicsMode.cc \
    #DLFLLighting.cc \
    DLFLRenderer.cc \
    DLFLSelection.cc \
    DLFLUndo.cc \
    include/Camera3.cc \
	vecmat/Matrix4x4.cc

RESOURCES += application.qrc

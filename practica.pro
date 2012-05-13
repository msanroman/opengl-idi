TEMPLATE	= app
LANGUAGE	= C++

QT += opengl

HEADERS	+= cameraIDI.h \
        glwidget.h \
	model.h \
	objectInstance.h \
	scene.h \
	face.h \
	vertex.h \
	color.h \
	box.h \
	XML.h \
	ground.h \
	material.h \
	material_lib.h \
	point.h \
	tinystr.h \
	tinyxml.h \
    principal.h

SOURCES	+= cameraIDI.cpp glwidget.cpp \
	model.cpp \
	objectInstance.cpp \
	scene.cpp \
	face.cpp \
	vertex.cpp \
	color.cpp \
	box.cpp \
	XML.cpp \
	ground.cpp \
	material.cpp \
	material_lib.cpp \
	point.cpp \
	tinystr.cpp \
	tinyxml.cpp \
	tinyxmlerror.cpp \
	tinyxmlparser.cpp \
	main.cpp \
    principal.cpp

FORMS	= principal.ui

unix {
  UI_DIR = .ui
  MOC_DIR = .moc
  OBJECTS_DIR = .obj
}

CONFIG += c++11
TEMPLATE = lib
TARGET = $$qtLibraryTarget(QJsonSerializer)
DEFINES += QJSONSERIALIZER_LIBRARY
VER_MAJ = 1

HEADERS += \
	Array.h \
    DeserializerBase.h \
	Dictionary.h \
    IDeserializer.h \
	ISerializable.h \
    QJsonSerializer \
    QJsonSerializer.h \
    SerializerBase.h \
    ISerializer.h \
    IObjectFactory.h

SOURCES += \
	Array.cpp \
	DeserializerBase.cpp \
	Dictionary.cpp \
	SerializerBase.cpp \
    QJsonSerializer.cpp

headers.files = $${HEADERS}
headers.path = $$[QT_INSTALL_HEADERS]/QJsonSerializer

target.path = $$[QT_INSTALL_LIBS]

features.files = jsonserializer.prf
features.path = $$[QMAKE_MKSPECS]/features

INSTALLS += headers target features

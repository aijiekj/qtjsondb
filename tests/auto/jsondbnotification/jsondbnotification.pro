TEMPLATE = app
TARGET = tst_jsondbnotification
DEPENDPATH += .
INCLUDEPATH += .

QT = core network testlib gui declarative jsondbcompat-private
CONFIG -= app_bundle
CONFIG += testcase

include($$PWD/../../shared/shared.pri)
include($$PWD/../../../src/3rdparty/qjson/qjson.pri)

DEFINES += JSONDB_DAEMON_BASE=\\\"$$QT.jsondb.bins\\\"
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += testjsondbnotification.h
SOURCES += testjsondbnotification.cpp

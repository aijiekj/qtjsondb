load(qt_module)

TEMPLATE = lib
CONFIG += qt plugin

isEmpty(TARGETPATH) {
    error("qimportbase.pri: You must provide a TARGETPATH!")
}
isEmpty(TARGET) {
    error("qimportbase.pri: You must provide a TARGET!")
}

mac {
    CONFIG(debug, debug|release) {
        QMLDIRFILE = $${_PRO_FILE_PWD_}/qmldir_debug
    } else {
        QMLDIRFILE = $${_PRO_FILE_PWD_}/qmldir
    }
} else {
    QMLDIRFILE = $${_PRO_FILE_PWD_}/qmldir
}
copy2build.input = QMLDIRFILE
copy2build.output = $$QT.jsondbcompat.imports/$$TARGETPATH/qmldir
!contains(TEMPLATE_PREFIX, vc):copy2build.variable_out = PRE_TARGETDEPS
copy2build.commands = $$QMAKE_COPY ${QMAKE_FILE_IN} ${QMAKE_FILE_OUT}
copy2build.name = COPY ${QMAKE_FILE_IN}
copy2build.CONFIG += no_link
# `clean' should leave the build in a runnable state, which means it shouldn't delete qmldir
copy2build.CONFIG += no_clean
QMAKE_EXTRA_COMPILERS += copy2build

TARGET = $$qtLibraryTarget($$TARGET)
contains(QT_CONFIG, reduce_exports):CONFIG += hide_symbols

CONFIG += qt_targets

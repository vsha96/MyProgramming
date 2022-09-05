QT += quick

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#CONFIG += c++1z \
#    c++17

SOURCES += \
        airport.cpp \
        appengine.cpp \
        flight_request.cpp \
        flightcontrolsystem.cpp \
        main.cpp \
        qairportmodel.cpp \
        qrequestsmodel.cpp \
        runway.cpp \
        testmodel.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    csv.h \
    airport.h \
    appengine.h \
    flight_request.h \
    flightcontrolsystem.h \
    qairportmodel.h \
    qrequestsmodel.h \
    runway.h \
    testmodel.h

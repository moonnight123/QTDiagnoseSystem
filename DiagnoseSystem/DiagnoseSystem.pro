QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    departmenteditview.cpp \
    departmentview.cpp \
    doctoreditview.cpp \
    doctorinformationview.cpp \
    doctorpatienteditview.cpp \
    doctorpatientview.cpp \
    doctorview.cpp \
    historyview.cpp \
    idatebase.cpp \
    loginview.cpp \
    main.cpp \
    masterview.cpp \
    patienteditview.cpp \
    patientview.cpp \
    registerview.cpp \
    welcomeview.cpp \
    welcondoctorview.cpp

HEADERS += \
    departmenteditview.h \
    departmentview.h \
    doctoreditview.h \
    doctorinformationview.h \
    doctorpatienteditview.h \
    doctorpatientview.h \
    doctorview.h \
    historyview.h \
    idatebase.h \
    loginview.h \
    masterview.h \
    patienteditview.h \
    patientview.h \
    registerview.h \
    welcomeview.h \
    welcondoctorview.h

FORMS += \
    departmenteditview.ui \
    departmentview.ui \
    doctoreditview.ui \
    doctorinformationview.ui \
    doctorpatienteditview.ui \
    doctorpatientview.ui \
    doctorview.ui \
    historyview.ui \
    loginview.ui \
    masterview.ui \
    patienteditview.ui \
    patientview.ui \
    registerview.ui \
    welcomeview.ui \
    welcondoctorview.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resource.qrc

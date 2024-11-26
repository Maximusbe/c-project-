QT       += core gui widgets printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    MathException.cpp \
    calculate.cpp \
    calculator.cpp \
    charStack.cpp \
    converter.cpp \
    equationValidation.cpp \
    main.cpp \
    calc6.cpp \
    numStack.cpp \
    priority.cpp \
    qcustomplot.cpp \
    solver.cpp \
    superStack.cpp

HEADERS += \
    calc6.h \
    calculator.h \
    qcustomplot.h

FORMS += \
    calc6.ui

INCLUDEPATH += "C:/Users/pc444/Documents/calc6"

QMAKE_CXXFLAGS += /bigobj # needed to build with the exprtk header


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

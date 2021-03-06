#-------------------------------------------------
#
# Project created by QtCreator 2018-07-30T19:38:30
#
#-------------------------------------------------

QT       += core gui widgets quick

TARGET = TestiMy
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    testitem.cpp \
    test.cpp \
    testitemwidget.cpp \
    testexaminedialog.cpp \
    testcreatedialog.cpp \
    testitemcreatewidget.cpp \
    createaccountform.cpp \
    account.cpp \
    loginform.cpp \
    accountslist.cpp \
    authorizationdialog.cpp \
    testlistmodel.cpp \
    createwindow.cpp \
    treecategory.cpp \
    changepassworddialog.cpp \
    manageaccountsdialog.cpp \
    accountslistmodel.cpp \
    changeaccountdialog.cpp \
    accountsstatsdialog.cpp \
    testitemwidget2.cpp \
    timer.cpp \
    treeitem.cpp \
    treemodel.cpp \
    testcreatecategory.cpp

HEADERS += \
        mainwindow.h \
    testitem.h \
    test.h \
    testitemwidget.h \
    testexaminedialog.h \
    testcreatedialog.h \
    testitemcreatewidget.h \
    createaccountform.h \
    account.h \
    loginform.h \
    accountslist.h \
    authorizationdialog.h \
    globals.h \
    testlistmodel.h \
    createwindow.h \
    treecategory.h \
    changepassworddialog.h \
    manageaccountsdialog.h \
    accountslistmodel.h \
    changeaccountdialog.h \
    accountsstatsdialog.h \
    testitemwidget2.h \
    timer.h \
    treeitem.h \
    treemodel.h \
    testcreatecategory.h

FORMS += \
        mainwindow.ui \
    testexaminedialog.ui \
    testcreatedialog.ui \
    testitemcreatewidget.ui \
    createaccountform.ui \
    loginform.ui \
    authorizationdialog.ui \
    createwindow.ui \
    changepassworddialog.ui \
    manageaccountsdialog.ui \
    changeaccountdialog.ui \
    accountsstatsdialog.ui \
    testitemwidget2.ui \
    testcreatecategory.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    stylesheets/authorization.css \
    stylesheets/main.qss \
    stylesheets/testexaminedialog.qss \
    stylesheets/testitemwidget.qss \
    stylesheets/createwindows.qss \
    stylesheets/testitemcreatewidget.qss

RESOURCES += \
    res.qrc

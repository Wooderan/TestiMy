#include "mainwindow.h"
#include <QApplication>
#include <QFontDatabase>
#include <QMessageBox>
#include "test.h"
#include "testitem.h"
#include "testitemwidget.h"
#include "testexaminedialog.h"
#include "testcreatedialog.h"
#include "testitemcreatewidget.h"
#include "authorizationdialog.h"
#include "createwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFontDatabase::addApplicationFont(":/fonts/fonts/Anton-Regular.ttf");
    AuthorizationDialog authorize;
    Account acc;
    if (authorize.exec() == QDialog::Accepted) {
        acc = authorize.getCurr_account();
        if (acc.getPermission() == Account::Teacher) {
            CreateWindow w(acc);
            w.show();
            return a.exec();
        }else{
            MainWindow w(acc);
            w.show();
            return a.exec();
        }
    }

//    TestCreateDialog dialog;
//    dialog.exec();
//    Test test = dialog.getTest();
//    qDebug() << "";

    return 0;
//    TestItemCreateWidget widget;
//    widget.show();
//    a.exec();
//    TestItem item = widget.getItem();

//    TestItemCreateWidget widget2;
//    widget2.show();
//    a.exec();
//    TestItem item2 = widget2.getItem();

//    test.setName("Test");
//    test.addQuestion(item);
//    test.addQuestion(item2);
//    test.setTime(QTime(0,0,10));

//    TestCreateDialog create_dialog;
//    create_dialog.setWindowState(Qt::WindowMaximized);
//    create_dialog.exec();
//    Test test = create_dialog.getTest();
//    if(!test.Save())
//        qDebug() << "Save failed";

//    Test test2;
//    if (!test2.Load(test.getName())) {
//        qDebug() << "Load failed";
//    }

//    TestExamineDialog dialog(test2);
//    return dialog.exec();




}

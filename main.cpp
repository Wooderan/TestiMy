#include "mainwindow.h"
#include <QApplication>
#include "test.h"
#include "testitem.h"
#include "testitemwidget.h"
#include "testexaminedialog.h"
#include "testitemcreatewidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

    TestItemCreateWidget widget;
    widget.show();
    a.exec();
    TestItem item = widget.getItem();

    TestItemCreateWidget widget2;
    widget2.show();
    a.exec();
    TestItem item2 = widget2.getItem();

    Test test;
    test.setName("Test");
    test.addQuestion(item);
    test.addQuestion(item2);
    test.setTime(QTime(0,0,10));
    if(!test.Save())
        qDebug() << "Save failed";

    Test test2;
    if (!test2.Load("Test")) {
        qDebug() << "Load failed";
    }

    TestExamineDialog dialog(test2);
    return dialog.exec();


//    return a.exec();
}

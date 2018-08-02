#include "mainwindow.h"
#include <QApplication>
#include "test.h"
#include "testitem.h"
#include "testitemwidget.h"
#include "testexaminedialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

    TestItem item("What?");
    item.addVar(false, "what1");
    item.addVar(false, "what2");
    item.addVar(true, "what3");
    item.addVar(false, "what4");
    TestItem item2("Where?");
    item2.addVar(false, "where1");
    item2.addVar(false, "where2");
    item2.addVar(true, "where3");
    item2.addVar(false, "where4");

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

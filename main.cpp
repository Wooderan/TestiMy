#include "mainwindow.h"
#include <QApplication>
#include "test.h"
#include "testitem.h"
#include "testitemwidget.h"
#include "testexaminedialog.h"
#include "testcreatedialog.h"
#include "testitemcreatewidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

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

    TestCreateDialog create_dialog;
    create_dialog.setWindowState(Qt::WindowMaximized);
    create_dialog.exec();
    Test test = create_dialog.getTest();
    if(!test.Save())
        qDebug() << "Save failed";

    Test test2;
    if (!test2.Load(test.getName())) {
        qDebug() << "Load failed";
    }

    TestExamineDialog dialog(test2);
    return dialog.exec();


//    return a.exec();
}

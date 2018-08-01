#include "mainwindow.h"
#include <QApplication>
#include "testitem.h"
#include "testitemwidget.h"

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

    TestItemWidget widget(item);

    widget.show();

    return a.exec();
}

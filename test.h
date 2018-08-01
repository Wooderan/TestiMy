#ifndef TEST_H
#define TEST_H

#include <QQuickItem>
#include "testitem.h"

class Test
{
protected:
    QList<TestItem> questions;
public:
    Test();
    TestItem& at(int n);
    void addQuestion(QString _str);
    void addQuestion(TestItem _question);

signals:

public slots:
};

#endif // TEST_H

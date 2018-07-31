#ifndef TEST_H
#define TEST_H

#include <QQuickItem>
#include "testitem.h"

class Test : public QQuickItem
{
    Q_OBJECT
protected:
    QList<TestItem> questions;
public:
    Test();
    TestItem& at(int n);
    void addQuestion(QString _str, int _n = 0);

signals:

public slots:
};

#endif // TEST_H

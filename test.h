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
    TestItem at(size_t n)const;
    void addQuestion(QString _str);
    void addQuestion(TestItem _question);
    size_t getN()const;

signals:

public slots:
};

#endif // TEST_H

#ifndef TEST_H
#define TEST_H

#include <QQuickItem>
#include <QTime>
#include "testitem.h"

class Test
{
protected:
    QList<TestItem> questions;
    QString name;
    QString descripton;
    QTime time;
public:
    Test();
    TestItem at(size_t n)const;
    void addQuestion(QString _str);
    void addQuestion(TestItem _question);
    size_t getN()const;

    QString getName() const;
    void setName(const QString &value);

    QString getDescripton() const;
    void setDescripton(const QString &value);

    QTime getTime() const;
    void setTime(const QTime &value);

signals:

public slots:
};

#endif // TEST_H

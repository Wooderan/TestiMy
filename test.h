#ifndef TEST_H
#define TEST_H

#include <QQuickItem>
#include <QTime>
#include "testitem.h"
#include "globals.h"


class Test
{
protected:
    QList<TestItem> questions;
    QString name;
    QString descripton;
    QTime time;
public:
    Test();
    ~Test();
    TestItem& at(size_t n);
    TestItem at(size_t n)const;
    void addQuestion(QString _str);
    void addQuestion(TestItem _question);
    size_t getN()const;

    QString& getName();
    QString getName()const;
    void setName(const QString &value);

    QString& getDescripton();
    QString getDescripton()const;
    void setDescripton(const QString &value);

    QTime& getTime();
    QTime getTime()const;
    void setTime(const QTime &value);

    bool Save();
    bool Load(QString _fileName);

signals:

public slots:
};
Q_DECLARE_METATYPE( Test )

#endif // TEST_H

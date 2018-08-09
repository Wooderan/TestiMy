#ifndef TEST_H
#define TEST_H

#include <QFileInfo>
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
    QString category;
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

    QString& getCategory();
    QString getCategory() const;
    void setCategory(const QString &value);

    bool Save() const;
    bool Export(const QString &test_file_name) const;
    bool Load(QString _fileName);
    bool Delete() const;

    friend QDataStream& operator<<(QDataStream& ostream, const Variant& var);
    friend QDataStream& operator>>(QDataStream& istream, Variant& var);
    friend QDataStream& operator<<(QDataStream& ostream, const TestItem& testitem);
    friend QDataStream& operator>>(QDataStream& istream, TestItem& testitem);
    friend QDataStream& operator<<(QDataStream& ostream, const Test& test);
    friend QDataStream& operator>>(QDataStream& istream, Test& test);

    friend bool operator==(const Test& _left, const Test& _right);

signals:

public slots:
};
Q_DECLARE_METATYPE( Test )

class find_dir_name
{
    QString needle;
public:
    find_dir_name(QString _needle);
    bool operator()(QFileInfo _info);
};

#endif // TEST_H

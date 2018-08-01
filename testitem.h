#ifndef TESTITEM_H
#define TESTITEM_H

#include <QString>
#include <QList>

struct Variant{
    Variant();
    Variant(bool _correct, QString _answer);
    bool correct;
    QString answer;
};

class TestItem
{
protected:
    QString question;
    QList<Variant> variants;
public:
    TestItem(QString _str);
    const QString &getQuestion() const;
    void setQuestion(const QString &value);
    const Variant &at(size_t n)const;
    void addVar(bool _correct, QString _answ);
    size_t getN()const;
};

#endif // TESTITEM_H

#ifndef TESTITEM_H
#define TESTITEM_H

#include <QString>
#include <vector>

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
    std::vector<Variant> variants;
public:
    TestItem(QString _str, int _n = 0);
    const QString &getQuestion() const;
    void setQuestion(const QString &value);
    const Variant &at(size_t n);
    void addVar(bool _correct, QString _answ);
    size_t getN();
};

#endif // TESTITEM_H

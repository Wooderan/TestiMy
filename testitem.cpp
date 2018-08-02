#include "testitem.h"


Variant::Variant()
{}
Variant::Variant(bool _correct, QString _answer)
    :correct(_correct), answer(_answer)
{}
TestItem::TestItem()
{

}

TestItem::TestItem(QString _str)
    :question(_str)
{}

Variant TestItem::at(size_t n)const
{
    return variants.at(n);
}

void TestItem::addVar(bool _correct, QString _answ)
{
    variants.push_back(Variant(_correct, _answ));
}

void TestItem::addVar(Variant _var)
{
    variants.push_back(_var);
}

size_t TestItem::getN() const
{
    return variants.size();
}

QString &TestItem::getQuestion()
{
    return question;
}

QString TestItem::getQuestion() const
{
    return question;
}

void TestItem::setQuestion(const QString &value)
{
    question = value;
}


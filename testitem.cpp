#include "testitem.h"


Variant::Variant()
{}
Variant::Variant(bool _correct, QString _answer)
    :correct(_correct), answer(_answer)
{}
TestItem::TestItem(QString _str)
    :question(_str)
{}

const Variant &TestItem::at(size_t n) const
{
    return variants.at(n);
}

void TestItem::addVar(bool _correct, QString _answ)
{
    variants.push_back(Variant(_correct, _answ));
}

size_t TestItem::getN() const
{
    return variants.size();
}

const QString& TestItem::getQuestion() const
{
    return question;
}

void TestItem::setQuestion(const QString &value)
{
    question = value;
}


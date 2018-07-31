#include "testitem.h"


Variant::Variant(bool _correct, QString _answer)
    :correct(_correct), answer(_answer)
{}
TestItem::TestItem(QString _str, int _n)
    :question(_str), variants(static_cast<size_t>(_n))
{}

const Variant &TestItem::at(size_t n)
{
    return variants.at(n);
}

void TestItem::addVar(bool _correct, QString _answ)
{
    variants.push_back(Variant(_correct, _answ));
}

size_t TestItem::getN()
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


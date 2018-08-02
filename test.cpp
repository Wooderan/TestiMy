#include "test.h"
#include <cassert>

QString Test::getName() const
{
    return name;
}

void Test::setName(const QString &value)
{
    name = value;
}

QString Test::getDescripton() const
{
    return descripton;
}

void Test::setDescripton(const QString &value)
{
    descripton = value;
}

QTime Test::getTime() const
{
    return time;
}

void Test::setTime(const QTime &value)
{
    time = value;
}

Test::Test()
{

}

TestItem Test::at(size_t n)const
{
    assert(n >= 0 && n < questions.size());
    return questions[n];
}

void Test::addQuestion(QString _str)
{
    questions.append(TestItem(_str));
}

void Test::addQuestion(TestItem _question)
{
    questions.append(_question);
}

size_t Test::getN() const
{
    return static_cast<size_t>(questions.count());
}

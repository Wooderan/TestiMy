#include "test.h"
#include <cassert>

Test::Test()
{

}

TestItem &Test::at(int n)
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

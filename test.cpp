#include "test.h"
#include <QDir>
#include <cassert>

QString &Test::getName()
{
    return name;
}

QString Test::getName() const
{
    return name;
}

void Test::setName(const QString &value)
{
    name = value;
}

QString &Test::getDescripton()
{
    return descripton;
}

QString Test::getDescripton() const
{
    return descripton;
}

void Test::setDescripton(const QString &value)
{
    descripton = value;
}

QTime &Test::getTime()
{
    return time;
}

QTime Test::getTime() const
{
    return time;
}

void Test::setTime(const QTime &value)
{
    time = value;
}

class find_dir_name
{
    QString needle;
public:
    find_dir_name(QString _needle):needle(_needle){}
    bool operator()(QFileInfo _info){
        if (_info.isDir() && _info.fileName() == needle) return true;
        return false;
    }
};

QDataStream& operator<<(QDataStream& ostream, const Variant& var)
{
    ostream << var.correct << var.answer;
    return ostream;
}
QDataStream& operator>>(QDataStream& istream, Variant& var)
{
    istream >> var.correct >> var.answer;
    return istream;
}

QDataStream& operator<<(QDataStream& ostream, const TestItem& testitem)
{
    ostream << testitem.getQuestion() << static_cast<int>(testitem.getN());
    for (size_t i = 0; i < testitem.getN(); i++) {
        ostream << testitem.at(i);
    }
    return ostream;
}
QDataStream& operator>>(QDataStream& istream, TestItem& testitem)
{
    istream >> testitem.getQuestion();
    Variant variant;
    int n;
    istream >> n;
    for (int i = 0; i < n; i++) {
        istream >> variant;
        testitem.addVar(variant);
    }
    return istream;
}

QDataStream& operator<<(QDataStream& ostream, const Test& test)
{
    ostream << test.getName() << test.getDescripton() << test.getTime();
    ostream << static_cast<int>(test.getN());
    for (size_t i = 0; i < test.getN(); i++) {
        ostream << test.at(i);
    }
    return ostream;
}
QDataStream& operator>>(QDataStream& istream, Test& test)
{
    istream >> test.getName() >> test.getDescripton() >> test.getTime();
    int n;
    istream >> n;
    for (size_t i = 0; i < static_cast<size_t>(n); i++) {
        TestItem item;
        istream >> item;
        test.addQuestion(item);
    }
    return istream;
}
//QTextStream& operator<<(QTextStream& ostream, const Variant& var)
//{
//    ostream << var.correct << var.answer;
//    return ostream;
//}
//QTextStream& operator>>(QTextStream& istream, Variant& var)
//{
////    istream >> var.correct >> var.answer;
//    return istream;
//}

//QTextStream& operator<<(QTextStream& ostream, const TestItem& testitem)
//{
//    ostream << testitem.getQuestion();
//    for (size_t i = 0; i < testitem.getN(); i++) {
//        ostream << testitem.at(i);
//    }
//    return ostream;
//}
//QTextStream& operator>>(QTextStream& istream, TestItem& testitem)
//{
//    istream >> testitem.getQuestion();
//    Variant variant;
//    for (size_t i = 0; i < testitem.getN(); i++) {
//        istream >> variant;
//        testitem.addVar(variant);
//    }
//    return istream;
//}

//QTextStream& operator<<(QTextStream& ostream, const Test& test)
//{
//    ostream << test.getName() << test.getDescripton() << test.getTime().toString();
//    for (size_t i = 0; i < test.getN(); i++) {
//        ostream << test.at(i);
//    }
//    return ostream;
//}
//QTextStream& operator>>(QTextStream& istream, Test& test)
//{
//    istream >> test.getName() >> test.getDescripton() >> test.getTime().toString();
//    for (size_t i = 0; i < test.getN(); i++) {
//        istream >> test.at(i);
//    }
//    return istream;
//}

bool Test::Save()
{
    QDir Dir(QCoreApplication::applicationDirPath());
    if(!Dir.exists()) return false;
    QFileInfoList list = Dir.entryInfoList();
    auto it = std::find_if(list.begin(),list.end(), find_dir_name(DEFAULT_DIR_NAME));
    if (it == list.end()) {//we dont find default tests folder
        Dir.mkdir(DEFAULT_DIR_NAME);
    }
    Dir.cd(DEFAULT_DIR_NAME);

    QString test_file_name = QString("%1/%2.testimy").arg(Dir.path()).arg(this->getName());
    QFile test_file(test_file_name);
    if (!test_file.open(QIODevice::WriteOnly)) return false;

    QDataStream test_stream(&test_file);
    test_stream << *this;
//    QTextStream test_stream(&test_file);
//    test_stream << *this;
    test_file.close();
    return true;
}

bool Test::Load(QString _fileName)
{
    QDir Dir(QCoreApplication::applicationDirPath());
    if(!Dir.exists()) return false;
    QFileInfoList list = Dir.entryInfoList();
    auto it = std::find_if(list.begin(),list.end(), find_dir_name(DEFAULT_DIR_NAME));
    if (it == list.end()) //we dont find default tests folder
        return false;
    Dir.cd(DEFAULT_DIR_NAME);

    QString test_file_name = QString("%1/%2.testimy").arg(Dir.path()).arg(_fileName);
    QFile test_file(test_file_name);
    if (!test_file.open(QIODevice::ReadOnly)) return false;

    QDataStream test_stream(&test_file);
    test_stream >> *this;
    test_file.close();
    return true;
}

Test::Test()
{

}

Test::~Test()
{

}

TestItem &Test::at(size_t n)
{
    assert(n < static_cast<size_t>(questions.size()));
    return questions[static_cast<int>(n)];
}

TestItem Test::at(size_t n) const
{
    assert(n < static_cast<size_t>(questions.size()));
    return questions[static_cast<int>(n)];
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

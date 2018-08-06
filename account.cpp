#include "account.h"

Account::Account()
{

}

const QString Account::RoleStr[] = {"Teacher", "Student"};

QString Account::getLogin() const
{
    return login;
}

QString &Account::getLogin()
{
    return login;
}

void Account::setLogin(const QString &value)
{
    login = value;
}

uint Account::getPassword() const
{
    return password;
}

uint &Account::getPassword()
{
    return password;
}

void Account::setPassword(const QString &value)
{
    password = qHash(value);
}

void Account::setResult(QString _name, int _points)
{
    result_table[_name] = _points;
}

int Account::getResult(QString _name) const
{
    if (result_table.contains(_name))
        return result_table[_name];
    return NO_RESULT;
}

QMap<QString, int>::const_iterator Account::begin()const
{
    return result_table.cbegin();
}

QMap<QString, int>::const_iterator Account::end()const
{
    return result_table.end();

}

const QMap<QString, int> &Account::getMap()const
{
    return result_table;
}

Account::Role Account::getPermission() const
{
    return Permission;
}

Account::Role &Account::getPermission()
{
    return Permission;
}

void Account::setPermission(const Role &value)
{
    Permission = value;
}

QString Account::getName() const
{
    return name;
}

QString &Account::getName()
{
    return name;
}

void Account::setName(const QString &value)
{
    name = value;
}

QString Account::getAdress() const
{
    return adress;
}

QString &Account::getAdress()
{
    return adress;
}

void Account::setAdress(const QString &value)
{
    adress = value;
}

QString Account::getPhone_number() const
{
    return phone_number;
}

QString &Account::getPhone_number()
{
    return phone_number;
}

void Account::setPhone_number(const QString &value)
{
    phone_number = value;
}

QDataStream& operator<<(QDataStream& ostream, const Account& var)
{
    ostream << var.getLogin() << var.getPassword() << var.getPermission()
            << var.getName() << var.getAdress() << var.getPhone_number();

    ostream << var.result_table;
    return ostream;
}
QDataStream& operator>>(QDataStream& istream, Account& var)
{
    int r;
    istream >> var.getLogin() >> var.getPassword() >> r
                              >> var.getName() >> var.getAdress() >> var.getPhone_number();
    var.setPermission(static_cast<Account::Role>(r));
    istream >> var.result_table;
    return istream;
}



find_account_password::find_account_password(uint _pass):password(_pass){}

bool find_account_password::operator()(const Account &_acc){
    if (_acc.getPassword() == password) return true;
    return false;
}

find_account_login::find_account_login(QString _login):login(_login){}

bool find_account_login::operator()(const Account &_acc){
    if (_acc.getLogin() == login) return true;
    return false;
}

lookup_account_results::lookup_account_results()
{
    count = 0;
    excelent_r = 0;
    avarage_r = 0;
    bad_r = 0;
    sum = 0;
}

int lookup_account_results::getCount() const
{
    return count;
}

int lookup_account_results::getExcelent() const
{
    return excelent_r;
}

int lookup_account_results::getAvarage() const
{
    return avarage_r;
}

int lookup_account_results::getBad() const
{
    return bad_r;
}

QMap<QString,int> lookup_account_results::getPassedTests() const
{
    return passedTests;
}

bool lookup_account_results::operator()(const Account &_acc)
{
    for (auto i = _acc.begin(); i != _acc.end(); i++) {
        count++;
        sum += *i;
        if (*i > 9)
            excelent_r++;
        else if(*i > 6)
            avarage_r++;
        else
            bad_r++;
    }
    if (passedTests.isEmpty()) {
        passedTests = _acc.getMap();
    }
    return false;
}

QString lookup_account_results::formLabale()
{
    return QString("Passed tests: %1\n"
                          "Excellent results: %2\n"
                          "Avarage results: %3\n"
                          "Bad results: %4\n"
                          "Avarage mark: %5")
                            .arg(count)
                            .arg(excelent_r)
                            .arg(avarage_r)
                            .arg(bad_r)
            .arg(getAvarageMark());
}

double lookup_account_results::getAvarageMark() const
{
    if (count == 0) return 0;
    else return static_cast<double>(sum)/count;
}

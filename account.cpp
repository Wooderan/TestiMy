#include "account.h"

Account::Account()
{

}

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

QDataStream& operator<<(QDataStream& ostream, const Account& var)
{
    ostream << var.getLogin() << var.getPassword() << var.getPermission();
    return ostream;
}
QDataStream& operator>>(QDataStream& istream, Account& var)
{
    QString str = "QT";
    int r;
    istream >> var.getLogin() >> var.getPassword() >> r;
    var.setPermission(static_cast<Account::Role>(r));

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

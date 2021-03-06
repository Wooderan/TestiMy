#include "accountslist.h"

#include <QCoreApplication>
#include <QDir>
#include <cassert>

AccountsList::AccountsList()
{

}

const Account &AccountsList::at(int i) const
{
    return accounts.at(i);
}

bool AccountsList::checkAccount(const Account &_acc) const
{
    auto it = std::find_if(accounts.begin(), accounts.end(), find_account_login(_acc.getLogin()));
    if (it == accounts.end()) return false;
    else
        return true;
}

bool AccountsList::checkPassword(const Account &_acc) const
{
    auto it = std::find_if(accounts.begin(), accounts.end(), find_account_login(_acc.getLogin()));
    if (it == accounts.end()) return false;
    else if (_acc.getPassword() == it->getPassword() && _acc.getPermission() == it->getPermission()) {
        return true;
    }else
        return false;
}

void AccountsList::addAccount(const Account &_acc)
{
    accounts.push_back(_acc);
}

const Account &AccountsList::getAccount(QString _login) const
{
    auto it = std::find_if(accounts.begin(), accounts.end(), find_account_login(_login));
    assert(it != accounts.end());
    return *it;
}

void AccountsList::deleteAccount(const QString &_login)
{
    auto it = std::find_if(accounts.begin(), accounts.end(), find_account_login(_login));
    accounts.erase(it);
}

int AccountsList::row(const QString &_login)
{
    int i;
    for (i = 0; i < accounts.count(); i++) {
        if (accounts[i].getLogin() == _login) break;
    }
    return i;
}

bool AccountsList::checkTeacher()
{
    bool teacher = false;
    for (int i = 0; i < accounts.count(); i++) {
        if (accounts[i].getPermission() == Account::Teacher){
            teacher = true;
            break;
        }
    }
    return teacher;
}

int AccountsList::getN()const
{
    return accounts.count();
}

bool AccountsList::Save()
{
    QDir Dir(QCoreApplication::applicationDirPath());
    QString account_file_name = QString("%1/%2.testimy").arg(Dir.absolutePath()).arg(DEFAULT_FILE_NAME);
    QFile test_file(account_file_name);
    if (!test_file.open(QIODevice::WriteOnly)) return false;

    QDataStream test_stream(&test_file);
    test_stream << accounts;
    test_file.close();
    return true;
}

bool AccountsList::Load()
{
    QDir Dir(QCoreApplication::applicationDirPath());
    QString account_file_name = QString("%1/%2.testimy").arg(Dir.absolutePath()).arg(DEFAULT_FILE_NAME);
    QFile test_file(account_file_name);
    if (!test_file.open(QIODevice::ReadOnly)) return false;

    QDataStream test_stream(&test_file);
    test_stream >> accounts;
    test_file.close();
    return true;
}

QDataStream &operator >>(QDataStream &istream, QVector<Account> &var)
{
    int n;
    istream >> n;
    for (int i = 0; i < n; i++) {
        Account acc;
        istream >> acc;
        var.push_back(acc);
    }
    return istream;
}

QDataStream &operator <<(QDataStream &ostream, const QVector<Account> &var)
{
    int n = var.count();
    if (n > 0)
        ostream << n;
    for (int i = 0; i < n; i++) {
        ostream << var.at(i);
    }
    return ostream;
}


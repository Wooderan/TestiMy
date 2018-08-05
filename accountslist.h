#ifndef ACCOUNTSLIST_H
#define ACCOUNTSLIST_H

#include <QVector>
#include "account.h"
#include "globals.h"

class AccountsList
{
public:
    AccountsList();
    const Account& at(int i)const;

    bool checkAccount(const Account& _acc)const;
    bool checkPassword(const Account& _acc)const;
    void addAccount(const Account& _acc);
    const Account& getAccount(QString login)const;
    void deleteAccount(const QString& _login);
    int getN()const;
    int row(const QString& _login);
    bool checkTeacher();

    bool Save();
    bool Load();

private:
    QVector<Account> accounts;
};
QDataStream &operator >>(QDataStream &istream, QVector<Account> &var);

QDataStream &operator <<(QDataStream &ostream, const QVector<Account> &var);

#endif // ACCOUNTSLIST_H

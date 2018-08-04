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

    bool Save();
    bool Load();

    friend QDataStream &operator >>(QDataStream &istream, QVector<Account> &var);

    friend QDataStream &operator <<(QDataStream &ostream, const QVector<Account> &var);
private:
    QVector<Account> accounts;
};

#endif // ACCOUNTSLIST_H

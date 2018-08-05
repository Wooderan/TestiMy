#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QWidget>
#include <QHash>



class Account
{
public:
    enum Role{Teacher, Student};
    static const QString RoleStr[];
    static const int NO_RESULT = -1;

    Account();

    QString getLogin() const;
    QString& getLogin();
    void setLogin(const QString &value);

    uint getPassword() const;
    uint& getPassword();
    void setPassword(const QString &value);


    int getResult(QString _name) const;
    void setResult(QString _name, int _points);

    Role getPermission() const;
    Role& getPermission();
    void setPermission(const Role &value);

    friend QDataStream& operator<<(QDataStream& ostream, const Account& var);
    friend QDataStream& operator>>(QDataStream& istream, Account& var);

    QString getName() const;
    QString& getName();
    void setName(const QString &value);

    QString getAdress() const;
    QString& getAdress();
    void setAdress(const QString &value);

    QString getPhone_number() const;
    QString& getPhone_number();
    void setPhone_number(const QString &value);

private:
    QString login;
    uint password;
    Role Permission;
    QString name;
    QString adress;
    QString phone_number;
    QHash<QString, int> result_table;
};

class find_account_login
{
    QString login;
public:
    find_account_login(QString _login);
    bool operator()(const Account& _acc);
};

class find_account_password
{
    uint password;
public:
    find_account_password(uint _pass);
    bool operator()(const Account& _acc);
};
#endif // ACCOUNT_H

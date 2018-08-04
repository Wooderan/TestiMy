#ifndef AUTHORIZATIONSTACKEDWIDGET_H
#define AUTHORIZATIONSTACKEDWIDGET_H

#include <QWidget>
#include <QStackedWidget>
#include "account.h"
#include "createaccountform.h"
#include "loginform.h"

class AuthorizationStackedWidget : public QStackedWidget
{
    Q_OBJECT
public:
    static const int NO_ACCOUNT = 1;
    explicit AuthorizationStackedWidget(QWidget *parent = nullptr);
    bool checkAccount(const Account& _acc)const;
    bool checkPassword(const Account& _acc)const;
    void addAccount(const Account& _acc);


    Account getCurr_account() const;

signals:
    void login_succes(bool);
    void changeIndex(int i);
public slots:
    void login_handler(bool);
    void index_handler(int i);
private:
    QVector<Account> accounts;
    Account curr_account;
    CreateAccountForm *createForm;
    LoginForm *loginForm;
};

#endif // AUTHORIZATIONSTACKEDWIDGET_H

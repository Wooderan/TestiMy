#ifndef AUTHORIZATIONDIALOG_H
#define AUTHORIZATIONDIALOG_H

#include <QDialog>
#include <QStackedWidget>
#include "account.h"
#include "accountslist.h"

namespace Ui {
class AuthorizationDialog;
}

class AuthorizationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AuthorizationDialog(QWidget *parent = nullptr);
    ~AuthorizationDialog();
    Account getCurr_account() const;
    void setCurr_account(const Account &value);

    AccountsList Accounts() const;
    AccountsList& Accounts();

    int getLoginId() const;

    int getCreateId() const;

    void setSubWidget(int id);

public slots:
private:
    Ui::AuthorizationDialog *ui;
    QStackedWidget *widget;
    Account curr_account;
    AccountsList accounts;
    int loginId;
    int createId;
};

#endif // AUTHORIZATIONDIALOG_H

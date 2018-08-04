#include "authorizationstackedwidget.h"

#include <QMessageBox>

AuthorizationStackedWidget::AuthorizationStackedWidget(QWidget *parent) : QStackedWidget(parent)
{
    createForm = new CreateAccountForm(this);
    loginForm = new LoginForm(this);

    this->addWidget(loginForm);
    this->addWidget(createForm);
    this->setCurrentIndex(0);

    QObject::connect(this, &AuthorizationStackedWidget::login_succes, this, &AuthorizationStackedWidget::login_handler);
    QObject::connect(this, &AuthorizationStackedWidget::changeIndex, this, &AuthorizationStackedWidget::index_handler);
}

bool AuthorizationStackedWidget::checkAccount(const Account &_acc) const
{
    auto it = std::find_if(accounts.begin(), accounts.end(), find_account_login(_acc.getLogin()));
    if (it == accounts.end()) return false;
    else
        return true;
}

bool AuthorizationStackedWidget::checkPassword(const Account &_acc) const
{
    auto it = std::find_if(accounts.begin(), accounts.end(), find_account_login(_acc.getLogin()));
    if (it == accounts.end()) return false;
    else if (_acc.getPassword() == it->getPassword()) {
        return true;
    }else
        return false;

}

void AuthorizationStackedWidget::addAccount(const Account &_acc)
{
    accounts.push_back(_acc);
}

void AuthorizationStackedWidget::login_handler(bool success)
{
    if (success) {

    }else
        QMessageBox::critical(this, "Can't login", "Login or password is wrong!");
}

void AuthorizationStackedWidget::index_handler(int i)
{
    this->setCurrentIndex(i);
}

Account AuthorizationStackedWidget::getCurr_account() const
{
    return curr_account;
}

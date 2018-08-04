#include "authorizationdialog.h"
#include "ui_authorizationdialog.h"
#include <QMessageBox>
#include <QVBoxLayout>
#include "loginform.h"
#include "createaccountform.h"

AuthorizationDialog::AuthorizationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AuthorizationDialog)
{
    accounts.Load();
    ui->setupUi(this);
    this->setLayout(new QVBoxLayout(this));
    widget = new QStackedWidget(this);
    this->layout()->addWidget(widget);

    LoginForm *login_form = new LoginForm(this, widget);
    CreateAccountForm *create_form = new CreateAccountForm(this, widget);

    loginId = widget->addWidget(login_form);
    createId = widget->addWidget(create_form);
    setSubWidget(loginId);
}

AuthorizationDialog::~AuthorizationDialog()
{
    delete ui;
}


Account AuthorizationDialog::getCurr_account() const
{
    return curr_account;
}

void AuthorizationDialog::setCurr_account(const Account &value)
{
    curr_account = value;
}

AccountsList AuthorizationDialog::Accounts() const
{
    return accounts;
}

AccountsList &AuthorizationDialog::Accounts()
{
    return accounts;
}

int AuthorizationDialog::getLoginId() const
{
    return loginId;
}

int AuthorizationDialog::getCreateId() const
{
    return createId;
}

void AuthorizationDialog::setSubWidget(int id)
{
    widget->setCurrentIndex(id);
}

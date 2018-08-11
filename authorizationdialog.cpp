#include "authorizationdialog.h"
#include "ui_authorizationdialog.h"
#include <QFile>
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
    CreateAccountForm *create_form = new CreateAccountForm(accounts, this, widget);

    loginId = widget->addWidget(login_form);
    createId = widget->addWidget(create_form);
    setSubWidget(loginId);
//    QObject::connect(this, &QDialog::accepted, this, &QDialog::accept);



    QFile file(":/qss/stylesheets/authorization.css");
    file.open(QFile::ReadOnly);
    QString styleSheet(file.readAll());
    setStyleSheet(styleSheet);
    ensurePolished();
    file.close();
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

void AuthorizationDialog::accept()
{
    if (widget->currentIndex() == 1) {
        curr_account = dynamic_cast<CreateAccountForm*>(widget->currentWidget())->getCurr_account();
    }
    QDialog::accept();
}

#include "createaccountform.h"
#include "ui_createaccountform.h"
#include <QDialogButtonBox>

#include "account.h"
#include "authorizationstackedwidget.h"
#include <QMessageBox>

CreateAccountForm::CreateAccountForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateAccountForm)
{
    ui->setupUi(this);
}

CreateAccountForm::~CreateAccountForm()
{
    delete ui;
}

void CreateAccountForm::on_buttonBox_accepted()
{
    Account acc;
    acc.setLogin(ui->lineEdit_login->text());

    if (ui->lineEdit_pass->text() == ui->lineEdit_repPass->text()) {
        acc.setPassword(ui->lineEdit_pass->text());
    }

    if (ui->radioButton_teacher->isChecked()) acc.setPermission(Account::Teacher);
    else acc.setPermission(Account::Student);

    AuthorizationStackedWidget *parent = dynamic_cast<AuthorizationStackedWidget*>(this->parent());
    if (parent != nullptr && !parent->checkAccount(acc)) {
        parent->addAccount(acc);
        emit parent->login_succes(true);
    }else{
        QMessageBox::critical(this, "Can't create account", "Account with such login exists!");
    }
}

void CreateAccountForm::on_buttonBox_rejected()
{
    AuthorizationStackedWidget *widget = dynamic_cast<AuthorizationStackedWidget*>(this->parent());
    if (widget != nullptr) {
        emit widget->changeIndex(0);
    }
}

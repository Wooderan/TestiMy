#include "createaccountform.h"
#include "ui_createaccountform.h"
#include <QDialogButtonBox>

#include "account.h"
#include <QMessageBox>

CreateAccountForm::CreateAccountForm(AuthorizationDialog *_dialog, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateAccountForm)
{
    ui->setupUi(this);
    dialog = _dialog;
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

    if (dialog != nullptr && !dialog->Accounts().checkAccount(acc)) {
        dialog->Accounts().addAccount(acc);
        dialog->Accounts().Save();
        dialog->setCurr_account(acc);
        dialog->accept();
    }else{
        QMessageBox::critical(this, "Can't create account", "Account with such login exists!");
    }
}

void CreateAccountForm::on_buttonBox_rejected()
{
    dialog->setSubWidget(dialog->getLoginId());
}

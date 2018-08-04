#include "loginform.h"
#include "ui_loginform.h"
#include "authorizationdialog.h"

#include <QMessageBox>

LoginForm::LoginForm(AuthorizationDialog *_dialog, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);
    dialog = _dialog;
}

LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::on_buttonBox_accepted()
{
    Account acc;

    if (ui->lineEdit_login->text().isEmpty()) {
        QMessageBox::critical(this, "Error", "Login is empty");
        return;
    }
    acc.setLogin(ui->lineEdit_login->text());

    if (ui->lineEdit_password->text().isEmpty())
    {
        QMessageBox::critical(this, "Error", "Password is empty");
        return;
    }
    acc.setPassword(ui->lineEdit_password->text());

    if (ui->radioButton_student->isChecked())
        acc.setPermission(Account::Student);
    else
        acc.setPermission(Account::Teacher);

    if (dialog->Accounts().checkAccount(acc)) {
        if (dialog->Accounts().checkPassword(acc)) {
            dialog->accept();
            dialog->setCurr_account(acc);
        }else{
            QMessageBox::critical(this, "Error", "Password or permission is wrong");
            return;
        }
    }else{
        QMessageBox::critical(this, "Error", "Login is wrong");
        return;
    }

}

void LoginForm::on_buttonBox_rejected()
{
    dialog->reject();
}



void LoginForm::on_pushButton_create_clicked()
{
    dialog->setSubWidget(dialog->getCreateId());
}

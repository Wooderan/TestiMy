#include "changepassworddialog.h"
#include "ui_changepassworddialog.h"

#include <QMessageBox>

ChangePasswordDialog::ChangePasswordDialog(const Account &_acc, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangePasswordDialog)
{
    ui->setupUi(this);
    acc = _acc;

    ui->lineEdit_login->setText(acc.getLogin());
}

ChangePasswordDialog::~ChangePasswordDialog()
{
    delete ui;
}

void ChangePasswordDialog::on_buttonBox_accepted()
{
    if (ui->lineEdit_login->text().isEmpty()) {
        QMessageBox::critical(this, "Error", "Login field is empty");
        return;
    }
    acc.setLogin(ui->lineEdit_login->text());

    if (ui->lineEdit_password->text().isEmpty()) {
        QMessageBox::critical(this, "Error", "Password field is empty");
        return;
    }
    acc.setPassword(ui->lineEdit_password->text());
    this->accept();
}

void ChangePasswordDialog::on_buttonBox_rejected()
{
    this->reject();
}

Account ChangePasswordDialog::getAcc() const
{
    return acc;
}

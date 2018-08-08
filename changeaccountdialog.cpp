#include "changeaccountdialog.h"
#include "ui_changeaccountdialog.h"

#include <QMessageBox>

ChangeAccountDialog::ChangeAccountDialog(const Account &_acc, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeAccountDialog)
{
    ui->setupUi(this);
    acc = _acc;
    ui->lineEdit_login->setText(acc.getLogin());
    ui->lineEdit_name->setText(acc.getName());
    ui->lineEdit_adress->setText(acc.getAdress());
    ui->lineEdit_phoneNumber->setText(acc.getPhone_number());
}

ChangeAccountDialog::~ChangeAccountDialog()
{
    delete ui;
}

Account ChangeAccountDialog::getAcc() const
{
    return acc;
}

void ChangeAccountDialog::on_pushButton_cancel_clicked()
{
    QDialog::reject();
}

void ChangeAccountDialog::on_pushButton_change_clicked()
{
    if (ui->lineEdit_login->text().isEmpty())
    {
        QMessageBox::critical(this, "Error", "Login field is empty");
        return;
    }
    acc.setLogin(ui->lineEdit_login->text());

    if (ui->lineEdit_password->text().isEmpty())
    {
        QMessageBox::critical(this, "Error", "Password field is empty");
        return;
    }
    acc.setPassword(ui->lineEdit_password->text());

    if (ui->lineEdit_name->text().isEmpty())
    {
        QMessageBox::critical(this, "Error", "Name field is empty");
        return;
    }
    acc.setName(ui->lineEdit_name->text());

    if (ui->lineEdit_adress->text().isEmpty())
    {
        QMessageBox::critical(this, "Error", "Adress field is empty");
        return;
    }
    acc.setAdress(ui->lineEdit_adress->text());

    if (ui->lineEdit_phoneNumber->text().isEmpty())
    {
        QMessageBox::critical(this, "Error", "Phone number field is empty");
        return;
    }
    acc.setPhone_number(ui->lineEdit_phoneNumber->text());

    QDialog::accept();
}

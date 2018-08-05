#include "createaccountform.h"
#include "ui_createaccountform.h"
#include <QDialogButtonBox>

#include "account.h"
#include "accountslist.h"
#include <QMessageBox>

CreateAccountForm::CreateAccountForm(const AccountsList& _list, QDialog *_dialog, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateAccountForm)
{
    ui->setupUi(this);
    list = _list;
    dialog = _dialog;
    QObject::connect(ui->radioButton_student, &QRadioButton::clicked, this, &CreateAccountForm::on_radioButton_teacher_clicked);
}

CreateAccountForm::~CreateAccountForm()
{
    delete ui;
}

void CreateAccountForm::on_buttonBox_accepted()
{
    Account acc;
    if (ui->lineEdit_login->text().isEmpty()) {
        QMessageBox::critical(this, "Error", "Login field is empty");
        return;
    }
    acc.setLogin(ui->lineEdit_login->text());

    if (ui->lineEdit_pass->text().isEmpty() || ui->lineEdit_repPass->text().isEmpty()) {
        QMessageBox::critical(this, "Error", "Password fields are empty");
        return;
    }
    if (ui->lineEdit_pass->text() == ui->lineEdit_repPass->text()) {
        acc.setPassword(ui->lineEdit_pass->text());
    }else{
        QMessageBox::critical(this, "Error", "Password fields aren't equal");
        return;
    }

    if (ui->radioButton_teacher->isChecked()){
        if (list.checkTeacher()) {
            QMessageBox::critical(this, "Error", "Can't create another teacher!");
            return;
        }
        acc.setPermission(Account::Teacher);
        acc.setName("Teacher Teacherovich");
    }
    else{
        acc.setPermission(Account::Student);
        if (ui->lineEdit_name->text().isEmpty()) {
            QMessageBox::critical(this, "Error", "Name field is empty");
            return;
        }
        acc.setName(ui->lineEdit_name->text());

        if (ui->lineEdit_adress->text().isEmpty()) {
            QMessageBox::critical(this, "Error", "Adress field is empty");
            return;
        }
        acc.setAdress(ui->lineEdit_adress->text());
        if (ui->lineEdit_phoneNumber->text().isEmpty()) {
            QMessageBox::critical(this, "Error", "Phone field is empty");
            return;
        }
        acc.setPhone_number(ui->lineEdit_phoneNumber->text());
    }

    if (!list.checkAccount(acc)) {
        list.addAccount(acc);
        list.Save();
        curr_account = acc;
        dialog->accept();
    }else{
        QMessageBox::critical(this, "Can't create account", "Account with such login exists!");
    }
}

void CreateAccountForm::on_buttonBox_rejected()
{
    QStackedWidget *widget = dynamic_cast<QStackedWidget*>(parent());
    if (widget != nullptr) {
        widget->setCurrentIndex(0);
    }else
        dialog->reject();
}

void CreateAccountForm::on_radioButton_teacher_clicked()
{
    QRadioButton *btn = dynamic_cast<QRadioButton*>(sender());
    if (btn->objectName() == "radioButton_teacher") {
        ui->lineEdit_name->setEnabled(false);
        ui->lineEdit_adress->setEnabled(false);
        ui->lineEdit_phoneNumber->setEnabled(false);
    }else{
        ui->lineEdit_name->setEnabled(true);
        ui->lineEdit_adress->setEnabled(true);
        ui->lineEdit_phoneNumber->setEnabled(true);
    }
}

Account CreateAccountForm::getCurr_account() const
{
    return curr_account;
}

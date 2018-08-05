#ifndef CREATEACCOUNTFORM_H
#define CREATEACCOUNTFORM_H

#include <QWidget>
#include "authorizationdialog.h"

namespace Ui {
class CreateAccountForm;
}

class CreateAccountForm : public QWidget
{
    Q_OBJECT

public:
    explicit CreateAccountForm(const AccountsList &_list, QDialog* _dialog, QWidget *parent = nullptr);
    ~CreateAccountForm();

    Account getCurr_account() const;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_radioButton_teacher_clicked();

private:
    Ui::CreateAccountForm *ui;
    AccountsList list;
    Account curr_account;
    QDialog *dialog;
};

#endif // CREATEACCOUNTFORM_H

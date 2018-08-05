#ifndef CHANGEPASSWORDDIALOG_H
#define CHANGEPASSWORDDIALOG_H

#include <QDialog>
#include "account.h"

namespace Ui {
class ChangePasswordDialog;
}

class ChangePasswordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChangePasswordDialog(const Account& acc, QWidget *parent = nullptr);
    ~ChangePasswordDialog();

    Account getAcc() const;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::ChangePasswordDialog *ui;
    Account acc;
};

#endif // CHANGEPASSWORDDIALOG_H

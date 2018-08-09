#ifndef ACCOUNTSSTATSDIALOG_H
#define ACCOUNTSSTATSDIALOG_H

#include <QDialog>
#include "account.h"

namespace Ui {
class AccountsStatsDialog;
}

class AccountsStatsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AccountsStatsDialog(const Account& _acc, QWidget *parent = nullptr);
    ~AccountsStatsDialog();

private:
    Ui::AccountsStatsDialog *ui;
};

#endif // ACCOUNTSSTATSDIALOG_H

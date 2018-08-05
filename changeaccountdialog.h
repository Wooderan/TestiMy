#ifndef CHANGEACCOUNTDIALOG_H
#define CHANGEACCOUNTDIALOG_H

#include <QDialog>
#include <account.h>

namespace Ui {
class ChangeAccountDialog;
}

class ChangeAccountDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeAccountDialog(const Account& _acc, QWidget *parent = nullptr);
    ~ChangeAccountDialog();

    Account getAcc() const;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::ChangeAccountDialog *ui;
    Account acc;
};

#endif // CHANGEACCOUNTDIALOG_H

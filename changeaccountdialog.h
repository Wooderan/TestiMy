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

    void on_pushButton_cancel_clicked();

    void on_pushButton_change_clicked();

private:
    Ui::ChangeAccountDialog *ui;
    Account acc;
};

#endif // CHANGEACCOUNTDIALOG_H

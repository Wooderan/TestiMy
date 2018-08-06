#ifndef MANAGEACCOUNTSDIALOG_H
#define MANAGEACCOUNTSDIALOG_H

#include <QDialog>
#include <QItemSelection>
#include "accountslistmodel.h"
#include "accountslist.h"

namespace Ui {
class ManageAccountsDialog;
}

class ManageAccountsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ManageAccountsDialog(QWidget *parent = nullptr);
    ~ManageAccountsDialog();

public slots:
    void selection_handler(const QItemSelection &selected, const QItemSelection &deselected);
private slots:
    void on_pushButton_create_clicked();

    void on_pushButton_delete_clicked();

    void on_pushButton_change_clicked();

private:
    Ui::ManageAccountsDialog *ui;
    AccountsListModel *model;
    AccountsList *list;
};

#endif // MANAGEACCOUNTSDIALOG_H

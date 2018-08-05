#include "manageaccountsdialog.h"
#include "ui_manageaccountsdialog.h"

ManageAccountsDialog::ManageAccountsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManageAccountsDialog)
{
    ui->setupUi(this);
    list = new AccountsList;
    list->Load();
    model = new AccountsListModel(list, this);
    ui->listView->setModel(model);
}

ManageAccountsDialog::~ManageAccountsDialog()
{
    delete ui;
}

void ManageAccountsDialog::on_pushButton_create_clicked()
{
    model->createAccount();
}

void ManageAccountsDialog::on_pushButton_delete_clicked()
{
    QItemSelectionModel *selection = ui->listView->selectionModel();
    if (!selection->hasSelection()) return;
    QString login = qvariant_cast<QString>(model->data(selection->currentIndex(), Qt::DisplayRole));
    model->deleteAccount(login);
}

void ManageAccountsDialog::on_pushButton_change_clicked()
{
    QItemSelectionModel *selection = ui->listView->selectionModel();
    if (!selection->hasSelection()) return;
    QString login = qvariant_cast<QString>(model->data(selection->currentIndex(), Qt::DisplayRole));
    model->changeAccount(login);
}

#include "accountslistmodel.h"

#include <QDialog>
#include <QLayout>
#include <QDebug>
#include "createaccountform.h"
#include "changeaccountdialog.h"

AccountsListModel::AccountsListModel(AccountsList* _list,QObject *parent) : QAbstractListModel(parent)
{
    list = _list;
//    list->Load();
}

AccountsListModel::~AccountsListModel()
{
    list->Save();
}


int AccountsListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return list->getN();
}

QVariant AccountsListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

     if (index.row() >= list->getN())
         return QVariant();

     if (role == Qt::DisplayRole)
         return list->at(index.row()).getLogin();
     else
         return QVariant();
}

void AccountsListModel::deleteAccount(const QString &_login)
{
    int i = list->row(_login);
    beginRemoveRows(QModelIndex(), i,i);
    list->deleteAccount(_login);
    endRemoveRows();
}

void AccountsListModel::createAccount()
{
    QDialog *dialog = new QDialog();
    QVBoxLayout *layout = new QVBoxLayout(dialog);
    CreateAccountForm *form = new CreateAccountForm(*list, dialog);
    layout->addWidget(form);
    dialog->setLayout(layout);
    if (dialog->exec() == QDialog::Accepted) {
        int n = list->getN();
        beginInsertRows(QModelIndex(), n,n);
        list->addAccount(form->getCurr_account());
        endInsertRows();
    }


    delete dialog;
}

void AccountsListModel::changeAccount(const QString &_login)
{
    Account acc = list->getAccount(_login);

    ChangeAccountDialog *dialog = new ChangeAccountDialog(acc);
    if (dialog->exec() == QDialog::Accepted) {
        deleteAccount(acc.getLogin());
        int n = list->getN();
        beginInsertRows(QModelIndex(), n,n);
        list->addAccount(dialog->getAcc());
        endInsertRows();
    }

    delete dialog;
}

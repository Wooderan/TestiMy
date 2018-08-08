#include "accountslistmodel.h"

#include <QDialog>
#include <QLayout>
#include <QDebug>
#include "createaccountform.h"
#include "changeaccountdialog.h"

AccountsListModel::AccountsListModel(AccountsList* _list,QObject *parent) : QAbstractTableModel(parent)
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

int AccountsListModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 2;
}

QVariant AccountsListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

     if (index.row() >= list->getN())
         return QVariant();

     if (role == Qt::DisplayRole)
         if (index.column() == 0) {
             return list->at(index.row()).getLogin();
         }else
             return list->at(index.row()).getName();
     else
         return QVariant();
}

void AccountsListModel::deleteAccount(const QString &_login)
{
    int i = list->row(_login);
    beginRemoveRows(QModelIndex(), i,i);
    list->deleteAccount(_login);
    endRemoveRows();
    list->Save();
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
        list->Save();
    }

    delete dialog;
}

lookup_account_results AccountsListModel::getStatistic(const QModelIndex &index)
{
    lookup_account_results stat;
    stat(list->at(index.row()));
    return stat;
}



QVariant AccountsListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
             return QVariant();

     if (orientation == Qt::Horizontal)
         if (section == 0) {
             return QString("Login");
         }else
             return QString("Name");
     else
         return QVariant();
}

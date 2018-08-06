#ifndef ACCOUNTSLISTMODEL_H
#define ACCOUNTSLISTMODEL_H

#include <QAbstractListModel>
#include <QAbstractTableModel>
#include "accountslist.h"

class AccountsListModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit AccountsListModel(AccountsList *_list, QObject *parent = nullptr);
    ~AccountsListModel();

    // QAbstractItemModel interface
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    void deleteAccount(const QString& _login);
    void createAccount();
    void changeAccount(const QString& _login);
    lookup_account_results getStatistic(const QModelIndex &index);

private:
    AccountsList *list;

};

#endif // ACCOUNTSLISTMODEL_H

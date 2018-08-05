#ifndef ACCOUNTSLISTMODEL_H
#define ACCOUNTSLISTMODEL_H

#include <QAbstractListModel>
#include <QAbstractTableModel>
#include "accountslist.h"

class AccountsListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit AccountsListModel(AccountsList *_list, QObject *parent = nullptr);
    ~AccountsListModel();

    // QAbstractItemModel interface
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    void deleteAccount(const QString& _login);
    void createAccount();
    void changeAccount(const QString& _login);

private:
    AccountsList *list;
};

#endif // ACCOUNTSLISTMODEL_H

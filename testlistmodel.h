#ifndef TESTLISTMODEL_H
#define TESTLISTMODEL_H

#include <QAbstractItemModel>
#include "test.h"
#include "treecategory.h"
#include "account.h"

class TestListModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit TestListModel(QObject *parent = nullptr,const Account* _acc = nullptr);
    ~TestListModel();

    // QAbstractItemModel interface
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int columnCount(const QModelIndex &parent) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QModelIndex secondColumn(const QModelIndex &_item);
    TreeCategory* getItem(const QModelIndex& _indx);

//    bool Save();
    bool Load();
    void appendTest(const Test &_test);
    void deleteTest(const Test &_test);

private:
    TreeCategory *root;
    const Account *acc;

};

#endif // TESTLISTMODEL_H

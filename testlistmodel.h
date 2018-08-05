#ifndef TESTLISTMODEL_H
#define TESTLISTMODEL_H

#include <QAbstractItemModel>
#include "test.h"
#include "treecategory.h"

class TestListModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit TestListModel(QObject *parent = nullptr);
    ~TestListModel();

    // QAbstractItemModel interface
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int columnCount(const QModelIndex &parent) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

//    bool Save();
    bool Load();
    void appendTest(const Test &_test);

private:
    TreeCategory *root;
};

#endif // TESTLISTMODEL_H

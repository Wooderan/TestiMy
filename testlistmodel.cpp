#include "testlistmodel.h"

#include <QDir>

TestListModel::TestListModel(QObject *parent) : QAbstractItemModel(parent)
{
    root = new TreeCategory();
    Load();
}

TestListModel::~TestListModel()
{
    delete root;
}

bool TestListModel::Load()
{
    QDir Dir(QCoreApplication::applicationDirPath());
    if(!Dir.exists()) return false;
    QFileInfoList list = Dir.entryInfoList();
    auto it = std::find_if(list.begin(),list.end(), find_dir_name(DEFAULT_DIR_NAME));
    if (it == list.end()) //we dont find default tests folder
        return false;
    Dir.cd(DEFAULT_DIR_NAME);


    list = Dir.entryInfoList();
    foreach (QFileInfo info, list) {
        Test tmp;
        QString test_file_name = info.absoluteFilePath();
        QFile test_file(test_file_name);
        if (!info.completeSuffix().compare(DEFAULT_FILE_EXTENSION) || !test_file.open(QIODevice::ReadOnly)) continue;

        QDataStream test_stream(&test_file);
        test_stream >> tmp;
        test_file.close();
        appendTest(tmp);

    }
    return true;
}

void TestListModel::appendTest(const Test &_test)
{
    int n = root->childCount();
    QModelIndex idx = QModelIndex();
    QString _category = _test.getCategory();
    for (int i = 0; i < n ; i++) {
        if (root->child(i)->data(0) == _category) {
            idx = index(i,0,QModelIndex());
        }
    }

    if (!idx.isValid()) {
        root->appendChild(new TreeCategory(_category, root));
        n = root->childCount();
        for (int i = 0; i < n ; i++) {
            if (root->child(i)->data(0) == _category) {
                idx = index(i,0,QModelIndex());
            }
        }
    }

    TreeCategory* parentCategory = static_cast<TreeCategory*>(idx.internalPointer());
    beginInsertRows(idx, 1,1);
    parentCategory->appendChild(new TreeCategory(_test, parentCategory));
    endInsertRows();
}


QVariant TestListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    TreeCategory* category = static_cast<TreeCategory*>(index.internalPointer());
    return category->data(index.column());
}


QModelIndex TestListModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row,column,parent))
        return QModelIndex();
    TreeCategory* parentCategory;

    if (!parent.isValid())
        parentCategory = root;
    else
        parentCategory = static_cast<TreeCategory*>(parent.internalPointer());

    TreeCategory* child = parentCategory->child(row);
    if (child)
        return createIndex(row, column, child);
    else
        return QModelIndex();
}

QModelIndex TestListModel::parent(const QModelIndex &child) const
{
    if (!child.isValid())
        return QModelIndex();

    TreeCategory* childCategory = static_cast<TreeCategory*>(child.internalPointer());
    TreeCategory* parentCategory = childCategory->parent();

    if (parentCategory == root)
        return QModelIndex();

    return createIndex(parentCategory->row(), 0, parentCategory);
}

int TestListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0) return 0;

    TreeCategory* parentCategory;
    if (!parent.isValid())
        parentCategory = root;
    else
        parentCategory = static_cast<TreeCategory*>(parent.internalPointer());

    return parentCategory->childCount();
}

int TestListModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<TreeCategory*>(parent.internalPointer())->columnCount();
    else
        return root->columnCount();
}

Qt::ItemFlags TestListModel::flags(const QModelIndex &index) const
{
    if (!index.isValid()) return 0;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

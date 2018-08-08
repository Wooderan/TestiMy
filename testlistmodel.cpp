#include "testlistmodel.h"

#include <QDir>

TestListModel::TestListModel(QObject *parent, const Account *_acc) : QAbstractItemModel(parent)
{
    acc = _acc;
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
        beginInsertRows(QModelIndex(),1,1);
        root->appendChild(new TreeCategory(_category, root));
        endInsertRows();
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

void TestListModel::deleteTest(const Test &_test)
{
    int n = root->childCount();
    QModelIndex idx = QModelIndex();
    QString _category = _test.getCategory();
    for (int i = 0; i < n ; i++) {
        if (root->child(i)->data(0) == _category) {
            idx = index(i,0,QModelIndex());
        }
    }

    if (idx.isValid()) {
        TreeCategory* parentCategory = static_cast<TreeCategory*>(idx.internalPointer());
        beginRemoveRows(idx,1,1);
        parentCategory->deleteChild(_test.getName());
        endRemoveRows();
        _test.Delete();
    }
}


QVariant TestListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    TreeCategory* category = static_cast<TreeCategory*>(index.internalPointer());
    if (acc != nullptr && index.column() == 1) {
        if (category->isCategory()) {
            return QString();
        }else{
            int score = acc->getResult(category->getTest().getName());
            if (score == Account::NO_RESULT)
                return QString("Not passed");
            else return QString::number(score);
        }
    }
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
    if (acc != nullptr)
        return 2;

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


QVariant TestListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
             return QVariant();

     if (orientation == Qt::Horizontal)
         if (section == 0) {
             return QString("Category/Test");
         }else
             return QString("Score");
     else
         return QVariant();
}

QModelIndex TestListModel::secondColumn(const QModelIndex &_item)
{
    return createIndex(_item.row(), 1, _item.internalPointer());
}

#include <QtWidgets>

#include "treeitem.h"
#include "treemodel.h"

//! [0]
TreeModel::TreeModel(QObject *parent, const Account *_acc)
    : QAbstractItemModel(parent)
{
    acc = _acc;
    rootItem = new TreeItem(Test());
    setupModelData(rootItem);
}
//! [0]

//! [1]
TreeModel::~TreeModel()
{
    delete rootItem;
}
//! [1]

//! [2]
int TreeModel::columnCount(const QModelIndex & /* parent */) const
{
    if (acc != nullptr)
        return 2;
    return rootItem->columnCount();
}
//! [2]

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    TreeItem *item = getItem(index);

    if (role == Qt::DecorationRole && index.column() == 0){
        QIcon icon(item->getTest().getImage());
        return icon;
    }

    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    TreeItem* category = static_cast<TreeItem*>(index.internalPointer());
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
    return item->data(index.column());
}

//! [3]
Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}
//! [3]

//! [4]
TreeItem *TreeModel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
        if (item)
            return item;
    }
    return rootItem;
}
//! [4]

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const
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

//! [5]
QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0)
        return QModelIndex();
//! [5]

//! [6]
    TreeItem *parentItem = getItem(parent);

    TreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}
//! [6]

//bool TreeModel::insertColumns(int position, int columns, const QModelIndex &parent)
//{
//    bool success;

//    beginInsertColumns(parent, position, position + columns - 1);
//    success = rootItem->insertColumns(position, columns);
//    endInsertColumns();

//    return success;
//}

bool TreeModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    TreeItem *parentItem = getItem(parent);
    bool success;

    beginInsertRows(parent, position, position + rows - 1);
    success = parentItem->insertChildren(position, rows, rootItem->columnCount());
    endInsertRows();

    return success;
}

//! [7]
QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItem *childItem = getItem(index);
    TreeItem *parentItem = childItem->parent();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->childNumber(), 0, parentItem);
}
//! [7]

//bool TreeModel::removeColumns(int position, int columns, const QModelIndex &parent)
//{
//    bool success;

//    beginRemoveColumns(parent, position, position + columns - 1);
//    success = rootItem->removeColumns(position, columns);
//    endRemoveColumns();

//    if (rootItem->columnCount() == 0)
//        removeRows(0, rowCount());

//    return success;
//}

bool TreeModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    TreeItem *parentItem = getItem(parent);
    bool success = true;

    beginRemoveRows(parent, position, position + rows - 1);
    success = parentItem->removeChildren(position, rows);
    endRemoveRows();

    return success;
}

//! [8]
int TreeModel::rowCount(const QModelIndex &parent) const
{

    TreeItem *parentItem = getItem(parent);

    return parentItem->childCount();
}
//! [8]

bool TreeModel::setData(const QModelIndex &index, const Test &value, int role)
{
    if (role != Qt::EditRole)
        return false;

    TreeItem *item = getItem(index);
    bool result = item->setData(index.column(), value);

    if (result)
        emit dataChanged(index, index);

    return result;
}

//bool TreeModel::setHeaderData(int section, Qt::Orientation orientation,
//                              const QVariant &value, int role)
//{
//    if (role != Qt::EditRole || orientation != Qt::Horizontal)
//        return false;

//    bool result = rootItem->setData(section, value);

//    if (result)
//        emit headerDataChanged(orientation, section, section);

//    return result;
//}

void TreeModel::setupModelData( TreeItem *parent)
{
    QDir Dir(QCoreApplication::applicationDirPath());
    if(!Dir.exists()) return;
    QFileInfoList list = Dir.entryInfoList(QDir::AllDirs);
    auto it = std::find_if(list.begin(),list.end(), find_dir_name(DEFAULT_DIR_CATEGORY_NAME));
    if (it == list.end()) //we dont find default category folder
        return;
    Dir.cd(DEFAULT_DIR_CATEGORY_NAME);


    list = Dir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot);
    foreach (QFileInfo info, list) {
        Test tmp;
        QString test_file_name = info.absoluteFilePath();
        QFile test_file(test_file_name);
        if (!info.completeSuffix().compare(DEFAULT_FILE_EXTENSION) || !test_file.open(QIODevice::ReadOnly)) continue;

        QDataStream test_stream(&test_file);
        test_stream >> tmp;
        test_file.close();
        parent->insertChildren(parent->childCount(), 1, rootItem->columnCount());
        parent->child(parent->childCount() - 1)->setData(0, tmp);
    }

    Dir.cdUp();
    list = Dir.entryInfoList(QDir::AllDirs);
    it = std::find_if(list.begin(),list.end(), find_dir_name(DEFAULT_DIR_TEST_NAME));
    if (it == list.end()) //we dont find default tests folder
        return;
    Dir.cd(DEFAULT_DIR_TEST_NAME);

    list = Dir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot);
    foreach (QFileInfo info, list) {
        Test tmp;
        QString test_file_name = info.absoluteFilePath();
        QFile test_file(test_file_name);
        if (!info.completeSuffix().compare(DEFAULT_FILE_EXTENSION) || !test_file.open(QIODevice::ReadOnly)) continue;

        QDataStream test_stream(&test_file);
        test_stream >> tmp;
        test_file.close();

        TreeItem* category = parent->findChild(tmp.getCategory());
        if (category == nullptr) continue;
        category->insertChildren(category->childCount(), 1, rootItem->columnCount());
        category->child(category->childCount() - 1)->setData(0, tmp);
    }
}

#include "treecategory.h"

TreeCategory::TreeCategory(const Test &_test, TreeCategory *_parent)
{
    test = _test;
    parentCategory = _parent;
    category = false;
}

TreeCategory::TreeCategory(const QString &categoryName, TreeCategory *parent)
{
    test.setName(categoryName);
    parentCategory = parent;
    category = true;
}

TreeCategory::~TreeCategory()
{
    qDeleteAll(children);
}

void TreeCategory::appendChild(TreeCategory *child)
{
    children.append(child);
}

TreeCategory *TreeCategory::child(int row)
{
    return children.value(row);
}

int TreeCategory::childCount() const
{
    return children.count();
}

int TreeCategory::columnCount() const
{
    return 1;
}

int TreeCategory::row() const
{
    if (parentCategory)
        return parentCategory->children.indexOf(const_cast<TreeCategory*>(this));
    return 0;
}

QVariant TreeCategory::data(int column) const
{
    Q_UNUSED(column)
    return test.getName();
}

QString TreeCategory::getCategory()
{
    return test.getCategory();
}

TreeCategory *TreeCategory::parent()
{
    return parentCategory;
}

bool TreeCategory::isCategory() const
{
    return category;
}

void TreeCategory::setCategory(bool value)
{
    category = value;
}

Test TreeCategory::getTest() const
{
    return test;
}

void TreeCategory::setTest(const Test &value)
{
    test = value;
}

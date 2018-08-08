#ifndef TREECATEGORY_H
#define TREECATEGORY_H

#include "test.h"

class TreeCategory
{
public:
    TreeCategory(const Test& _test = Test(), TreeCategory *parent = nullptr);
    TreeCategory(const QString& categoryName, TreeCategory *parent = nullptr);
    ~TreeCategory();

    void appendChild(TreeCategory* child);
    void deleteChild(const QString &_testName);

    TreeCategory* child(int row);
    int childCount()const;
    int columnCount()const;
    int row()const;
    QVariant data(int column) const;
    QString getCategory();
    TreeCategory* parent();
    bool isCategory() const;
    void setCategory(bool value);

    Test getTest() const;
    void setTest(const Test &value);

private:
    QList<TreeCategory*> children;
    Test test;
    TreeCategory* parentCategory;
    bool category;

};

#endif // TREECATEGORY_H

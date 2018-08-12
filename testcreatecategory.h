#ifndef TESTCREATECATALOG_H
#define TESTCREATECATALOG_H

#include <QDialog>
#include "test.h"

namespace Ui {
class TestCreateCategory;
}

class TestCreateCategory : public QDialog
{
    Q_OBJECT

public:
    explicit TestCreateCategory(QWidget *parent = nullptr, const Test *_test = nullptr);
    ~TestCreateCategory();

    Test getTest() const;

private slots:
    void on_accepted();

    void on_pushButton_iconPath_clicked();

private:
    Ui::TestCreateCategory *ui;
    Test test;
};

#endif // TESTCREATEDIALOG_H

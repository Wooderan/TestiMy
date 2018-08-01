#ifndef TESTEXAMINEDIALOG_H
#define TESTEXAMINEDIALOG_H

#include <QDialog>
#include <test.h>

namespace Ui {
class TestExamineDialog;
}

class TestExamineDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TestExamineDialog(const Test& _test, QWidget *parent = nullptr);
    ~TestExamineDialog();

private:
    Ui::TestExamineDialog *ui;
};

#endif // TESTEXAMINEDIALOG_H

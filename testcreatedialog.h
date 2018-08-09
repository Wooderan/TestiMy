#ifndef TESTCREATEDIALOG_H
#define TESTCREATEDIALOG_H

#include <QDialog>
#include "test.h"

namespace Ui {
class TestCreateDialog;
}

class TestCreateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TestCreateDialog(QWidget *parent = nullptr, const Test *_test = nullptr);
    ~TestCreateDialog();

    Test getTest() const;

private slots:
    void on_accepted();

    void on_pushButton_add_clicked();

private:
    Ui::TestCreateDialog *ui;
    void scrollEvent(int min, int max);
    Test test;
};

#endif // TESTCREATEDIALOG_H

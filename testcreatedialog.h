#ifndef TESTCREATEDIALOG_H
#define TESTCREATEDIALOG_H

#include <QDialog>

namespace Ui {
class TestCreateDialog;
}

class TestCreateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TestCreateDialog(QWidget *parent = nullptr);
    ~TestCreateDialog();

private:
    Ui::TestCreateDialog *ui;
};

#endif // TESTCREATEDIALOG_H

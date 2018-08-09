#ifndef CREATEWINDOW_H
#define CREATEWINDOW_H

#include <QItemSelection>
#include <QMainWindow>
#include <account.h>
#include "testlistmodel.h"

namespace Ui {
class CreateWindow;
}

class CreateWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CreateWindow(const Account& account, QWidget *parent = nullptr);
    ~CreateWindow();

public slots:
    void test_change(const QItemSelection &selected, const QItemSelection &deselected);
private slots:
    void on_pushButton_passTest_clicked();

    void on_pushButton_clicked();

    void on_actionChange_login_or_password_triggered();

    void on_actionManage_accounts_triggered();

    void on_pushButton_make_clicked();

    void on_pushButton_delete_clicked();

    void on_pushButton_change_clicked();

    void on_pushButton_export_clicked();

private:
    Ui::CreateWindow *ui;
    Account account;
    TestListModel *tests;
};

#endif // CREATEWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QItemSelection>
#include <QMainWindow>
#include <account.h>
#include "treemodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(const Account& account, QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void test_change(const QItemSelection &selected, const QItemSelection &deselected);
private slots:
    void on_pushButton_passTest_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    Account account;
    lookup_account_results statistic;
    TreeModel *tests;
};

#endif // MAINWINDOW_H

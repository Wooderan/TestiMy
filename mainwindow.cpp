#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "testexaminedialog.h"

#include <QMessageBox>
#include <accountslist.h>


MainWindow::MainWindow(const Account &_account, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    account(_account)
{
    ui->setupUi(this);

    //filling listview and model
    tests = new TestListModel(this);
    ui->listView_tests->setModel(tests);

    //filling account info
    ui->label_accountInfo->setText(QString("%1\n"
                                           "Name:%2\n"
                                           "Adress:%3\n"
                                           "Phone:%4")
                                            .arg(Account::RoleStr[account.getPermission()])
                                            .arg(account.getName())
                                            .arg(account.getAdress())
                                            .arg(account.getPhone_number()));

    //filling testinfo
    QItemSelectionModel *selection = ui->listView_tests->selectionModel();
    QObject::connect(selection, &QItemSelectionModel::selectionChanged, this, &MainWindow::test_change);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::test_change(const QItemSelection &selected, const QItemSelection &deselected)
{
    Q_UNUSED(deselected)
    QModelIndexList indexList = selected.indexes();
    // we always will have only one selected item
    TreeCategory* category = static_cast<TreeCategory*>(indexList[0].internalPointer());
    if (category->isCategory()) return;

    Test test = category->getTest();

    int result = account.getResult(test.getName());
    QString bestResult;
    if (result != Account::NO_RESULT) {
        bestResult = QString::number(result);
    }else{
        bestResult = "You don't pass this test before";
    }

    ui->label_testInfo->setText(QString("Subject:%1\n"
                                        "Description:%2\n"
                                        "Time:%3\n"
                                        "Questions:%4\n"
                                        "Your result:%5")
                                        .arg(test.getName())
                                        .arg(test.getDescripton())
                                        .arg(test.getTime().toString())
                                        .arg(test.getN())
                                        .arg(bestResult));

    if (!ui->pushButton_passTest->isEnabled())
        ui->pushButton_passTest->setEnabled(true);
}

void MainWindow::on_pushButton_passTest_clicked()
{

    TreeCategory* category = static_cast<TreeCategory*>(ui->listView_tests->selectionModel()->currentIndex().internalPointer());
    if (category->isCategory()) return;
    Test test = category->getTest();
    QString testName = test.getName();
    if (account.getResult(testName) != Account::NO_RESULT) {
        QMessageBox::warning(this, "Note", "You have already passed this test, and this passage will not change the mark");
    }
    TestExamineDialog *dialog = new TestExamineDialog(test, this);
    if (dialog->exec() == QDialog::Accepted) {
        if (account.getResult(testName) == Account::NO_RESULT) {
            account.setResult(testName, dialog->getMark());
            ui->label_testInfo->setText(QString("Subject:%1\n"
                                                "Description:%2\n"
                                                "Time:%3\n"
                                                "Questions:%4\n"
                                                "Your result:%5")
                                                .arg(test.getName())
                                                .arg(test.getDescripton())
                                                .arg(test.getTime().toString())
                                                .arg(test.getN())
                                                .arg(account.getResult(testName)));
            AccountsList list;
            list.Load();
            list.deleteAccount(account.getLogin());
            list.addAccount(account);
            list.Save();
            list.Load();
        }

    }

}

void MainWindow::on_pushButton_clicked()
{
    this->close();
}

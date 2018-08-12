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
    tests = new TestListModel(this, &account);
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

    statistic(account);
    ui->label_1->setText("Passed tests: ");
    ui->textBrowser_1->setText(QString::number(statistic.getCount()));
    ui->label_2->setText("Excelent results: ");
    ui->textBrowser_2->setText(QString::number(statistic.getExcelent()));
    ui->label_3->setText("Avarage results: ");
    ui->textBrowser_3->setText(QString::number(statistic.getAvarage()));
    ui->label_4->setText("Bad results: ");
    ui->textBrowser_4->setText(QString::number(statistic.getBad()));
    ui->label_5->setText("Avarage mark: ");
    ui->textBrowser_5->setText(QString::number(statistic.getAvarageMark()));

    ui->listView_tests->header()->setSectionResizeMode(QHeaderView::Stretch);

    QFile file(":/qss/stylesheets/main.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet(file.readAll());
    setStyleSheet(styleSheet);
    ensurePolished();
    file.close();
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
    if (category->isCategory()){
        if (ui->pushButton_passTest->isEnabled())
            ui->pushButton_passTest->setEnabled(false);
        ui->label_1->setText("Passed tests: ");
        ui->textBrowser_1->setText(QString::number(statistic.getCount()));
        ui->label_2->setText("Excelent results: ");
        ui->textBrowser_2->setText(QString::number(statistic.getExcelent()));
        ui->label_3->setText("Avarage results: ");
        ui->textBrowser_3->setText(QString::number(statistic.getAvarage()));
        ui->label_4->setText("Bad results: ");
        ui->textBrowser_4->setText(QString::number(statistic.getBad()));
        ui->label_5->setText("Avarage mark: ");
        ui->textBrowser_5->setText(QString::number(statistic.getAvarageMark()));
        return;
    }

    Test test = category->getTest();

    int result = account.getResult(test.getName());
    QString bestResult;
    if (result != Account::NO_RESULT) {
        bestResult = QString::number(result);
    }else{
        bestResult = "You don't pass this test before";
    }

    ui->label_1->setText("Subject: ");
    ui->textBrowser_1->setText(test.getName());
    ui->label_2->setText("Description: ");
    ui->textBrowser_2->setText(test.getDescripton());
    ui->label_3->setText("Time: ");
    ui->textBrowser_3->setText(test.getTime().toString());
    ui->label_4->setText("Questions: ");
    ui->textBrowser_4->setText(QString::number(test.getN()));
    ui->label_5->setText("Your result: ");
    ui->textBrowser_5->setText(bestResult);

    if (!ui->pushButton_passTest->isEnabled())
        ui->pushButton_passTest->setEnabled(true);
}

void MainWindow::on_pushButton_passTest_clicked()
{
    QModelIndex idx = ui->listView_tests->selectionModel()->currentIndex();
    TreeCategory* category = static_cast<TreeCategory*>(ui->listView_tests->selectionModel()->currentIndex().internalPointer());
    if (category->isCategory()) return;
    Test test = category->getTest();
    QString testName = test.getName();
    if (account.getResult(testName) != Account::NO_RESULT) {
        QMessageBox::warning(this, "Note", "You have already passed this test, and this passage will not change the mark");
    }
    TestExamineDialog *dialog = new TestExamineDialog(test, this);
    dialog->setWindowState(dialog->windowState() | Qt::WindowMaximized);
    if (dialog->exec() == QDialog::Accepted) {
        if (account.getResult(testName) == Account::NO_RESULT) {
            account.setResult(testName, dialog->getMark());
            ui->label_1->setText("Subject: ");
            ui->textBrowser_1->setText(test.getName());
            ui->label_2->setText("Description: ");
            ui->textBrowser_2->setText(test.getDescripton());
            ui->label_3->setText("Time: ");
            ui->textBrowser_3->setText(test.getTime().toString());
            ui->label_4->setText("Questions: ");
            ui->textBrowser_4->setText(QString::number(test.getN()));
            ui->label_5->setText("Your result: ");
            ui->textBrowser_4->setText(QString::number(account.getResult(testName)));

            AccountsList list;
            list.Load();
            list.deleteAccount(account.getLogin());
            list.addAccount(account);
            list.Save();
            tests->dataChanged(idx,tests->secondColumn(idx));
//            QModelIndex idx2 = tests->secondColumn(idx);
//            QString str = qvariant_cast<QString>(tests->data(tests->secondColumn(idx),Qt::DisplayRole));
        }

    }

}

void MainWindow::on_pushButton_clicked()
{
    this->close();
}

#include "createwindow.h"
#include "ui_createwindow.h"
#include "testexaminedialog.h"
#include "testcreatedialog.h"
#include "testcreatecategory.h"
#include "changepassworddialog.h"
#include "accountslist.h"
#include "manageaccountsdialog.h"

#include <QFileDialog>
#include <QMessageBox>


CreateWindow::CreateWindow(const Account &_account, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CreateWindow),
    account(_account)
{
    ui->setupUi(this);
    setWindowTitle("TestiMy");

    QFile file(":/qss/stylesheets/createwindows.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet(file.readAll());
    setStyleSheet(styleSheet);
    ensurePolished();
    file.close();

    //filling listview and model
    tests = new TreeModel(this);
    ui->listView_tests->setModel(tests);
    ui->listView_tests->setIconSize(QSize(50,50));
    ui->listView_tests->setAlternatingRowColors(true);

    //filling account info
    ui->label_accountInfo->setText(QString("Login:%1\n"
                                           "Permission:%2")
                                            .arg(account.getLogin())
                                            .arg(Account::RoleStr[account.getPermission()]));

    //filling testinfo
    QItemSelectionModel *selection = ui->listView_tests->selectionModel();
    QObject::connect(selection, &QItemSelectionModel::selectionChanged, this, &CreateWindow::test_change);

    ui->label_1->setText("Subject: ");
    ui->textBrowser_1->setText("");
    ui->label_2->setText("Description: ");
    ui->textBrowser_2->setText("");
    ui->label_3->setText("Time: ");
    ui->textBrowser_3->setText("");
    ui->label_4->setText("Questions: ");
    ui->textBrowser_4->setText("");


}

CreateWindow::~CreateWindow()
{
    delete ui;
}

void CreateWindow::test_change(const QItemSelection &selected, const QItemSelection &deselected)
{
    Q_UNUSED(deselected)
    QModelIndexList indexList = selected.indexes();
    // we always will have only one selected item
    TreeItem* category = static_cast<TreeItem*>(indexList[0].internalPointer());
    Test test = category->getTest();
    if (test.getIsCategory()) {
        if (ui->pushButton_passTest->isEnabled())
            ui->pushButton_passTest->setEnabled(false);
        if (ui->pushButton_delete->isEnabled())
            ui->pushButton_delete->setEnabled(false);
        if (ui->pushButton_export->isEnabled())
            ui->pushButton_export->setEnabled(false);
        if (ui->pushButton_change->isEnabled())
            ui->pushButton_change->setEnabled(false);
        if (!ui->pushButton_delete_category->isEnabled())
            ui->pushButton_delete_category->setEnabled(true);
        ui->label_1->setText("Category name: ");
        ui->textBrowser_1->setText(test.getName());
        ui->label_2->setText("Description: ");
        ui->textBrowser_2->setText(test.getDescripton());
        ui->label_3->setText("");
        ui->textBrowser_3->setText("");
        ui->label_4->setText("");
        ui->textBrowser_4->setText("");
        return;
    }


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

    if (!ui->pushButton_passTest->isEnabled())
        ui->pushButton_passTest->setEnabled(true);
    if (!ui->pushButton_delete->isEnabled())
        ui->pushButton_delete->setEnabled(true);
    if (!ui->pushButton_change->isEnabled())
        ui->pushButton_change->setEnabled(true);
    if (!ui->pushButton_export->isEnabled())
        ui->pushButton_export->setEnabled(true);
    if (ui->pushButton_delete_category->isEnabled())
        ui->pushButton_delete_category->setEnabled(false);
}

void CreateWindow::on_pushButton_passTest_clicked()
{
    TreeItem* category = static_cast<TreeItem*>(ui->listView_tests->selectionModel()->currentIndex().internalPointer());
    if (category->isCategory()) return;
    Test test = category->getTest();
    TestExamineDialog *dialog = new TestExamineDialog(test, this);
    dialog->setWindowState(dialog->windowState() | Qt::WindowMaximized);
    dialog->exec();
}

void CreateWindow::on_pushButton_clicked()
{
    this->close();
}

void CreateWindow::on_actionChange_login_or_password_triggered()
{
    ChangePasswordDialog *dialog = new ChangePasswordDialog(account, this);
    dialog->setWindowTitle("Change login and password");
    if (dialog->exec() == QDialog::Accepted) {
        AccountsList list;
        list.Load();
        list.deleteAccount(account.getLogin());
        list.addAccount(dialog->getAcc());
        list.Save();
    }
}

void CreateWindow::on_actionManage_accounts_triggered()
{
    ManageAccountsDialog *dialog = new ManageAccountsDialog(this);
    dialog->setWindowTitle("Account manager");
    dialog->setWindowState(dialog->windowState() | Qt::WindowMaximized);
    dialog->exec();
}

void CreateWindow::on_pushButton_make_clicked()
{
    if (!ui->listView_tests->selectionModel()->hasSelection()) {
        QMessageBox::critical(this, "Error", "Please, select or create some category first!");
        return;
    }
    QModelIndex index = ui->listView_tests->currentIndex();
    QModelIndex categoryIndex;
    QString category;
    Test test = tests->getItem(index)->getTest();
    if (test.getIsCategory()) {
        categoryIndex = index;
        category = test.getName();
    }else{
        categoryIndex = index.parent();
        category = test.getCategory();
    }


    TestCreateDialog *dialog = new TestCreateDialog(category, this);
    dialog->setWindowTitle("Create test");
    dialog->setWindowState(dialog->windowState() | Qt::WindowMaximized);
    if (dialog->exec() == QDialog::Accepted) {
        const Test& test = dialog->getTest();
        if (tests->insertRows(0,1,categoryIndex)) {
            QModelIndex idx = tests->index(0,0, categoryIndex);
            tests->setData(idx, test);
            test.Save();
        }
    }
}

void CreateWindow::on_pushButton_delete_clicked()
{
    QModelIndex index = ui->listView_tests->selectionModel()->currentIndex();
    Test category = tests->getItem(index)->getTest();
    if (!category.getIsCategory()) {
        tests->removeRow(index.row(), index.parent());
        category.Delete();
    }else
        QMessageBox::critical(this, "Error", "Please, select test first");
}

void CreateWindow::on_pushButton_change_clicked()
{
    if (!ui->listView_tests->selectionModel()->hasSelection()) {
        QMessageBox::critical(this, "Error", "Please, select or create some test first!");
        return;
    }
    QModelIndex index = ui->listView_tests->currentIndex();
    Test test = tests->getItem(index)->getTest();
    if (test.getIsCategory()) {
        QMessageBox::critical(this, "Error", "Please, select or create some test first!");
        return;
    }else{
        QModelIndex categoryIndex = index.parent();
        TestCreateDialog *dialog = new TestCreateDialog(this, &test);
        dialog->setWindowTitle("Change test");
        dialog->setWindowState(dialog->windowState() | Qt::WindowMaximized);
        if (dialog->exec() == QDialog::Accepted) {
            const Test& test = dialog->getTest();
            on_pushButton_delete_clicked();
            if (tests->insertRows(0,1,categoryIndex)) {
                QModelIndex idx = tests->index(0,0,categoryIndex);
                tests->setData(idx, test);
                test.Save();
            }
        }
    }
}

void CreateWindow::on_pushButton_export_clicked()
{
    TreeItem* current = tests->getItem(ui->listView_tests->selectionModel()->currentIndex());
    if (current->isCategory()) return;
    Test test = current->getTest();
    QString test_file_name = QFileDialog::getExistingDirectory(this, "Choose Directory to export",
                                                               "",
                                                               QFileDialog::ShowDirsOnly
                                                               | QFileDialog::DontResolveSymlinks);
    test_file_name += "/" + test.getName() + ".txt";
    test.Export(test_file_name);
}

void CreateWindow::on_pushButton_make_category_clicked()
{
    TestCreateCategory *dialog = new TestCreateCategory(this);
//    dialog->setWindowState(dialog->windowState() | Qt::WindowMaximized);
    dialog->setWindowTitle("Create category");
    dialog->resize(800, 400);
    if (dialog->exec() == QDialog::Accepted) {
        const Test& test = dialog->getTest();
        if (tests->insertRows(0,1)) {
            QModelIndex idx = tests->index(0,0);
            tests->setData(idx, test);
            test.Save();
        }
    }
}

void CreateWindow::on_pushButton_delete_category_clicked()
{
    QModelIndex index = ui->listView_tests->selectionModel()->currentIndex();
    TreeItem* item = tests->getItem(index);
    Test category = item->getTest();
    if (category.getIsCategory()) {

        int n = item->childCount();
        for (int i = 0; i < n; i++) {
            Test tmp = item->child(i)->getTest();
            tmp.Delete();
        }
        tests->removeRows(0, n, index);

        tests->removeRow(index.row(), index.parent());
        category.Delete();
    }else
        QMessageBox::critical(this, "Error", "Please, select category first");
}

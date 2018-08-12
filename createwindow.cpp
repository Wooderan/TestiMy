#include "createwindow.h"
#include "ui_createwindow.h"
#include "testexaminedialog.h"
#include "testcreatedialog.h"
#include "changepassworddialog.h"
#include "accountslist.h"
#include "manageaccountsdialog.h"

#include <QFileDialog>


CreateWindow::CreateWindow(const Account &_account, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CreateWindow),
    account(_account)
{
    ui->setupUi(this);

    QFile file(":/qss/stylesheets/createwindows.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet(file.readAll());
    setStyleSheet(styleSheet);
    ensurePolished();
    file.close();

    //filling listview and model
    tests = new TestListModel(this);
    ui->listView_tests->setModel(tests);

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
    TreeCategory* category = static_cast<TreeCategory*>(indexList[0].internalPointer());
    if (category->isCategory()) {
        if (ui->pushButton_passTest->isEnabled())
            ui->pushButton_passTest->setEnabled(false);
        if (ui->pushButton_delete->isEnabled())
            ui->pushButton_delete->setEnabled(false);
        if (ui->pushButton_change->isEnabled())
            ui->pushButton_change->setEnabled(false);
        if (ui->pushButton_export->isEnabled())
            ui->pushButton_export->setEnabled(false);
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

    if (!ui->pushButton_passTest->isEnabled())
        ui->pushButton_passTest->setEnabled(true);
    if (!ui->pushButton_delete->isEnabled())
        ui->pushButton_delete->setEnabled(true);
    if (!ui->pushButton_change->isEnabled())
        ui->pushButton_change->setEnabled(true);
    if (!ui->pushButton_export->isEnabled())
        ui->pushButton_export->setEnabled(true);

}

void CreateWindow::on_pushButton_passTest_clicked()
{
    TreeCategory* category = static_cast<TreeCategory*>(ui->listView_tests->selectionModel()->currentIndex().internalPointer());
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
    dialog->setWindowState(dialog->windowState() | Qt::WindowMaximized);
    dialog->exec();
}

void CreateWindow::on_pushButton_make_clicked()
{
    TestCreateDialog *dialog = new TestCreateDialog(this);
    dialog->setWindowState(dialog->windowState() | Qt::WindowMaximized);
    if (dialog->exec() == QDialog::Accepted) {
        const Test& test = dialog->getTest();
        tests->appendTest(test);
        test.Save();
    }
}

void CreateWindow::on_pushButton_delete_clicked()
{
    TreeCategory* category = static_cast<TreeCategory*>(ui->listView_tests->selectionModel()->currentIndex().internalPointer());
    if (category->isCategory()){

    }else{
        Test test = category->getTest();
        tests->deleteTest(test);
    }
}

void CreateWindow::on_pushButton_change_clicked()
{
    TreeCategory* current = tests->getItem(ui->listView_tests->selectionModel()->currentIndex());
    Test test = current->getTest();
    TestCreateDialog *dialog = new TestCreateDialog(this, &test);
    dialog->setWindowState(dialog->windowState() | Qt::WindowMaximized);
    if (dialog->exec() == QDialog::Accepted) {
        tests->deleteTest(test);
        test.Delete();
        test = dialog->getTest();
        tests->appendTest(test);
        test.Save();
    }
}

void CreateWindow::on_pushButton_export_clicked()
{
    TreeCategory* current = tests->getItem(ui->listView_tests->selectionModel()->currentIndex());
    if (current->isCategory()) return;
    Test test = current->getTest();
    QString test_file_name = QFileDialog::getExistingDirectory(this, "Choose Directory to export",
                                                               "",
                                                               QFileDialog::ShowDirsOnly
                                                               | QFileDialog::DontResolveSymlinks);
    test_file_name += "/" + test.getName() + ".txt";
    test.Export(test_file_name);
}

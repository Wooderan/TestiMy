#include "createwindow.h"
#include "ui_createwindow.h"
#include "testexaminedialog.h"
#include "testcreatedialog.h"
#include "changepassworddialog.h"
#include "accountslist.h"
#include "manageaccountsdialog.h"


CreateWindow::CreateWindow(const Account &_account, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CreateWindow),
    account(_account)
{
    ui->setupUi(this);

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
                                        "Best result:%5")
                                        .arg(test.getName())
                                        .arg(test.getDescripton())
                                        .arg(test.getTime().toString())
                                        .arg(test.getN())
                                        .arg(bestResult));

    if (!ui->pushButton_passTest->isEnabled())
        ui->pushButton_passTest->setEnabled(true);
}

void CreateWindow::on_pushButton_passTest_clicked()
{
    TreeCategory* category = static_cast<TreeCategory*>(ui->listView_tests->selectionModel()->currentIndex().internalPointer());
    if (category->isCategory()) return;
    Test test = category->getTest();
    TestExamineDialog *dialog = new TestExamineDialog(test, this);
    dialog->exec();
}

void CreateWindow::on_pushButton_clicked()
{
    this->close();
}

void CreateWindow::on_pushButton_2_clicked()
{
    TestCreateDialog *dialog = new TestCreateDialog(this);
    if (dialog->exec() == QDialog::Accepted) {
        const Test& test = dialog->getTest();
        tests->appendTest(test);
        test.Save();
    }
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
    dialog->exec();
}

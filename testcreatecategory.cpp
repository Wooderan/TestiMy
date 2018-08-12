#include "testcreatecategory.h"
#include "ui_testcreatecategory.h"
#include "testitemcreatewidget.h"

#include <QFileDialog>
#include <QScrollBar>
#include <QTimeEdit>
#include <QImageReader>
#include <QMessageBox>

TestCreateCategory::TestCreateCategory(QWidget *parent, const Test *_test) :
    QDialog(parent),
    ui(new Ui::TestCreateCategory)
{
    ui->setupUi(this);
    QObject::connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &TestCreateCategory::on_accepted);
    if (_test && _test->getIsCategory()) {
        ui->lineEdit_name->setText(_test->getName());
        ui->textEdit_description->setText(_test->getDescripton());
    }
}

TestCreateCategory::~TestCreateCategory()
{
    delete ui;
}


Test TestCreateCategory::getTest() const
{
    return test;
}

void TestCreateCategory::on_accepted()
{
    QLineEdit *le = ui->lineEdit_name;
    test.setName(le->text());

    QTextEdit *te = ui->textEdit_description;
    test.setDescripton(te->toPlainText());

    test.setIsCategory(true);

    QString iconPath = ui->lineEdit_iconPath->text();
    if (iconPath.isEmpty()) {
        test.setImage(QPixmap(":/icons/icons/empty.jpg"));
    }else
        test.setImage(QPixmap(iconPath));

//    test.setImage(QPixmap(":/icons/icons/radio-button-on-hovered.svg"));
}

void TestCreateCategory::on_pushButton_iconPath_clicked()
{
    QString icon_file_name = QFileDialog::getOpenFileName(this, "Choose Icon file",
                                                               "");
    QByteArray imageFormat = QImageReader::imageFormat(icon_file_name);
    if (imageFormat.isEmpty()) {
        QMessageBox::critical(this, "Error", "Can't open file like image! You can try another format.");
    }else{
        ui->lineEdit_iconPath->setText(icon_file_name);
    }

}

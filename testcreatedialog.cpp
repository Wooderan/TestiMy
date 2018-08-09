#include "testcreatedialog.h"
#include "ui_testcreatedialog.h"
#include "testitemcreatewidget.h"

#include <QScrollBar>
#include <QTimeEdit>

TestCreateDialog::TestCreateDialog(QWidget *parent, const Test *_test) :
    QDialog(parent),
    ui(new Ui::TestCreateDialog)
{
    ui->setupUi(this);
    QObject::connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &TestCreateDialog::on_accepted);
    ui->timeEdit->setDisplayFormat("hh:mm:ss");
    if (_test) {
        ui->lineEdit_name->setText(_test->getName());
        ui->textEdit_description->setText(_test->getDescripton());
        ui->lineEdit_category->setText(_test->getCategory());
        ui->timeEdit->setTime(_test->getTime());
        size_t n = _test->getN();
        for (size_t i = 0; i < n; i++) {
            TestItem item = _test->at(i);
            TestItemCreateWidget *itemWidget = new TestItemCreateWidget(this, &item);
            QWidget* widget = ui->scrollArea->widget();
            QLayout* layout = widget->layout();
            if (layout == nullptr) {
                layout = new QVBoxLayout(widget);
            }
            layout->addWidget(itemWidget);
        }
    }
}

TestCreateDialog::~TestCreateDialog()
{
    delete ui;
}


void TestCreateDialog::on_pushButton_add_clicked()
{
    TestItemCreateWidget  *item = new TestItemCreateWidget(this);

    QWidget* widget = ui->scrollArea->widget();
    QLayout* layout = widget->layout();
    if (layout == nullptr) {
        layout = new QVBoxLayout(widget);
    }
    layout->addWidget(item);
    widget->setLayout(layout);
    QObject::connect(ui->scrollArea->verticalScrollBar(), &QScrollBar::rangeChanged, this, &TestCreateDialog::scrollEvent);
    ui->scrollArea->setWidget(widget);
}

void TestCreateDialog::scrollEvent(int min, int max)
{
    Q_UNUSED(min);
    ui->scrollArea->verticalScrollBar()->setValue(max);
    QObject::disconnect(ui->scrollArea->verticalScrollBar(), &QScrollBar::rangeChanged, this, &TestCreateDialog::scrollEvent);
}

Test TestCreateDialog::getTest() const
{
    return test;
}

void TestCreateDialog::on_accepted()
{
    QLineEdit *le = ui->lineEdit_name;
    test.setName(le->text());

    QTextEdit *te = ui->textEdit_description;
    test.setDescripton(te->toPlainText());

    QTimeEdit *time = ui->timeEdit;
    test.setTime(time->time());

    test.setCategory(ui->lineEdit_category->text());

    QScrollArea *scroll = ui->scrollArea;
    if (scroll != nullptr) {
        QObjectList scrollChildren = scroll->takeWidget()->children();
        for (int y = 0; y < scrollChildren.count(); y++) {
            TestItemCreateWidget *item = dynamic_cast<TestItemCreateWidget*>(scrollChildren.at(y));
            if (item != nullptr) {
                test.addQuestion(item->getItem());
            }
        }
    }
}

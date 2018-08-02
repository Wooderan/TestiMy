#include "testexaminedialog.h"
#include "ui_testexaminedialog.h"
#include "testitem.h"
#include "testitemwidget.h"

#include <QRadioButton>
#include <QDebug>

TestExamineDialog::TestExamineDialog(const Test &_test, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TestExamineDialog)
{
    ui->setupUi(this);

    size_t n = _test.getN();
    QWidget* scrollWidget = new QWidget(this);
    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollWidget);
    scrollWidget->setLayout(scrollLayout);

    for (size_t i = 0; i < n; i++) {
        TestItemWidget *itemWidget = new TestItemWidget(_test.at(i), scrollWidget);
        scrollLayout->addWidget(itemWidget);
    }

    ui->scrollArea->setWidget(scrollWidget);
    ui->timer_edit->setTime(_test.getTime());
    ui->timer_edit->setDisplayFormat("hh:mm:ss");
    ui->timer_edit->setReadOnly(true);
    score = 0;
    timer = new QTimer(this);
    QObject::connect(timer, &QTimer::timeout, this, &TestExamineDialog::update_timer);
    timer->start(1000);

    QObject::connect(ui->btn_Check, &QPushButton::clicked, this, &TestExamineDialog::check_results);
    QObject::connect(this, &TestExamineDialog::TimeOut, this, &TestExamineDialog::check_results);
}

TestExamineDialog::~TestExamineDialog()
{
    delete ui;
}

void TestExamineDialog::on_btn_Ok_clicked()
{
    emit this->accept();
}

void TestExamineDialog::check_results()
{
    this->timer->stop();
    QWidget *widget = ui->scrollArea->takeWidget();
    QVBoxLayout *layout = dynamic_cast<QVBoxLayout*>(widget->layout());

    for (int i = 0; i < layout->count(); i++) {
        TestItemWidget *item = dynamic_cast<TestItemWidget*>(layout->itemAt(i)->widget());
        if (item != nullptr) {
            if (check_question(item))
            {
                item->setStyleSheet(QString("background-color:green"));
                score++;
            }else{
                item->setStyleSheet(QString("background-color:red"));
            }

        }
    }

    ui->scrollArea->setWidget(widget);
    ui->btn_Check->setEnabled(false);
}

bool TestExamineDialog::check_question(TestItemWidget *_item)
{
    QObjectList list = _item->children();
    QRadioButton *btn = nullptr;
    foreach (QObject* obj, list) {
        if ((btn = dynamic_cast<QRadioButton*>(obj)) != nullptr) {
            if (btn->isChecked()) {
                if (_item->getCorrect_variant() == btn->text()) {
                    return true;
                }else
                    return false;
            }
        }
    }
    return false;
}

void TestExamineDialog::update_timer()
{
    QTime time = ui->timer_edit->time();
    if (time == QTime(0,0,0)) {
        this->timer->stop();
        emit TimeOut();
    }else{
        time.setHMS(time.addSecs(-1).hour(),time.addSecs(-1).minute(),time.addSecs(-1).second());
        ui->timer_edit->setTime(time);
    }
}

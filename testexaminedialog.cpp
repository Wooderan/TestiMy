#include "testexaminedialog.h"
#include "ui_testexaminedialog.h"
#include "testitem.h"
#include "testitemwidget2.h"

#include <QRadioButton>
#include <QDebug>
#include <QMessageBox>
#include "testitemcreatewidget.h"

TestExamineDialog::TestExamineDialog(const Test &_test, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TestExamineDialog)
{
    ui->setupUi(this);

    QFile file(":/qss/stylesheets/testexaminedialog.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet(file.readAll());
    setStyleSheet(styleSheet);
    ensurePolished();
    file.close();
    this->setWindowTitle(QString("TestiMy - %1").arg(_test.getName()));

    size_t n = _test.getN();
    QWidget* scrollWidget = new QWidget(this);
    scrollWidget->setObjectName("scrollWidget");
    scrollWidget->setObjectName("scrollWidget");
    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollWidget);
    scrollLayout->setSpacing(5);
    scrollLayout->setContentsMargins(1,1,1,1);
    scrollWidget->setLayout(scrollLayout);

    for (size_t i = 0; i < n; i++) {
        TestItemWidget2 *itemWidget = new TestItemWidget2(_test.at(i), scrollWidget);
        itemWidget->setProperty("state", 'u');
        scrollLayout->addWidget(itemWidget);
    }

    ui->scrollArea->setWidget(scrollWidget);
    ui->timer_edit->setTime(_test.getTime());
    ui->timer_edit->setDisplayFormat("hh:mm:ss");
    ui->timer_edit->setReadOnly(true);
    ui->timer_edit->setStyleSheet("QTimeEdit{border-radius:4px;background:#666666;border:2px solid #2d89ef;}");
    mark = 0;
    timer = new QTimer(this);
    QObject::connect(timer, &QTimer::timeout, this, &TestExamineDialog::update_timer);
    timer->start(1000);

    QObject::connect(ui->btn_Check, &QPushButton::clicked, this, &TestExamineDialog::check_results);
    QObject::connect(this, &TestExamineDialog::TimeOut, this, &TestExamineDialog::check_results);

    ui->label_Name->setText(_test.getName());
    ui->label_Description->setText(_test.getDescripton());
    questions = static_cast<int>(_test.getN());

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
    int score = 0;
    this->timer->stop();
    QWidget *widget = ui->scrollArea->takeWidget();
    QVBoxLayout *layout = dynamic_cast<QVBoxLayout*>(widget->layout());

    for (int i = 0; i < layout->count(); i++) {
        TestItemWidget2 *item = dynamic_cast<TestItemWidget2*>(layout->itemAt(i)->widget());
        if (item != nullptr) {
            if (check_question(item))
            {
                item->setProperty("state", 'r');
                score++;
            }else{
                item->setProperty("state", 'w');
            }
            item->disableRadio();
        }
    }

    ui->scrollArea->setWidget(widget);
    ui->btn_Check->setEnabled(false);
    ui->btn_Ok->setEnabled(true);

//    double coef = static_cast<double>(questions) / 12;
    double perc_coef = static_cast<double>(100) / questions;
    double percent = static_cast<int>(perc_coef) * score;
    mark = static_cast<int>(static_cast<double>(12) * (percent / 100));
    QMessageBox::information(this, "Your results", QString("Right answers: %1\n"
                                                           "Percentage of correct answers: %2%\n"
                                                           "Mark: %3")
                                                            .arg(score)
                                                            .arg(percent)
                                                            .arg(mark));
}

bool TestExamineDialog::check_question(TestItemWidget2 *_item)
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
    static bool b = true;
    QTime time = ui->timer_edit->time();

    if (time < QTime(0,0,30)) {
        if (b) {
            ui->timer_edit->setStyleSheet("QTimeEdit{border-radius:4px;background:#666666;border:2px solid #2d89ef;font-size:16px;}");
            b = false;
        }else{
            ui->timer_edit->setStyleSheet("QTimeEdit{border-radius:4px;background:#666666;border:2px solid red;font-size:16px;}");
            b = true;
        }
    }
    if (time == QTime(0,0,0)) {
        this->timer->stop();
        emit TimeOut();
    }else{
        time.setHMS(time.addSecs(-1).hour(),time.addSecs(-1).minute(),time.addSecs(-1).second());
        ui->timer_edit->setTime(time);
    }
}

int TestExamineDialog::getMark() const
{
    return mark;
}

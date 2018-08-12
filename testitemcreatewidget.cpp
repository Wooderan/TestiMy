#include "testitemcreatewidget.h"
#include "ui_testitemcreatewidget.h"

#include <QLineEdit>
#include <QDebug>
#include <QRadioButton>

TestItemCreateWidget::TestItemCreateWidget(QWidget *parent, const TestItem *_item) :
    QWidget(parent),
    ui(new Ui::TestItemCreateWidget)
{
    ui->setupUi(this);

    QFile file(":/qss/stylesheets/testitemcreatewidget.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet(file.readAll());
    setStyleSheet(styleSheet);
    ensurePolished();
    file.close();

    if (_item != nullptr) {
        ui->text_question->setText(_item->getQuestion());
        for (size_t i = 0; i < _item->getN(); i++) {
            Variant var = _item->at(i);
            MyRadioButton *rb = new MyRadioButton(this);
            rb->setChecked(var.correct);
            QLineEdit *le = new QLineEdit(this);
            le->setText(var.answer);
            MyPushButton *pb = new MyPushButton(this);
            QObject::connect(pb, &MyPushButton::clicked, this, &TestItemCreateWidget::deleteLine);
            pb->setText("X");
            rb->setRespond_line(le);
            pb->setRespond_line(le);
            pb->setRespond_btn(rb);
            QSizePolicy policy(QSizePolicy::Preferred,QSizePolicy::Fixed);
            policy.setHorizontalStretch(1);
            le->setSizePolicy(policy);
            int row = ui->formVariants->rowCount();
            ui->formVariants->addWidget(rb, row, 0);
            ui->formVariants->addWidget(le, row, 1);
            ui->formVariants->addWidget(pb, row, 2);
        }
    }
}

TestItemCreateWidget::~TestItemCreateWidget()
{
    delete ui;
}

TestItem TestItemCreateWidget::getItem() const
{
    TestItem item;
    QObjectList list = this->children();

    for (int i = 0; i < list.count(); i++) {
        QTextEdit *question = dynamic_cast<QTextEdit*>(list.at(i));
        if (question != nullptr && question->objectName() == "text_question") {
            item.setQuestion(question->toPlainText());
        }
        MyRadioButton *rb = dynamic_cast<MyRadioButton*>(list.at(i));
        if (rb != nullptr) {
            item.addVar(rb->isChecked(), rb->respond_line()->text());
        }
    }

    return item;
}


void TestItemCreateWidget::on_addBtn_clicked()
{
    MyRadioButton *rb = new MyRadioButton(this);
    rb->setChecked(true);
    QLineEdit *le = new QLineEdit(this);
    MyPushButton *pb = new MyPushButton(this);
    QObject::connect(pb, &MyPushButton::clicked, this, &TestItemCreateWidget::deleteLine);
    pb->setText("X");
    rb->setRespond_line(le);
    pb->setRespond_line(le);
    pb->setRespond_btn(rb);
    QSizePolicy policy(QSizePolicy::Preferred,QSizePolicy::Fixed);
    policy.setHorizontalStretch(1);
    le->setSizePolicy(policy);
    int row = ui->formVariants->rowCount();
    ui->formVariants->addWidget(rb, row, 0);
    ui->formVariants->addWidget(le, row, 1);
    ui->formVariants->addWidget(pb, row, 2);
}

void TestItemCreateWidget::deleteLine()
{
    MyPushButton* pb = dynamic_cast<MyPushButton*>(sender());
    MyRadioButton *rb = pb->respond_btn();
    QLineEdit *le = pb->respond_line();
    delete pb;
    delete rb;
    delete le;
    QObjectList list = this->children();
    foreach (QObject *const obj, list) {
        rb = dynamic_cast<MyRadioButton *>(obj);
        if (rb != nullptr) {
            rb->setChecked(true);
            break;
        }
    }
}



MyRadioButton::MyRadioButton(QWidget *parent)
    :QRadioButton(parent)
{

}

QLineEdit *MyRadioButton::respond_line() const
{
    return m_respond_line;
}

void MyRadioButton::setRespond_line(QLineEdit *respond_line)
{
    m_respond_line = respond_line;
}

MyPushButton::MyPushButton(QWidget *parent)
    :QPushButton (parent)
{

}

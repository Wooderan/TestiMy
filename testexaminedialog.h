#ifndef TESTEXAMINEDIALOG_H
#define TESTEXAMINEDIALOG_H

#include <QDialog>
#include "testitemwidget2.h"
#include <QTimer>
#include <test.h>

namespace Ui {
class TestExamineDialog;
}

class TestExamineDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TestExamineDialog(const Test& _test, QWidget *parent = nullptr);
    ~TestExamineDialog();

    int getMark() const;

protected slots:
    void check_results();
private slots:
    void on_btn_Ok_clicked();

    bool check_question(TestItemWidget2 *_item);
    void update_timer();
signals:
    void TimeOut();
private:
    Ui::TestExamineDialog *ui;
    QTimer *timer;
    int mark;
    int questions;
};

#endif // TESTEXAMINEDIALOG_H

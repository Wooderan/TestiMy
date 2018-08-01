#ifndef TESTITEMWIDGET_H
#define TESTITEMWIDGET_H

#include <QVBoxLayout>
#include <QWidget>
#include "testitem.h"

class TestItemWidget : public QWidget
{
    Q_OBJECT
private:
    QVBoxLayout *mainLayout;
    QString correct_variant;
    void fill_subLayout(QGridLayout *_layout, const TestItem &_item);
public:
    explicit TestItemWidget(const TestItem& _item, QWidget *parent = nullptr);

signals:

public slots:
};

#endif // TESTITEMWIDGET_H

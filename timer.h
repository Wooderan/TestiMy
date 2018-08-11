#ifndef TIMER_H
#define TIMER_H

#include <QObject>
#include <QTimeEdit>

class Timer : public QTimeEdit
{
    Q_OBJECT
    Q_PROPERTY(char warn READ warn WRITE setWarn NOTIFY warnChanged)
    char m_warn;

public:
    explicit Timer(QWidget *parent = nullptr);

char warn() const
{
    return m_warn;
}

signals:

void warnChanged(char warn);

public slots:
void setWarn(char warn)
{
    if (m_warn == warn)
        return;

    m_warn = warn;
    emit warnChanged(m_warn);
}
};

#endif // TIMER_H

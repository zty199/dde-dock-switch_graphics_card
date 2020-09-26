#ifndef SWITCHITEMWIDGET_H
#define SWITCHITEMWIDGET_H

#include <QPushButton>
#include <QMessageBox>
#include <QTimer>

#include "ddeUtil.h"

class SwitchGraphicsCardAppletWidget : public QWidget
{
    Q_OBJECT

private:

    QPushButton *IntelCard;
    QPushButton *NvidiaCard;
    QTimer *RefreshTimer;
    QProcess *process;

    QString CardName;
    QString locale;

private slots:
    void SwitchIntel();
    void SwitchNvidia();

public:
    explicit SwitchGraphicsCardAppletWidget(QWidget *parent = nullptr);

    QString GetCardName();
    QString GetLocale();
    void UpdateGraphicsInfo();

};

#endif

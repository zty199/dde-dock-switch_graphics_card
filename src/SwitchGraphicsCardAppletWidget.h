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

private slots:
    void SwitchIntel();
    void SwitchNvidia();

public:
    explicit SwitchGraphicsCardAppletWidget(QWidget *parent = nullptr);

    QString GetCardName();
    void UpdateConfig();
    void UpdateCardName();

};

#endif

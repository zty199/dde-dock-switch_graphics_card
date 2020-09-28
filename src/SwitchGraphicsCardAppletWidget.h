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
    QTimer *RefreshTimer;

    QPushButton *Intel;
    QPushButton *NVIDIA;
    QProcess *process;

    QString CardName;
    QString Locale;

private slots:
    void switchIntel();
    void switchNVIDIA();

public:
    explicit SwitchGraphicsCardAppletWidget(QWidget *parent = nullptr);

    void setCardName();
    QString getCardName();
    void setLocale();
    QString getLocale();
    void refreshButton();

};

#endif

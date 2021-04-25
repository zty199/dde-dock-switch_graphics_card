#ifndef SWITCHITEMWIDGET_H
#define SWITCHITEMWIDGET_H

#include "ddeUtil.h"

class SwitchGraphicsCardAppletWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SwitchGraphicsCardAppletWidget(QWidget *parent = nullptr);

    void setCardName();
    QString getCardName();
    void refreshButton();

private:
    QPushButton *btn_intel;
    QPushButton *btn_nvidia;
    QProcess *process;

    QString m_cardName;
    QString m_locale;

private slots:
    void switchIntel();
    void switchNVIDIA();

};

#endif

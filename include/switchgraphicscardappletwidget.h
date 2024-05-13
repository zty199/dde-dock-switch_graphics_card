#ifndef SWITCHITEMWIDGET_H
#define SWITCHITEMWIDGET_H

#include <DPushButton>

#include <QProcess>

class SwitchGraphicsCardAppletWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SwitchGraphicsCardAppletWidget(QWidget *parent = nullptr);
    ~SwitchGraphicsCardAppletWidget();

private:
    void initUI();
    void initConnections();

private slots:
    void slotIntelButtonClicked();
    void slotNvidiaButtonClicked();

private:
    Dtk::Widget::DPushButton *m_intelButton = nullptr;
    Dtk::Widget::DPushButton *m_nvidiaButton = nullptr;

    QString m_cardName;
    QString m_locale;
};

#endif

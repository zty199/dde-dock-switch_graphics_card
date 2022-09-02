#ifndef SWITCHITEMWIDGET_H
#define SWITCHITEMWIDGET_H

#include <DPushButton>

#include <QProcess>

DWIDGET_USE_NAMESPACE

class SwitchGraphicsCardAppletWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SwitchGraphicsCardAppletWidget(QWidget *parent = nullptr);
    ~SwitchGraphicsCardAppletWidget();

    void setCardName();
    QString getCardName() const;

    void updateButtonText();

private:
    void initUI();
    void initConnections();

private slots:
    void slotIntelButtonClicked();
    void slotNvidiaButtonClicked();

private:
    QPushButton *m_intelButton = nullptr;
    QPushButton *m_nvidiaButton = nullptr;
    QProcess *m_process = nullptr;

    QString m_cardName;
    QString m_locale;
};

#endif

#ifndef INFORMATIONWIDGET_H
#define INFORMATIONWIDGET_H

#include <QLabel>
#include <QTimer>
#include <QVBoxLayout>

#include "ddeUtil.h"
#include "SwitchGraphicsCardAppletWidget.h"

class SwitchGraphicsCardWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SwitchGraphicsCardWidget(QWidget *parent = nullptr);

    void getInfo(SwitchGraphicsCardAppletWidget *m_appletWidget);

private slots:
    // 用于更新数据的槽函数
    void refreshIcon();

private:
    // 真正的数据显示在这个 Label 上
    QLabel *m_infoLabel;
    // 处理时间间隔的计时器
    QTimer *m_refreshTimer;

    // 储存 SwitchGraphicsCardPlugin.cpp 中实例化的 m_appletWidget
    SwitchGraphicsCardAppletWidget *m_appletWidget;

};

#endif // INFORMATIONWIDGET_H

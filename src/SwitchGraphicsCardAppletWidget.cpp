#include "SwitchGraphicsCardAppletWidget.h"

SwitchGraphicsCardAppletWidget::SwitchGraphicsCardAppletWidget(QWidget *parent) : 
        QWidget(parent),
        RefreshTimer(new QTimer(this))
{
    resize(150, 60);

    IntelCard = new QPushButton(this);
    IntelCard->resize(148, 28);
    IntelCard->move(1, 1);
    IntelCard->setText("切换 Intel 显卡");
    NvidiaCard = new QPushButton(this);
    NvidiaCard->resize(148, 28);
    NvidiaCard->move(1, 30);
    NvidiaCard->setText("切换 NVIDIA 显卡");

    // 连接 Timer 超时的信号到更新数据的槽上
    connect(RefreshTimer, &QTimer::timeout, this, &SwitchGraphicsCardAppletWidget::UpdateGraphicsInfo);
    connect(IntelCard, SIGNAL(clicked(bool)), this, SLOT(SwitchIntel()));
    connect(NvidiaCard, SIGNAL(clicked(bool)), this, SLOT(SwitchNvidia()));

    // 设置 Timer 超时为 10s，即每 10s 更新一次控件上的数据，并启动这个定时器
    RefreshTimer->start(10000);

    UpdateGraphicsInfo();
}

QString SwitchGraphicsCardAppletWidget::GetCardName()
{
    return this->CardName;
}

void SwitchGraphicsCardAppletWidget::SwitchIntel()
{
    if(this->CardName == "Intel"){
        QMessageBox::warning(NULL, "警告", tr("已经是 Intel 显卡了！"));
        return;
    }

    system("pkexec sh /opt/apps/com.deepin.dde-dock-graphics-plugin/files/bin/Intel.sh");
}

void SwitchGraphicsCardAppletWidget::SwitchNvidia()
{
    if(this->CardName == "NVIDIA"){
        QMessageBox::warning(NULL, "警告", tr("已经是 NVIDIA 显卡了！"));
        return;
    }

    system("pkexec sh /opt/apps/com.deepin.dde-dock-graphics-plugin/files/bin/NVIDIA.sh");
}

void SwitchGraphicsCardAppletWidget::UpdateGraphicsInfo()
{
    // 刷新显卡信息
    system("sh /opt/apps/com.deepin.dde-dock-graphics-plugin/files/bin/CheckConf.sh");
    QFile Config(QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + ConfigFilePath);
    Config.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray TextByte = Config.readAll();
    Config.close();
    CardName = QString(TextByte);
}

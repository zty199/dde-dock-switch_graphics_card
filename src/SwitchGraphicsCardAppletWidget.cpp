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

    //设置 10s 定时器
    RefreshTimer->start(10000);

    connect(IntelCard, SIGNAL(clicked(bool)), this, SLOT(SwitchIntel()));
    connect(NvidiaCard, SIGNAL(clicked(bool)), this, SLOT(SwitchNvidia()));
    connect(RefreshTimer, &QTimer::timeout, this, &SwitchGraphicsCardAppletWidget::UpdateCardName);

    UpdateCardName();
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

    CardName = "Intel";
    UpdateConfig();
    system("pkexec sh /opt/durapps/dde-dock-switch_graphics_card/Intel.sh");
}

void SwitchGraphicsCardAppletWidget::SwitchNvidia()
{
    if(this->CardName == "NVIDIA"){
        QMessageBox::warning(NULL, "警告", tr("已经是 NVIDIA 显卡了！"));
        return;
    }

    CardName = "Intel";
    UpdateConfig();
    system("pkexec sh /opt/durapps/dde-dock-switch_graphics_card/NVIDIA.sh");
}

void SwitchGraphicsCardAppletWidget::UpdateConfig()
{
    QFile Config(QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + ConfigFilePath);
    // 没有显卡配置文件则进行初始化
    if(!Config.exists())
    {
        system("sh /opt/durapps/dde-dock-switch_graphics_card/CheckConf.sh");
    }
    Config.open(QIODevice::WriteOnly | QIODevice::Truncate);
    Config.write(CardName.toUtf8());
    Config.close();
}

void SwitchGraphicsCardAppletWidget::UpdateCardName()
{
    QFile Config(QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + ConfigFilePath);
    // 没有显卡配置文件则进行初始化
    if(!Config.exists())
    {
        system("sh /opt/durapps/dde-dock-switch_graphics_card/CheckConf.sh");
    }
    Config.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray TextByte = Config.readAll();
    Config.close();
    
    CardName = QString(TextByte);
    if(CardName.isEmpty() || (CardName != "Intel" && CardName != "NVIDIA"))
    {
        system("sh /opt/durapps/dde-dock-switch_graphics_card/CheckConf.sh");
    }
}

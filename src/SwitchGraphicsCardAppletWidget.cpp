#include "SwitchGraphicsCardAppletWidget.h"

SwitchGraphicsCardAppletWidget::SwitchGraphicsCardAppletWidget(QWidget *parent) : 
        QWidget(parent),
        RefreshTimer(new QTimer(this))
{
    resize(30, 60);

    IntelCard = new QPushButton(this);
    IntelCard->resize(28, 28);
    IntelCard->move(1, 1);
    IntelCard->setIcon(QIcon(IntelIconPath));
    NvidiaCard = new QPushButton(this);
    NvidiaCard->resize(28, 28);
    NvidiaCard->move(1, 30);
    NvidiaCard->setIcon(QIcon(NvidiaIconPath));

    //设置10s定时器
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
        QMessageBox::about(NULL, "Tips", tr("已经是Intel显卡了！"));
        return;
    }

    system("deepin-terminal -e /opt/durapps/dde-dock-switch_graphics_card/Intel.sh");
}

void SwitchGraphicsCardAppletWidget::SwitchNvidia()
{
    if(this->CardName == "Nvidia"){
        QMessageBox::about(NULL, "Tips", tr("已经是NVIDIA显卡了！"));
        return;
    }

    system("deepin-terminal -e /opt/durapps/dde-dock-switch_graphics_card/NVIDIA.sh");
}

void SwitchGraphicsCardAppletWidget::UpdateConfig()
{
    QFile Config(QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + ConfigFilePath);
    // 没有显卡配置文件则进行初始化
    if(!Config.exists())
    {
        system("deepin-terminal -e /opt/durapps/dde-dock-switch_graphics_card/Initialize.sh");
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
        system("deepin-terminal -e /opt/durapps/dde-dock-switch_graphics_card/Initialize.sh");
    }
    Config.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray TextByte = Config.readAll();
    Config.close();
    
    CardName = QString(TextByte);
    if(CardName.isEmpty()){
        system("deepin-terminal -e /opt/durapps/dde-dock-switch_graphics_card/Initialize.sh");
    }
}

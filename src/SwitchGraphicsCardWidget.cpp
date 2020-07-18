#include "SwitchGraphicsCardWidget.h"

SwitchGraphicsCardWidget::SwitchGraphicsCardWidget(QWidget *parent)
    : QWidget(parent)
    , m_infoLabel(new QLabel)
    , m_refreshTimer(new QTimer(this))
{
    m_infoLabel->setStyleSheet("QLabel {"
                               "color: white;"
                               "}");
    m_infoLabel->setAlignment(Qt::AlignCenter);

    QVBoxLayout *centralLayout = new QVBoxLayout;
    centralLayout->addWidget(m_infoLabel);
    centralLayout->setSpacing(0);
    centralLayout->setMargin(0);

    setLayout(centralLayout);

    // 连接 Timer 超时的信号到更新数据的槽上
    connect(m_refreshTimer, &QTimer::timeout, this, &SwitchGraphicsCardWidget::RefreshInfo);

    // 设置 Timer 超时为 10s，即每 10s 更新一次控件上的数据，并启动这个定时器
    m_refreshTimer->start(10000);

    RefreshInfo();
}

void SwitchGraphicsCardWidget::RefreshInfo()
{
    QFile Config(QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + ConfigFilePath);
    // 没有显卡配置文件则进行初始化
    if(!Config.exists())
    {
        system("deepin-terminal -e /opt/durapps/dde-dock-switch_graphics_card/Initialize.sh");
    }
    Config.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray TextByte = Config.readAll();

    // 更新内容
    m_infoLabel->setText(QString(TextByte));
}

#include "SwitchGraphicsCardWidget.h"

SwitchGraphicsCardWidget::SwitchGraphicsCardWidget(QWidget *parent) :
    QWidget(parent),
    m_infoLabel(new QLabel),
    m_refreshTimer(new QTimer(this))
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
    connect(m_refreshTimer, &QTimer::timeout, this, &SwitchGraphicsCardWidget::RefreshIcon);

    // 设置 Timer 超时为 10s，即每 10s 更新一次控件上的数据，并启动这个定时器
    m_refreshTimer->start(10000);

    RefreshIcon();
}

void SwitchGraphicsCardWidget::RefreshIcon()
{
    // 刷新显卡信息
    system("sh /opt/durapps/dde-dock-switch_graphics_card/bin/CheckConf.sh");
    QFile Config(QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + ConfigFilePath);
    Config.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray TextByte = Config.readAll();
    Config.close();
    QString CardName = QString(TextByte);

    QImage *img = new QImage;   // 新建一个image对象
    if(CardName == "Intel")
    {
        img->load(IntelIconPath);   // 载入图像资源
    }
    else {
        img->load(NvidiaIconPath);
    }
    // 更新 dock栏 图标
    m_infoLabel->setPixmap(QPixmap::fromImage(*img));
}

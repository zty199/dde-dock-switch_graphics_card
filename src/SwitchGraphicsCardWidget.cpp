#include "SwitchGraphicsCardWidget.h"
#include <DGuiApplicationHelper>

DGUI_USE_NAMESPACE

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

    connect(DGuiApplicationHelper::instance(), &DGuiApplicationHelper::themeTypeChanged, this, [ = ] {
        refreshIcon();
    });

    /* 可以设置定时刷新 */
    // 连接 Timer 超时的信号到更新数据的槽上
    //connect(m_refreshTimer, &QTimer::timeout, this, &SwitchGraphicsCardWidget::getInfo);

    // 设置 Timer 超时为 10s，即每 10s 更新一次控件上的数据，并启动这个定时器
    //m_refreshTimer->start(10000);

    //getInfo();
}

void SwitchGraphicsCardWidget::getInfo(SwitchGraphicsCardAppletWidget *m_appletWidget)
{
    // 获取 appletwidget 中的信息
    this->m_appletWidget = m_appletWidget;

    // 刷新图标
    refreshIcon();
}

void SwitchGraphicsCardWidget::refreshIcon()
{
    // 双重触发机制：1.手动刷新信息  2.系统主题改变

    // 获取 appletwidget 中的显卡信息
    QString CardName = m_appletWidget->getCardName();
    QImage *img = new QImage;   // 新建一个image对象
    if(CardName == "Intel")
    {
        if(DGuiApplicationHelper::instance()->themeType() == DGuiApplicationHelper::LightType)  // 判断主题颜色
            img->load(IntelDarkPath);   // 载入图像资源
        else
            img->load(IntelLightPath);
    }
    else {
        if(DGuiApplicationHelper::instance()->themeType() == DGuiApplicationHelper::LightType)
            img->load(NvidiaDarkPath);
        else
            img->load(NvidiaLightPath);
    }

    // 更新 dock栏 图标
    m_infoLabel->setPixmap(QPixmap::fromImage(*img));
}

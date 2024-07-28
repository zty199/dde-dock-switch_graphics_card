#include "switchgraphicscardwidget.h"
#include "switchgraphicscarditem.h"
#include "../include/common.h"
#include "utils.h"

#include <constants.h>

#include <DGuiApplicationHelper>

#include <QPainter>
#include <QPainterPath>
#include <QtMath>

DGUI_USE_NAMESPACE

SwitchGraphicsCardWidget::SwitchGraphicsCardWidget(QWidget *parent)
    : QWidget(parent)
{
    initUI();
    initConnections();
}

void SwitchGraphicsCardWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    m_icon.paint(&painter, rect());

    QWidget::paintEvent(event);
}

void SwitchGraphicsCardWidget::initUI()
{
    setMinimumSize(PLUGIN_BACKGROUND_MIN_SIZE, PLUGIN_BACKGROUND_MIN_SIZE);

    refreshIcon();
}

void SwitchGraphicsCardWidget::initConnections()
{
    connect(DGuiApplicationHelper::instance(), &DGuiApplicationHelper::themeTypeChanged,
            this, &SwitchGraphicsCardWidget::refreshIcon);
}

void SwitchGraphicsCardWidget::refreshIcon()
{
    // 获取 appletwidget 中的信息
    QString iconName = kDefaultIconName;
    if (Singleton<SwitchGraphicsCardItem>::instance()->cardName() == "Intel") {
        iconName = kIntelIconName;
    } else if (Singleton<SwitchGraphicsCardItem>::instance()->cardName() == "NVIDIA") {
        iconName = kNvidiaIconName;
    }
    if (DGuiApplicationHelper::instance()->themeType() == DGuiApplicationHelper::LightType) {
        iconName += PLUGIN_MIN_ICON_NAME;
    }

    QPixmap pixmap = Utils::loadSVG(QString(":/icons/%1.svg").arg(iconName), Dock::DOCK_PLUGIN_ITEM_FIXED_SIZE);
    m_icon = QIcon(pixmap);

    // 刷新图标
    update();
}

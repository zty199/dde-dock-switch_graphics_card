#include "switchgraphicscardwidget.h"
#include "common.h"

#include <DGuiApplicationHelper>
#include <DStyle>

#include <QPainterPath>
#include <QtMath>

DWIDGET_USE_NAMESPACE

SwitchGraphicsCardWidget::SwitchGraphicsCardWidget(QWidget *parent)
    : QWidget(parent)
{
    setMouseTracking(true);

    initUI();
    initConnections();
}

SwitchGraphicsCardWidget::~SwitchGraphicsCardWidget()
{
}

void SwitchGraphicsCardWidget::updateData(SwitchGraphicsCardAppletWidget *m_appletWidget)
{
    // 获取 appletwidget 中的信息
    m_cardName = m_appletWidget->getCardName();

    // 刷新图标
    update();
}

void SwitchGraphicsCardWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::HighQualityAntialiasing | QPainter::SmoothPixmapTransform | QPainter::Antialiasing);
    painter.save();

    // 获取图标名称
    QString iconName;
    if (m_cardName == "Intel") {
        iconName = kIntelIconName;
    } else {
        iconName = kNvidiaIconName;
    }

    // 绘制图标背景
    int minSize = qMin(width(), height());
    if (minSize > PLUGIN_BACKGROUND_MIN_SIZE) {
        QColor color;
        if (DGuiApplicationHelper::instance()->themeType() == DGuiApplicationHelper::LightType) {
            color = Qt::black;
            painter.setOpacity(0.5);
            if (m_hover) {
                painter.setOpacity(0.6);
            }
            if (m_pressed) {
                painter.setOpacity(0.3);
            }
        } else {
            color = Qt::white;
            painter.setOpacity(0.1);
            if (m_hover) {
                painter.setOpacity(0.2);
            }
            if (m_pressed) {
                painter.setOpacity(0.05);
            }
        }

        QPainterPath path;

        QRect rect(0, 0, minSize, minSize);
        rect.moveTo(this->rect().center() - rect.center());

        DStyleHelper dstyle(style());
        const int radius = dstyle.pixelMetric(DStyle::PM_FrameRadius);

        path.addRoundedRect(rect, radius, radius);
        painter.fillPath(path, color);
    } else if (DGuiApplicationHelper::instance()->themeType() == DGuiApplicationHelper::LightType) {
        iconName += PLUGIN_MIN_ICON_NAME;
    }

    painter.restore();

    QString fileName = QString(":/icons/icons/%1.svg").arg(iconName);
    QPixmap pixmap = loadSVG(fileName, QSize(PLUGIN_ICON_MAX_SIZE, PLUGIN_ICON_MAX_SIZE));

    const QRectF &rectf = QRectF(rect());
    const QRectF &pixmapRectf = QRectF(pixmap.rect());
    painter.drawPixmap(rectf.center() - pixmapRectf.center() / devicePixelRatioF(), pixmap);

    QWidget::paintEvent(event);
}

void SwitchGraphicsCardWidget::mousePressEvent(QMouseEvent *event)
{
    m_pressed = true;
    update();

    QWidget::mousePressEvent(event);
}

void SwitchGraphicsCardWidget::mouseMoveEvent(QMouseEvent *event)
{
    m_hover = true;

    QWidget::mouseMoveEvent(event);
}

void SwitchGraphicsCardWidget::mouseReleaseEvent(QMouseEvent *event)
{
    m_pressed = false;
    m_hover = false;
    update();

    QWidget::mouseReleaseEvent(event);
}

void SwitchGraphicsCardWidget::leaveEvent(QEvent *event)
{
    m_hover = false;
    m_pressed = false;
    update();

    QWidget::leaveEvent(event);
}

void SwitchGraphicsCardWidget::initUI()
{
    setMinimumSize(PLUGIN_BACKGROUND_MIN_SIZE, PLUGIN_BACKGROUND_MIN_SIZE);
}

void SwitchGraphicsCardWidget::initConnections()
{
    connect(DGuiApplicationHelper::instance(), &DGuiApplicationHelper::themeTypeChanged, this, [=]() {
        update();
    });
}

const QPixmap SwitchGraphicsCardWidget::loadSVG(const QString &fileName, const QSize &size) const
{
    const qreal ratio = devicePixelRatioF();

    QPixmap pixmap;
    pixmap = QIcon::fromTheme(fileName).pixmap(size * ratio);
    pixmap.setDevicePixelRatio(ratio);

    return pixmap;
}

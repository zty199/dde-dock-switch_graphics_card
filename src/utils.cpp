#include "utils.h"

#include <QIcon>
#include <QCoreApplication>
#include <QSvgRenderer>
#include <QPainter>

const QPixmap Utils::loadSVG(const QString &iconName, const QSize size, const qreal ratio)
{
    QIcon icon = QIcon::fromTheme(iconName);
    if (!icon.isNull()) {
        QPixmap pixmap = icon.pixmap(QCoreApplication::testAttribute(Qt::AA_UseHighDpiPixmaps) ? size : QSize(size * ratio));
        pixmap.setDevicePixelRatio(ratio);
        if (ratio == 1) {
            return pixmap;
        }

        if (pixmap.size().width() > size.width() * ratio) {
            pixmap = pixmap.scaledToWidth(size.width() * ratio);
        }
        if (pixmap.size().height() > size.height() * ratio) {
            pixmap = pixmap.scaledToHeight(size.height() * ratio);
        }

        return pixmap;
    }

    return QPixmap();
}

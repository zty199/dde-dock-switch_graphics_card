#ifndef UTILS_H
#define UTILS_H

#include <QPixmap>
#include <QGuiApplication>

class Utils
{
public:
    static const QPixmap loadSVG(const QString &iconName, const QSize size, const qreal ratio = qApp->devicePixelRatio());
};

#endif // UTILS_H

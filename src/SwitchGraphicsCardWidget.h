#ifndef INFORMATIONWIDGET_H
#define INFORMATIONWIDGET_H

#include "ddeUtil.h"
#include "constants.h"

#include "SwitchGraphicsCardAppletWidget.h"

class SwitchGraphicsCardWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SwitchGraphicsCardWidget(QWidget *parent = nullptr);

    void getInfo(SwitchGraphicsCardAppletWidget *m_appletWidget);

protected:
    void paintEvent(QPaintEvent *e) override;

private:
    // 通过 SwitchGraphicsCardPlugin.cpp 中实例化的 m_appletWidget 获取当前显卡
    QString CardName;

    bool m_hover;
    bool m_pressed;

    const QString Intel_dark = ":/icons/icons/Intel_dark.svg";
    const QString Intel_light = ":/icons/icons/Intel_light.svg";
    const QString NVIDIA_dark = ":/icons/icons/NVIDIA_dark.svg";
    const QString NVIDIA_light = ":/icons/icons/NVIDIA_light.svg";

    const QPixmap loadSVG(const QString &fileName, const QSize &size) const;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

};

#endif // INFORMATIONWIDGET_H

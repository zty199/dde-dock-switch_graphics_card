#ifndef INFORMATIONWIDGET_H
#define INFORMATIONWIDGET_H

#include "switchgraphicscardappletwidget.h"
#include "constants.h"

class SwitchGraphicsCardWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SwitchGraphicsCardWidget(QWidget *parent = nullptr);
    ~SwitchGraphicsCardWidget() override;

    void updateData();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void leaveEvent(QEvent *event) override;

private:
    void initUI();
    void initConnections();

private:
    // 通过 SwitchGraphicsCardPlugin.cpp 中实例化的 m_appletWidget 获取当前显卡
    QString m_cardName = "";

    bool m_hover = false;
    bool m_pressed = false;
};

#endif // INFORMATIONWIDGET_H

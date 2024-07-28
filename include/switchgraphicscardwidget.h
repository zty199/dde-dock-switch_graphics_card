#ifndef INFORMATIONWIDGET_H
#define INFORMATIONWIDGET_H

#include <QWidget>
#include <QIcon>

class SwitchGraphicsCardWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SwitchGraphicsCardWidget(QWidget *parent = nullptr);
    ~SwitchGraphicsCardWidget() override = default;

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void initUI();
    void initConnections();

public slots:
    void refreshIcon();

private:
    QIcon m_icon;
};

#endif // INFORMATIONWIDGET_H

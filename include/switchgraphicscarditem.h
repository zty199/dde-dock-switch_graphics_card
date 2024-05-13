#ifndef SWITCHGRAPHICSCARDITEM_H
#define SWITCHGRAPHICSCARDITEM_H

#include "singleton.hpp"

#include <QProcess>

class SwitchGraphicsCardItem : public QObject
{
    Q_OBJECT

public:
    enum Status {
        Initializing = -1,
        InitializeFailed = 0,
        InitializeFinished = 1
    };

    Status status() const;
    QString cardName() const;

private:
    explicit SwitchGraphicsCardItem(QObject *parent = nullptr);

signals:
    void sigStatusChanged(Status status);

public slots:
    void refresh();

private slots:
    void slotProcessFinished(int exitCode, QProcess::ExitStatus exitStatus);

private:
    QProcess *m_process = nullptr;

    Status m_status = Initializing;
    QString m_cardName;

    template<typename>
    friend class Singleton;
};

#endif // SWITCHGRAPHICSCARDITEM_H

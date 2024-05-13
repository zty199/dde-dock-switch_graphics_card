#include "switchgraphicscarditem.h"

#include <QDebug>

SwitchGraphicsCardItem::SwitchGraphicsCardItem(QObject *parent)
    : QObject(parent)
{
    m_process = new QProcess(this);
    connect(m_process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, &SwitchGraphicsCardItem::slotProcessFinished);

    QString cmd = "/bin/sh";
    QStringList args {"/opt/apps/dde-dock-graphics-plugin/files/bin/CheckGraphics.sh"};
    m_process->setProgram(cmd);
    m_process->setArguments(args);
}

SwitchGraphicsCardItem::Status SwitchGraphicsCardItem::status() const
{
    return m_status;
}

QString SwitchGraphicsCardItem::cardName() const
{
    return m_cardName;
}

void SwitchGraphicsCardItem::refresh()
{
    m_cardName.clear();

    m_status = Initializing;
    emit sigStatusChanged(m_status);

    m_process->start();
}

void SwitchGraphicsCardItem::slotProcessFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    if (exitCode != 0 || exitStatus != QProcess::NormalExit) {
        qWarning().noquote() << "Initialize current graphics card name failed!";

        m_status = InitializeFailed;
        emit sigStatusChanged(m_status);
        return;
    }

    m_cardName = m_process->readAllStandardOutput().trimmed();
    m_process->close();

    m_status = InitializeFinished;
    emit sigStatusChanged(m_status);
}

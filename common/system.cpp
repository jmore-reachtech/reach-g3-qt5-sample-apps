#include <QFile>
#include <QProcess>
#include <QDebug>

#include "system.h"

System::System(QObject *parent): QObject(parent), m_version("") {}

QString System::version()
{
    if (!m_version.isEmpty())
    {
        return m_version;
    }

    QFile f(SYSTEM_RELEASE_FILE);

    if (!f.exists())
    {
        qDebug() << "release file not found";
        return "0.0.0";
    }

    qDebug() << "reading system version";
    f.open(QIODevice::ReadOnly);
    QTextStream in (&f);
    m_version = in .readLine();
    f.close();

    return m_version;
}

QString System::execute(QString cmd)
{
    QProcess p(this);
    p.start(cmd);
    p.waitForFinished();
    QByteArray data = p.readAllStandardOutput();
    return QString::fromLatin1(data.data());
}

QString System::execute(QString cmd, QStringList args)
{
    QProcess p(this);
    p.start(cmd, args);
    p.waitForFinished();
    QByteArray data = p.readAllStandardOutput();
    return QString::fromLatin1(data.data());
}

bool System::executeUpgrade(QStringList args)
{
    return QProcess::startDetached("/usr/bin/qml-upgrade-helper.sh", args, "/data");

}

// Set the wav file and then play it.
void System::doTheBeep(QString file)
{
    qDebug() << "doTheBeep";
    emit setSoundFile(file);  //set the sound file
    emit doBeep();            //do the actual beep
}

// Execute a linux command and return the output as a string
QString System::doCommand(QString cmd)
{
    qDebug() << "doCommand == " << cmd;
    QProcess *proc_ovpn = new QProcess();
    proc_ovpn->start("sh",QStringList() << "-c" << cmd);
    if(!proc_ovpn->waitForStarted())  //default wait time 30 sec
    {
        qWarning() << " cannot start process ";
    }

    int waitTime = 600 ; //60 sec
    if (!proc_ovpn->waitForFinished(waitTime))
    {
        qWarning() << "timeout .. ";
    }

    proc_ovpn->setProcessChannelMode(QProcess::MergedChannels);
    QString str(proc_ovpn->readAllStandardOutput());
    return str;
}

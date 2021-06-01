// Copyright 2020 Reach Technology

// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.

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
    const QStringList args;
    QProcess p(this);
    p.start(cmd, args);
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
void System::doTheBeep(const QString file)
{
    qDebug() << "Opening " << file ;
    emit setSoundFile(file);  //set the sound file
    emit beep();            //do the actual beep
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

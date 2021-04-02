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

#include <QNetworkInterface>
#include <QHostAddress>

#include "network.h"

Network::Network(QObject *parent): QObject(parent)
{
    qDebug() << "[NET] CTOR Up";



}

QString Network::ipAddress()
{
    QNetworkInterface iface = QNetworkInterface::interfaceFromName("eth0");

    qDebug() << "[NET] Up";

    if (!iface.isValid())
    {
        return "127.0.0.1";
    }

    const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
    for (const QHostAddress &address: QNetworkInterface::allAddresses())
    {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost)
        {
            qDebug() << "Network Address " << address.toString();
            return address.toString();
        }
    }

    return "127.0.0.1";
}

void Network::setIpAddress(const QString &ip)
{
    QHostAddress addr(ip);

    qDebug() << "Setting ip address: " << addr;

    emit ipAddressChanged();
}

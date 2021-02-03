#ifndef SERIALCONTROLLER_H
#define SERIALCONTROLLER_H

#include <QObject>
#include <QSerialPort>
#include <QSettings>
#include <QString>
#include <QDebug>
#include "translator.h"

class SerialController : public QObject
{
    Q_OBJECT
    //Q_Property()

public:
    explicit SerialController(QObject *parent = nullptr);
    ~SerialController();

    void setTranslator(Translator& t);

signals:
    void messageAvailable(QStringList msg);

public slots:
    void send(QString msg);
    void onSerialReadyRead(void);

private slots:

private:
    QSerialPort m_port;
    QSettings m_settings;
    Translator* m_translator;
};

#endif // SERIALCONTROLLER_H

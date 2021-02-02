#ifndef MYGLOBAL_H
#define MYGLOBAL_H

#include <QQmlPropertyMap>

class GlobalValues : public QQmlPropertyMap
{
    Q_OBJECT
    public:
    GlobalValues(QObject* parent = nullptr);

    Q_INVOKABLE void startEngine();

    QVariant doUpdate(const QString key, const QVariant input);

};

#endif // MYGLOBAL_H

#include "myStyle.h"
#include <QDebug>

StyleValues::StyleValues(QObject * parent): QQmlPropertyMap(this, parent) {
  setObjectName("style");
  insert("statusBarHeight", QVariant::fromValue(40));
  insert("titleColor", "#c2b59b");

//  insert("propertyTitleColor", "#889607");
//  insert("propertyBPColor", "#fafa74");
//  insert("propertyTitleColorDark", "black");
//  insert("propertyValueColor", "white");

  insert("columnSpacing", QVariant::fromValue(102));
  insert("rowSpacing", QVariant::fromValue(40));

  insert("themeDark", true);
  insert("textColor", QVariant::fromValue(QString("black")));
  insert("backColor", QVariant::fromValue(QString("gray")));
  insert("statusBackColor", QVariant::fromValue(QString("white")));
  insert("statusTextColor", QVariant::fromValue(QString("black")));

  insert("textColorLt", QVariant::fromValue(QString("white")));
  insert("backColorLt", QVariant::fromValue(QString("gray")));
  insert("statusBackColorLt", QVariant::fromValue(QString("white")));
  insert("statusTextColorLt", QVariant::fromValue(QString("black")));

  insert("textColorDk", QVariant::fromValue(QString("red")));
  insert("backColorDk", QVariant::fromValue(QString("white")));
  insert("statusBackColorDk", QVariant::fromValue(QString("gray")));
  insert("statusTextColorDk", QVariant::fromValue(QString("black")));

  insert("btnColor", QVariant::fromValue(QString("green")));

  insert("imgLogo", QVariant::fromValue(QString("Images/reach_logo_color_30.png")));
  insert("borderWidth", QVariant::fromValue(3));
  insert("borderRadius", QVariant::fromValue(15));
  insert("borderColor", QVariant::fromValue(QString("white")));

  insert("dialWidth", QVariant::fromValue(150));
  insert("dialHeight", QVariant::fromValue(200));
  insert("dialBarWidth", QVariant::fromValue(15));
  insert("dialTicksOn", QVariant::fromValue(true));

  insert("componentX", QVariant::fromValue(130));
  insert("componentY", QVariant::fromValue(160));
  insert("iconSize", QVariant::fromValue(100));

  insert("clrConnBox", QVariant::fromValue(QString("tan")));
}

void StyleValues::startEngine() {
  qDebug() << "Start ENGINE STYLE " << Q_FUNC_INFO;
}

QString StyleValues::getColor(const QString name) {
  QVariant tempColor = value(name);
  return tempColor.value < QString > ();
}

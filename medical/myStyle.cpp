#include "myStyle.h"
#include <QDebug>

StyleValues::StyleValues(QObject * parent): QQmlPropertyMap(this, parent) {
  setObjectName("style");

  //Styles
  insert("titleColor", "#c2b59b");
  insert("propertyTitleColor", "#889607");
  insert("propertyBPColor", "#fafa74");
  insert("propertyTitleColorDark", "black");
  insert("propertyValueColor", "white");

  insert("blueColor", "blue");
  insert("purpleColor", "purple");
  insert("greenColor", "green");

  insert("barGraphOffColor", "#404040");
  insert("barGraphOnColor", "white");
  insert("backgroundColor", "black");

  insert("alarmColorBool", false);
  insert("alarmColorOn", "red");
  insert("alarmBtnBckGOn", "lightGray");
  insert("alarmColorOff", "gray");
  insert("alarmBtnBckGOff", "lightGray");
  insert("alarmFontColor", "black");

  insert("vitalsImageBool", false);
  insert("vitalsColorOn", "yellow");
  insert("vitalsBtnBckGOn", "lightGray");
  insert("vitalsColorOff", "gray");
  insert("vitalsBtnBckGOff", "lightGray");
  insert("vitalsFontColor", "black");

  insert("helpImageBool", false);
  insert("helpColorOn", "yellow");
  insert("helpBtnBckGOn", "lightGray");
  insert("helpColorOff", "gray");
  insert("helpBtnBckGOff", "lightGray");
  insert("helpFontColor", "black");
}

void StyleValues::startEngine() {
  qDebug() << "Start ENGINE STYLE " << Q_FUNC_INFO;
}



#include "myStyle.h"
#include <QDebug>

StyleValues::StyleValues(QObject * parent): QQmlPropertyMap(this, parent) {
  setObjectName("style");
  insert("panelWidth", QVariant::fromValue(800));
  insert("panelHeight", QVariant::fromValue(480));
  insert("statusBarHeight", QVariant::fromValue(40));

  insert("columnSpacing", QVariant::fromValue(102));
  insert("rowSpacing", QVariant::fromValue(40));

  insert("themeDark", true);
  insert("backColor", QVariant::fromValue(QString("black")));
  insert("textColor", QVariant::fromValue(QString("white")));
  insert("statusBackColor", QVariant::fromValue(QString("white")));
  insert("statusTextColor", QVariant::fromValue(QString("")));

  insert("clrOff", QVariant::fromValue(QString("gray")));
  insert("clrNormal", QVariant::fromValue(QString("green")));
  insert("clrWarning", QVariant::fromValue(QString("goldenrod")));
  insert("clrFault", QVariant::fromValue(QString("#ff3434")));
  insert("clrError", QVariant::fromValue(QString("red")));

  insert("backColorLt", QVariant::fromValue(QString("white")));
  insert("textColorLt", QVariant::fromValue(QString("black")));
  insert("statusBackColorLt", QVariant::fromValue(QString("lightGrey")));
  insert("statusTextColorLt", QVariant::fromValue(QString("black")));

  insert("clrOffLt", QVariant::fromValue(QString("darkGray")));
  insert("clrNormalLt", QVariant::fromValue(QString("darkGreen")));
  insert("clrWarningLt", QVariant::fromValue(QString("yellow")));
  insert("clrFaultLt", QVariant::fromValue(QString("red")));
  insert("clrErrorLt", QVariant::fromValue(QString("darkRed")));

  insert("backColorDk", QVariant::fromValue(QString("black")));
  insert("textColorDk", QVariant::fromValue(QString("white")));
  insert("statusBackColorDk", QVariant::fromValue(QString("darkCyan")));
  insert("statusTextColorDk", QVariant::fromValue(QString("white")));

  insert("clrOffDk", QVariant::fromValue(QString("lightGray")));
  insert("clrNormalDk", QVariant::fromValue(QString("lightGreen")));
  insert("clrWarningDk", QVariant::fromValue(QString("lightYellow")));
  insert("clrFaultDk", QVariant::fromValue(QString("tomato")));
  insert("clrErrorDk", QVariant::fromValue(QString("lightRed")));

  insert("fontName", QVariant::fromValue(QString("Source Sans Pro")));
  insert("fontSize", QVariant::fromValue(17));

  insert("strOff", QVariant::fromValue(QString("System Off")));
  insert("strNormal", QVariant::fromValue(QString("System Normal")));
  insert("strWarning", QVariant::fromValue(QString("System Warning")));
  insert("strFault", QVariant::fromValue(QString("System Fault")));
  insert("strError", QVariant::fromValue(QString("System Error")));

  insert("imgOff", QVariant::fromValue(QString("Images/led_off_40.png")));
  insert("imgNormal", QVariant::fromValue(QString("Images/led_normal_40.png")));
  insert("imgWarning", QVariant::fromValue(QString("Images/led_warning_40.png")));
  insert("imgFault", QVariant::fromValue(QString("Images/led_fault_40.png")));
  insert("imgError", QVariant::fromValue(QString("Images/led_error_40.png")));
  insert("imgLogo", QVariant::fromValue(QString("Images/reach_logo_color_30.png")));

  insert("borderWidth", QVariant::fromValue(1));
  insert("borderColor", QVariant::fromValue(QString("lightGray")));

  insert("drawerFontSize", QVariant::fromValue(22));
  insert("drawerLeftMargin", QVariant::fromValue(15));

  insert("dialWidth", QVariant::fromValue(225));
  insert("dialHeight", QVariant::fromValue(300));
  insert("dialBarWidth", QVariant::fromValue(15));
  insert("dialTicksOn", QVariant::fromValue(true));

  insert("componentX", QVariant::fromValue(130));
  insert("componentY", QVariant::fromValue(160));
  insert("iconSize", QVariant::fromValue(100));

  insert("textY", QVariant::fromValue(90));
  insert("imgX", QVariant::fromValue(QString("Images/X_100.png")));

  insert("metricBool", QVariant::fromValue(false));
  insert("metricStr", QVariant::fromValue(QString("°F")));
  insert("centigradeStr", QVariant::fromValue(QString("°C")));
  insert("fahrenheitStr", QVariant::fromValue(QString("°F")));
}

void StyleValues::startEngine() {
  qDebug() << "Start ENGINE STYLE " << Q_FUNC_INFO;
}

QString StyleValues::getColor(const QString name) {
  QVariant tempColor = value(name);
  return tempColor.value < QString > ();
}

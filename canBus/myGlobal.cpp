#include "myGlobal.h"
#include <QDebug>

GlobalValues::GlobalValues(QObject * parent): QQmlPropertyMap(this, parent) {
  setObjectName("global");

  //engineRPM
  insert("engineRPMValue", 0);
  insert("engineRPMState", 0);
  insert("engineRPMMeasure", "");

  insert("engineRPMmaxText", "");
  insert("engineRPMavgText", "");
  insert("engineRPMSrcName", "Images/engine.png");

  insert("engineRPMmeasuredMaxValue", -1);
  insert("engineRPMmeasuredAvgValue", -1);

  insert("engineRPMminimumRangeValue", 0);
  insert("engineRPMmaximumRangeValue", 6000);

  insert("engineRPMwarningValueLow", 0);
  insert("engineRPMerrorValueLow", 0);
  insert("engineRPMwarningValueHigh", 4000);

  insert("engineRPMerrorValueHigh", 5000);
  insert("engineRPMbarWidth", 15);
  insert("engineRPM_ticksOn", true);

  //speedDial
  insert("speedDial_currentValue", 0);

  insert("speedDial_measuredMaxValue", -1);
  insert("speedDial_maxText", "");
  insert("speedDial_measuredAvgValue", -1);
  insert("speedDial_avgText", "");

  insert("speedDial_minimumRangeValue", 0);
  insert("speedDial_maximumRangeValue", 100);

  insert("speedDial_warningValueLow", 0);
  insert("speedDial_errorValueLow", 0);
  insert("speedDial_warningValueHigh", 80);

  insert("speedDial_errorValueHigh", 90);
  insert("speedDial_barWidth", 15);
 // insert("speedDial_ticksOn", true);

  //acceleration
  insert("airDial_currentValue", 0);
  insert("airDial_measuredMaxValue", -1);
  insert("airDial_maxText", "");
  insert("airDial_measuredAvgValue", 0);
  insert("airDial_avgText", "");
  insert("airDial_minimumRangeValue", 0);
  insert("airDial_maximumRangeValue", 100);
  insert("airDial_warningValueLow", 0);
  insert("airDial_errorValueLow", 0);
  insert("airDial_warningValueHigh", 100);
  insert("airDial_errorValueHigh", 100);
  insert("airDial_barWidth", 15);
 // insert("airDial_ticksOn", false);

}

void GlobalValues::startEngine() {
  qDebug() << "Start ENGINE GLOBAL " << Q_FUNC_INFO;
}

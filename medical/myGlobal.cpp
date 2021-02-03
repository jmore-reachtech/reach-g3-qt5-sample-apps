#include "myGlobal.h"
#include <QDebug>

GlobalValues::GlobalValues(QObject * parent): QQmlPropertyMap(this, parent) {
   setObjectName("global");
   insert("bpSysValue", 144);
   insert("bpDiaValue", 110);

   insert("patientName", "Anthony Brown");
   insert("patientNumber", "P23456789N123");
   insert("patientGender", "Male");
   insert("patientAge", 51);
   insert("patientCondition", "Stable");
   insert("patientConditionColor", "green");

   insert("patientAdmitDate", "Feb 21");
   insert("patientAdmitTime", "13:00");

   insert("hospitalName", "SF General");
   insert("hospitalRoom", "2312");

   insert("temperatureCelsius", "Celsius");
   insert("temperature1", "37.2");
   insert("temperature2", "37.1");
   insert("temperatureHigh", "38.1");
   insert("temperatureArrowRotation", 0);
   insert("temperatureArrowColor", "yellow");


   insert("ekgValue", 88);
   insert("spo2Value", 61);

   insert("salineValue", 50);
   insert("hiCorValue", 25);
   insert("glucagonValue", 54);

   insert("insulinValue", "0.52");
   insert("lastBolusValue", "3.11");
   insert("iOBValue", "2.5");
   insert("glucoseValue", "125");

   qDebug() << "GLOBALS CONSTRUCTOR "  << value("screenWidth") ;

}

void GlobalValues::startEngine() {
   qDebug() << "Start ENGINE GLOBAL " << Q_FUNC_INFO;
}

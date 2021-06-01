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

}

void GlobalValues::startEngine() {
   qDebug() << "Start ENGINE GLOBAL " << Q_FUNC_INFO;
}

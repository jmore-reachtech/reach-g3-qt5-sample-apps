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
//  insert("airDial_measuredAvgValue", 0);
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

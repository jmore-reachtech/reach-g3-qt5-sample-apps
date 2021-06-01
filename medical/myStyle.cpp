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



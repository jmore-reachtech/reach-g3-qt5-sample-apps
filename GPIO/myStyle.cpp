// Copyright 2020 Reach Technology

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
  insert("statusBarHeight", QVariant::fromValue(40));

  //coded values for different error or warning levels
  insert("clrOff", QVariant::fromValue(QString("gray")));
  insert("clrNormal", QVariant::fromValue(QString("green")));
  insert("clrWarning", QVariant::fromValue(QString("goldenrod")));
  insert("clrFault", QVariant::fromValue(QString("#ff3434")));
  insert("clrError", QVariant::fromValue(QString("red")));

  //change from light to dark with a simple boolean -- preset values are then save to backColor, etc
  insert("themeDark", true);
  insert("backColor", QVariant::fromValue(QString("gray")));
  insert("textColor", QVariant::fromValue(QString("white")));
  insert("statusBackColor", QVariant::fromValue(QString("white")));
  insert("statusTextColor", QVariant::fromValue(QString("gray")));

  insert("clrOffLt", QVariant::fromValue(QString("darkGray")));
  insert("clrNormalLt", QVariant::fromValue(QString("darkGreen")));
  insert("clrWarningLt", QVariant::fromValue(QString("yellow")));
  insert("clrFaultLt", QVariant::fromValue(QString("red")));
  insert("clrErrorLt", QVariant::fromValue(QString("darkRed")));

  insert("backColorLt", QVariant::fromValue(QString("white")));
  insert("textColorLt", QVariant::fromValue(QString("black")));
  insert("statusBackColorLt", QVariant::fromValue(QString("lightGrey")));
  insert("statusTextColorLt", QVariant::fromValue(QString("black")));

  insert("backColorDk", QVariant::fromValue(QString("black")));
  insert("textColorDk", QVariant::fromValue(QString("white")));
  insert("statusBackColorDk", QVariant::fromValue(QString("darkCyan")));
  insert("statusTextColorDk", QVariant::fromValue(QString("white")));

  insert("clrOffDk", QVariant::fromValue(QString("lightGray")));
  insert("clrNormalDk", QVariant::fromValue(QString("lightGreen")));
  insert("clrWarningDk", QVariant::fromValue(QString("lightYellow")));
  insert("clrFaultDk", QVariant::fromValue(QString("tomato")));
  insert("clrErrorDk", QVariant::fromValue(QString("lightRed")));
//----------------------------------------------------------------------------

  insert("fontName", QVariant::fromValue(QString("Source Sans Pro")));
  insert("fontSize", QVariant::fromValue(17));

  insert("imgLogo", QVariant::fromValue(QString("Images/reach_logo_color_30.png")));
  insert("borderWidth", QVariant::fromValue(1));
  insert("borderColor", QVariant::fromValue(QString("lightGray")));

  insert("connectedText",QVariant::fromValue(QString( "Connect") ));
  insert("clrConnBox", QVariant::fromValue(QString("tan")));
  insert("clrConnect", QVariant::fromValue(QString("gray")));
  insert("clrBtnConn", QVariant::fromValue(QString("lightGray")));
  insert("connectedFontColor", QVariant::fromValue(QString("black")));

  insert("clrStatus", QVariant::fromValue(QString("white")));
  insert("clrNonStatus", QVariant::fromValue(QString("green")));
  insert("clrSerial", QVariant::fromValue(QString("white")));
  insert("clrTCP", QVariant::fromValue(QString("green")));
}

void StyleValues::startEngine() {
  qDebug() << "Start ENGINE STYLE " << Q_FUNC_INFO;
}

QString StyleValues::getColor(const QString name) {
  QVariant tempColor = value(name);
  return tempColor.value < QString > ();
}

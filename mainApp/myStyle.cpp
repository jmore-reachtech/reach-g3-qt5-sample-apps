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

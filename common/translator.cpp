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

#include <QIODevice>
#include <QTextStream>
#include <QMap>
#include <QDebug>

#include "translator.h"
#include "common.h"
#include "myStyle.h"
#include "myGlobal.h"
#include "string.h"

extern StyleValues MyStyle;
extern GlobalValues MyGlobal;

Translator::Translator(QObject * parent): QObject(parent), m_settings(APP_SETTINGS_PATH, QSettings::NativeFormat) {
  m_settings.beginGroup("Translate");
  m_translateFile.setFileName(m_settings.value("translate_file").value < QString > ());
  m_settings.endGroup();
}

Translator::~Translator() {
  if (m_translateFile.isOpen()) {
    m_translateFile.close();
  }
}

QStringList Translator::translateGui(QString msg) {
  QStringList list = msg.split("=");
  return list;
}

QStringList Translator::translateSerial(QString msg) {
  QStringList split = msg.split("=");

  if (split.length() != 2)  {
    if(( msg.compare("\r") != 0)) {
        qDebug() << "ERROR - Message in wrong format, missing equals -- " << msg ;
    } else{
        qDebug() << "SPLIT -" << msg ;
    }
    return split;
  }

  QString valu = split[1].toLocal8Bit();
    valu.remove("\r");

  if (MyStyle.contains(split[0])) {
    QVariant myType = MyStyle.value(split[0]);  //find the type of variable stored
    int theType = myType.type();

    if (theType == 1) //Bool
    {
      bool b = (strcmp("true", valu.toLocal8Bit()) == 0) ? true : false;
      MyStyle.insert(split[0], b);
    } else if (theType == 2) //Int
    {
      MyStyle.insert(split[0], valu.toInt());
    } else if (theType == 6) //Double
    {
      MyStyle.insert(split[0], valu.toDouble());
    } else if (theType == 10) //String
    {
      qDebug() << "String Key " << split[0] << " = " <<valu;
      MyStyle.insert(split[0], valu);
    } else {
      qDebug() << "ERROR - Did not find a valid match for Type " << theType;
    }
  }


  else if (MyGlobal.contains(split[0])) {
    qDebug() << "myGlobal = " << split[0];
    QVariant myType = MyGlobal.value(split[0]);
    int theType = myType.type();

    if (theType == 1) //Bool
    {
      bool b = (QString::compare("true", valu) == 0) ? true : false;
      MyGlobal.insert(split[0], b);
    } else if (theType == 2) //Int
    {
      MyGlobal.insert(split[0], valu.toInt());
    } else if (theType == 6) //Double
    {
      MyGlobal.insert(split[0], valu.toDouble());
    } else if (theType == 10) //String
    {
      MyGlobal.insert(split[0], valu);
    } else if (theType == 12) //QByteArray
    {
      QByteArray ba =  QByteArray::fromHex(valu.toUtf8());
      MyGlobal.insert(split[0], ba);
    } else {
      qDebug() << "ERROR - Did not find a valid match for Type " << theType;
    }
  } else {
    qDebug() << "ERROR No item " << split[0] << " found in Style or Global";
  }
  QStringList lst;
  return lst;
}

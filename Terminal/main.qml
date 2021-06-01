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

import QtQuick 2.12
import QtGraphicalEffects 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Dialogs 1.2
import QtQuick.Extras 1.4
import QtQuick.Layouts 1.12
import QtQuick.Window 2.2

import "."

ApplicationWindow {
  objectName: "theWindow"
  id: theWindow

  visible: true

  property string color1: "darkBlue"
  property string color2: "black"
  property string bColor: "yellow"
  property string colorText: "white"

  color: color2

  width: screen.width
  height: screen.height
  property int val: 0;

  signal submitTextField(string text)
  signal toggle(int val)
  signal read(int val)

  function setConsole(text) {
    consoleBox.append(text);
  }

  function getSerial(cmd) {
      consoleBox.append(cmd);
  }


  Rectangle {
    objectName: "button1"
    id: button1
    width: 240
    height: 56
    color: color1
    border.color: "white"
    border.width: 1
    radius: 18
    antialiasing: true

    anchors {
      top: parent.top
      topMargin: 18
      right: parent.right
      rightMargin: 18
    }

    Rectangle {
      objectName: "buttonToggle1"
      id: buttonToggle1
      height: 40
      width: height + 18
      color: color1

      border.color: bColor
      border.width: 1

      radius: 18
      antialiasing: true
      anchors.fill: parent

      Text {
        id: elementTextReadButton1
        color: colorText
        text: "Send HELLO"
        font.pixelSize: 20
        anchors {
          verticalCenter: parent.verticalCenter
          horizontalCenter: parent.horizontalCenter;
        }
      }

      Accessible.role: Accessible.Button
      Accessible.onPressAction: {
        button.clicked()
      }

      signal clicked

      MouseArea {
        id: mouseAreaToggle1
        anchors.fill: buttonToggle1
        onClicked: buttonToggle1.clicked()
      }

      onClicked: {
        submitTextField("Hello to you, too");
        toggle(val+1);
        consoleBox.append("Button1 Pressed");
      }
    } //end buttonToggle1
  } //Toggle BOX


  //Clear Console BOX
  Rectangle {
    objectName: "modClearBox"
    id: modClearBox
    width: button1.width
    height: 56
    color: color1
    border.color: bColor
    border.width: 1
    radius: 18
    antialiasing: true

    anchors {
      bottom: statusBox.bottom
      left: button1.left
    }

    Rectangle {
      objectName: "buttonClear"
      id: buttonClear
      height: parent.height - 24
      width: parent.width - 50
      color: color1

      border.color: bColor
      border.width: 1

      radius: 18
      antialiasing: true

      anchors {
        fill: parent
      }

      Text {
        id: elementTextClearButton
        color: colorText
        text: "Clear Console"
        font.pixelSize: 20
        anchors {
          verticalCenter: parent.verticalCenter
          horizontalCenter: parent.horizontalCenter;
        }
      }

      Accessible.role: Accessible.Button
      Accessible.onPressAction: {
        button.clicked()
      }

      signal clicked
      MouseArea {
        id: mouseAreaClear
        anchors.fill: parent
        onClicked: buttonClear.clicked()
      }

      onClicked: {
        submitTextField("Clear Button pressed");
        consoleBox.clear();
      }
    } //end buttonClear

  }

  //Status / Console BOX
  Rectangle {
    objectName: "statusBox"
    id: statusBox
    width: parent.width / 2 + 80
    height: parent.height - 40
    color: color1
    border.color: bColor
    border.width: 1
    radius: 5
    antialiasing: true

    anchors {
      top: parent.top
      topMargin: 20
      left: parent.left
      leftMargin: 20
      bottomMargin: 20
    }

    TextEdit {
      objectName: "consoleBox"
      id: consoleBox
      width: 240
      text: "Hello, World"
      color: colorText
      leftPadding: 15
      topPadding: 15
      bottomPadding: 15
    }

  }



}

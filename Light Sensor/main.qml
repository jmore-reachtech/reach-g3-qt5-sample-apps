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
import i2c.reachtech 1.0

import "."

ApplicationWindow {
   objectName : "theWindow"
   id : theWindow
   visible : true
   color : MyStyle.backColor
   width : MyGlobal.screenWidth
   height : MyGlobal.screenHeight

   property int theValue : MyGlobal.screenFactor
   property int val : 0

   //These values are used for scaling different sized displays.
   property int fontSize240 : theValue / 2
   property int fontSize150 : theValue / 3
   property int fontSize120 : theValue / 4
   property int fontSize80 : theValue / 6
   property int fontSize60 : theValue / 8
   property int fontSize56 : theValue / 9
   property int fontSize50 : theValue / 10
   property int fontSize40 : theValue / 12
   property int fontSize35 : theValue / 14
   property int fontSize30 : theValue / 16
   property int fontSize24 : theValue / 20
   property int fontSize20 : theValue / 24
   property int fontSize18 : theValue / 26
   property int fontSize16 : theValue / 30
   property int fontSize15 : theValue / 32
   property int fontSize14 : theValue / 34
   property int fontSize13 : theValue / 37
   property int fontSize12 : theValue / 40
   property int fontSize11 : theValue / 44
   property int fontSize10 : theValue / 48
   property int fontSize8 : theValue / 60
   property int fontSize6 : theValue / 80
   property int fontSize5 : theValue / 96
   property int fontSize2 : theValue / 240
   property int myFontSize : fontSize15
   property int myRowSpace : fontSize5


   signal submitTextField(string text)
   signal toggle(int val)
   signal read(int val)
   property int foo : 0
    property int len: 0;
   title : qsTr("Reach Technology GPIO Demo")

   function setConsole(text) {
       consoleBox.insert(0, text + "\n")
       len = consoleBox.length;
       if(len > 1000){                               //dont let the console text get too long for memory sake.
           consoleBox.remove(1000, len);
       }
   }

   I2C {
       id : luxSensor
       buss: "/dev/i2c-2"
       address: 0x4a
   }

   Connections {
       target: luxSensor
       function onSensorChanged(val) {
           submitTextField( qsTr("luxSensor=") + val);
           setConsole("sensorVal=" + val);

       }
   }

   header : ToolBar {
       id : tools
       Rectangle {
           id : statRow
           anchors.fill : parent
           width : parent.width
           height : MyStyle.statusBarHeight
           anchors.top : parent.top
           border.width : MyStyle.borderWidth
           border.color : MyStyle.clrConnBox
           color : MyStyle.statusBackColor
           Text {
               id : lblCtr
               color : MyStyle.statusTextColor
               text : "I2C Test"
               font.pixelSize : fontSize16
               anchors {
                   left : parent.left
                   leftMargin : fontSize14
                   verticalCenter : parent.verticalCenter
               }
           }
           Image {
               id : logo
               source : MyStyle.imgLogo
               height : fontSize30
               fillMode : Image.PreserveAspectFit
               anchors {
                   right : parent.right
                   rightMargin : fontSize10
                   verticalCenter : parent.verticalCenter
               }
           }
       }
   } //ToolBar

   Rectangle {
       objectName : "readSensor"
       id : readSensor
       width : fontSize240
       height : fontSize56
       color : MyStyle.clrConnBox
       border.color : "white"
       border.width : 1
       radius : fontSize18
       antialiasing : true
       anchors {
           top : tools.bottom
           topMargin : fontSize18
           right : parent.right
           rightMargin : fontSize18
       }

       Rectangle {
           objectName : "buttonToggle1"
           id : buttonToggle1
           height : fontSize40
           width : height + fontSize18
           color : MyStyle.clrBtnConn
           border.color : "white"
           border.width : 1
           radius : fontSize18
           antialiasing : true
           anchors.fill : parent
           Text {
               id : elementTextReadButton1
               color : MyStyle.statusTextColorLt
               text : "Read Sensor"
               font.pixelSize : fontSize20
               anchors {
                   verticalCenter : parent.verticalCenter
                   horizontalCenter : parent.horizontalCenter
               }
           }
           Accessible.role : Accessible.Button
           Accessible.onPressAction : {
               button.clicked()
           }
           signal clicked
           MouseArea {
               id : mouseAreaToggle1
               anchors.fill : buttonToggle1
               onClicked : buttonToggle1.clicked()
           }
           onClicked : {
               luxSensor.readSensor();
           }
       } // end buttonToggle1
   }

// Clear Console BOX
   Rectangle {
       objectName : "modClearBox"
       id : modClearBox
       width : readSensor.width
       height : fontSize56
       color : MyStyle.clrConnBox
       border.color : "white"
       border.width : 1
       radius : fontSize18
       antialiasing : true
       anchors {
           top : readSensor.bottom
           topMargin : fontSize18
           right : parent.right
           rightMargin : fontSize18
       }

       Rectangle {
           objectName : "buttonClear"
           id : buttonClear
           height : parent.height - fontSize24
           width : parent.width - fontSize50
           color : MyStyle.clrBtnConn
           border.color : "white"
           border.width : 1
           radius : fontSize18
           antialiasing : true
           anchors {
               fill : parent
           }
           Text {
               id : elementTextClearButton
               color : MyStyle.statusTextColorLt
               text : "Clear Console"
               font.pixelSize : fontSize20
               anchors {
                   verticalCenter : parent.verticalCenter
                   horizontalCenter : parent.horizontalCenter
               }
           }
           Accessible.role : Accessible.Button
           Accessible.onPressAction : {
               button.clicked()
           }
           signal clicked
           MouseArea {
               id : mouseAreaClear
               anchors.fill : parent
               onClicked : buttonClear.clicked()
           }
           onClicked : {
               submitTextField("buttonClear=pressed")
               consoleBox.clear()
           }
       } // end buttonClear
   } // Clear Console BOX


   // Sensor Value BOX
      Rectangle {
          objectName : "sensorValueBox"
          id : sensorValueBox
          width : readSensor.width - fontSize20
          height : fontSize56
          color : MyStyle.clrConnBox
          border.color : "black"
          border.width : 1
          radius : fontSize18
          antialiasing : true
          anchors {
              top : modClearBox.bottom
              topMargin : fontSize30
              horizontalCenter : modClearBox.horizontalCenter
          }

          Text {
              id : elementTextSensorValue
              color : MyStyle.statusTextColorLt
              text : "Lux = " + MyGlobal.luxSensor
              font.pixelSize : fontSize20
              anchors {
                  verticalCenter : parent.verticalCenter
                  horizontalCenter : parent.horizontalCenter
              }
          }
      } // Clear Console BOX


   Rectangle {
       objectName : "statusBox"
       id : statusBox
       width : parent.width / 2 + fontSize80
       height : parent.height - tools.height - fontSize20
       color : "white"
       border.color : "black"
       border.width : 1
       radius : fontSize5
       antialiasing : true
       anchors {
           top : tools.bottom
           topMargin : fontSize18
           left : tools.left
           leftMargin : fontSize20
       }

       TextArea {
           objectName : "consoleBox"
           id : consoleBox
           anchors.fill: parent
           width : fontSize240
           text : "I2C Test"
           font.pixelSize : fontSize14
           readOnly:true
       }
    }

   Timer {
       id: sensorTimer
       interval: 1000
       repeat: true
       running: true
       triggeredOnStart: true
       onTriggered: luxSensor.readSensor()
   }


   Connections {
       target : MyStyle
       function onThemeDarkChanged() {
           if (MyStyle.themeDark === true) {
               MyStyle.backColor = MyStyle.backColorDk
               MyStyle.statusBackColor = MyStyle.statusBackColorDk
               MyStyle.textColor = MyStyle.textColorDk
               MyStyle.statusTextColor = MyStyle.statusTextColorDk
           } else {
               MyStyle.backColor = MyStyle.backColorLt
               MyStyle.statusBackColor = MyStyle.statusBackColorLt
               MyStyle.textColor = MyStyle.textColorLt
               MyStyle.statusTextColor = MyStyle.statusTextColorLt
           } // else
       } // onTheme...
   }
}

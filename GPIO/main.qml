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
import GPIOPinInput.reachtech 1.0
import GPIOPinOutput.reachtech 1.0
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
//       console.log("TEXT AREA Length =" + len );
       if(len > 1000){                               //dont let the console text get too long for memory sake.
           consoleBox.remove(1000, len);
       }
   }

   GPIOPinInput {
       id : pin0
       pollPin : true
       pin : 0

   }

   Connections {
       target: pin0
       function onStateChanged(val) {
           submitTextField( qsTr("gpioPin0Value=") + val);
       }
   }

   GPIOPinOutput {
    id : pin1
    pin : 1
   }

   GPIOPinOutput {
       id : pin2
       pin : 2
   }
   GPIOPinOutput {
       id : pin3
       pin : 3
   }

   GPIOPinOutput {
       id : pin4
       pin : 4
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
               text : "GPIO Test"
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
       objectName : "gpioToggleBox1"
       id : gpioToggleBox1
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
               text : "Toggle GPIO 1"
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
               submitTextField("buttonToggle1=pressed")
               setConsole("buttonToggle1=pressed")
               pin1.togglePin()
           }
       } // end buttonToggle1
   }

   Rectangle {
       objectName : "gpioToggleBox2"
       id : gpioToggleBox2
       width : fontSize240
       height : fontSize56
       color : MyStyle.clrConnBox
       border.color : "white"
       border.width : 1
       radius : fontSize18
       antialiasing : true
       anchors {
           top : gpioToggleBox1.bottom
           topMargin : fontSize18
           right : parent.right
           rightMargin : fontSize18
       }

       Rectangle {
           objectName : "buttonToggle2"
           id : buttonToggle2
           height : fontSize40
           width : height + fontSize18
           color : MyStyle.clrBtnConn
           border.color : "white"
           border.width : 1
           radius : fontSize18
           antialiasing : true
           anchors.fill : parent
           Text {
               id : elementTextReadButton2
               color : MyStyle.statusTextColorLt
               text : "Toggle GPIO 2"
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
               id : mouseAreaToggle2
               anchors.fill : buttonToggle2
               onClicked : buttonToggle2.clicked()
           }
           onClicked : {
               submitTextField("buttonToggle2=pressed")
               setConsole("buttonToggle2=pressed")
               pin2.togglePin()
           }
       } // end buttonToggle
   }

   Rectangle {
       objectName : "gpioToggleBox3"
       id : gpioToggleBox3
       width : fontSize240
       height : fontSize56
       color : MyStyle.clrConnBox
       border.color : "white"
       border.width : 1
       radius : fontSize18
       antialiasing : true
       anchors {
           top : gpioToggleBox2.bottom
           topMargin : fontSize18
           right : parent.right
           rightMargin : fontSize18
       }

       Rectangle {
           objectName : "buttonToggle3"
           id : buttonToggle3
           height : fontSize40
           width : height + fontSize18
           color : MyStyle.clrBtnConn
           border.color : "white"
           border.width : 1
           radius : fontSize18
           antialiasing : true
           anchors.fill : parent
           Text {
               id : elementTextReadButton3
               color : MyStyle.statusTextColorLt
               text : "Toggle GPIO 3"
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
               id : mouseAreaToggle3
               anchors.fill : buttonToggle3
               onClicked : buttonToggle3.clicked()
           }
           onClicked : {
               submitTextField("buttonToggle3=pressed")
               setConsole("buttonToggle3=pressed")
               pin3.togglePin()
           }
       } // end buttonToggle3
   }

   Rectangle {
       objectName : "gpioToggleBox4"
       id : gpioToggleBox4
       width : fontSize240
       height : fontSize56
       color : MyStyle.clrConnBox
       border.color : "white"
       border.width : 1
       radius : fontSize18
       antialiasing : true
       anchors {
           top : gpioToggleBox3.bottom
           topMargin : fontSize18
           right : parent.right
           rightMargin : fontSize18
       }

       Rectangle {
           objectName : "buttonToggle4"
           id : buttonToggle4
           height : fontSize40
           width : height + fontSize18
           color : MyStyle.clrBtnConn
           border.color : "white"
           border.width : 1
           radius : fontSize18
           antialiasing : true
           anchors.fill : parent
           Text {
               id : elementTextReadButton4
               color : MyStyle.statusTextColorLt
               text : "Toggle GPIO 4"
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
               id : mouseAreaToggle4
               anchors.fill : buttonToggle4
               onClicked : buttonToggle4.clicked()
           }
           onClicked : {
               submitTextField("buttonToggle4=pressed")
               setConsole("buttonToggle4=pressed")
               pin4.togglePin()
           }
       } // end buttonToggle4
   }

// Clear Console BOX
   Rectangle {
       objectName : "modClearBox"
       id : modClearBox
       width : gpioToggleBox1.width
       height : fontSize56
       color : MyStyle.clrConnBox
       border.color : "white"
       border.width : 1
       radius : fontSize18
       antialiasing : true
       anchors {
           top : gpioToggleBox4.bottom
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

   Rectangle {
       objectName : "pin0Status"
       id : pin0Status
       width : gpioToggleBox1.width - 50
       height : fontSize40
       color : MyStyle.clrConnBox
       border.color : "white"
       border.width : 1
       radius : fontSize18
       antialiasing : true
       anchors {
           top : modClearBox.bottom
           topMargin : fontSize18
           right : parent.right
           rightMargin : fontSize40
       }
       Rectangle {
           objectName : "pin0Val"
           id : pin0Val
           height : parent.height - fontSize24
           width : parent.width - fontSize120
           color : "coral"
           border.color : "white"
           border.width : 1
           antialiasing : true
           anchors {
               fill : parent
           }
           Text {
               id : elementPin0Status
               color : MyStyle.statusTextColorLt
               text : "Pin0 = " + MyGlobal.gpioPin0Value // HERE is where the value is retrieved/displayed
               font.pixelSize : fontSize20
               anchors {
                   verticalCenter : parent.verticalCenter
                   horizontalCenter : parent.horizontalCenter
               }
           }
       } // end buttonClear
   }

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
           text : "GPIO Test"
           font.pixelSize : fontSize14
           readOnly:true
       }
    }

   Connections {
       target : MyGlobal
       function onDoToggleChanged() {
           val = 0
           toggle(val)
       }
   }

   Connections {
       target: MyGlobal
       function onSetGpioPin1Changed(){
           pin1.writeToPin(MyGlobal.setGpioPin1);
       }
    }

   Connections {
       target: MyGlobal
       function onSetGpioPin2Changed(){
           pin2.writeToPin(MyGlobal.setGpioPin2);
       }
    }

   Connections {
       target: MyGlobal
       function onSetGpioPin3Changed(){
           pin3.writeToPin(MyGlobal.setGpioPin3);
       }
    }

   Connections {
       target: MyGlobal
       function onSetGpioPin4Changed(){
           pin4.writeToPin(MyGlobal.setGpioPin4);
       }
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

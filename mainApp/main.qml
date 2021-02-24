import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Dialogs 1.2
import QtQuick.Extras 1.4
import QtQuick.Layouts 1.12

import QtQuick.Window 2.12
import QtGraphicalEffects 1.12

import "."

ApplicationWindow {
  objectName: "theWindow"
  id: theWindow

  visible: true
  color: MyStyle.backColor

  width: MyGlobal.screenWidth
  height: MyGlobal.screenHeight
  property int theValue: MyGlobal.screenFactor

  property int fontSize240: theValue / 2
  property int fontSize150: theValue / 3
  property int fontSize120: theValue / 4
  property int fontSize80: theValue / 6
  property int fontSize60: theValue / 8
  property int fontSize56: theValue / 9
  property int fontSize50: theValue / 10
  property int fontSize40: theValue / 12
  property int fontSize35: theValue / 14
  property int fontSize30: theValue / 16
  property int fontSize25: theValue / 19
  property int fontSize24: theValue / 20
  property int fontSize20: theValue / 24
  property int fontSize18: theValue / 26
  property int fontSize16: theValue / 30
  property int fontSize15: theValue / 32
  property int fontSize14: theValue / 34
  property int fontSize13: theValue / 37
  property int fontSize12: theValue / 40
  property int fontSize11: theValue / 44
  property int fontSize10: theValue / 48
  property int fontSize8: theValue / 60
  property int fontSize6: theValue / 80
  property int fontSize5: theValue / 96
  property int fontSize2: theValue / 240

  property int myFontSize: fontSize15
  property int myRowSpace: fontSize5

  signal submitTextField(string text)
  signal doCmd(string text)
  signal connTypeChanged()
  signal processConnect()
  signal processDisconnect()
  signal read()
  signal write()

  property int foo: 0
  title: qsTr("Reach Technology Demo")

  function setConsole(text) {
    consoleBox.append(text);
  }


  //Function to get date and time
  function getDate() {
      var date = new Date();
      var weekdays = ['Sunday', 'Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday', 'Saturday'];
      var months = ['January', 'February', 'March', 'April', 'May', 'June', 'July', 'August', 'September', 'October', 'November', 'December'];
      var weekday = weekdays[date.getDay()];
      var month = months[date.getMonth()];
      var day = date.getDate();
      var time = new Date().toLocaleTimeString([], {
          hour: '2-digit'
      }, {
          minute: '2-digit'
      }).toString()
      var hour = time.slice(1, 2) === ":" ? time.slice(0, 1) : time.slice(0, 2)
      var minute = time.slice(1, 2) === ":" ? time.slice(2, 4) : time.slice(3, 5)
      var secs = time.slice(1, 2) === ":" ? time.slice(5, 7) : time.slice(6, 8)
      return weekday + ", " + month + " " + day + "  " + hour + ":" + minute + ":" + secs
  }


  header: ToolBar {
    id: tools
    Rectangle {
      id: statRow
      width: parent.width
      height: MyStyle.statusBarHeight

      anchors {
        fill: parent
        top: parent.top
      }
     border{
        width: MyStyle.borderWidth
        color: MyStyle.borderColor
     }
     color: MyStyle.statusBackColor

      Text {
        id: lblCtr
        color: MyStyle.statusTextColor
        text: "G3 System Info"
        font.pixelSize: fontSize16
        anchors {
          left: parent.left
          leftMargin: fontSize14
          verticalCenter: parent.verticalCenter
        }
      }

      Image {
        id: logo
        source: MyStyle.imgLogo
        height: fontSize30
        fillMode: Image.PreserveAspectFit
        anchors {
          right: parent.right;
          rightMargin: fontSize10
          verticalCenter: parent.verticalCenter;
        }
      }
    }
  } //end Toolbar


  Rectangle {
    objectName: "systemDataBox"
    id: systemDataBox
    width:  parent.width - fontSize24
    height: fontSize240 + fontSize150
    color: MyStyle.clrConnBox
    border {
        color: MyStyle.borderColor
        width: MyStyle.borderWidth
    }
    radius: MyStyle.borderRadius
    antialiasing: true

    anchors {
      top: parent.top
      topMargin: fontSize12
      left: parent.left
      leftMargin: fontSize12
    }

    //screen size
    Rectangle {
        id: screenSize
        anchors {
            top: parent.top
            topMargin: fontSize12
            left: parent.left
            leftMargin: fontSize25
        }

        Text {
            id: screenSizeText
            font.pixelSize: fontSize14
            color: MyStyle.textColor
            text: "Screen Size = " + MyGlobal.screenWidth + " x " + MyGlobal.screenHeight
        }
    } //rectangle

    //Date and Time
    Rectangle {
        id: clockRow
        anchors {
            top: parent.top
            topMargin: fontSize12
            right: parent.right
            rightMargin: fontSize25
        }

        Text {
            id: currentDateLabel
            property date currentDate: new Date()
            font.pixelSize: fontSize14
            anchors {
                top: parent.top;
                right: parent.right;
            }
            color: MyStyle.textColor
        }

        //Timer to update the date using the getDate() function"
        Timer {
            id: dateTimer
            interval: 1000
            repeat: true
            running: true
            triggeredOnStart: true
            onTriggered: currentDateLabel.text = getDate()
        }
    } //rectangle

    //IP address
    Rectangle {
        id: ipAddrRow
        anchors {
            top: screenSize.bottom
            topMargin: fontSize25
            left: screenSize.left
        }

        Text {
            id: ipAddrLabel
            font.pixelSize: fontSize14
            color: MyStyle.textColor
            text: "IP Address = " + MyGlobal.tcpAddr
        }
    } //rectangle

    //com port
    Rectangle {
        id: comRow
        anchors {
            top: ipAddrRow.bottom
            topMargin: fontSize25
            left: ipAddrRow.left
        }

        Text {
            id: comLabel
            font.pixelSize: fontSize14
            color: MyStyle.textColor
            text: "RS-232 Port = " +
                  MyGlobal.comSerialName + ", " +
                  MyGlobal.comSerialBaud + ", " +
                  MyGlobal.comSerialParity + ", " +
                  MyGlobal.comSerialDataBits +", " +
                  MyGlobal.comSerialStopBits
        }
    } //rectangle

    //com port
    Rectangle {
        id: rs485Row
        anchors {
            top: comRow.bottom
            topMargin: fontSize25
            left: ipAddrRow.left
        }

        Text {
            id: rs485Label
            font.pixelSize: fontSize14
            color: MyStyle.textColor
            text: "RS-485 Port = " +
                  MyGlobal.rs485SerialName + ", " +
                  MyGlobal.rs485SerialBaud + ", " +
                  MyGlobal.rs485SerialParity + ", " +
                  MyGlobal.rs485SerialDataBits +", " +
                  MyGlobal.rs485SerialStopBits
        }
    } //rectangle


    Rectangle {
        id: lineRect
        anchors {
            top: rs485Row.bottom
            topMargin: fontSize8
            left: comRow.left
        }

        Text {
            id: lineLabel
            font.pixelSize: fontSize24
            color: MyStyle.textColor
            text: "____________________________________________________________"
        }
    } //rectangle

    Rectangle {
        id: lineRect2
        anchors {
            top: lineRect.bottom
            topMargin: fontSize25
            left: lineRect.left
        }
    } //rectangle

    Rectangle {
        id: dfRow
        anchors {
            top: lineRect2.bottom
            topMargin: fontSize12
            left: lineRect2.left
        }

        Text {
            id: dfLabel
            font.family: "Courier"
            font.pixelSize: fontSize15
            color: MyStyle.textColor
            text: MyGlobal.free
        }
    } //rectangle
  }


  Connections {
    target: MyGlobal
    function onModConnectTypeTCPChanged() {
      connTypeChanged();
      if (MyGlobal.modConnectTypeTCP === false) {
        MyStyle.clrSerial = MyStyle.clrStatus
        MyStyle.clrTCP = MyStyle.clrNonStatus
      } else {
        MyStyle.clrSerial = MyStyle.clrNonStatus
        MyStyle.clrTCP = MyStyle.clrStatus
      }
    } //onModConn...
  } //Connections

  Connections {
    target: MyStyle
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
      } //else
    } //onTheme...
  } //Connections

}


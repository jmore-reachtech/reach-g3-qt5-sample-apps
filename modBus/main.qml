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

  //used to scale across different screen resolutions
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

 header: ToolBar {
    id: tools
    Rectangle {
      id: statRow

      anchors.fill: parent
      width: parent.width
      height: MyStyle.statusBarHeight
      anchors.top: parent.top
      border.width: MyStyle.borderWidth
      border.color: MyStyle.clrConnBox
      color: MyStyle.statusBackColor

      Text {
        id: lblCtr
        color: MyStyle.statusTextColor
        text: "ModBus Tester"
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

  //Connected
  Rectangle {
    objectName: "connectBox"
    id: connectBox
    width: parent.width - fontSize35
    height: fontSize80
    color: MyStyle.clrConnBox
    border.color: "white"
    border.width: 1
    radius: fontSize12
    antialiasing: true

    anchors {
      top: parent.top
      topMargin: fontSize12
      left: parent.left
      leftMargin: fontSize12
    }

    Rectangle {
      objectName: "buttonConnect"
      id: buttonConnect
      height: fontSize60
      width: height + fontSize12
      color: MyStyle.clrBtnConn

      border.color: "white"
      border.width: 1

      radius: fontSize12
      antialiasing: true

      anchors {
        verticalCenter: parent.verticalCenter
        left: parent.left
        leftMargin: fontSize12
      }

      Text {
        id: elementTextConnectedButton
        color: MyStyle.connectedFontColor
        text: MyStyle.connectedText
        font.pixelSize: fontSize10
        anchors {
          bottom: parent.bottom;
          bottomMargin: fontSize5
          horizontalCenter: parent.horizontalCenter;
        }
      }

      Accessible.role: Accessible.Button
      Accessible.onPressAction: {
        button.clicked()
      }

      signal clicked
      Image {
        id: connectedImage
        width: fontSize40
        height: width
        anchors {
          bottom: parent.bottom;
          bottomMargin: fontSize18
          horizontalCenter: parent.horizontalCenter;
        }
        fillMode: Image.PreserveAspectFit
        source: "Images/wifi_40.png"
      }

      ColorOverlay {
        id: connectedImageColor
        anchors.fill: connectedImage
        source: connectedImage
        color: MyStyle.clrConnect
      }

      MouseArea {
        id: mouseAreaConnected
        anchors.fill: parent
        onClicked: buttonConnect.clicked()
      }

      onClicked: {
        MyGlobal.connectedBool = !MyGlobal.connectedBool;
        if (MyGlobal.connectedBool) {
          MyGlobal.doConnect = true;
        } else {
          MyGlobal.doDisconnect = true;
        }
        submitTextField("Connect pressed = " + (MyGlobal.connectedBool ? "Connected" : "Disconnected"));
      }
    } //end Connected

    //Connection Status
    Rectangle {
      objectName: "connStatBox"
      id: connStatBox
      width: fontSize120
      height: connectBox.height - fontSize18
      color: MyStyle.clrConnBox
      antialiasing: true

      anchors {
        verticalCenter: parent.verticalCenter
        left: buttonConnect.right
        leftMargin: fontSize18
      }

      Text {
        anchors {
          verticalCenter: parent.verticalCenter
          verticalCenterOffset: -fontSize11
          left: parent.left
        }

        objectName: "modConnType"
        id: modConnType
        color: MyStyle.clrStatus
        text: (MyGlobal.modConnectTypeTCP ? "TCP" : "Serial")
        font.pixelSize: myFontSize
      }

      Text {
        anchors {
          verticalCenter: parent.verticalCenter
          verticalCenterOffset: fontSize11
          left: parent.left
        }

        objectName: "connState"
        id: connState
        color: MyStyle.clrStatus
        text: (MyGlobal.connectedBool ? "Connected" : "Disconnected")
        font.pixelSize: myFontSize
      }

    }

    Rectangle {
      objectName: "netConnBox"
      id: netConnBox
      width: fontSize150
      height: connectBox.height - fontSize18
      color: MyStyle.clrConnBox
      antialiasing: true

      anchors {
        verticalCenter: parent.verticalCenter
        left: connStatBox.right
        leftMargin: fontSize18
      }

      Text {
        anchors {
          bottom: tcpAddr.top
          bottomMargin: fontSize5
          left: parent.left
        }
        objectName: "tcp"
        id: tcp
        color: MyStyle.clrTCP
        text: "TCP"
        font.pixelSize: myFontSize
      }

      Text {
        anchors {
          verticalCenter: parent.verticalCenter
          left: parent.left
        }
        objectName: "tcpAddr"
        id: tcpAddr
        color: MyStyle.clrTCP
        text: MyGlobal.tcpAddr
        font.pixelSize: myFontSize
      }

      Text {
        anchors {
          top: tcpAddr.bottom
          topMargin: fontSize5
          left: parent.left
        }
        objectName: "tcpPort"
        id: tcpPort
        color: MyStyle.clrTCP
        text: MyGlobal.tcpPort
        font.pixelSize: myFontSize
      }
    }

    //Serial
    Rectangle {
      objectName: "rtuConnBox"
      id: rtuConnBox
      width: fontSize150
      height: connectBox.height - fontSize18

      color: MyStyle.clrConnBox
      antialiasing: true

      anchors {
        verticalCenter: parent.verticalCenter
        left: netConnBox.right
        leftMargin: fontSize18
      }

      Text {
        anchors {
          bottom: boxSerialPort.top
          bottomMargin: fontSize5
          left: parent.left
        }
        objectName: "ser"
        id: ser
        color: MyStyle.clrSerial
        text: "Serial"
        font.pixelSize: myFontSize
      }

      Text {
        anchors {
          verticalCenter: parent.verticalCenter
          left: parent.left
        }
        objectName: "boxSerialPort"
        id: boxSerialPort
        color: MyStyle.clrSerial
        text: MyGlobal.modSerialName
        font.pixelSize: myFontSize
      }

      Text {
        anchors {
          top: boxSerialPort.bottom
          topMargin: fontSize5
          left: parent.left
        }
        objectName: "boxSerialBaud"
        id: boxSerialBaud
        color: MyStyle.clrSerial
        text: MyGlobal.modSerialBaud
        font.pixelSize: myFontSize
      }

      Text {
        anchors {
          bottom: boxSerialBaud.bottom
          left: boxSerialBaud.right
          leftMargin: fontSize6
        }

        objectName: "boxSerialParity"
        id: boxSerialParity
        color: MyStyle.clrSerial
        text: MyGlobal.modSerialParity
        font.pixelSize: myFontSize
      }

      Text {
        anchors {
          bottom: boxSerialParity.bottom
          left: boxSerialParity.right
          leftMargin: fontSize6
        }

        objectName: "boxSerialDataBits"
        id: boxSerialDataBits
        color: MyStyle.clrSerial
        text: MyGlobal.modSerialDataBits
        font.pixelSize: myFontSize
      }

      Text {
        anchors {
          bottom: boxSerialDataBits.bottom
          left: boxSerialDataBits.right
          leftMargin: fontSize6
        }

        objectName: "boxSerialStopBits"
        id: boxSerialStopBits
        color: MyStyle.clrSerial
        text: MyGlobal.modSerialStopBits
        font.pixelSize: myFontSize
      }
    } //Serial

    Rectangle {
      objectName: "boxOther"
      id: boxOther
      width: fontSize80
      height: connectBox.height - fontSize18
      color: MyStyle.clrConnBox
      antialiasing: true

      anchors {
        verticalCenter: parent.verticalCenter
        left: rtuConnBox.right
        leftMargin: fontSize18
      }

      Text {
        anchors {
          verticalCenter: parent.verticalCenter
          left: parent.left
        }
        objectName: "boxSvrAddrTitle"
        id: boxSvrAddrTitle
        color: MyStyle.clrNormal
        text: "Srvr Addr: "
        font.pixelSize: myFontSize
      }

      Text {
        anchors {
          bottom: boxSvrAddrTitle.bottom
          left: boxSvrAddrTitle.right
          leftMargin: fontSize5
        }
        objectName: "boxSvrAddr"
        id: boxSvrAddr
        color: MyStyle.clrStatus
        text: MyGlobal.serverAddress
        font.pixelSize: myFontSize
      }
    } //boxOther
  } //Connected Rectangle

  //Read BOX
  Rectangle {
    objectName: "modReadBox"
    id: modReadBox
    width: fontSize240
    height: fontSize80
    color: MyStyle.clrConnBox
    border.color: "white"
    border.width: 1
    radius: fontSize18
    antialiasing: true

    anchors {
      top: connectBox.bottom
      topMargin: fontSize18
      right: parent.right
      rightMargin: fontSize18
    }

    Rectangle {
      objectName: "buttonRead"
      id: buttonRead
      height: fontSize56
      width: height + fontSize18
      color: MyStyle.clrBtnConn

      border.color: "white"
      border.width: 1

      radius: fontSize18
      antialiasing: true

      anchors {
        verticalCenter: parent.verticalCenter
        left: parent.left
        leftMargin: fontSize12
      }

      Text {
        id: elementTextReadButton
        color: MyStyle.statusTextColorLt
        text: "Read"
        font.pixelSize: fontSize20
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
        id: mouseAreaRead
        anchors.fill: parent
        onClicked: buttonRead.clicked()
      }

      onClicked: {
        submitTextField("Read Button pressed");
        read();
        consoleBox.append("Read Button Pressed");
      }
    } //end buttonRead

    Text {
      anchors {
        bottom: readSize.top
        bottomMargin: fontSize5
        left: readSize.left
      }
      objectName: "readRegister"
      id: readRegister
      color: MyStyle.clrNormal
      text: "Reg: " + MyGlobal.readRegister
      font.pixelSize: myFontSize
    }

    Text {
      anchors {
        verticalCenter: parent.verticalCenter
        left: buttonRead.right
        leftMargin: fontSize14
      }
      objectName: "readSize"
      id: readSize
      color: MyStyle.clrNormal
      text: "Size: " + MyGlobal.readSize
      font.pixelSize: myFontSize
    }

    Text {
      anchors {
        top: readSize.bottom
        topMargin: fontSize5
        left: readSize.left
      }
      objectName: "readType"
      id: readType
      color: MyStyle.clrNormal
      text: "Type: " + MyGlobal.readType
      font.pixelSize: myFontSize
    }

  } //Read BOX

  //Write BOX
  Rectangle {
    objectName: "modWriteBox"
    id: modWriteBox
    width: modReadBox.width
    height: modReadBox.height
    color: MyStyle.clrConnBox
    border.color: "white"
    border.width: 1
    radius: fontSize18
    antialiasing: true

    anchors {
      top: modReadBox.bottom
      topMargin: fontSize18
      left: modReadBox.left
    }

    Rectangle {
      objectName: "buttonWrite"
      id: buttonWrite
      height: fontSize56
      width: height + fontSize18
      color: MyStyle.clrBtnConn

      border.color: "white"
      border.width: 1

      radius: fontSize18
      antialiasing: true

      anchors {
        verticalCenter: parent.verticalCenter
        left: parent.left
        leftMargin: fontSize12
      }

      Text {
        id: elementTextWriteButton
        color: MyStyle.statusTextColorLt
        text: "Write"
        font.pixelSize: fontSize20
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
        id: mouseAreaWrite
        anchors.fill: parent
        onClicked: buttonWrite.clicked()
      }

      onClicked: {
        submitTextField("Write Button pressed");
        write();
      }
    } //end buttonWrite

    Text {
      anchors {
        bottom: writeSize.top
        bottomMargin: fontSize5
        left: writeSize.left
      }

      objectName: "writeRegister"
      id: writeRegister
      color: MyStyle.clrNormal
      text: "Reg: " + MyGlobal.writeRegister
      font.pixelSize: myFontSize
    }

    Text {
      anchors {
        verticalCenter: parent.verticalCenter
        left: buttonWrite.right
        leftMargin: fontSize14
      }
      objectName: "writeSize"
      id: writeSize
      color: MyStyle.clrNormal
      text: "Size: " + MyGlobal.writeSize
      font.pixelSize: myFontSize
    }

    Text {
      anchors {
        top: writeSize.bottom
        topMargin: fontSize5
        left: writeSize.left
      }
      objectName: "writeType"
      id: writeType
      color: MyStyle.clrNormal
      text: "Type: " + MyGlobal.writeType
      font.pixelSize: myFontSize
    }

  }

  //Clear Console BOX
  Rectangle {
    objectName: "modClearBox"
    id: modClearBox
    width: modReadBox.width
    height: fontSize56
    color: MyStyle.clrConnBox
    border.color: "white"
    border.width: 1
    radius: fontSize18
    antialiasing: true

    anchors {
      bottom: statusBox.bottom
      left: modReadBox.left
    }

    Rectangle {
      objectName: "buttonClear"
      id: buttonClear
      height: parent.height - fontSize24
      width: parent.width - fontSize50
      color: MyStyle.clrBtnConn

      border.color: "white"
      border.width: 1

      radius: fontSize18
      antialiasing: true

      anchors {
        fill: parent
      }

      Text {
        id: elementTextClearButton
        color: MyStyle.statusTextColorLt
        text: "Clear Console"
        font.pixelSize: fontSize20
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

  //Status BOX
  Rectangle {
    objectName: "statusBox"
    id: statusBox
    width: parent.width / 2 + fontSize80
    height: parent.height - connectBox.height - tools.height - fontSize20
    color: "white"
    border.color: "black"
    border.width: 1
    radius: fontSize5
    antialiasing: true

    anchors {
      top: connectBox.bottom
      topMargin: fontSize18
      left: connectBox.left
    }

    TextEdit {
      objectName: "consoleBox"
      id: consoleBox
      width: 240
      text: "ModBus Tester"
      leftPadding: 15
      topPadding: 15
    }
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
    target: MyGlobal
    function onDoWriteChanged() {
      console.log("DO A WRITE from QML");
      write()
    }
  } //Connections

  Connections {
    target: MyGlobal
    function onDoReadChanged() {
      read()
    }
  } //Connections

  Connections {
    target: MyGlobal
    function onDoConnectChanged() {
      console.log("QML - Connect command");
      processConnect();
    }
  } //Connections

  Connections {
    target: MyGlobal
    function onDoDisconnectChanged() {
      console.log("QML - Disconnect command");
      processDisconnect();
    }
  } //Connections

  Connections {
    target: MyGlobal
    function onConnectedBoolChanged() {
      console.log("QML - Connection Status Changed = ", (MyGlobal.connectedBool ? "Connected" : "Disconnected"));
      if (MyGlobal.connectedBool === false) {
        connectedImageColor.color = "gray";
        buttonConnect.color = "darkGray";
        MyStyle.connectedText = "Connect";
        MyStyle.connectedFontColor = "black";
        console.log("QML - Disconnected");
      } else {
        connectedImageColor.color = "white";
        buttonConnect.color = "green";
        MyStyle.connectedText = "Disconnect";
        MyStyle.connectedFontColor = "white";
        console.log("QML - Connected");
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


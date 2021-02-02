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
 property int val: 0;

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
  signal toggle(int val)

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
        text: "GPIO Test"
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

  //Read BOX
  Rectangle {
    objectName: "gpioToggleBox"
    id: gpioToggleBox
    width: fontSize240
    height: fontSize56
    color: MyStyle.clrConnBox
    border.color: "white"
    border.width: 1
    radius: fontSize18
    antialiasing: true

    anchors {
      top: tools.bottom
      topMargin: fontSize18
      right: parent.right
      rightMargin: fontSize18
    }

    Rectangle {
      objectName: "buttonToggle"
      id: buttonToggle
      height: fontSize40
      width: height + fontSize18
      color: MyStyle.clrBtnConn

      border.color: "white"
      border.width: 1

      radius: fontSize18
      antialiasing: true
      anchors.fill: parent

      Text {
        id: elementTextReadButton
        color: MyStyle.statusTextColorLt
        text: "Toggle GPIO 0"
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
        id: mouseAreaToggle
        anchors.fill: buttonToggle
        onClicked: buttonToggle.clicked()
      }

      onClicked: {
        submitTextField("Toggle Button pressed");
        toggle(val);
        consoleBox.append("Toggle Button Pressed");
      }
    } //end buttonToggle
  } //Toggle BOX


  //Clear Console BOX
  Rectangle {
    objectName: "modClearBox"
    id: modClearBox
    width: gpioToggleBox.width
    height: fontSize56
    color: MyStyle.clrConnBox
    border.color: "white"
    border.width: 1
    radius: fontSize18
    antialiasing: true

    anchors {
      bottom: statusBox.bottom
      left: gpioToggleBox.left
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

  //Status / Console BOX
  Rectangle {
    objectName: "statusBox"
    id: statusBox
    width: parent.width / 2 + fontSize80
    height: parent.height - tools.height - fontSize20
    color: "white"
    border.color: "black"
    border.width: 1
    radius: fontSize5
    antialiasing: true

    anchors {
      top: tools.bottom
      topMargin: fontSize18
      left: tools.left
      leftMargin: fontSize20

    }

    TextEdit {
      objectName: "consoleBox"
      id: consoleBox
      width: 240
      text: "GPIO Test"
      leftPadding: 15
      topPadding: 15
    }
  }

  Connections {
    target: MyGlobal
    onModConnectTypeTCPChanged: {
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
    onDoToggleChanged: {
       val = 0;
      console.log("Toggle " + val)
      toggle(val)
    }
  } //Connections

  Connections {
    target: MyStyle
    onThemeDarkChanged: {
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

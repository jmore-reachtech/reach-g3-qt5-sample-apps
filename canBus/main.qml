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

import QtQuick 2.2
import QtGraphicalEffects 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Dialogs 1.2
import QtQuick.Extras 1.4
import QtQuick.Layouts 1.12
import QtQuick.Window 2.2

import "."

ApplicationWindow {
  id: window
  objectName: "window"
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
  signal read(int val)


  //**** Do not change directly
  property int engineStatus: 0
  property string engineStatusColor: MyStyle.clrWarning

  property int speedStatus: 0
  property string speedStatusColor: MyStyle.clrWarning

  property int aggregatedStatus: 0


  //OK to change
  onEngineStatusChanged: {
    computePageStatus_Engine()
  }

  function computePageStatus_Engine() {
    var myRet = 1 //MyGlobal.engineRPMValue

    if(MyGlobal.engineRPMValue >= MyGlobal.engineRPMwarningValueHigh)
    {
        myRet = 2;
    }

    if(MyGlobal.engineRPMValue >= MyGlobal.engineRPMerrorValueHigh)
    {
        myRet = 3;
    }

    if (myRet > 4) myRet = 4
    if (myRet < 0) myRet = 0

    if      (myRet === 0) window.engineStatusColor = MyStyle.clrOff
    else if (myRet === 1) window.engineStatusColor = MyStyle.clrNormal
    else if (myRet === 2) window.engineStatusColor = MyStyle.clrWarning
    else if (myRet === 3) window.engineStatusColor = MyStyle.clrFault
    else if (myRet === 4) window.engineStatusColor = MyStyle.clrError

    window.engineStatus = myRet //~~myRet //convert float to int by bit inverting twice.
    getAggStatus()
  }

  //OK to change
  onSpeedStatusChanged: {
    computePageStatus_Speed()
  }

  function computePageStatus_Speed() {
    var myRet = 1

    if(MyGlobal.speedDial_currentValue >= MyGlobal.speedDial_warningValueHigh)
    {
        myRet = 2;
    }

    if(MyGlobal.speedDial_currentValue >= MyGlobal.speedDial_errorValueHigh)
    {
        myRet = 3;
    }

    if (myRet > 4) myRet = 4
    if (myRet < 0) myRet = 0

    if      (myRet === 0) window.engineStatusColor = MyStyle.clrOff
    else if (myRet === 1) window.engineStatusColor = MyStyle.clrNormal
    else if (myRet === 2) window.engineStatusColor = MyStyle.clrWarning
    else if (myRet === 3) window.engineStatusColor = MyStyle.clrFault
    else if (myRet === 4) window.engineStatusColor = MyStyle.clrError

    window.speedStatus = myRet //~~myRet //convert float to int by bit inverting twice.
    getAggStatus()
  }


  // Aggregated Status
  property int drawState: 0

  onDrawStateChanged: {
    computePageStatus_Engine()
    computePageStatus_Speed()
  }

  ///Aggregated Condition Data
  //**** Do not change directly
  property int aggregatedswipeViewStatus: 1
  property string aggregatedStatusColor: MyStyle.clrNormal


  function getAggStatus() {
    window.aggregatedStatus = 1
    var ret = window.engineStatus
    window.aggregatedStatusColor = MyStyle.clrNormal
    if (window.speedStatus > window.engineStatus) ret = window.speedStatus
    window.aggregatedStatus = ret

    //ret has the highest value
    var str = MyStyle.strOff
    if (window.aggregatedStatus === 0) {
      str = MyStyle.strOff
      window.aggregatedStatusColor = MyStyle.clrOff
      imgState.source = MyStyle.imgOff
    } else if (aggregatedStatus === 1) {
      str = MyStyle.strNormal
      window.aggregatedStatusColor = MyStyle.clrNormal
      imgState.source = MyStyle.imgNormal
    } else if (window.aggregatedStatus === 2) {
      str = MyStyle.strWarning
      window.aggregatedStatusColor = MyStyle.clrWarning
      imgState.source = MyStyle.imgWarning
    } else if (window.aggregatedStatus === 3) {
      str = MyStyle.strFault
      window.aggregatedStatusColor = MyStyle.clrFault
      imgState.source = MyStyle.imgFault
    } else if (window.aggregatedStatus === 4) {
      str = MyStyle.strError
      window.aggregatedStatusColor = MyStyle.clrError
      imgState.source = MyStyle.imgError
    }
    systemState.text = str
    systemState.color = MyStyle.statusTextColor
  }

  //Left here in case someone wants to add more pages....
  SwipeView {
      id: view
      currentIndex: 0
      anchors.fill: parent

      function addPage(page) {
          addItem(page)
          page.visible = true
      }

      function removePage(page) {
          for (var n = 0; n < count; n++) { if (page === itemAt(n)) { removeItem(n) } }
          page.visible = false
      }

      P_Home {
          id: firstpage
//          objectName: "Home"
          anchors {
              //top.parent.top
              horizontalCenter: parent.horizontalCenter
              horizontalCenterOffset: -20
          }
      }
  }

  SwipeView {
      id: swipeView
      Repeater {  visible: true

          width: MyGlobal.screenWidth
          height: MyGlobal.screenHeight

          signal submitTextField(string text)
          model: 3
          Loader {
              active: SwipeView.isCurrentItem || SwipeView.isNextItem || SwipeView.isPreviousItem
              sourceComponent: Text {
                  //text: "foo " + index + "  "
                  Component.onCompleted: console.log("created:", index)
                  Component.onDestruction: console.log("destroyed:", index)
              }
          }
      }
  }



  title: qsTr("Reach Technology Demo")

  header: ToolBar {
    id: tools
    Rectangle {
      id: statRow

      anchors.fill: parent
      width: parent.width
      height: MyStyle.statusBarHeight
      anchors.top: parent.top
      border.width: MyStyle.borderWidth
      border.color: MyStyle.borderColor
      color: MyStyle.statusBackColor

      PageIndicator {
          id: indicator
          count: view.count
          currentIndex: view.currentIndex
          anchors.verticalCenter: parent.verticalCenter
          anchors.left: parent.left
      }

      Label {
        id: lblCtr
        Text {
          color: MyStyle.statusTextColor
          text: view.currentItem.objectName
          font.pixelSize: fontSize16
        }
        anchors {
          left: indicator.right
          leftMargin: fontSize10
          verticalCenter: parent.verticalCenter
        }
      }

      Image {
        id: imgState
        source: MyStyle.imgOff
        height: fontSize30
        fillMode: Image.PreserveAspectFit
        anchors {
          left: lblCtr.right
          leftMargin: fontSize150
          verticalCenter: parent.verticalCenter
        }
      }

      Label {
        id: systemState
        Text {
          text: "" //MyStyle.strOff
          font.pixelSize: fontSize12
          color: MyStyle.statusTextColor
        }
        anchors {
          verticalCenter: parent.verticalCenter
          left: imgState.right
          leftMargin: fontSize10
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


  //Connections
  Connections {
    target: MyGlobal
    function onEngineRPMValueChanged() {
      computePageStatus_Engine()
    }
  }

  Connections {
    target: MyGlobal
    function onSpeedDial_currentValueChanged() {
      computePageStatus_Speed()
    }
  }

  Connections {
    target: MyStyle
    function onThemeDarkChanged() {
      if (MyStyle.themeDark === true) {
//  console.debug("THEME DARK ")
        MyStyle.backColor = MyStyle.backColorDk
        MyStyle.statusBackColor = MyStyle.statusBackColorDk
        MyStyle.textColor = MyStyle.textColorDk
        MyStyle.statusTextColor = MyStyle.statusTextColorDk

        MyStyle.clrOff = MyStyle.clrOffDk
        MyStyle.clrNormal = MyStyle.clrNormalDk
        MyStyle.clrWarning = MyStyle.clrWarningDk
        MyStyle.clrFault = MyStyle.clrFaultDk
        MyStyle.clrError = MyStyle.clrErrorDk

      } else {
//  console.debug("THEME LIGHT ")
        MyStyle.backColor = MyStyle.backColorLt
        MyStyle.statusBackColor = MyStyle.statusBackColorLt
        MyStyle.textColor = MyStyle.textColorLt
        MyStyle.statusTextColor = MyStyle.statusTextColorLt

        MyStyle.clrOff = MyStyle.clrOffLt
        MyStyle.clrNormal = MyStyle.clrNormalLt
        MyStyle.clrWarning = MyStyle.clrWarningLt
        MyStyle.clrFault = MyStyle.clrFaultLt
        MyStyle.clrError = MyStyle.clrErrorLt

      }
    }
  }

  Connections {
    target: MyStyle
    function onMetricBoolChanged() {
      if (MyStyle.metricBool) {
        //                console.log("CENTIGRADE")
        MyStyle.metricStr = MyStyle.centigradeStr
      } else {
        //                console.log("FAHRENHEIT")
        MyStyle.metricStr = MyStyle.fahrenheitStr
      }
    }
  }

}

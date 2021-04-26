import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12

import "."

Page {
  id: homePage
  width: MyGlobal.screenWidth
  height: MyGlobal.screenHeight

  Rectangle {
    anchors.fill: parent
    color: MyStyle.backColor
  }

  title: qsTr("Main Page")

  property int cols: 3 //how many columns to display
  property int rws: 2 //how many rows to display
  property int colSpace: 40 //Math.round((width - MyStyle.dialWidth * cols) / (cols + 1))
  property int rowSpace: 20 //Math.round((height - MyStyle.statusBarHeight - MyStyle.dialHeight - MyStyle.componentY) / (rws + 1))

  Rectangle {
    width: parent.width - colSpace
    height: parent.height
    anchors {
      top: parent.top
      horizontalCenter: parent.horizontalCenter
    }
    color: MyStyle.backColor

    GridLayout {
      id: grid
      anchors {
        fill: parent;
        margins: {
          topMargin: rowSpace
        }
      }

      columns: cols
      columnSpacing: colSpace
      Layout.leftMargin: colSpace

      rows: rws
      rowSpacing: rowSpace
      Layout.topMargin: rowSpace

      C_SpeedDial {
        objectName: "rpmDial"
        id: rpmDial
        legendText: "Tach"
        units: "RPM"
        state: 0
        Layout.row: 0
        Layout.column: 0
        Layout.alignment: Qt.AlignHCenter

        currentValue: MyGlobal.engineRPMValue
        maxText: MyGlobal.engineRPMmaxText
        avgText: MyGlobal.engineRPMavgText
        minimumRangeValue: MyGlobal.engineRPMminimumRangeValue
        maximumRangeValue: MyGlobal.engineRPMmaximumRangeValue
        warningValueLow: MyGlobal.engineRPMwarningValueLow
        errorValueLow: MyGlobal.engineRPMerrorValueLow
        warningValueHigh: MyGlobal.engineRPMwarningValueHigh
        errorValueHigh: MyGlobal.engineRPMerrorValueHigh

        barWidth: MyStyle.dialBarWidth
        ticksOn: MyStyle.dialTicksOn

        Connections {
          target: MyGlobal
          function onRpmDial_currentValueChanged() {
            rpmDial.currentValue = MyGlobal.rpmDial_currentValue
          }
        }

        Connections {
          target: MyGlobal
          function onRpmDial_measuredMaxValueChanged() {
            rpmDial.measuredMaxValue = MyGlobal.rpmDial_measuredMaxValue
          }
        }
        Connections {
          target: MyGlobal
          function onRpmDial_maxTextChanged() {
            rpmDial.maxText = "" //MyGlobal.rpmDial_maxText
          }
        }
        Connections {
          target: MyGlobal
          function onRpmDial_measuredAvgValueChanged() {
            rpmDial.measuredAvgValue = MyGlobal.rpmDial_measuredAvgValue
          }
        }
        Connections {
          target: MyGlobal
          function onRpmDial_avgTextValueChanged() {
            rpmDial.avgText = "" //MyGlobal.rpmDial_avgText
          }
        }
        Connections {
          target: MyGlobal
          function onRpmDial_minimumRangeValueChanged() {
            rpmDial.minimumRangeValue = MyGlobal.rpmDial_minimumRangeValue
          }
        }
        Connections {
          target: MyGlobal
          function onRpmDial_maximumRangeValueChanged() {
            rpmDial.maximumRangeValue = MyGlobal.rpmDial_maximumRangeValue
          }
        }
        Connections {
          target: MyGlobal
          function onRpmDial_warningValueLowChanged() {
            rpmDial.warningValueLow = MyGlobal.rpmDial_warningValueLow
          }
        }
        Connections {
          target: MyGlobal
          function onRpmDial_errorValueLowChanged() {
            rpmDial.errorValueLow = MyGlobal.rpmDial_errorValueLow
          }
        }
        Connections {
          target: MyGlobal
          function onRpmDial_warningValueHighChanged() {
            rpmDial.warningValueHigh = MyGlobal.rpmDial_warningValueHigh
          }
        }
        Connections {
          target: MyGlobal
          function onRpmDial_errorValueHighChanged() {
            rpmDial.errorValueHigh = MyGlobal.rpmDial_errorValueHigh
          }
        }

        Connections {
          target: MyStyle
         function onDialBarWidthChanged() {
            rpmDial.barWidth = MyStyle.dialBarWidth
          }
        }

        Connections {
          target: MyStyle
         function onDialTicksOnChanged() {
            rpmDial.ticksOn = MyStyle.dialTicksOn
          }
        }

      }

      C_SpeedDial {
        objectName: "speedDial"
        id: speedDial
        legendText: "Speed"
        units: "MPH"
        state: 0

        Layout.row: 0
        Layout.column: 1
        Layout.alignment: Qt.AlignHCenter

        currentValue: MyGlobal.speedDial_currentValue
        measuredMaxValue: MyGlobal.speedDial_measuredMaxValue
        minimumRangeValue: MyGlobal.speedDial_minimumRangeValue
        maximumRangeValue: MyGlobal.speedDial_maximumRangeValue
        warningValueLow: MyGlobal.speedDial_warningValueLow
        errorValueLow: MyGlobal.speedDial_errorValueLow
        warningValueHigh: MyGlobal.speedDial_warningValueHigh
        errorValueHigh: MyGlobal.speedDial_errorValueHigh
        barWidth: MyStyle.dialBarWidth
        ticksOn: MyStyle.dialTicksOn

        Connections {
          target: MyStyle
          function onDialBarWidthChanged() {
            speedDial.barWidth = MyStyle.dialBarWidth
          }
        }

        Connections {
          target: MyStyle
          function onDialTicksOnChanged() {
            speedDial.ticksOn = MyStyle.dialTicksOn
          }
        }

        Connections {
          target: MyGlobal
         function  onSpeedDial_currentValueChanged() {
            speedDial.currentValue = MyGlobal.speedDial_currentValue
          }
        }

        Connections {
          target: MyGlobal
          function onSpeedDial_measuredMaxValueChanged() {
            speedDial.measuredMaxValue = MyGlobal.speedDial_measuredMaxValue
          }
        }
        Connections {
          target: MyGlobal
          function onSpeedDial_maxTextChanged() {
            speedDial.maxText = MyGlobal.speedDial_maxText
          }
        }
        Connections {
          target: MyGlobal
          function onSpeedDial_measuredAvgValueChanged() {
            speedDial.measuredAvgValue = MyGlobal.speedDial_measuredAvgValue
          }
        }
        Connections {
          target: MyGlobal
          function onSpeedDial_avgTextValueChanged() {
            speedDial.avgText = MyGlobal.speedDial_avgText
          }
        }
        Connections {
          target: MyGlobal
          function onSpeedDial_minimumRangeValueChanged() {
            speedDial.minimumRangeValue = MyGlobal.speedDial_minimumRangeValue
          }
        }
        Connections {
          target: MyGlobal
          function onSpeedDial_maximumRangeValueChanged() {
            speedDial.maximumRangeValue = MyGlobal.speedDial_maximumRangeValue
          }
        }
        Connections {
          target: MyGlobal
         function  onSpeedDial_warningValueLowChanged() {
            speedDial.warningValueLow = MyGlobal.speedDial_warningValueLow
          }
        }
        Connections {
          target: MyGlobal
         function  onSpeedDial_errorValueLowChanged() {
            speedDial.errorValueLow = MyGlobal.speedDial_errorValueLow
          }
        }
        Connections {
          target: MyGlobal
         function  onSpeedDial_warningValueHighChanged() {
            speedDial.warningValueHigh = MyGlobal.speedDial_warningValueHigh
          }
        }
        Connections {
          target: MyGlobal
         function  onSpeedDial_errorValueHighChanged() {
            speedDial.errorValueHigh = MyGlobal.speedDial_errorValueHigh
          }
        }

        Connections {
          target: MyStyle
         function  onDialBarWidthChanged() {
            speedDial.barWidth = MyStyle.dialBarWidth
          }
        }

        Connections {
          target: MyStyle
         function  onDialTicksOnChanged() {
            SpeedDial.ticksOn = MyStyle.dialTicksOn
          }
        }


      }

      C_SpeedDial {
        objectName: "AccPedal"
        id: airDial
        legendText: "Accel"
        units: "%"
        state: 0

        Layout.row: 0
        Layout.column: 2
        Layout.alignment: Qt.AlignHCenter

        currentValue: MyGlobal.airDial_currentValue
        measuredMaxValue: MyGlobal.airDial_measuredMaxValue
        maxText: MyGlobal.airDial_maxText
        avgText: MyGlobal.airDial_avgText
        minimumRangeValue: MyGlobal.airDial_minimumRangeValue
        maximumRangeValue: MyGlobal.airDial_maximumRangeValue
        warningValueLow: MyGlobal.airDial_warningValueLow
        errorValueLow: MyGlobal.airDial_errorValueLow
        warningValueHigh: MyGlobal.airDial_warningValueHigh
        errorValueHigh: MyGlobal.airDial_errorValueHigh
        barWidth: MyStyle.dialBarWidth
        ticksOn: MyStyle.dialTicksOn

        Connections {
          target: MyStyle
          function onDialBarWidthChanged() {
            airDial.barWidth = MyStyle.dialBarWidth
          }
        }

        Connections {
          target: MyStyle
          function onDialTicksOnChanged() {
            airDial.ticksOn = MyStyle.dialTicksOn
          }
        }

        Connections {
          target: MyGlobal
          function onAirDial_currentValueChanged() {
            airDial.currentValue = MyGlobal.airDial_currentValue
          }
        }

        Connections {
          target: MyGlobal
          function onAirDial_measuredMaxValueChanged() {
            airDial.measuredMaxValue = MyGlobal.airDial_measuredMaxValue
          }
        }
        Connections {
          target: MyGlobal
          function onAirDial_maxTextChanged() {
            airDial.maxText = MyGlobal.airDial_maxText
          }
        }
        Connections {
          target: MyGlobal
          function onAirDial_measuredAvgValueChanged() {
            airDial.measuredAvgValue = MyGlobal.airDial_measuredAvgValue
          }
        }
        Connections {
          target: MyGlobal
          function onAirDial_avgTextValueChanged() {
            airDial.avgText = MyGlobal.airDial_avgText
          }
        }
        Connections {
          target: MyGlobal
          function onAirDial_minimumRangeValueChanged() {
            airDial.minimumRangeValue = MyGlobal.airDial_minimumRangeValue
          }
        }
        Connections {
          target: MyGlobal
          function onAirDial_maximumRangeValueChanged() {
            airDial.maximumRangeValue = MyGlobal.airDial_maximumRangeValue
          }
        }
        Connections {
          target: MyGlobal
          function onAirDial_warningValueLowChanged() {
            airDial.warningValueLow = MyGlobal.speedDial_warningValueLow
          }
        }
        Connections {
          target: MyGlobal
          function onAirDial_errorValueLowChanged() {
            airDial.errorValueLow = MyGlobal.airDial_errorValueLow
          }
        }
        Connections {
          target: MyGlobal
          function onAirDial_warningValueHighChanged() {
            airDial.warningValueHigh = MyGlobal.airDial_warningValueHigh
          }
        }
        Connections {
          target: MyGlobal
          function onAirDial_errorValueHighChanged(){
            airDial.errorValueHigh = MyGlobal.airDial_errorValueHigh
          }
        }

        Connections {
          target: MyStyle
          function onDialBarWidthChanged() {
            airDial.barWidth = MyStyle.dialBarWidth
          }
        }

        Connections {
          target: MyStyle
          function onDialTicksOnChanged() {
            airDial.ticksOn = MyStyle.dialTicksOn
          }
        }

      }


    }
  }
}

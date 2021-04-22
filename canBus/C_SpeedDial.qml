import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4
import QtQuick.Extras.Private 1.0
import QtGraphicalEffects 1.0
import "."

Rectangle {
    id: gauge
    property alias state: canvas.state
    property alias currentValue: canvas.currentValue
    property alias measuredMaxValue: canvas.measuredMaxValue
    property alias measuredAvgValue: canvas.measuredAvgValue
    property alias minimumRangeValue: canvas.minimumRangeValue
    property alias maximumRangeValue: canvas.maximumRangeValue

    property alias warningValueHigh: canvas.warningValueHigh
    property alias errorValueHigh: canvas.errorValueHigh
    property alias warningValueLow: canvas.warningValueLow
    property alias errorValueLow: canvas.errorValueLow
    property alias ticksOn: canvas.ticks
    property alias primaryColor: canvas.secondaryColor
    property alias secondaryColor: canvas.primaryColor
    property alias barWidth: canvas.barWidth

    property alias legendText: canvas.legendStr
    property alias units: metric.text
    property alias maxText: max.text
    property alias avgText: avg.text

    border.width: MyStyle.borderWidth
    border.color: MyStyle.borderColor
    height: MyStyle.dialHeight
    width: MyStyle.dialWidth
    color: MyStyle.backColor

    //These define relative sizes for different resolutions
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
    property int fontSize28: theValue / 17
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
    property int fontSize7: theValue / 68
    property int fontSize6: theValue / 80
    property int fontSize5: theValue / 96
    property int fontSize2: theValue / 240

    property real cnt: 0


  Canvas {
    id: canvas
    height: gauge.height
    width: gauge.width
    antialiasing: true
    anchors {
      verticalCenter: parent.verticalCenter
      horizontalCenter: parent.horizontalCenter
    }

    property real barWidth: MyStyle.dialBarWidth
    property color primaryColor: "grey"
    property color secondaryColor: "white"

    property int centerOffset: centerWidth - width / 2
    property int centerWidth: width * .64
    property real centerHeight: height / 2

    property int arcWidth: height / fontSize20
    property real radius: Math.min(width, height) / 2
    property real angle: (currentValue - minimumRangeValue) / (maximumRangeValue - minimumRangeValue) * Math.PI
    property real angleOffset: Math.PI / 2

    property string legendStr: "boop"
    property int state: 0
    property real currentValue: 66
    property real measuredMaxValue: -1
    property real measuredAvgValue: -1
    property real minimumRangeValue: 0
    property real maximumRangeValue: 100

    property real warningValueLow: 60
    property real errorValueLow: 80
    property real warningValueHigh: 60
    property real errorValueHigh: 80
    property bool ticks: myStyle.dialTicksOn


    signal clicked()

    onPrimaryColorChanged: requestPaint()
    onSecondaryColorChanged: requestPaint()
    onMinimumRangeValueChanged: requestPaint()
    onMaximumRangeValueChanged: requestPaint()
    onMeasuredMaxValueChanged: requestPaint()
    onMeasuredAvgValueChanged: requestPaint()
    onCurrentValueChanged: requestPaint()
    onBarWidthChanged: requestPaint()

    onPaint: {
      console.log("cnt", cnt++,  "Angle =", angle, " CurrentVal", currentValue);
      if(angle > Math.PI) angle = Math.PI - 0.01;

      var ctx = getContext("2d");
      var barColor;
      var myAngle;
      ctx.save();
      ctx.clearRect(0, 0, width, height);

      // First, thinner arc From angle to PI
      ctx.beginPath();
      ctx.lineWidth = barWidth;
      ctx.strokeStyle = primaryColor;
      ctx.arc(canvas.centerWidth,
        canvas.centerHeight,
        canvas.radius,
        angleOffset + canvas.angle,
        angleOffset + Math.PI,
        false);
      ctx.stroke();

      // Second, thicker arc - from 0 to angle
      ctx.beginPath();
      ctx.lineWidth = barWidth;

      barColor = MyStyle.clrOff;

      if (currentValue < minimumRangeValue) {
        currentValue = minimumRangeValue;
      }
      if (currentValue > maximumRangeValue) {
        currentValue = maximumRangeValue;
      }

      if (currentValue >= minimumRangeValue && currentValue <= maximumRangeValue) {
        barColor = MyStyle.clrNormal; //oN/Normal
        state = 1;
      }

      if (warningValueHigh < maximumRangeValue && currentValue > warningValueHigh) {
        barColor = MyStyle.clrWarning //warnHigh
        state = 2;
      }

/*      if (warningValueLow > minimumRangeValue && currentValue < warningValueLow) {
        barColor = MyStyle.clrWarning //warnLow
        state = 2;
      }
*/
      if (errorValueHigh < maximumRangeValue && currentValue > errorValueHigh) {
        barColor = MyStyle.clrError //errHigh
        state = 3;
      }

/*      if (errorValueLow > minimumRangeValue && currentValue < errorValueLow) {
        barColor = MyStyle.clrError //errLow
        state = 3;
      }
*/

      ctx.strokeStyle = barColor;
      ctx.arc(canvas.centerWidth,
        canvas.centerHeight,
        canvas.radius,
        canvas.angleOffset,
        canvas.angleOffset + canvas.angle,
        false);
      ctx.stroke();

      // fills the mouse area when pressed
      // the fill color is a lighter version of the secondary color
      if (mouseArea.pressed) {
        ctx.beginPath();
        ctx.lineWidth = barWidth + 2;
        ctx.strokeStyle = Qt.lighter(barColor, 1.25);
        ctx.arc(canvas.centerWidth,
          canvas.centerHeight,
          canvas.radius,
          canvas.angleOffset,
          canvas.angleOffset + canvas.angle,
          false);
        ctx.stroke();
      }

      if (ticks) {
        //set the warningValueHigh tick
        if (warningValueHigh < maximumRangeValue) {
          myAngle = (warningValueHigh - minimumRangeValue) / (maximumRangeValue - minimumRangeValue) * Math.PI
          ctx.beginPath();
          ctx.lineWidth = barWidth + fontSize5;
          ctx.strokeStyle = MyStyle.clrWarning;
          ctx.arc(canvas.centerWidth,
            canvas.centerHeight,
            canvas.radius,
            canvas.angleOffset + myAngle, // -  0.0174533,
            canvas.angleOffset + myAngle + 0.0174533,
            false);
          ctx.stroke();
        }

        //set the warningValueLow tick
        if (warningValueLow > minimumRangeValue) {
          myAngle = (warningValueLow - minimumRangeValue) / (maximumRangeValue - minimumRangeValue) * Math.PI
          ctx.beginPath();
          ctx.lineWidth = barWidth + fontSize5;
          ctx.strokeStyle = MyStyle.clrWarning;
          ctx.arc(canvas.centerWidth,
            canvas.centerHeight,
            canvas.radius,
            canvas.angleOffset + myAngle - 0.0174533,
            canvas.angleOffset + myAngle, // +  0.0174533,
            false);
          ctx.stroke();
        }

        //set the errorValueHigh tick
        if (errorValueHigh < maximumRangeValue) {
          myAngle = (errorValueHigh - minimumRangeValue) / (maximumRangeValue - minimumRangeValue) * Math.PI
          ctx.beginPath();
          ctx.lineWidth = barWidth + fontSize5;
          ctx.strokeStyle = MyStyle.clrError;
          ctx.arc(canvas.centerWidth,
            canvas.centerHeight,
            canvas.radius,
            canvas.angleOffset + myAngle, // -  0.0174533,
            canvas.angleOffset + myAngle + 0.0174533,
            false);
          ctx.stroke();
        }

        //set the warningValueLow tick
        if (errorValueLow > minimumRangeValue) {
          myAngle = (errorValueLow - minimumRangeValue) / (maximumRangeValue - minimumRangeValue) * Math.PI
          ctx.beginPath();
          ctx.lineWidth = barWidth + fontSize5;
          ctx.strokeStyle = MyStyle.clrError;
          ctx.arc(canvas.centerWidth,
            canvas.centerHeight,
            canvas.radius,
            canvas.angleOffset + myAngle - 0.0174533,
            canvas.angleOffset + myAngle, // +  0.0174533,
            false);
          ctx.stroke();
        }
      }

      // Set the needle
      ctx.beginPath();
      ctx.lineWidth = barWidth + fontSize5;
      ctx.strokeStyle = "white";
      ctx.arc(canvas.centerWidth,
        canvas.centerHeight,
        canvas.radius,
        canvas.angleOffset + canvas.angle - 0.0349066, //0.0174533,
        canvas.angleOffset + canvas.angle + 0.0349066, //0.0174533,
        false);
      ctx.stroke();

      ctx.restore();
    } //onPaint
  } //Canvas

  //The description field of the component - tach, speed, etc
  Text {
    id: descript
    anchors {
      horizontalCenter: parent.horizontalCenter
      horizontalCenterOffset: fontSize20
      bottom: parent.verticalCenter
      bottomMargin: fontSize15
      //.centerIn: parent
    }
    text: canvas.legendStr
    color: MyStyle.textColor
    font.pixelSize: fontSize20
  }

  //The value field of the component -
  Text {
    id: val
    anchors {
      horizontalCenter: descript.horizontalCenter
      top: descript.bottom
    }
    text: gauge.currentValue
    color: MyStyle.textColor
    font.pixelSize: fontSize24
  }

  //The metric field of the component - rpm, mph, etc
  Text {
    id: metric
    anchors {
      horizontalCenter: descript.horizontalCenter
      top: val.bottom
    }
    text: "SCFM"
    color: MyStyle.textColor
    font.pixelSize: fontSize16
  }

  // MAX AND MIN
  Text {
    id: maxVal
    anchors {
      left: descript.horizontalCenter
      leftMargin: fontSize10
      top: gauge.top
      topMargin: fontSize8
    }
    text: gauge.maximumRangeValue
    color: MyStyle.textColor
    font.pixelSize: fontSize14
  }

  Text {
    id: minVal
    anchors {
      left: descript.horizontalCenter
      leftMargin: fontSize10
      bottom: gauge.bottom
      bottomMargin: fontSize8
    }
    text: gauge.minimumRangeValue
    color: MyStyle.textColor
    font.pixelSize: fontSize14
  }

  // Measured MAX AND AVG
  Text {
    id: measuredMaxVal
    anchors {
      left: gauge.left
      leftMargin: fontSize10
      top: gauge.top
      topMargin: fontSize8
    }

    text: (gauge.measuredMaxValue == -1) ? "" : gauge.measuredMaxValue
    color: MyStyle.textColor
    font.pixelSize: fontSize14
  }

  Text {
    id: max
    anchors {
      horizontalCenter: measuredMaxVal.horizontalCenter
      top: measuredMaxVal.bottom
    }
    text:  gauge.maxText  //"MAX"
    color: MyStyle.textColor
    font.pixelSize: fontSize10
  }

  Text {
    id: measuredAvgVal
    anchors {
      horizontalCenter: measuredMaxVal.horizontalCenter
      bottom: avg.top
    }
    text: (gauge.measuredAvgValue == -1) ? "" : gauge.measuredAvgValue
    color: MyStyle.textColor
    font.pixelSize: fontSize14
  }

  Text {
    id: avg
    anchors {
      horizontalCenter: measuredMaxVal.horizontalCenter
      bottom: gauge.bottom
      bottomMargin: fontSize8
    }
    text: gauge.avgText //"AVG"
    color: MyStyle.textColor
    font.pixelSize: fontSize10
  }

//MOUSE
MouseArea {
  id: mouseArea
  anchors.fill: parent
  onPressed: {
    console.log("Mouse pressed " + gauge.objectName)
    canvas.requestPaint()
  }
  onReleased: {
    console.log("Mouse released " + gauge.objectName)
    canvas.requestPaint()
  }
} //MouseArea

}

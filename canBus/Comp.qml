import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0
import "."

Rectangle {
    id: component

    objectName: "component"
    property var value: 0
    property string measure: qsTr(" measure")
    property string srcName: "Images/led_error_40.png"

    property alias c_objectName: component.objectName
    property alias c_value: component.value
    property alias c_measure: component.measure
    property alias c_srcName: component.srcName
    property alias c_state: component.internalState

    property int internalState: 0
    width: MyStyle.componentX
    height: MyStyle.componentY
    border.width: MyStyle.borderWidth
    border.color: MyStyle.borderColor
    property string dispMeasure: measure

    signal clicked(int stVal)

    function setState(val)
    {
        internalState = val
        console.log("State handler")
    }

    Rectangle {
        anchors.fill: parent
        border.width: MyStyle.borderWidth
        border.color: MyStyle.borderColor
        color: MyStyle.backColor
    }

    Image {
        id: myImage
        width: MyStyle.iconSize
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        fillMode: Image.PreserveAspectFit
        source: srcName
    }

    ColorOverlay {
        id: cOverlay
        anchors.fill: myImage
        source: myImage
        color: "white"    //MyStyle.clrOff
    }

    Image {
        id: imageX
        width: MyStyle.iconSize
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        fillMode: Image.PreserveAspectFit
        source: MyStyle.imgX
        opacity: 0.3
        visible: false
    }

    Item {
        id: item2
        x: 0
        y: MyStyle.textY
        width: parent.width
        height: MyStyle.fontSize + 2
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5

        Text {
            id: text1
            text: value + dispMeasure
            anchors.horizontalCenter: parent.horizontalCenter
            font.family: MyStyle.fontName
            font.pixelSize: MyStyle.fontSize
            color: MyStyle.textColor
        }
    }

    states: [
        State {
            name: "Off"
            when: internalState === 0
            PropertyChanges {
                target: component
                dispMeasure: measure
            }
            PropertyChanges {
                target: cOverlay
                color: MyStyle.clrOff
            }
            PropertyChanges {
                target: imageX
                visible: false
            }

        },
        State {
            name: "On"
            when: internalState === 1
            PropertyChanges {
                target: cOverlay
                color: MyStyle.clrNormal
            }

            PropertyChanges {
                target: component
                dispMeasure: measure
            }
            PropertyChanges {
                target: imageX
                visible: false
            }
        },
        State {
            name: "Warning"
            when: internalState === 2
            PropertyChanges {
                 target: parent
             }

            PropertyChanges {
                target: cOverlay
                color: MyStyle.clrWarning
            }

            PropertyChanges {
                target: component
                dispMeasure: measure
            }
            PropertyChanges {
                target: imageX
                visible: false
            }
        },
        State {
            name: "Fault"
            when: internalState === 3
            PropertyChanges {
                target: cOverlay
                color: MyStyle.clrFault
            }
            PropertyChanges {
                target: component
                dispMeasure: measure
            }
            PropertyChanges {
                target: imageX
                visible: false
            }
        },
        State {
            name: "Failed"
            when: internalState >= 4
            PropertyChanges {
                target: cOverlay
                color: MyStyle.clrError
            }

            PropertyChanges {
                target: component
                value: qsTr("Failed")
                dispMeasure: qsTr("")
            }
            PropertyChanges {
                target: imageX
                visible: true
            }
        }
    ]
}

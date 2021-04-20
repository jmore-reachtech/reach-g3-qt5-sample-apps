import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0
import "."

Item {
    objectName: "engineRPM"
    id: engineRPM
    width: Style.componentX
    height: Style.componentY
    property string value: qsTr("0")
    property string measure: qsTr(" rpm")
    property string srcName: "Images/engine.png"
    property int state: 0

    property string dispMeasure: measure
    signal statusChanged(int state)

    Rectangle {
        anchors.fill: parent
        border.width: Style.borderWidth
        color: Style.backColor
    }

    Image {
        id: image
        width: Style.iconSize
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        fillMode: Image.PreserveAspectFit
        source: srcName
    }

    ColorOverlay {
        id: cOverlay
        anchors.fill: image
        source: image
        color: Style.overState0
    }

    Button {
        id: up
        x: 0
        y: 0
        width: 34
        height: 25
        text: qsTr("U")
        display: AbstractButton.TextOnly
        highlighted: true
        font.family: Style.fontName
        onClicked: engineRPM.state++
    }

    Button {
        id: down
        x: Style.componentY - 34
        y: 0
        width: 34
        height: 25
        text: qsTr("D")
        anchors.right: parent.right
        anchors.rightMargin: 0
        highlighted: true
        display: AbstractButton.TextOnly
        font.family: Style.fontName
        onClicked: engineRPM.state--
    }

    Item {
        id: item2
        x: 0
        y: Style.textY
        width: parent.width
        height: Style.fontSize + 2
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5

        Text {
            id: text1
            text: value + dispMeasure
            anchors.horizontalCenter: parent.horizontalCenter
            font.family: Style.fontName
            font.pixelSize: Style.fontSize
            color: Style.textColor
        }
    }

    Connections {
        target: up
        onClicked: {
            engineRPM.state = engineRPM.state > 9 ? 9 : engineRPM.state
            print("clicked " + "engineRPM.state=" + engineRPM.state)
        }
    }

    Connections {
        target: down
        onClicked: {
            engineRPM.state = engineRPM.state < 0 ? 0 : engineRPM.state
            print("clicked " + "engineRPM.state=" + engineRPM.state)
        }
    }

    states: [
        State {
            name: "Off"
            when: engineRPM.state === 0
            PropertyChanges {
                target: engineRPM
                value: qsTr("0")
                dispMeasure: measure
            }
            PropertyChanges {
                target: cOverlay
                color: Style.overState0
            }
        },
        State {
            name: "On"
            when: engineRPM.state === 1
            PropertyChanges {
                target: cOverlay
                color: Style.overState1
            }

            PropertyChanges {
                target: engineRPM
                value: qsTr("600")
                dispMeasure: measure
            }
        },
        State {
            name: "Warning"
            when: engineRPM.state === 2

            PropertyChanges {
                 target: enginePage
                 onClicked: statusChanged()
                 //console.log("state", state)
                 //engineRPM.statusChanged(state)
             }

            PropertyChanges {
                target: cOverlay
                color: Style.overState2
            }

            PropertyChanges {
                target: engineRPM
                value: qsTr("700")
                dispMeasure: measure
            }
        },
        State {
            name: "Fault"
            when: engineRPM.state === 3
            PropertyChanges {
                target: cOverlay
                color: Style.overState3
            }
            PropertyChanges {
                target: engineRPM
                value: qsTr("800")
                dispMeasure: measure
            }
        },
        State {
            name: "Failed"
            when: engineRPM.state === 4
            PropertyChanges {
                target: cOverlay
                color: Style.overState4
            }

            PropertyChanges {
                target: engineRPM
                value: qsTr("Failed")
                dispMeasure: qsTr("")
            }
        },
        State {
            name: "Failed5"
            when: engineRPM.state === 5
            PropertyChanges {
                target: cOverlay
                color: Style.overState5
            }
            PropertyChanges {
                target: engineRPM
                value: qsTr("Failed")
                dispMeasure: measure
            }
        },
        State {
            name: "Failed6"
            when: engineRPM.state === 6
            PropertyChanges {
                target: cOverlay
                color: Style.overState6
            }
            PropertyChanges {
                target: engineRPM
                value: qsTr("Failed")
                dispMeasure: measure
            }
        },
        State {
            name: "Failed7"
            when: engineRPM.state === 7
            PropertyChanges {
                target: cOverlay
                color: Style.overState7
            }
            PropertyChanges {
                target: engineRPM
                value: qsTr("Failed")
                dispMeasure: measure
            }
        },
        State {
            name: "Failed8"
            when: engineRPM.state === 8
            PropertyChanges {
                target: cOverlay
                color: Style.overState8
            }
            PropertyChanges {
                target: engineRPM
                value: qsTr("Failed")
                dispMeasure: measure
            }
        },
        State {
            name: "Failed9"
            when: engineRPM.state === 9
            PropertyChanges {
                target: cOverlay
                color: Style.overState9
            }
            PropertyChanges {
                target: engineRPM
                value: qsTr("Failed")
                dispMeasure: measure
            }
        }
    ]
}

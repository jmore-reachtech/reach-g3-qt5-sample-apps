import QtQuick 2.15
import QtQuick.Window 2.2

Window {
    visible: true
    width: Window.width
    height: Window.height
    visibility: Window.FullScreen
    id: window

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onPressed: {
            target.x = mouse.x
            target.y = mouse.y
            console.log("Pressed  at ", mouse.x, "-", mouse.y, "--", Window.width, "x", Window.height)
        }

        onReleased: {
            target.x = mouse.x
            target.y = mouse.y
            console.log("Released at ", mouse.x, "-", mouse.y)
        }

    }
    Item {
        id: target

        property color color: mouseArea.pressed ? "red" : "green"

        Rectangle {
            color: "gray"
            border.width: 2
            border.color: parent.color
            opacity: 0.3
            anchors.centerIn: parent
            width: 200
            height: 200
            radius: width/2
        }
        Rectangle {
            color: "gray"
            border.width: 2
            border.color: parent.color
            opacity: 0.6
            anchors.centerIn: parent
            width: 100
            height: 100
            radius: width/2
        }
        Rectangle {
            border.color: parent.color
            anchors.centerIn: parent
            width: 20
            height: 20
            radius: width/2
            Rectangle {
                color: target.color
                height: parent.height
                width: 1
                anchors.centerIn: parent
            }
            Rectangle {
                color: target.color
                height: 1
                width: parent.width
                anchors.centerIn: parent
            }
        }
    }

    Text {
        anchors.centerIn: parent
        font.pixelSize: 28
        text: (mouseArea.pressed ? "pressed" : "not pressed") + "\n" + window.width + "x" + window.height + "\n" + target.x + "x" + target.y
    }
}

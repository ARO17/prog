import QtQuick 2.2
import QtQuick.Controls 1.1

import QtSensors 5.0

ApplicationWindow {
    title: qsTr("Accelerate Bubble")
    id: mainWindow
    width: 640
    height: 480
    visible: true

    Image {
        id: bubble
        source: "Bluebubble.svg"
        smooth: true
        property real centerX: mainWindow.width / 2
        property real centerY: mainWindow.height / 2
        property real bubbleCenter: bubble.width / 2
        x: centerX - bubbleCenter
        y: centerY - bubbleCenter

        Behavior on y {
            SmoothedAnimation {
                easing.type: Easing.Linear
                duration: 100
            }
        }
        Behavior on x {
            SmoothedAnimation {
                easing.type: Easing.Linear
                duration: 100
            }
        }
    }
    Accelerometer {
        id: accel
        dataRate: 100
        active:true

        onReadingChanged: {
            var newX = (bubble.x + calcRoll(accel.reading.x, accel.reading.y, accel.reading.z) * 0.8)
            var newY = (bubble.y - calcPitch(accel.reading.x, accel.reading.y, accel.reading.z) * 0.8)

            if (isNaN(newX) || isNaN(newY))
                return;

            if (newX < 0)
                newX = 0

            if (newX > mainWindow.width - bubble.width)
                newX = mainWindow.width - bubble.width

            if (newY < 18)
                newY = 18

            if (newY > mainWindow.height - bubble.height)
                newY = mainWindow.height - bubble.height

            bubble.x = newX
            bubble.y = newY
        }
    }

    function calcPitch(x, y, z) {
        return -(Math.atan(y / Math.sqrt(x * x + z * z)) * 57.2957795);
    }
    function calcRoll(x, y, z) {
        return -(Math.atan(x / Math.sqrt(y * y + z * z)) * 57.2957795);
    }

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("&Open")
                onTriggered: console.log("Open action triggered");
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }
}

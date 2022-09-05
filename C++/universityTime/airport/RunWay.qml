import QtQuick 2.0
import QtQuick.Shapes 1.15

Rectangle {
    id: _runway

    property string displayID
    property string displayRequest
    property bool runwayIsBusy

    color: "grey"
    border.color: "white"
    border.width: 2
    radius: 2

    // central line
    Shape {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.margins: _runway.height * 0.02
        ShapePath {
            strokeWidth: 2
            strokeColor: "white"
            strokeStyle: ShapePath.DashLine
            dashPattern: [7, 6]

            PathLine { x: 0; y: 0 }
            PathLine { x: 0; y: _runway.height * 0.98}

        }
    }

    // signal lines
    SignalLines {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.margins: parent.height * 0.02
//        lineIsBusy: _runway.runwayIsBusy // TODO
    }

    // IDs of the runway
    Text {
        anchors.left: _runway.left
        anchors.bottom: _runway.bottom
        anchors.margins: Math.min(_runway.width, _runway.height) / 20

        text: _runway.displayID
        color: "white"
        font {
            pointSize: 20
            bold: true
        }
    }

    Text {
        anchors.right: _runway.right
        anchors.top: _runway.top
        anchors.margins: Math.min(_runway.width, _runway.height) / 20

        text: _runway.displayID
        color: "white"
        font {
            pointSize: 20
            bold: true
        }
    }

    // current request
    Text {
        anchors.centerIn: _runway

        text: _runway.displayRequest
//        color: "#fcb205"
        color: "black"
        font {
            pointSize: 18
            bold: true
        }
    }
}

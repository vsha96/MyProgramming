import QtQuick 2.0

Rectangle {
    id: _airplanePark
    border.color: "black"
    border.width: 1
    color: "grey"
    Text {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        text: "Requests"
        color: "white"
        font {
            bold: true
            pointSize: 16
        }
    }

    RequestList {
        anchors.fill: parent
        anchors.margins: 10
        anchors.topMargin: parent.height * 0.04
        width: parent.width
        height: parent.height * 0.92
    }

}

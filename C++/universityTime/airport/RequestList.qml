import QtQuick 2.0

ListView {

    id: _root

//    model: app.numberOfRunways
    model: requestsListModel

    delegate: Item {
        id: _backgroundDelegate
        anchors.horizontalCenter: parent.horizontalCenter
        width: _root.width
        height: _root.height * 0.1

        property string statusInfo: display
        property string statusColor: decoration
        Rectangle {
            anchors.fill: _backgroundDelegate
            anchors.margins: 2
            border.color: _backgroundDelegate.statusColor
            color: "darkgray"
            border.width: 3
            Text {
                anchors.centerIn: parent

                text: _backgroundDelegate.statusInfo
        //        color: "#fcb205"
                color: "black"
                font {
                    pointSize: 12
                    bold: true
                }
            }

        }
    }
}

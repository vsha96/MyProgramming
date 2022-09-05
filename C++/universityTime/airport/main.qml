import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    id: _root

    minimumWidth: 720
    minimumHeight: 480
    width: 800
    height: 500
    visible: true
    title: qsTr("Airport simulation")
    color: "darkgrey"

    // TODO AirplanePark
    // make GridView for placing airplanes
    // with the number fligh and runway assigned
    RequestsPanel {
        id: _requestsPanel
        z: 1
        width: _root.width * 0.2
        height: _root.height
    }

    AirportRunWays {
        id: _airportRunWays

        anchors.left: _requestsPanel.right
        anchors.bottom: parent.bottom

        width: _root.width * 0.5
        height: _root.height * 0.9
    }

    // control panel
    ControlPanel {
        id: _controls
        z: 1
        anchors.left: _airportRunWays.right
        width: _root.width * 0.3
        height: _root.height
    }







    /*
    Rectangle {
        id: _controls
        z: 1
        anchors.left: _airportRunWays.right
        width: _root.width * 0.3
        height: _root.height

        border.color: "black"
        border.width: 1
        color: "orange"
        Text {
            anchors.centerIn: parent
            text: "Controls"
            color: "white"
            font {
                bold: true
                pointSize: 16
            }
        }
    }
    */

    /*
    RunWay {
        width: root.width * 0.2
        height: root.height * 0.8
    }
    */
}

import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.15

Rectangle {
    id: _controlPanel
    border.color: "black"
    border.width: 1
    color: "grey"

    Text {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        text: "Control Panel"
        color: "white"
        font {
            bold: true
            pointSize: 16
        }
    }

    // current time
    Rectangle {
        id: _currentTimeDisplay

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: parent.height * 0.05

        width: parent.width * 0.7
        height: parent.height * 0.1

        color: "darkgray"
        border.color: "white"
        border.width: 2
        radius: 2
        Text {
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            anchors.margins: parent.width * 0.28
            text: app.worldTimeHour
            font.pointSize: 24
        }
        Text {
            anchors.centerIn: parent
            text: ":"
            font.pointSize: 24
        }
        Text {
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            anchors.margins: parent.width * 0.28
            text: app.worldTimeMin
            font.pointSize: 24
        }
        /*
        Text {
            anchors.centerIn: parent
            // TODO how to derive struct of worldTime?
            text: app.worldTimeHour + ":" + app.worldTimeMin
            font {
                pointSize: 24
            }
        }
        */
    }
    // TODO speed of time several buttons or slider

    // statistics
    Rectangle {
        id: _stats

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: _currentTimeDisplay.bottom
        anchors.topMargin: parent.height * 0.02

        width: parent.width
        height: parent.height * 0.3

        color: "darkgray"
        border.color: "black"
        border.width: 1
        radius: 2

        Text {
            anchors.fill: parent
            anchors.verticalCenter: parent.verticalCenter
            anchors.margins: parent.width * 0.01
            text:
                "Handled requests:\t" + app.statNumberRequestsHandled + "\n" +
                "Max delay (min): \t" + app.statMaxActualDelay + "\n" +
                "Avg delay (min): \t" + (app.statAverageActualDelay).toFixed(2) + "\n" +
                "Max request num: \t" + app.statMaxRequestNumberOnRunway + "\n" +
                "Avg request num: \t" + (app.statAverageRequestNumberOnRunway).toFixed(2) + "\n" +
                "Avg busy runways num:  " + (app.statAverageNumberBusyRunway).toFixed(2)
            font {
                pointSize: 16
            }
        }
    }

    // show timetable
    /*
    Button {
        id: _timetableButton
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: _currentTimeDisplay.bottom
        anchors.topMargin: parent.height * 0.01

        width: parent.width * 0.8
        height: parent.height * 0.1

        Text {
            anchors.centerIn: parent
            text: "show timetable"
            font {
                pointSize: 24
            }
        }

        // TODO show timetable
        //onClicked:
    }
    */


    // increase N
    Button {
        id: _increaseButton
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: parent.height * 0.5

//        signal increaseClicked()
        onClicked: { app.increaseClicked() }

        Connections {
            target: app

        }

        width: parent.width * 0.8
        height: parent.height * 0.1

        Text {
            anchors.centerIn: parent
            text: "add runway"
            font {
                pointSize: 24
            }
        }

        // TODO increase N if simulation was not started
        //onClicked:
    }

    // the parameter N
    Rectangle {
        id: _parameterN

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: _increaseButton.bottom
        anchors.topMargin: 0

        width: parent.width
        height: parent.height * 0.1

        color: "darkgray"
        border.color: "black"
        border.width: 1
        radius: 2

        Text {
            anchors.centerIn: parent
            text: " Runways = " + app.numberOfRunways // TODO the parameter of simulation
            font {
                pointSize: 24
            }
        }
    }

    // decrease N
    Button {
        id: _decreaseButton
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: _parameterN.bottom
        anchors.topMargin: 0

        onClicked: { app.decreaseClicked() }

        width: parent.width * 0.8
        height: parent.height * 0.1

        Text {
            anchors.centerIn: parent
            text: "delete runway"
            font {
                pointSize: 24
            }
        }

        // TODO decrease N if simulation was not started and N>2
        //onClicked:
    }

    // start simulation
    Button {
        id: _startSimButton
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: _stopSimButton.top
        anchors.topMargin: parent.height * 0.6

        // TODO start simulation if not started
        onClicked: { app.startSimulation() }

        width: parent.width * 0.9
        height: parent.height * 0.1

        Text {
            anchors.centerIn: parent
            text: "start simulation"
            font {
                pointSize: 20
            }
        }
    }

    // stop simulation
    Button {
        id: _stopSimButton
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.topMargin: parent.height * 0.6

        // TODO stop simulation if not stopped
        onClicked: app.stopSimulation()

        width: parent.width * 0.9
        height: parent.height * 0.1

        Text {
            anchors.centerIn: parent
            text: "stop simulation"
            font {
                pointSize: 20
            }
        }

    }
}

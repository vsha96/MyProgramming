import QtQuick 2.0
//import Airport 1.0

ListView {
    id: _root

//    model: app.numberOfRunways
    model: runwaysListModel

    orientation: ListView.Horizontal
    delegate: Item {
        id: _backgroundDelegate
        width: _root.width * 0.2
        height: _root.height
        RunWay {
            anchors.fill: _backgroundDelegate
            anchors.margins: 2
            color: "grey"
            displayID: index
            displayRequest: display
//            displayID: display
            runwayIsBusy: decoration
        }
    }

}

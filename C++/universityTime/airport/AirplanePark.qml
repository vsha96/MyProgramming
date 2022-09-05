import QtQuick 2.0

GridView {
    id: _root
    model: 3

    delegate: Rectangle {
        width: _root.width / 2
        height: _root.width / 2
        color: "black"
    }
}

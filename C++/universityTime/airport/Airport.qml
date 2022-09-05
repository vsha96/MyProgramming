import QtQuick 2.0

ListView {
    id: _airport
    model: 5

    delegate: RunWay {
        width: root.width * 0.2
        height: root.height * 0.8

    }
}

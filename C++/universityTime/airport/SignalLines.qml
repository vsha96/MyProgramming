import QtQuick 2.0
import QtQuick.Shapes 1.15

Shape {
    width: parent.width * 0.15
    height: parent.height * 0.97

    property bool lineIsBusy: runwayIsBusy
    // left signal line
    ShapePath {
        strokeWidth: 2
        strokeColor: lineIsBusy ? "red" : "lightgreen"
        strokeStyle: ShapePath.DashLine
        dashPattern: [1, 4]

        PathLine { x: 0; y: 0 }
        PathLine { x: 0; y: height}
    }

    // right singnal line
    ShapePath {
        strokeWidth: 2
        strokeColor: lineIsBusy ? "red" : "lightgreen"
        strokeStyle: ShapePath.DashLine
        dashPattern: [1, 4]

        startX: width; startY: 0
        PathLine { x: width; y: 0 }
        PathLine { x: width; y: height}
    }
}

import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.11


Canvas {
    id: root

    property var view_model
    property var counter
            
    property bool isFirst: true

    function clear() {
        var ctx = this.getContext("2d");
        ctx.clearRect(0, 0, width, height);
        ctx.beginPath();
        ctx.fillStyle = Qt.rgba(1, 1, 1, 1);
        ctx.fillRect(0, 0, width, height);
        this.requestPaint();
    }

    function draw() {
        if (counter) {
            counter.mouse_clicks = 0;
        }
        var lines = root.view_model.lines;

        for (let index = 0; index < lines.length; index++) {
            const line =lines[index];            
            drawLine(line.begin, line.end);
        }
        
        this.requestPaint();
    }

    onPaint: {                
        if (isFirst) {
            this.clear();
            isFirst = false;
        }                
    }

    function drawLine(from, to) {
        var ctx = this.getContext("2d");
        ctx.strokeStyle = '#0';
        ctx.moveTo(from.x, from.y);
        ctx.lineTo(to.x, to.y);
        ctx.stroke();
    }

    MouseArea {
        
        anchors.fill: parent
        
        onClicked: {
            if (mouse.button == Qt.LeftButton) {
                root.view_model.mouse_clicked(this.mouseX, this.mouseY);
                if (counter) {
                    counter.mouse_clicks++;
                }
            }
        }
    }
}
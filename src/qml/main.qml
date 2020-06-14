import QtQuick 2.5
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.11
import QtQuick.Window 2.2

import QtQuick.Controls.Material 2.2
import QtQuick.Dialogs 1.1

import App 1.0

import "Components"

ApplicationWindow {
    visible: true
    width: 800
    height: 600
    title: qsTr("Fractals App")

    Material.theme: Material.Dark
    Material.accent: Material.Purple


    MessageDialog {
        id: notifier
        property int mouse_clicks
        title: "Attempt"
        text: "invalid points count " + this.mouse_clicks + ". Clear or add even count of points."
        onAccepted: {
            Qt.quit()
        }
    }


    ColumnLayout {
        anchors.fill: parent
        
        RowLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true

            LinesRenderSurface {
                id: fractalsRenderer
                view_model: ViewModelsFactory.make_fractals_renderer_vm(this)
                counter: notifier
                Layout.fillWidth: true
                Layout.fillHeight: true

                Component.onCompleted: {
                    var self = this;
                    self.view_model.onInitDraw.connect(function () {
                        self.draw();
                    });
                }
            }

           ColumnLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignTop

                TextField {
                    id: recursionInput
                    placeholderText: qsTr("Enter recursion depth")
                    validator: IntValidator {bottom: 0; top: 1000;}
                }

                Button {
                    text: "Clear"
                    Material.background: Material.Purple

                    onClicked: {
                        fractalsRenderer.clear();
                    }
                    
                }

                Button {
                    text: "Draw"
                    Material.background: Material.Purple
                    enabled: recursionInput.text != ""
                    onClicked: {
                        fractalsRenderer.view_model.calculate_fractal(recursionInput.text);
                    }
                }

                LinesRenderSurface {
                    id: patternRenderer

                    width: 200
                    height: 200

                    view_model: ViewModelsFactory.make_pattern_generator_vm(this)

                    onHeightChanged: {
                        this.view_model.on_surface_size_changed(this.width, this.height);
                    }

                    onWidthChanged: {
                        this.view_model.on_surface_size_changed(this.width, this.height);
                    }

                    Component.onCompleted: {
                        this.view_model.on_surface_size_changed(this.width, this.height);
                        var self = this;
                        self.view_model.onInitDraw.connect(function () {
                            self.draw();
                        });
                    }
                }

                Button {
                    text: "Clear pattern"
                    Material.background: Material.Purple

                    onClicked: {
                        patternRenderer.clear()
                        patternRenderer.view_model.clear()
                    }
                }

                Button {
                    text: "Apply pattern"
                    Material.background: Material.Purple

                    onClicked: {
                        patternRenderer.view_model.apply_pattern()
                        patternRenderer.view_model.clear()
                        patternRenderer.clear()
                    }
                }
           }
        }
    }
}
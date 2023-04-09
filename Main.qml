import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts

import QtXcodeDataModel 1.0

ApplicationWindow {
    id: appRoot
    width: 720
    height: 600
    maximumWidth: 720
    maximumHeight: 600
    minimumWidth: 720
    minimumHeight: 600
    visible: true
    title: qsTr("Xcode Releases")
    visibility: "Windowed"

    XcodeDataModel { id: xcodeDataModel; }

    Component.onCompleted: {

    }

    ScrollView {
        anchors.fill: parent
        ListView {
            id: view
            model: xcodeDataModel
            spacing: 10
            header: Pane {
                width: parent.width
                height: 128
                z:999
                Column {
                    anchors.centerIn: parent
                    Label {
                        font.pixelSize: 32
                        text: qsTr("<strong>Xcode Releases</strong>")
                    }
                    Label {
                        font.pixelSize: 14
                        text: qsTr("More than you ever wanted to know™")
                    }
                }
            }

            headerPositioning: ListView.OverlayHeader

            delegate: RowLayout {
                Layout.fillWidth: true
                anchors.topMargin: 64

                Item { width: 25; }

                Label {
                    font.pixelSize: 14
                    text: "<strong>Xcode</strong> " + model.version
                    Layout.minimumWidth: 120
                }
                Label {
                    font.pixelSize: 14
                    text: model.build
                    Layout.minimumWidth: 64
                }
                Label {
                    font.pixelSize: 14
                    text: model.release
                    Layout.minimumWidth: 64
                }
                Label {
                    font.pixelSize: 14
                    text: model.released
                    Layout.minimumWidth: 96
                }
                Label {
                    font.pixelSize: 14
                    text: "macOS " + model.requires + "+"
                    Layout.minimumWidth: 200
                }
                Button {
                    text: "Get"
                    onClicked: {
                        Qt.openUrlExternally(model.url)
                    }
                }
            }
        }
    }
}

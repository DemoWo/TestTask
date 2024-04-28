import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import QtQuick.Dialogs
import QtGraphs

Window {
    width: 800
    height: 600
    visible: true
    title: qsTr("TZ2Gis")

    ColumnLayout {
        Layout.preferredWidth: Window.width
        Layout.preferredHeight: Window.height
        Timer {
            id: tim
            interval: 50
            running: false
            repeat: true
            onTriggered: {
                _mainwindow.timerUpdate()
            }
        }
        Rectangle {
            Layout.preferredWidth: Window.width
            Layout.preferredHeight: Window.height / 2
            color: "#00000000"

            RowLayout {
                implicitHeight: parent.height
                implicitWidth: parent.width

                Bars3D {
                    id: surfaceGraph
                    Layout.preferredWidth: parent.width
                    Layout.preferredHeight: parent.height
                    orthoProjection: true
                    inputHandler: InputHandler3D {
                        rotationEnabled: false
                        zoomEnabled: false
                    }
                    Bar3DSeries {
                        itemLabelFormat: "@colLabel: @valueLabel"
                        baseColor: "green"

                        ItemModelBarDataProxy {
                            id: itemBar
                            itemModel: dataModel
                            rowRole: "row"
                            columnRole: "word"
                            valueRole: "countMode"
                        }
                    }
                    theme: Theme3D {
                        ambientLightStrength: 0.5
                        backgroundColor: "#00000000"
                        backgroundEnabled: true
                        font.family: "green"
                        font.pointSize: 20
                        gridEnabled: true
                        gridLineColor: "black"
                        labelBackgroundColor: "#00000000"
                        labelBackgroundEnabled: true
                        labelBorderEnabled: true
                        labelTextColor: "black"
                        lightColor: "#00000000"
                        singleHighlightColor: "yellow"
                        windowColor: "white"
                    }
                }
            }
            ListModel {
                id: dataModel
            }

            Repeater {
                id: repeaterMod
                model: _mainwindow.modeWord

                Text {
                    text: modelData["word"]
                    visible: false
                    onTextChanged: {
                        // for( )
                        let indexes = [...Array(dataModel.count).keys()]
                        if (indexes.length < 15) {
                            dataModel.append({
                                                 "row": modelData["row"],
                                                 "word": modelData["word"],
                                                 "countMode": modelData["countMode"]
                                             })
                        }
                        dataModel.set(modelData["Index"], {
                                          "row": modelData["row"],
                                          "word": modelData["word"],
                                          "countMode": modelData["countMode"]
                                      })
                    }
                }
            }
        }
        ProgressBar {
            Layout.preferredWidth: Window.width
            Layout.fillHeight: true
            value: _mainwindow.progressLoad

            background: Rectangle {
                radius: 5
                color: "lightgray"
                border.color: "gray"
                border.width: 1
                implicitWidth: Window.width
                implicitHeight: 20
            }
        }
        FileDialog {
            id: fileDialog
            nameFilters: ["Text files (*.txt)"]
            onAccepted: {
                _mainwindow.setPathFile(currentFile)
            }
        }
        RowLayout {
            ColumnLayout {
                id: columnLayout_button
                Layout.preferredHeight: Window.height / 2 - 30
                spacing: 0

                Text {
                    text: _mainwindow.pathFile
                    visible: _mainwindow.pathFile.length > 0 ? true : false
                    Layout.preferredWidth: Window.width
                    Layout.preferredHeight: columnLayout_button.height / 5 - 5
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }

                Button {
                    // Кнопка Открыть
                    text: "Открыть"
                    Layout.preferredWidth: Window.width
                    Layout.preferredHeight: columnLayout_button.height / 5 - 5
                    background: Rectangle {
                        radius: 5
                        color: _mainwindow.startActive ? "orange" : "snow"
                        border.color: "black"
                    }
                    onClicked: {
                        fileDialog.open()
                    }
                }
                Button {
                    // Кнопка Старт
                    text: "Старт"
                    Layout.preferredWidth: Window.width
                    Layout.preferredHeight: columnLayout_button.height / 5 - 5
                    background: Rectangle {
                        radius: 5
                        color: _mainwindow.startActive ? "orange" : "snow"
                        border.color: "black"
                    }
                    onClicked: {
                        _mainwindow.setStartActive(true)
                        tim.start()
                    }
                }
                Button {
                    // Кнопка Пауза
                    text: "Пауза"
                    Layout.preferredWidth: Window.width
                    Layout.preferredHeight: columnLayout_button.height / 5 - 5
                    background: Rectangle {
                        radius: 5
                        color: _mainwindow.pauseActive ? "orange" : "snow"
                        border.color: "black"
                    }
                    onClicked: {
                        _mainwindow.setPauseActive(true)
                        tim.stop()
                    }
                }
                Button {
                    // Кнопка Отмена
                    text: "Отмена"
                    Layout.preferredWidth: Window.width
                    Layout.preferredHeight: columnLayout_button.height / 5 - 5
                    background: Rectangle {
                        radius: 5
                        color: _mainwindow.cancelActive ? "orange" : "snow"
                        border.color: "black"
                    }
                    onClicked: {
                        _mainwindow.setCancelActive(true)
                    }
                }
            }
        }
    }
}

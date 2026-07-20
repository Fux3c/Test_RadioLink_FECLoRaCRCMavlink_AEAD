import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt.labs.platform as Platform
import FmControllers
import HumidityCollection
import com.horizon.components
import "components"

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Horizon Groundstation")

    // File dialog for importing mission CSV files
    Platform.FileDialog {
        id: importDialog
        title: "Import Mission CSV"
        nameFilters: ["CSV files (*.csv)", "All files (*)"]
        fileMode: Platform.FileDialog.OpenFile
        onAccepted: {
            var filePath = importDialog.file.toString()
            // Remove "file://" prefix if present
            if (filePath.startsWith("file://")) {
                filePath = filePath.substring(7)
            }
            console.log("Importing file:", filePath)
            handleImport(filePath)
        }
        onRejected: {
            console.log("Import cancelled")
        }
    }

    // Function to handle imported file, respond with ui elements based on returned result
    function handleImport(filePath) {
        console.log("Processing import from:", filePath)
        // Call C++ method to handle the import through context porperty
        var success = missionManager.importMissionData(filePath)
        if (success) {
            console.log("Import successful!")
        } else {
            console.log("Import failed!")
        }
    }

    menuBar: MenuBar {
        background: Rectangle {
            color: palette.button
            Text {
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                anchors.rightMargin: 12
                text: missionManager.modeText
                color: palette.buttonText
                font.pixelSize: 12
            }
            Text {
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.rightMargin: 120
                    text: serialReader.isOpen ? "● Connected" : "○ Disconnected"
                    color: serialReader.isOpen ? "#2CDE85" : "#ff4444"
                    font.pixelSize: 16
            }
}
        Menu {
            title: qsTr("File")
            Action {
                text: qsTr("Import...")
                onTriggered: importDialog.open()
            }
            Action { text: qsTr("Export...") }
            MenuSeparator { }
            Action {
                text: qsTr("Quit")
                onTriggered: Qt.quit() // TODO: ADD PROMPT
            }
        }
        Menu {
            title: qsTr("&Edit")
            Action { text: qsTr("Cu&t") }
            Action { text: qsTr("&Copy") }
            Action { text: qsTr("&Paste") }
        }
        Menu {
            title: qsTr("&Help")
            Action { text: qsTr("&About") }
        }
        Menu {
            title: qsTr("&Connection")
            Action {
                text: serialReader.isOpen ? qsTr("● Connected") : qsTr("○ Disconnected")
                enabled: false
            }
            MenuSeparator {}

            Action {
                text: qsTr("Reconnect")
                enabled: !serialReader.isOpen
                onTriggered: {
                    var port = serialReader.findHorizonPort()
                    if (port === ""){
                        console.log("No Horizon Module found")
                    }
                    else {
                        if (serialReader.openPort(port, 115200)) {
                            console.log("Reconnected on", port)
                        } else {
                            console.log("Failed to reconnect on", port)
                        }
                    }
                }
            }

            Action {
                text: qsTr("Disconnect")
                enabled: serialReader.isOpen
                onTriggered: serialReader.closePort()
            }
        }
    }

    ColumnLayout {
        anchors.fill: parent
        Layout.fillWidth: true
        Layout.fillHeight: true
        Layout.margins: 0
        spacing: 0


        TopBar {
            id: topBar
            objectName: "topBar"
            Layout.fillWidth: true
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true


            RowLayout {
                Layout.alignment: left
                Layout.fillHeight: true
                spacing: 0

                TabBar {
                    id: tabBar
                    Layout.fillHeight: true
                    Layout.preferredWidth: 100
                    Layout.minimumWidth: 100
                    padding: 0
                    leftPadding: 0
                    rightPadding: 0



                    // Make tabs vertical
                    contentItem: ListView {
                        model: tabBar.contentModel
                        currentIndex: tabBar.currentIndex
                        spacing: 0
                        orientation: ListView.Vertical
                    }

                    TabButton {
                        text: "Avionics"
                        rotation: 0
                        implicitHeight: tabBar.height / 2
                        width: tabBar.width
                    }
                    TabButton {
                        text: "Payload"
                        implicitHeight: tabBar.height / 2
                        width: tabBar.width
                    }
                }

                StackLayout {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    currentIndex: tabBar.currentIndex

                    AvionicsMain {}
                    PayloadMain {}
                }
            }

        }
    }
}

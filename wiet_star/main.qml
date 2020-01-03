import QtQuick 2.9
import QtQuick.Controls 2.2
import Qt.labs.folderlistmodel 2.1

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("WietStar")

    Page {
        width: 600
        height: 400

        ComboBox {
            id: comboBox
            model: folderModel
            x: 203
            y: 241
            width: 194
            height: 40

            FolderListModel {
                id: folderModel
                folder: "file:///home/regis/projects/untitled/music"
                nameFilters: ["*.mp3"]
            }

            textRole: "fileName"
        }

        Button {
            id: button
            x: 250
            y: 174
            text: qsTr("Play")
            onClicked: {
                console.log('elo')
            }
        }

        Text {
            x: 218
            y: 12
            text: qsTr("WietStar")
            font.pixelSize: 41
        }
    }


}

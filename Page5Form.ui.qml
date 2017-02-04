import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Item {
    id: item5
    objectName: "item5" //very important if one wishes to access more than just the root item
    property alias item5: item5
    property alias textField5: textField5
    property alias button5: button5
    width: 900
    height: 1600

    RowLayout {
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.topMargin: 10
        anchors.top: parent.top

        TextField {
            id: textField5
            Layout.fillWidth: true
            placeholderText: qsTr("Insert text here...")
            font.family: "Segoe UI"
        }

        Button {
            id: button5
            text: qsTr("Search")
            font.family: "Segoe UI"
        }
    }

    Flickable {
        id: flickable5
        objectName: "flickable5"
        x: 0
        y: 0
        anchors.rightMargin: 10
        anchors.leftMargin: 10
        anchors.bottomMargin: 0
        anchors.topMargin: 70
        anchors.fill: parent
        Layout.fillHeight: false
        Layout.fillWidth: false
        TextArea.flickable: TextArea {
            id: textArea5
            objectName: "textArea5"
            x: 0
            y: 0
            antialiasing: true
            textFormat: Text.RichText
            readOnly: true
            font.family: "Perpetua"
            wrapMode: Text.WordWrap
        }
        ScrollBar.vertical: ScrollBar {
        }
    }
}

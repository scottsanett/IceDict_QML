import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Item {
    id: item4
    objectName: "item4" //very important if one wishes to access more than just the root item
    property alias item4: item4
    property alias textField4: textField4
    property alias button4: button4
    property alias listView4: listView4
    property alias alterList4: alterList4
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
            id: textField4
            Layout.fillWidth: true
            placeholderText: qsTr("Insert text here...")
            font.family: "Segoe UI"
        }

        Button {
            id: button4
            text: qsTr("Search")
            font.family: "Segoe UI"
        }
    }

    Flickable {
        id: flickable4
        objectName: "flickable4"
        x: 0
        y: 0
        anchors.rightMargin: 10
        anchors.leftMargin: 120
        anchors.bottomMargin: 0
        anchors.topMargin: 70
        anchors.fill: parent
        Layout.fillHeight: false
        Layout.fillWidth: false
        TextArea.flickable: TextArea {
            id: textArea4
            objectName: "textArea4"
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

    ListView {
        id: listView4
        objectName: "listView4"
        anchors.right: flickable4.left
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.rightMargin: 10
        anchors.leftMargin: 10
        anchors.bottomMargin: 0
        anchors.topMargin: 70
        Layout.fillWidth: true
        Layout.fillHeight: true
        focus: true
        model: alterList4
        highlight: Rectangle {
            color: "black"
            radius: 5
            opacity: 0.3
            focus: true
        }
        ScrollBar.vertical: ScrollBar {
        }
    }
    ListModel {
        id: alterList4
    }
}

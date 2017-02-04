import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Item {
    id: item3
    objectName: "item3" //very important if one wishes to access more than just the root item
    property alias item3: item3
    property alias textField3: textField3
    property alias button3: button3
    property alias listView3: listView3
    property alias alterList3: alterList3
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
            id: textField3
            Layout.fillWidth: true
            placeholderText: qsTr("Insert text here...")
            font.family: "Segoe UI"
        }

        Button {
            id: button3
            text: qsTr("Search")
            font.family: "Segoe UI"
        }
    }

    Flickable {
        id: flickable3
        objectName: "flickable3"
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
            id: textArea3
            objectName: "textArea3"
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
        id: listView3
        objectName: "listView3"
        anchors.right: flickable3.left
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
        model: alterList3
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
        id: alterList3
    }
}

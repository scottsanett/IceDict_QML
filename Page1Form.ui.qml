import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Item {
    id: item1
    objectName: "item1" //very important if one wishes to access more than just the root item
    property alias item1: item1
    property alias textField1: textField1
    property alias button1: button1
    property alias listView: listView
    property alias alterList: alterList
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
            id: textField1
            Layout.fillWidth: true
            placeholderText: qsTr("Insert word here...")
            font.family: "Segoe UI"
        }

        Button {
            id: button1
            text: qsTr("Search")
            font.family: "Segoe UI"
        }
    }

    Flickable {
        id: flickable
        objectName: "flickable"
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
            id: textArea
            objectName: "textArea"
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
        id: listView
        objectName: "listView"
        anchors.right: flickable.left
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
        model: alterList
        highlight: Rectangle {
            color: "black"
            radius: 5
            opacity: 0.3
            focus: true
        }
        ScrollBar.vertical: ScrollBar {
        }
        ScrollBar.horizontal: ScrollBar {}
    }
    ListModel {
        id: alterList
    }
}

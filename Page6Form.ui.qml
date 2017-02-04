import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Item {
    id: item6
    objectName: "item6" //very important if one wishes to access more than just the root item
    property alias item6: item6
    property alias textField6: textField6
    property alias button6: button6
    property alias listView6: listView6
    property alias alterList6: alterList6
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
            id: textField6
            Layout.fillWidth: true
            placeholderText: qsTr("Insert text here...")
            font.family: "Segoe UI"
        }

        Button {
            id: button6
            text: qsTr("Search")
            font.family: "Segoe UI"
        }
    }

    Flickable {
        id: flickable6
        objectName: "flickable6"
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
            id: textArea6
            objectName: "textArea6"
            x: 0
            y: 0
            antialiasing: true
            textFormat: Text.RichText
            readOnly: true
            font.family: "Perpetua"
//            wrapMode: Text.WordWrap
        }
        ScrollBar.vertical: ScrollBar {}
        ScrollBar.horizontal: ScrollBar {}
    }

    ListView {
        id: listView6
        objectName: "listView6"
        anchors.right: flickable6.left
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
        model: alterList6
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
        id: alterList6
    }
}

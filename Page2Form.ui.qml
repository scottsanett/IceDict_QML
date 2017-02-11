import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Item {
    id: item2
    objectName: "item2" //very important if one wishes to access more than just the root item
    property alias item2: item2
    property alias textField2: textField2
    property alias button2: button2
    property alias listView2: listView2
    property alias alterList2: alterList2
    property alias flickable2: flickable2

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
            id: textField2
            Layout.fillWidth: true
            placeholderText: qsTr("Insert text here...")
            font.family: "Segoe UI"
        }

        Button {
            id: button2
            text: qsTr("Search")
            font.family: "Segoe UI"
        }
    }

    Flickable {
        id: flickable2
        objectName: "flickable2"
        x: 0
        y: 0
        anchors.rightMargin: 10
        anchors.leftMargin: 120
        anchors.bottomMargin: 0
        anchors.topMargin: 70
        anchors.fill: parent
        TextArea.flickable: TextArea {
            id: textArea2
            objectName: "textArea2"
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
        id: listView2
        objectName: "listView2"
        height: parent.height
        width: parent.width
        anchors.right: flickable2.left
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
        model: alterList2
        highlight: Rectangle {
            color: "black"
            radius: 5
            opacity: 0.3
            focus: true
        }
        ScrollBar.vertical: ScrollBar {}
    }
    ListModel {
        id: alterList2
    }
}

import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

ApplicationWindow {
    FontLoader { id: perpetua; source: "qrc:/alphabet/perpetua.ttf" }
    FontLoader { id: segoe; source: "qrc:/alphabet/segoeui.ttf" }
    width: 500
    height: 800
    visible: true
    title: qsTr("Icelandic Dictionary")

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex
        Page1 {}
        Page2 {}
        Page3 {}
        Page4 {}
        Page5 {}
        Page6 {}
    }


    footer: TabBar {
        id: tabBar
        width: parent.width
        currentIndex: swipeView.currentIndex
        TabButton {
            text: qsTr("Headword")
            font.family: "Segoe UI"
            width: 110
        }
        TabButton {
            text: qsTr("Entry")
            font.family: "Segoe UI"
            width: 110
        }
        TabButton {
            text: qsTr("Norse")
            font.family: "Segoe UI"
            width: 110
        }
        TabButton {
            text: qsTr("Textual")
            font.family: "Segoe UI"
            width: 110
        }
        TabButton {
            text: qsTr("Query")
            font.family: "Segoe UI"
            width: 110
        }
        TabButton {
            text: qsTr("Inflections")
            font.family: "Segoe UI"
            width: 110
        }
    }
}

import QtQuick 2.7

Page1Form {
    item1 {
        signal onlineDefSig(string str)
        signal onlineDefClickedSig(int key)
    }

    button1.onClicked: {
        alterList.clear();
        item1.onlineDefSig(textField1.text)
    }

    function addItemToList(item) {
        alterList.append({word: item});
    }

    listView {
        delegate: Item {
            width: parent.width
            height: 25
            focus: true
            Row {
                id: row1
                Text {
                    text: word
                    font.family: "Perpetua"
                    font.pointSize: 16
                    width: parent.width
                    wrapMode: Text.WordWrap
                }
            }
            MouseArea {
                id: itemMouseArea
                anchors.fill: parent
                onClicked: {
                    listView.currentIndex = index
                    item1.onlineDefClickedSig(index)
                }
            }
        }
    }

}

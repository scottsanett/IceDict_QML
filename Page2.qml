import QtQuick 2.7

Page2Form {
    item2 {
        signal onlineTextSig(string str)
        signal onlineTextClickedSig(int key)
    }

    button2.onClicked: {
        alterList2.clear();
        item2.onlineTextSig(textField2.text)
    }

    function addItemToList(item) {
        alterList2.append({word: item});
    }

    listView2 {
        delegate: Item {
            width: parent.width
            height: 25
            focus: true
            Row {
                id: row2
                Text {
                    text: word
                    font.family: "Perpetua"
                    font.pointSize: 16
                    width: parent.width
                    wrapMode: Text.WordWrap
                }
            }
            MouseArea {
                id: itemMouseArea2
                anchors.fill: parent
                onClicked: {
                    listView2.currentIndex = index
                    item2.onlineTextClickedSig(index)
                }
            }
        }
    }

}

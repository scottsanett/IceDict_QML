import QtQuick 2.7

Page6Form {
    item6 {
        signal printAllSig(string str)
        signal printAllClickedSig(int key)
    }

    button6.onClicked: {
        alterList6.clear();
        item6.printAllSig(textField6.text)
    }

    function addItemToList(item) {
        alterList6.append({word: item});
    }

    function clearList() {
        alterList6.clear();
    }

    listView6 {
        delegate: Item {
            width: parent.width
            height: 25
            focus: true
            Row {
                id: row6
                Text {
                    text: word
                    font.family: "Perpetua"
                    font.pointSize: 16
                    width: parent.width
                    wrapMode: Text.WordWrap
                }
            }
            MouseArea {
                id: itemMouseArea6
                anchors.fill: parent
                onClicked: {
                    listView6.currentIndex = index
                    item6.printAllClickedSig(index)
                }
            }
        }
    }

}

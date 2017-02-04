import QtQuick 2.7

Page4Form {
    item4 {
        signal findTextSig(string str)
        signal findTextClickedSig(int key)
    }

    button4.onClicked: {
        alterList4.clear();
        item4.findTextSig(textField4.text)
    }

    function addItemToList(item) {
        alterList4.append({word: item});
    }

    function clearList() {
        alterList4.clear();
    }

    listView4 {
        delegate: Item {
            width: parent.width
            height: 25
            focus: true
            Row {
                id: row4
                Text {
                    text: word
                    font.family: "Perpetua"
                    font.pointSize: 16
                    width: parent.width
                    wrapMode: Text.WordWrap
                }
            }
            MouseArea {
                id: itemMouseArea4
                anchors.fill: parent
                onClicked: {
                    listView4.currentIndex = index
                    item4.findTextClickedSig(index)
                }
            }
        }
    }

}

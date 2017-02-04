import QtQuick 2.7

Page3Form {
    item3 {
        signal findDefSig(string str)
        signal findDefClickedSig(int key)
        signal textChangedSig(string str)
    }

    button3.onClicked: {
        alterList3.clear()
        item3.findDefSig(textField3.text)
    }

    textField3.onTextChanged: {
        alterList3.clear()
        item3.textChangedSig(textField3.text)
    }

    function addItemToList(item) {
        alterList3.append({word: item});
    }
    function clearList() {
        alterList3.clear();
    }

    listView3 {
        delegate: Item {
            width: parent.width
            height: 25
            focus: true
            Row {
                id: row3
                Text {
                    text: word
                    font.family: "Perpetua"
                    font.pointSize: 16
                    width: parent.width
                    wrapMode: Text.WordWrap
                }
            }
            MouseArea {
                id: itemMouseArea3
                anchors.fill: parent
                onClicked: {
                    listView3.currentIndex = index
                    item3.findDefClickedSig(index)
                }
            }
        }
    }

}

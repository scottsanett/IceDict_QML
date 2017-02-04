import QtQuick 2.7

Page5Form {
    item5 {
        signal querySig(string str)
    }

    button5.onClicked: {
        item5.querySig(textField5.text)
    }
}

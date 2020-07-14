import QtQuick 2.12

Rectangle {
    color: Theme.sidePanelBg

    ListView {
        id: chatList
        x: sidePanel.x
        y: sidePanel.y
        width: sidePanel.width
        height: sidePanel.height
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

import QtQuick 2.12

Rectangle {
    color: Theme.chatBg

    Text {
        x: chat.x + chat.width / 2
        y: chat.y + chat.height / 2
        text: qsTr("No messages yet")
        anchors.centerIn: parent
        font.family: Constants.font.family
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

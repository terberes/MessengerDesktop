import QtQuick 2.12
import QtGraphicalEffects 1.15

Rectangle {
    property string nameStr
    property string dateStr
    property string msgStatus
    Image {
            id: avatar
            width: height
            height: parent.height
            anchors.left: parent.left
            anchors.centerIn: parent.horizontalCenter
            property int margin: 10
            anchors.leftMargin: margin
            anchors.rightMargin: margin
            anchors.topMargin: margin
            anchors.bottomMargin: margin
            fillMode: Image.PreserveAspectCrop
            layer.enabled: true
            layer.effect: OpacityMask {
                maskSource: avatarMask
            }
        }

        Rectangle {
            id: avatarMask
            width: avatar.width
            height: avatar.height
            radius: 250
            visible: false
        }
        Text {
            id: nameTxt
            text: nameStr
            anchors.left: avatar.left
        }
        Text {
            id: dateTxt
            text: dateStr
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.rightMargin: 5
            anchors.topMargin: 5
        }
        function getMsgStatusIconSrc() {
            switch (msgStatus) {
                case "received":
                    return "icons/msgStatus/received.png"
                case "sent":
                    return "icons/msgStatus/sent.png"
                case "sending":
                    return "icons/msgStatus/sending.png"
            }
        }
        Image {
            id: msgStatusIcon
            source: getMsgStatusIconSrc()
        }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

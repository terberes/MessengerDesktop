import QtQuick 2.0
import QtQuick.Controls 2.12
import Api 1.0
import Data 1.0
import Network 1.0

IntroStage {
    Label {
        id: title
        text: qsTr("Enter your server address")
        anchors.horizontalCenterOffset: 0
        anchors.verticalCenterOffset: -24
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 20
        fontSizeMode: Text.Fit
    }
    function submitServerPrefs() {
        console.warn("addr: " + addressInput.text
                     != "" ? addressInput.text : addressInput.placeholderText)
        setSpin(true)
        Api.get_server_preferences().then(() => {
            setSpin(false)
            stageComplete()
        })
    }

    TextField {
        id: addressInput
        width: 170
        placeholderText: "127.0.0.1:5000"
        horizontalAlignment: Text.AlignHCenter
        anchors.top: title.bottom
        anchors.topMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter
        font.pointSize: 11
        onAccepted: submitServerPrefs()
    }

    Button {
        id: submitButton
        text: qsTr("Submit")
        anchors.top: addressInput.bottom
        anchors.horizontalCenter: addressInput.horizontalCenter
        anchors.topMargin: 30
        onClicked: submitServerPrefs()
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/


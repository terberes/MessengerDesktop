import QtQuick 2.0
import QtQuick.Controls 2.12
import "../misc"

IntroStage {
    id: root
    Label {
        id: title
        text: qsTr("Enter your phone number")
        anchors.horizontalCenterOffset: 0
        anchors.verticalCenterOffset: -24
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 20
        fontSizeMode: Text.Fit
    }

    function submitNumber() {
        root.stageComplete()
    }

    NumberTextField {
        id: numberInput
        width: 170
        anchors.top: title.bottom
        anchors.topMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter
        font.pointSize: 11
        onSubmit: submitNumber()
    }

    Button {
        id: submitButton
        text: qsTr("Submit")
        anchors.top: numberInput.bottom
        anchors.horizontalCenter: numberInput.horizontalCenter
        anchors.topMargin: 30
        onClicked: numberInput.check() ? submitNumber() : {}
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/


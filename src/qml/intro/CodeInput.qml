import QtQuick 2.4
import QtQuick.Controls 2.12
import Api 1.0

IntroStage {
    Label {
        id: title
        text: qsTr("Enter code")
        anchors.horizontalCenterOffset: 0
        anchors.verticalCenterOffset: -24
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 20
        fontSizeMode: Text.Fit
    }

    function submitCode(code) {
        Api.verifyCode(code, root.number).then((result) => {
            console.error(result)
        }).fail((err, description) => {
                    console.log("Error in sending number; code \"",
                                err, "\"; description \"", description, "\"")
            openErrorDialog("Error in sending number; code \""
                            + err + "\"; description \"" + description + "\"")
        })
    }

    TextField {
        id: codeInput
        width: 170
        horizontalAlignment: Text.AlignHCenter
        anchors.top: title.bottom
        anchors.topMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter
        font.pointSize: 11
        validator: RegExpValidator {
            regExp: /\d{6}/
        }
        onAccepted: submitCode(text)
    }

    Button {
        id: submitButton
        text: qsTr("Submit")
        anchors.top: codeInput.bottom
        anchors.horizontalCenter: codeInput.horizontalCenter
        anchors.topMargin: 30
        onClicked: codeInput.acceptableInput ? submitCode(codeInput.text) : {}
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/


import QtQuick 2.4
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import Api 1.0

IntroStage {
    ColumnLayout {
        id: container
        anchors.centerIn: parent
        spacing: 25
        Label {
            Layout.alignment: Qt.AlignCenter
            id: title
            text: qsTr("Enter code")
            font.pixelSize: 20
            fontSizeMode: Text.Fit
        }

        TextField {
            id: codeInput
            Layout.alignment: Qt.AlignCenter
            width: 170
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 11
            validator: RegExpValidator {
                regExp: /\d{6}/
            }
            onAccepted: submitCode(text)
        }

        Button {
            id: submitButton
            Layout.alignment: Qt.AlignCenter
            text: qsTr("Submit")
            onClicked: codeInput.acceptableInput ? submitCode(codeInput.text) : {}
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
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/


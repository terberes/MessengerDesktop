import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import Api 1.0
import Persist 1.0
import "../misc"

IntroStage {
    id: numberInputRoot
    ColumnLayout {
        anchors.centerIn: parent
        spacing: 25
        Label {
            id: title
            Layout.alignment: Qt.AlignCenter
            text: qsTr("Enter your phone number")
            font.pixelSize: 20
            fontSizeMode: Text.Fit
        }

        Row {
            id: column
            Layout.alignment: Qt.AlignCenter
            Layout.preferredHeight: 40

            NumberTextField {
                id: numberInput
                width: 170
                font.pointSize: 11
                onSubmit: numberInputRoot.submitNumber(number)
            }

            ComboBox {
                id: channelSelect
                width: 100
                model: [
                    "SMS",
                    "Call"
                ]
                function getEnumValue() {
                    switch (model) {
                    case "SMS": return Api.Sms
                    case "Call": return Api.Call
                    }
                }
            }
        }

        Button {
            id: submitButton
            Layout.alignment: Qt.AlignCenter
            text: qsTr("Submit")
            onClicked: numberInput.check();
        }
    }
    function submitNumber(number) {
        setSpin(true);
        Api.sendCode(number, channelSelect.getEnumValue()).then(() => {
            setSpin(false);
            setNumber(number)
            Settings.sendCode()
            numberInputRoot.stageComplete()
        }).fail((err, description) => {
            setSpin(false)
            console.log("Error in sending number; code",
                                err, "description", description)
            numberInputRoot.openErrorDialog("Error in sending number; code '%1'; description: '%2'".arg(err, description))
        })
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/


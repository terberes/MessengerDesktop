import QtQuick 2.0
import QtQuick.Controls 2.12
import Api 1.0
import "../misc"

IntroStage {
    id: root
    Label {
        id: title
        text: qsTr("Enter your phone number")
        anchors.horizontalCenterOffset: 0
        anchors.verticalCenterOffset: -50
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 20
        fontSizeMode: Text.Fit
    }

    function submitNumber(number) {
        setSpin(true);
        Api.sendCode(number, channelSelect.getEnumValue()).then(() => {
            setSpin(false);
            setNumber(number)
            root.stageComplete()
        }).fail((err, description) => {
            setSpin(false)
            console.log("Error in sending number; code \"",
                                err, "\"; description \"", description, "\"")
            openErrorDialog("Error in sending number; code \""
                            + err + "\"; description \"" + description + "\"")
        })
    }

    Row {
        id: column
        anchors.top: title.bottom
        anchors.topMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter

        NumberTextField {
            id: numberInput
            width: 170
//            anchors.top: title.bottom
//            anchors.topMargin: 20
//            anchors.horizontalCenter: parent.horizontalCenter
            font.pointSize: 11
            onSubmit: submitNumber(number)
        }

        ComboBox {
            id: channelSelect
            width: 110
            height: 40
//            anchors.top: numberInput.bottom
//            anchors.horizontalCenter: numberInput.horizontalCenter
//            anchors.topMargin: 30
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
        text: qsTr("Submit")
        anchors.top: column.bottom
        anchors.horizontalCenter: column.horizontalCenter
        anchors.topMargin: 30
        onClicked: numberInput.check();
    }

}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/


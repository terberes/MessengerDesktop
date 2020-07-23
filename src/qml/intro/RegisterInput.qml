import QtQuick 2.0
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

IntroStage {
//    ColumnLayout {
//        anchors.centerIn: parent
//        Label {
//            Layout.alignment: Qt.AlignCenter
//            horizontalAlignment: Text.AlignHCenter
//            font.pointSize: 20
//            fontSizeMode: Text.Fit
//            text: qsTr("Register")
//        }
//        TextField {

//        }
//    }

    ColumnLayout {
        id: container
        anchors.centerIn: parent
        spacing: 25
        Label {
            Layout.alignment: Qt.AlignCenter
            id: title
            text: qsTr("Register")
            font.pixelSize: 20
            fontSizeMode: Text.Fit
        }

        TextField {
            id: firstNameInput
            placeholderText: qsTr("First Name")
            Layout.alignment: Qt.AlignCenter
            width: 170
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 11
        }
        TextField {
            id: lastNameInput
            placeholderText: qsTr("Last Name")
            Layout.alignment: Qt.AlignCenter
            width: 170
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 11
        }
        TextField {
            id: usernameInput
            placeholderText: qsTr("Username")
            Layout.alignment: Qt.AlignCenter
            width: 170
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 11
        }

        Button {
            id: submitButton
            Layout.alignment: Qt.AlignCenter
            text: qsTr("Submit")
            onClicked: codeInput.acceptableInput ? submitCode(codeInput.text) : {}
        }

        function submitData(code) {
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

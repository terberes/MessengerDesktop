import QtQuick 2.0
import MessengerDesktop.Numbers 1.0
import QtQuick.Controls 2.12

//Component {
Item {
    id: root
    signal setSpin(bool t)
    signal stageComplete
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

    PhoneNumberService {
        id: numberService
    }

    function submitNumber() {
        root.stageComplete()
    }

    TextField {
        id: numberInput
        width: 170
        anchors.top: title.bottom
        anchors.topMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter
        font.pointSize: 11
        readOnly: true
        text: "+"
        horizontalAlignment: Text.AlignHCenter
        property bool isError: false
        property bool isChecked: false
        color: isError ? "#c00000" : (isChecked ? "#00c000" : "#000000")
        function check() {
            isError = !numberService.verify()
            isChecked = !isError
            if (isChecked)
                submitNumber()
            return isChecked
        }

        Keys.onPressed: {
            switch (event.key) {
            case Qt.Key_Return:
            case Qt.Key_Enter:
                check()
                break
            case Qt.Key_Backspace:
                numberService.remove_digit()
                text = numberService.number
                break
            default:
                if (numberService.add_digit(event.text)) {
                    text = numberService.number
                    isError = false
                } else
                    isError = true
                break
            }
        }
    }

    Button {
        id: submitButton
        text: qsTr("Submit")
        anchors.top: numberInput.bottom
        anchors.horizontalCenter: numberInput.horizontalCenter
        anchors.topMargin: 30
        onClicked: numberInput.check() ? submitNumber() : {}
    }
} //}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/


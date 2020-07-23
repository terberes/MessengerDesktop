import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import Api 1.0
//import Persist 1.0
import Network 1.0

IntroStage {
    ColumnLayout {
        anchors.centerIn: parent
        spacing: 25
        Label {
            id: title
            Layout.alignment: Qt.AlignCenter
            text: qsTr("Enter your server address")
            font.pixelSize: 20
            fontSizeMode: Text.Fit
        }

        TextField {
            id: addressInput
            Layout.alignment: Qt.AlignCenter
            width: 170
            placeholderText: "127.0.0.1:5000"
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 11
            onAccepted: submitServerPrefs()
            function getAddr() {
                return text != "" ? text : placeholderText
            }
        }

        Button {
            id: submitButton
            Layout.alignment: Qt.AlignCenter
            text: qsTr("Submit")
            onClicked: submitServerPrefs()
        }

        function submitServerPrefs() {
            setSpin(true)
            Api.setBaseUrl(addressInput.getAddr())
            Api.getServerPrefs().then((result) => {
                setSpin(false)
                Settings.setRealTimeURLs(result["realTimeServerIPv4"], result["realTimeServerIPv6"], result["realTimePortIPv4"], result["realTimePortIPv6"])
                stageComplete()
            }).fail((error, description) => {
                setSpin(false)
                console.debug("Error; code", error, "description", description)
                openErrorDialog(`Error code ${error}, ${description}`)
            })
        }
    }
}




/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

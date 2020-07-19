import QtQuick 2.0
import QtQuick.Controls 2.12
import Api 1.0
import Persist 1.0
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
        function getAddr() {
            return text != "" ? text : placeholderText
        }
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




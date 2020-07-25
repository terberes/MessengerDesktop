import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 2.15
import Api 1.0
import Persist 1.0
import Misc.System 1.0

ApplicationWindow {
    id: root
    width: 600
    height: 480
    visible: true
//    signal introFinished

    BusyIndicator {
        id: busyIndicator
        x: 0
        width: 50
        height: width
        enabled: false
        visible: enabled
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
    }

    StackView {
        id: stagesStack
        hoverEnabled: true
        anchors.centerIn: parent
        anchors.fill: parent
    }
    property var currentStage: 0
    property list<Component> templateStages: [
        Component {
            id: serverDetailsInput
            ServerDetailsInput {}
        },
        Component {
            id: numberInput
            NumberInput {}
        },
        Component {
            id: codeInput
            CodeInput {}
        }
    ]

    property var stages: []

    Popup {
        id: apiErrorDialog
        modal: true
        anchors.centerIn: parent
        width: 250
        height: 100
//        title: qsTr("Connection Error")
        contentItem: Label { verticalAlignment: Text.AlignVCenter; horizontalAlignment: Text.AlignHCenter }
    }
    property var number: ""

    Component.onCompleted: {
        if (!Settings.isUrlSet())
            stages.push(serverDetailsInput)
        else Api.setUrl(Settings.url)
        if (Settings.codeExpired())
            stages.push(numberInput)
        stages.push(codeInput)
        currentStage = 0
        stagesStack.push(stages[0])
    }

    Connections {
        id: connections
        target: stagesStack.currentItem
        function onSetSpin(t) {
            busyIndicator.enabled = t
        }
        function onStageComplete() {
            if (++currentStage === stages.length)
                Restarter.restart()
            else stagesStack.push(stages[currentStage])
        }
        function onOpenErrorDialog(content) {
            console.error("Opening dialog")
//            apiErrorDialog.title = !!header || "Api error"
            apiErrorDialog.contentItem.label = content
//            apiErrorDialog.footer = !!header || ""
            apiErrorDialog.visible = true;
        }
        function onSetNumber(numberIn) {
            number = numberIn
        }
        function onEnableRegister() {
            stages.push(registerInput)
        }
    }
}

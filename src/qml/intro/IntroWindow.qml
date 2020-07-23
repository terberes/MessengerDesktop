import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 2.15
import Api 1.0
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
        initialItem: stages[currentStage]
    }
    property var currentStage: 0
    property list<Component> stages: [
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
    Component {
        id: registerInput

    }

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
        function onOpenErrorDialog(content, header, footer) {
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

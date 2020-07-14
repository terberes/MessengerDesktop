import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    
    Rectangle {
	    id: root
	    width: Constants.width
	    height: Constants.height
	    color: Constants.backgroundColor
	    anchors.fill: parent
        SidePanel {
            id: sidePanel
            x: 0
            y: 0
            width: parent.width / 3
            height: parent.height
	    }
	    Chat {
            id: chat
            x: sidePanel.width
            y: 0
            width: (parent.width / 3) * 2
            height: parent.height
	    }
	}
}

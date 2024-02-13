import QtQuick
import QtQuick.Controls
import QtQuick.VirtualKeyboard

Rectangle {
    id: control
    property string placeholderText
    property string placeholderTextColor:"#aaa"

    property alias text: _idEdt.text
    property alias _idEdt: _idEdt
    property alias _idAnimation: _idAnimation
    property alias enterKeyAction: _idEdt.enterKeyAction

    border.color: "#8888ff"
    radius: 0
    border.width: 1
    clip: true

    Rectangle {
        id: opacityBox
        anchors.fill: parent
        color: "orange"
        radius: 5
        opacity: 0.0
        visible: false
        OpacityAnimator {
            id: _idAnimation
            target: opacityBox;
            from: 0;
            to: 0.5;
            duration: 150
            loops: 2
            onStopped: { opacityBox.visible = false; opacityBox.opacity = 0.0 }
            onStarted: { opacityBox.visible = true }
        }
    }

    TextInput {
        id: _idEdt
        anchors.fill: parent
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
        font.pointSize: 12
        leftPadding: 10
        rightPadding: 10
        clip: true
        selectByMouse: true
        maximumLength: 128

        property int enterKeyAction: EnterKeyAction.None
        readonly property bool enterKeyEnabled: enterKeyAction === EnterKeyAction.None || text.length > 0 || inputMethodComposing

        EnterKeyAction.actionId: _idEdt.enterKeyAction
        EnterKeyAction.enabled: _idEdt.enterKeyEnabled

        Text {
            leftPadding: 10
            rightPadding: 10
            anchors.fill: parent
            clip: true
            text: control.placeholderText
            font.pointSize: 12
            color: "#8D8D8D"
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            visible: !_idEdt.text
        }
    }
}

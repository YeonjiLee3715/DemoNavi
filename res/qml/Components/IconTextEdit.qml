import QtQuick
import QtQuick.Controls 2.15
import QtQuick.Layouts

Rectangle {
    id: control
    property string iconSrc
    property string placeholderText
    property string placeholderTextColor:"#aaa"

    property alias text: _idEdt.text
    property alias _idEdt: _idEdt
    property alias _idIcon: _idIcon
    property alias _idAnimation: _idAnimation
    property real spacing: 5

    border.color: "#8D8D8D"
    radius: 5
    border.width: 1
    clip: true


    Rectangle {
        id: opacityBox
        width: control.width
        height: control.height
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

    RowLayout {
        x: 5
        width: control.width
        height: control.height
        Layout.fillHeight: true
        Layout.fillWidth: true
        spacing: control.spacing

        Image {
            id: _idIcon
            clip: true
            Layout.minimumWidth: 30
            Layout.maximumWidth: 30
            Layout.minimumHeight: 30
            Layout.maximumHeight: 30
            visible: true
            source: iconSrc
        }

        Item{
            id: _idHSpacer2
            Layout.minimumWidth: 1
            Layout.maximumWidth: 1
        }

        TextInput {
            id: _idEdt
            rightPadding: 10
            Layout.fillHeight: true
            Layout.fillWidth: true
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            font.pointSize: 12
            clip: true
            maximumLength: 128

            Text {
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
}

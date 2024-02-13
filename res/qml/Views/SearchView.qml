import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.VirtualKeyboard
import QtQuick.VirtualKeyboard.Settings

import com.custom.basecomponents
import Components
import CustomControlEnum 1.0

BaseView {
    id: _idVwSearch
    objectId: CustomControlEnum.ID_VW_SEARCH
    objectName: '_idVwSearch'

    readonly property string viewTitle: ''

    visible: true

    RowLayout{
        Layout.fillWidth: true
        height: 50
        spacing: 0

        CustomTextEdit{
            id: _idEdtSearch
            objectName: '_idEdtSearch'
            placeholderText: '어디로 갈까요?'
            width: _idVwSearch.width - _idBtnSearch.width
            Layout.fillWidth: true
            Layout.fillHeight: true
            enterKeyAction: EnterKeyAction.Search

            Keys.onReleased: {
                    if (event.key === Qt.Key_Return) {
                        _idBtnSearch.focus = true
                        //todo: search action
                    }
                }
        }

        FlatButton {
            id: _idBtnSearch
            objectName: '_idBtnSearch'
            objectId: CustomControlEnum.ID_BTN_SEARCH

            bConnectEvent: true
            bConnectClickedEvent: true

            width: 50
            Layout.fillHeight: true
            icon.source: "qrc:/Main/res/img/search.png"
            display: AbstractButton.IconOnly

            bgNormalColor: "#8888ff"
            bgHoverColor: "#5555ff"
            bgFocusColor: "#8888ff"
            bgPressedColor: "#2222ff"
            opacity: 0.5

            onClicked: {
                //todo: search action
            }
        }

    }

    /*  Handwriting input panel for full screen handwriting input.

        This component is an optional add-on for the InputPanel component, that
        is, its use does not affect the operation of the InputPanel component,
        but it also can not be used as a standalone component.

        The handwriting input panel is positioned to cover the entire area of
        application. The panel itself is transparent, but once it is active the
        user can draw handwriting on it.
    */
    HandwritingInputPanel {
        z: 79
        id: handwritingInputPanel
        anchors.fill: parent
        inputPanel: inputPanel
        Rectangle {
            z: -1
            anchors.fill: parent
            color: "black"
            opacity: 0.10
        }
    }

    /*  Keyboard input panel.

        The keyboard is anchored to the bottom of the application.
    */
    InputPanel {
        id: inputPanel
        z: 89
        y: yPositionWhenHidden
        x: 0
        width: parent.width

        property real yPositionWhenHidden: parent.height

        states: State {
            name: "visible"
            /*  The visibility of the InputPanel can be bound to the Qt.inputMethod.visible property,
                but then the handwriting input panel and the keyboard input panel can be visible
                at the same time. Here the visibility is bound to InputPanel.active property instead,
                which allows the handwriting panel to control the visibility when necessary.
            */
            when: inputPanel.active
            PropertyChanges {
                target: inputPanel
                y: inputPanel.yPositionWhenHidden - inputPanel.height
            }
        }
        transitions: Transition {
            id: inputPanelTransition
            from: ""
            to: "visible"
            reversible: true
            enabled: !VirtualKeyboardSettings.fullScreenMode
            ParallelAnimation {
                NumberAnimation {
                    properties: "y"
                    duration: 250
                    easing.type: Easing.InOutQuad
                }
            }
        }
        Binding {
            target: InputContext
            property: "animating"
            value: inputPanelTransition.running
            restoreMode: Binding.RestoreBinding

        }
    }
}

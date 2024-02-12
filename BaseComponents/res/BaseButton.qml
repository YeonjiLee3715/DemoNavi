import QtQuick
import QtQuick.Controls
import com.custom.basecomponents

Button {
    id: control

    property int objectType: ControlEnum.OBJECT_BUTTON_CONTROL
    property int objectId: 0
    property int controlType: ControlEnum.CONTROL_BUTTON
    property bool bConnectEvent: false

    property bool bConnectClickedEvent: false
    property bool bConnectDoubleClickedEvent: false
    property bool bConnectPressAndHoldEvent: false
    property bool bConnectPressedEvent: false
    property bool bConnectReleasedEvent: false
    property bool bConnectCanceledEvent: false
    property bool bConnectToggledEvent: false
    property bool bConnectHoveredEvent: false
    property bool bConnectFocusedEvent: false
    property bool bConnectFocusOutEvent: false
    property bool bConnectEnabledEvent: false
    property bool bConnectDisabledEvent: false

    signal controlClickedEvent()
    signal controlDoubleClickedEvent()
    signal controlPressAndHoldEvent()
    signal controlPressedEvent()
    signal controlReleasedEvent()
    signal controlCanceledEvent()
    signal controlToggledEvent()
    signal controlHoveredEvent(bool bHovered)
    signal controlFocusedEvent()
    signal controlFocusOutEvent()
    signal controlEnabledEvent()
    signal controlDisabledEvent()

    onClicked: {
        if(bConnectClickedEvent)
            controlClickedEvent()
    }

    onDoubleClicked: {
        if(bConnectDoubleClickedEvent)
            controlDoubleClickedEvent()
    }

    onPressAndHold: {
        if(bConnectPressAndHoldEvent)
            controlPressAndHoldEvent()
    }

    onPressed: {
        if(bConnectPressedEvent)
            controlPressedEvent()
    }

    onReleased: {
        if(bConnectReleasedEvent)
            controlReleasedEvent()
    }

    onCanceled: {
        if(bConnectCanceledEvent)
            controlCanceledEvent()
    }

    onToggled: {
        if(bConnectToggledEvent)
            controlToggledEvent()
    }

    onHoveredChanged: {
        if(bConnectHoveredEvent)
            controlHoveredEvent(hovered)
    }

    onActiveFocusChanged: {
        if( activeFocus )
        {
            if(bConnectFocusedEvent)
                controlFocusedEvent()
        }
        else
        {
            if(bConnectFocusOutEvent)
                controlFocusOutEvent()
        }
    }

    onEnabledChanged: {
        if(enabled)
        {
            if(bConnectEnabledEvent)
                controlEnabledEvent()
        }
        else
        {
            if(bConnectDisabledEvent)
                controlDisabledEvent()
        }
    }
}

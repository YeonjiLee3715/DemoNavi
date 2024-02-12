import QtQuick
import QtQuick.Controls
import com.custom.basecomponents

ComboBox {
    id: control

    property int objectType: ControlEnum.OBJECT_COMBOBOX_CONTROL
    property int objectId: 0
    property bool bConnectEvent: false

    property bool bConnectPressedEvent: false
    property bool bConnectHoveredEvent: false
    property bool bConnectFocusedEvent: false
    property bool bConnectFocusOutEvent: false
    property bool bConnectEnabledEvent: false
    property bool bConnectDisabledEvent: false
    property bool bConnectOpenEvent: false
    property bool bConnectClosedEvent: false
    property bool bConnectSelectedEvent: false
    property bool bConnectAcceptedEvent: false

    signal controlPressedEvent(bool bPressed)
    signal controlHoveredEvent(bool bHovered)
    signal controlFocusedEvent()
    signal controlFocusOutEvent()
    signal controlEnabledEvent()
    signal controlDisabledEvent()
    signal controlOpenEvent()
    signal controlClosedEvent()
    signal controlSelectedEvent(int idx)
    signal controlAcceptedEvent()

    onPressedChanged: {
        if(bConnectPressedEvent)
            controlPressedEvent(pressed)
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

    popup.onOpened: {
        if(bConnectOpenEvent)
            controlOpenEvent()
    }

    popup.onClosed: {
        if(bConnectClosedEvent)
            controlClosedEvent()
    }

    onActivated: {
        if(bConnectSelectedEvent)
            controlSelectedEvent(index)
    }

    onAccepted: {
        if(bConnectAcceptedEvent)
            controlAcceptedEvent()
    }
}

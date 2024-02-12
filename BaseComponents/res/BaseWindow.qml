import QtQuick
import com.custom.basecomponents

Window{
    property int objectType: ControlEnum.OBJECT_WINDOW
    property int objectId: 0
    property int windowType: ControlEnum.WINDOW_NONE
    property bool bConnectEvent: false

    property bool bConnectShowEvent: false
    property bool bConnectHideEvent: false
    property bool bConnectOpenEvent: false
    property bool bConnectClosedEvent: false
    property bool bConnectActiveEvent: false
    property bool bConnectInactiveEvent: false

    signal windowShowEvent()
    signal windowHideEvent()
    signal windowOpenEvent()
    signal windowClosedEvent()
    signal windowActiveEvent()
    signal windowInactiveEvent()

    onVisibleChanged: {
        if( visible )
        {
            if(bConnectShowEvent)
                windowShowEvent()
        }
        else
        {
            if(bConnectHideEvent)
                windowHideEvent()
        }
    }

    Component.onCompleted: {
        if(bConnectOpenEvent)
            windowOpenEvent()
    }

    Component.onDestruction: {
        if(bConnectClosedEvent)
            windowClosedEvent()
    }

    onActiveChanged: {
        if( active )
        {
            if(bConnectActiveEvent)
                windowActiveEvent()
        }
        else
        {
            if(bConnectInactiveEvent)
                windowInactiveEvent()
        }
    }
}

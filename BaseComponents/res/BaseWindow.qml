import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Window 2.11
import ViewEnum 1.0

Window{
    property int objectType: ViewEnum.OBJECT_WINDOW
    property int objectId: 0
    property int windowType: ViewEnum.WINDOW_NONE
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

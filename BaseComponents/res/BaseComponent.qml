import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Window 2.11
import ViewEnum 1.0

Item{
    required property int objectType
    property int objectId: 0
    property bool bConnectEvent: false

    signal componentDestructionEvent()

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

    Component.onCompleted: {
        if(bConnectOpenEvent)
            windowOpenEvent()
    }

    Component.onDestruction: {
        if( bConnectEvent && property( 'isEventConnected' ) ) {
            controlDestructionEvent()
        }
    }
}

import QtQuick 2.12
import QtQuick.Controls
import ViewEnum 1.0

Page {
    property int objectType: ViewEnum.OBJECT_VIEW
    property int objectId: 0
    property int viewType: 0
    property bool bConnectEvent: false

    property bool bConnectShowEvent: false
    property bool bConnectHideEvent: false
    property bool bConnectOpenEvent: false
    property bool bConnectClosedEvent: false
    property bool bConnectActiveFocusEvent: false
    property bool bConnectInactiveFocusEvent: false

    signal viewShowEvent()
    signal viewHideEvent()
    signal viewOpenEvent()
    signal viewClosedEvent()
    signal viewActiveFocusEvent()
    signal viewInactiveFocusEvent()

    signal controlLoaded( string objName )
    signal controlDestruction( string objName )

    onVisibleChanged: {
        if( visible )
        {
            if(bConnectShowEvent)
                viewShowEvent()
        }
        else
        {
            if(bConnectHideEvent)
                viewHideEvent()
        }
    }

    Component.onCompleted: {
        if(bConnectOpenEvent)
            viewOpenEvent()
    }


    Component.onDestruction: {
        if(bConnectClosedEvent)
            viewClosedEvent()
    }

    onActiveFocusChanged: {
        if( activeFocus )
        {
            if(bConnectActiveFocusEvent)
                viewActiveFocusEvent()
        }
        else
        {
            if(bConnectInactiveFocusEvent)
                viewInactiveFocusEvent()
        }
    }
}

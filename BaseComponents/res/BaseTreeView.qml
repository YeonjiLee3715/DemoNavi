import QtQuick
import QtQuick.Controls
import com.custom.basecomponents

Item {
    id: control
    property int objectType: ControlEnum.OBJECT_TREE_VIEW
    property int objectId: 0
    property bool bConnectEvent: false

    property bool bConnectClickedEvent: false
    property bool bConnectDoubleClickedEvent: false
    property bool bConnectEnteredEvent: false
    property bool bConnectExitedEvent: false
    property bool bConnectPressAndHoldEvent: false
    property bool bConnectPressedEvent: false
    property bool bConnectReleasedEvent: false
    property bool bConnectCanceledEvent: false
    property bool bConnectWheelEvent: false
    property bool bConnectHoveredEvent: false
    property bool bConnectFocusedEvent: false
    property bool bConnectFocusOutEvent: false
    property bool bConnectOpenEvent: false
    property bool bConnectClosedEvent: false
    property bool bConnectDragEvent: false
    property bool bConnectEnabledEvent: false
    property bool bConnectDisabledEvent: false
    property bool bConnectSelectedEvent: false

    signal controlClickedEvent( int row, int col )
    signal controlDoubleClickedEvent( int row, int col )
    signal controlEnteredEvent( int row, int col )
    signal controlExitedEvent( int row, int col )
    signal controlPressAndHoldEvent( int row, int col )
    signal controlPressedEvent( int row, int col )
    signal controlReleasedEvent( int row, int col )
    signal controlCanceledEvent( int row, int col )
    signal controlWheelEvent( int row, int col, int x, int y )
    signal controlHoveredEvent( int row, int col )
    signal controlFocusedEvent( int row, int col )
    signal controlFocusOutEvent( int row, int col )
    signal controlOpenEvent( int row, int col )
    signal controlClosedEvent( int row, int col )
    signal controlDragEvent( int row, int col, int x, int y )
    signal controlEnabledEvent( int row, int col )
    signal controlDisabledEvent( int row, int col )
    signal controlSelectedEvent( int row, int col )

    property alias _idRectTree: _idRectTree
    property alias _idTree: _idTree

    clip: true

    Rectangle{
        id: _idRectTree
        radius: 0
        anchors.fill: parent
        border.width: 0
        border.color: "#ffffff"
        color: "#ffffff"
    }

    onActiveFocusChanged: {
        if(activeFocus)
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

    TreeView {
        id: _idTree
        objectName: "_idTree"
        clip: true
        anchors.fill: parent
        boundsBehavior: Flickable.StopAtBounds
        visible: ( rows > 0 )
        flickableDirection: Flickable.HorizontalAndVerticalFlick

/**
    There is an error where the contentY coordinate becomes strange
    when the content is resized after an overshot in the downward direction.
    A fix for that.
*/
        property real preContentY: 0
        onMovementEnded: {
            preContentY = contentY
        }

        onContentHeightChanged: {
            contentY = preContentY
        }
    }
}

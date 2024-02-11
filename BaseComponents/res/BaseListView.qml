import QtQuick 2.9
import QtQuick.Controls 2.1
import ViewEnum 1.0

Item {
    id: control
    property int objectType: ViewEnum.OBJECT_LIST_VIEW
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

    property alias _idRectList: _idRectList
    property alias _idLst: _idLst
    property Component header: null

    clip: true

    property bool bIsHeader: false

    function resizeChildrenWidth()
    {
        var childrenWidth = control.width

        if( bIsHeader )
        {
            _idLdrFlickable.width = childrenWidth
            _idLdrFlickable.item._idLdrHeader.width = childrenWidth
            _idLdrFlickable.item._idLdrHeader.item.resizeWidth( _idLdrFlickable.width )
            _idLdrFlickable.item.contentWidth = _idLdrFlickable.item._idLdrHeader.item.width
            _idLst.contentWidth = _idLdrFlickable.item.contentWidth
        }
        else
        {
            _idLdrFlickable.width = 0
        }
        _idLst.width = childrenWidth
    }

    function resizeChildrenHeight()
    {
        if( bIsHeader )
        {
            var hdHight = _idLdrFlickable.item._idLdrHeader.item.height
            _idLdrFlickable.item.contentHeight = hdHight
            _idLdrFlickable.item._idLdrHeader.height = hdHight

            if( _idLst.count <= 0 )
            {
                hdHight = control.height
            }
            _idLdrFlickable.height = hdHight

            _idLst.y = _idLdrFlickable.height
            _idLst.height = Math.max( 0, ( control.height - _idLdrFlickable.height ) )
        }
        else
        {
            _idLdrFlickable.height = 0
            _idLst.y = 0
            _idLst.height = control.height
        }
    }

    Rectangle{
        id: _idRectList
        radius: 5
        anchors.fill: parent
        border.width: 1
        border.color: "#808080"
        color: "#00000000"
    }

    Loader{
        id: _idLdrFlickable
        onLoaded: {
            if( sourceComponent === null )
                return
            _idLdrFlickable.item._idLdrHeader.sourceComponent = header
        }
    }

    Component{
        id: _idComFlickable

        Flickable{
            id: _idFlickable
            property alias _idLdrHeader: _idLdrHeader
            width: _idLdrFlickable.width
            height: _idLdrFlickable.height
            boundsBehavior: Flickable.StopAtBounds
            flickableDirection: Flickable.HorizontalFlick
            clip: true

            Loader{
                id: _idLdrHeader
                onLoaded: {
                    if( sourceComponent !== null )
                        bIsHeader = true
                }
            }

            onContentXChanged: {
                if(_idLst.contentX !== _idFlickable.contentX)
                    _idLst.contentX = _idFlickable.contentX
            }
        }
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

    onWidthChanged: {
        resizeChildrenWidth()
    }

    onHeightChanged: {
        resizeChildrenHeight()
    }

    onHeaderChanged: {
        if( header === null )
        {
            _idLdrFlickable.item._idLdrHeader.sourceComponent = null
            _idLdrFlickable.sourceComponent = null
            bIsHeader = false
        }
        else
        {
            if( bIsHeader )
            {
                _idLdrFlickable.item._idLdrHeader.sourceComponent = header
                resizeChildrenWidth()
                resizeChildrenHeight()
            }
            else
                _idLdrFlickable.sourceComponent = _idComFlickable
        }
    }

    onBIsHeaderChanged: {
        resizeChildrenWidth()
        resizeChildrenHeight()
    }

    ListView {
        id: _idLst
        objectName: "_idLst"
        clip: true
        cacheBuffer: 30
        boundsBehavior: Flickable.StopAtBounds
        visible: ( count > 0 )
        onContentXChanged: {
            if( bIsHeader && _idLst.contentX !== _idLdrFlickable.item.contentX)
                _idLdrFlickable.item.contentX = _idLst.contentX
        }
        flickableDirection: Flickable.HorizontalAndVerticalFlick
        onCountChanged: {
            resizeChildrenHeight()
        }
    }
}

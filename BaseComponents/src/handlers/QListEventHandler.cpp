#include "QListEventHandler.h"

#include <QDir>

#include <cmnDef.h>

#include <CLogger.h>
#include <assert.h>

#include "baseComponentsDefs.h"

namespace nsQListEventHandler {
    const char* TAG = "QListEventHandler";
}

using namespace nsQListEventHandler;

QListEventHandler::QListEventHandler( QObject *parent)
    : QBaseEventHandler(parent)
{

}

QListEventHandler::~QListEventHandler()
{
    disconnect( this, nullptr, nullptr, nullptr );
}

void QListEventHandler::connectObjectEvent( QObject * pObj )
{
    if( pObj == nullptr )
    {
        LOGE( TAG, "Object is null" );
        return;
    }

    QVariant vConnectEvent = pObj->property( PROP_B_CONNECT_EVENT );
    if( vConnectEvent.isNull() || vConnectEvent.isValid() == false
        || vConnectEvent.toBool() == false )
        return;

    QVariant vEventConnected = pObj->property( PROP_IS_EVENT_CONNECTED );
    if( vEventConnected.isNull() == false && vEventConnected.isValid()
            && vEventConnected.toBool() )
        return;

    QVariant vObjectType = pObj->property( "objectType" );
    if( vObjectType.isNull() || vObjectType.isValid() == false )
    {
        LOGE( TAG, "Object type is null" );
        return;
    }

    int nObjectType = vObjectType.toInt();
    if( nObjectType != static_cast<int>( ControlEnum::OBJECT_LIST_VIEW ) )
    {
        LOGE( TAG, "This object is not a button control. objectType: %d", nObjectType );
        return;
    }

    QVariant varEventConnectFlag = pObj->property( PROP_B_CONNECT_CLICKED_EVENT );
    if( varEventConnectFlag.isNull() == false && vEventConnected.isValid() && vEventConnected.toBool() )
        connect( pObj, SIGNAL( controlClickedEvent(int, int) ), this, SLOT( HandleControlClickedEvent(int, int) ), Qt::QueuedConnection );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_DOUBLE_CLICKED_EVENT );
    if( varEventConnectFlag.isNull() == false && vEventConnected.isValid() && vEventConnected.toBool() )
        connect( pObj, SIGNAL( controlDoubleClickedEvent(int, int) ), this, SLOT( HandleControlDoubleClickedEvent(int, int) ), Qt::QueuedConnection );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_ENTERED_EVENT );
    if( varEventConnectFlag.isNull() == false && varEventConnectFlag.isValid() && varEventConnectFlag.toBool() )
        connect( pObj, SIGNAL( controlEnteredEvent(int, int) ), this, SLOT( HandleControlEnteredEvent(int, int) ), Qt::QueuedConnection );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_EXITED_EVENT );
    if( varEventConnectFlag.isNull() == false && varEventConnectFlag.isValid() && varEventConnectFlag.toBool() )
        connect( pObj, SIGNAL( controlExitedEvent(int, int) ), this, SLOT( HandleControlExitedEvent(int, int) ), Qt::QueuedConnection );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_PRESS_AND_HOLD_EVENT );
    if( varEventConnectFlag.isNull() == false && vEventConnected.isValid() && vEventConnected.toBool() )
        connect( pObj, SIGNAL( controlPressAndHoldEvent(int, int) ), this, SLOT( HandleControlPressAndHoldEvent(int, int) ), Qt::QueuedConnection );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_PRESSED_EVENT );
    if( varEventConnectFlag.isNull() == false && vEventConnected.isValid() && vEventConnected.toBool() )
        connect( pObj, SIGNAL( controlPressedEvent(int, int) ), this, SLOT( HandleControlPressedEvent(int, int) ), Qt::QueuedConnection );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_RELEASED_EVENT );
    if( varEventConnectFlag.isNull() == false && vEventConnected.isValid() && vEventConnected.toBool() )
        connect( pObj, SIGNAL( controlReleasedEvent(int, int) ), this, SLOT( HandleControlReleasedEvent(int, int) ), Qt::QueuedConnection );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_CANCELED_EVENT );
    if( varEventConnectFlag.isNull() == false && vEventConnected.isValid() && vEventConnected.toBool() )
        connect( pObj, SIGNAL( controlCanceledEvent(int, int) ), this, SLOT( HandleControlCanceledEvent(int, int) ), Qt::QueuedConnection );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_WHEEL_EVENT );
    if( varEventConnectFlag.isNull() == false && vEventConnected.isValid() && vEventConnected.toBool() )
        connect( pObj, SIGNAL( controlWheelEvent(int, int, int, int) ), this, SLOT( HandleControlWheelEvent(int, int, int, int) ), Qt::QueuedConnection );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_HOVERED_EVENT );
    if( varEventConnectFlag.isNull() == false && vEventConnected.isValid() && vEventConnected.toBool() )
        connect( pObj, SIGNAL( controlHoveredEvent(int, int) ), this, SLOT( HandleControlHoveredEvent(int, int) ), Qt::QueuedConnection );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_FOCUSED_EVENT );
    if( varEventConnectFlag.isNull() == false && vEventConnected.isValid() && vEventConnected.toBool() )
        connect( pObj, SIGNAL( controlFocusedEvent(int, int) ), this, SLOT( HandleControlFocusedEvent(int, int) ), Qt::QueuedConnection );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_FOCUS_OUT_EVENT );
    if( varEventConnectFlag.isNull() == false && vEventConnected.isValid() && vEventConnected.toBool() )
        connect( pObj, SIGNAL( controlFocusOutEvent(int, int) ), this, SLOT( HandleControlFocusOutEvent(int, int) ), Qt::QueuedConnection );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_OPEN_EVENT );
    if( varEventConnectFlag.isNull() == false && vEventConnected.isValid() && vEventConnected.toBool() )
        connect( pObj, SIGNAL( controlOpenEvent(int, int) ), this, SLOT( HandleControlOpenEvent(int, int) ), Qt::QueuedConnection );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_CLOSED_EVENT );
    if( varEventConnectFlag.isNull() == false && vEventConnected.isValid() && vEventConnected.toBool() )
        connect( pObj, SIGNAL( controlClosedEvent(int, int) ), this, SLOT( HandleControlClosedEvent(int, int) ), Qt::QueuedConnection );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_DRAG_EVENT );
    if( varEventConnectFlag.isNull() == false && vEventConnected.isValid() && vEventConnected.toBool() )
        connect( pObj, SIGNAL( controlDragEvent( int, int, int, int ) ), this, SLOT( HandleControlDragEvent( int, int, int, int ) ), Qt::QueuedConnection );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_ENABLED_EVENT );
    if( varEventConnectFlag.isNull() == false && vEventConnected.isValid() && vEventConnected.toBool() )
        connect( pObj, SIGNAL( controlEnabledEvent(int, int) ), this, SLOT( HandleControlEnabledEvent(int, int) ), Qt::QueuedConnection );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_DISABLED_EVENT );
    if( varEventConnectFlag.isNull() == false && vEventConnected.isValid() && vEventConnected.toBool() )
        connect( pObj, SIGNAL( controlDisabledEvent(int, int) ), this, SLOT( HandleControlDisabledEvent(int, int) ), Qt::QueuedConnection );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_SELECTED_EVENT );
    if( varEventConnectFlag.isNull() == false && vEventConnected.isValid() && vEventConnected.toBool() )
        connect( pObj, SIGNAL( controlSelectedEvent(int, int) ), this, SLOT( HandleControlSelectedEvent(int, int) ), Qt::QueuedConnection );

    pObj->setProperty( PROP_IS_EVENT_CONNECTED, true );
}

void QListEventHandler::disconnectObjectEvent( QObject * pObj )
{
    if( pObj == nullptr )
    {
        LOGE( TAG, "Object is null" );
        return;
    }

    QVariant vConnectEvent = pObj->property( PROP_B_CONNECT_EVENT );
    if( vConnectEvent.isNull() || vConnectEvent.isValid() == false
        || vConnectEvent.toBool() == false )
        return;

    QVariant vEventConnected = pObj->property( PROP_IS_EVENT_CONNECTED );
    if( vEventConnected.isNull() || vEventConnected.isValid() == false
        || vEventConnected.toBool() == false )
        return;

    QVariant vObjectType = pObj->property( "objectType" );
    if( vObjectType.isNull() || vObjectType.isValid() == false )
    {
        LOGE( TAG, "Object type is null" );
        return;
    }

    int nObjectType = vObjectType.toInt();
    if( nObjectType != static_cast<int>( ControlEnum::OBJECT_LIST_VIEW ) )
    {
        LOGE( TAG, "This object is not a button control. objectType: %d", nObjectType );
        return;
    }

    QVariant varEventConnectFlag = pObj->property( PROP_B_CONNECT_CLICKED_EVENT );
    if( varEventConnectFlag.isNull() == false && varEventConnectFlag.isValid() && varEventConnectFlag.toBool() )
        disconnect( pObj, SIGNAL( controlClickedEvent(int, int) ), this, SLOT( HandleControlClickedEvent(int, int) ) );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_DOUBLE_CLICKED_EVENT );
    if( varEventConnectFlag.isNull() == false && varEventConnectFlag.isValid() && varEventConnectFlag.toBool() )
        disconnect( pObj, SIGNAL( controlDoubleClickedEvent(int, int) ), this, SLOT( HandleControlDoubleClickedEvent(int, int) ) );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_ENTERED_EVENT );
    if( varEventConnectFlag.isNull() == false && varEventConnectFlag.isValid() && varEventConnectFlag.toBool() )
        disconnect( pObj, SIGNAL( controlEnteredEvent(int, int) ), this, SLOT( HandleControlEnteredEvent(int, int) ) );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_EXITED_EVENT );
    if( varEventConnectFlag.isNull() == false && varEventConnectFlag.isValid() && varEventConnectFlag.toBool() )
        disconnect( pObj, SIGNAL( controlExitedEvent(int, int) ), this, SLOT( HandleControlExitedEvent(int, int) ) );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_PRESS_AND_HOLD_EVENT );
    if( varEventConnectFlag.isNull() == false && varEventConnectFlag.isValid() && varEventConnectFlag.toBool() )
        disconnect( pObj, SIGNAL( controlPressAndHoldEvent(int, int) ), this, SLOT( HandleControlPressAndHoldEvent(int, int) ) );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_PRESSED_EVENT );
    if( varEventConnectFlag.isNull() == false && varEventConnectFlag.isValid() && varEventConnectFlag.toBool() )
        disconnect( pObj, SIGNAL( controlPressedEvent(int, int) ), this, SLOT( HandleControlPressedEvent(int, int) ) );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_RELEASED_EVENT );
    if( varEventConnectFlag.isNull() == false && varEventConnectFlag.isValid() && varEventConnectFlag.toBool() )
        disconnect( pObj, SIGNAL( controlReleasedEvent(int, int) ), this, SLOT( HandleControlReleasedEvent(int, int) ) );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_CANCELED_EVENT );
    if( varEventConnectFlag.isNull() == false && varEventConnectFlag.isValid() && varEventConnectFlag.toBool() )
        disconnect( pObj, SIGNAL( controlCanceledEvent(int, int) ), this, SLOT( HandleControlCanceledEvent(int, int) ) );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_WHEEL_EVENT );
    if( varEventConnectFlag.isNull() == false && varEventConnectFlag.isValid() && varEventConnectFlag.toBool() )
        disconnect( pObj, SIGNAL( controlWheelEvent(int, int, int, int) ), this, SLOT( HandleControlWheelEvent(int, int, int, int) ) );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_HOVERED_EVENT );
    if( varEventConnectFlag.isNull() == false && varEventConnectFlag.isValid() && varEventConnectFlag.toBool() )
        disconnect( pObj, SIGNAL( controlHoveredEvent(int, int) ), this, SLOT( HandleControlHoveredEvent(int, int) ) );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_FOCUSED_EVENT );
    if( varEventConnectFlag.isNull() == false && varEventConnectFlag.isValid() && varEventConnectFlag.toBool() )
        disconnect( pObj, SIGNAL( controlFocusedEvent(int, int) ), this, SLOT( HandleControlFocusedEvent(int, int) ) );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_FOCUS_OUT_EVENT );
    if( varEventConnectFlag.isNull() == false && varEventConnectFlag.isValid() && varEventConnectFlag.toBool() )
        disconnect( pObj, SIGNAL( controlFocusOutEvent(int, int) ), this, SLOT( HandleControlFocusOutEvent(int, int) ) );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_OPEN_EVENT );
    if( varEventConnectFlag.isNull() == false && varEventConnectFlag.isValid() && varEventConnectFlag.toBool() )
        disconnect( pObj, SIGNAL( controlOpenEvent(int, int) ), this, SLOT( HandleControlOpenEvent(int, int) ) );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_CLOSED_EVENT );
    if( varEventConnectFlag.isNull() == false && varEventConnectFlag.isValid() && varEventConnectFlag.toBool() )
        disconnect( pObj, SIGNAL( controlClosedEvent(int, int) ), this, SLOT( HandleControlClosedEvent(int, int) ) );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_DRAG_EVENT );
    if( varEventConnectFlag.isNull() == false && varEventConnectFlag.isValid() && varEventConnectFlag.toBool() )
        disconnect( pObj, SIGNAL( controlDragEvent( int, int, int, int ) ), this, SLOT( HandleControlDragEvent( int, int, int, int ) ) );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_ENABLED_EVENT );
    if( varEventConnectFlag.isNull() == false && varEventConnectFlag.isValid() && varEventConnectFlag.toBool() )
        disconnect( pObj, SIGNAL( controlEnabledEvent(int, int) ), this, SLOT( HandleControlEnabledEvent(int, int) ) );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_DISABLED_EVENT );
    if( varEventConnectFlag.isNull() == false && varEventConnectFlag.isValid() && varEventConnectFlag.toBool() )
        disconnect( pObj, SIGNAL( controlDisabledEvent(int, int) ), this, SLOT( HandleControlDisabledEvent(int, int) ) );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_SELECTED_EVENT );
    if( varEventConnectFlag.isNull() == false && varEventConnectFlag.isValid() && varEventConnectFlag.toBool() )
        disconnect( pObj, SIGNAL( controlSelectedEvent(int, int) ), this, SLOT( HandleControlSelectedEvent(int, int) ) );

    pObj->setProperty( PROP_IS_EVENT_CONNECTED, false );
}

void QListEventHandler::HandleControlClickedEvent( int row, int col )
{
    QObject* pObj = sender();

    const QString& strObjName = pObj->objectName();

    LOGD( TAG, "strObjName: %s", strObjName.toStdString().c_str() );
}

void QListEventHandler::HandleControlDoubleClickedEvent( int row, int col )
{
    QObject* pObj = sender();

    const QString& strObjName = pObj->objectName();

    LOGD( TAG, "strObjName: %s", strObjName.toStdString().c_str() );
}

void QListEventHandler::HandleControlEnteredEvent( int row, int col )
{
    QObject* pObj = sender();

    const QString& strObjName = pObj->objectName();

    LOGD( TAG, "strObjName: %s", strObjName.toStdString().c_str() );
}

void QListEventHandler::HandleControlExitedEvent( int row, int col )
{
    QObject* pObj = sender();

    const QString& strObjName = pObj->objectName();

    LOGD( TAG, "strObjName: %s", strObjName.toStdString().c_str() );
}

void QListEventHandler::HandleControlPressAndHoldEvent( int row, int col )
{
    QObject* pObj = sender();

    const QString& strObjName = pObj->objectName();

    LOGD( TAG, "strObjName: %s", strObjName.toStdString().c_str() );
}

void QListEventHandler::HandleControlPressedEvent( int row, int col )
{
    QObject* pObj = sender();

    const QString& strObjName = pObj->objectName();

    LOGD( TAG, "strObjName: %s", strObjName.toStdString().c_str() );
}

void QListEventHandler::HandleControlReleasedEvent( int row, int col )
{
    QObject* pObj = sender();

    const QString& strObjName = pObj->objectName();

    LOGD( TAG, "strObjName: %s", strObjName.toStdString().c_str() );
}

void QListEventHandler::HandleControlCanceledEvent( int row, int col )
{
    QObject* pObj = sender();

    const QString& strObjName = pObj->objectName();

    LOGD( TAG, "strObjName: %s", strObjName.toStdString().c_str() );
}

void QListEventHandler::HandleControlWheelEvent( int row, int col, int x, int y )
{
    QObject* pObj = sender();

    const QString& strObjName = pObj->objectName();

    LOGD( TAG, "strObjName: %s", strObjName.toStdString().c_str() );
}

void QListEventHandler::HandleControlHoveredEvent( int row, int col )
{
    QObject* pObj = sender();

    const QString& strObjName = pObj->objectName();

    LOGD( TAG, "strObjName: %s", strObjName.toStdString().c_str() );
}

void QListEventHandler::HandleControlFocusedEvent( int row, int col )
{
    QObject* pObj = sender();

    const QString& strObjName = pObj->objectName();

    LOGD( TAG, "strObjName: %s", strObjName.toStdString().c_str() );
}

void QListEventHandler::HandleControlFocusOutEvent( int row, int col )
{
    QObject* pObj = sender();

    const QString& strObjName = pObj->objectName();

    LOGD( TAG, "strObjName: %s", strObjName.toStdString().c_str() );
}

void QListEventHandler::HandleControlOpenEvent( int row, int col )
{
    QObject* pObj = sender();

    const QString& strObjName = pObj->objectName();

    LOGD( TAG, "strObjName: %s", strObjName.toStdString().c_str() );
}

void QListEventHandler::HandleControlClosedEvent( int row, int col )
{
    QObject* pObj = sender();

    const QString& strObjName = pObj->objectName();

    LOGD( TAG, "strObjName: %s", strObjName.toStdString().c_str() );
}

void QListEventHandler::HandleControlDragEvent( int row, int col, int x, int y )
{
    QObject* pObj = sender();

    const QString& strObjName = pObj->objectName();

    LOGD( TAG, "strObjName: %s", strObjName.toStdString().c_str() );
}

void QListEventHandler::HandleControlEnabledEvent( int row, int col )
{
    QObject* pObj = sender();

    const QString& strObjName = pObj->objectName();

    LOGD( TAG, "strObjName: %s", strObjName.toStdString().c_str() );
}

void QListEventHandler::HandleControlDisabledEvent( int row, int col )
{
    QObject* pObj = sender();

    const QString& strObjName = pObj->objectName();

    LOGD( TAG, "strObjName: %s", strObjName.toStdString().c_str() );
}

void QListEventHandler::HandleControlSelectedEvent( int row, int col )
{
    QObject* pObj = sender();

    const QString& strObjName = pObj->objectName();

    LOGD( TAG, "strObjName: %s", strObjName.toStdString().c_str() );
}

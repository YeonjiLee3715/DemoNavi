#include "QButtonEventHandler.h"

#include <QVariant>
#include <QVariantMap>

#include <CLogger.h>

#include "viewDefs.h"

namespace nsQButtonEventHandler
{
    const char* TAG = "QButtonEventHandler";
}

using namespace nsQButtonEventHandler;

QButtonEventHandler::QButtonEventHandler(QObject *parent)
    : QBaseEventHandler(parent)
{

}

QButtonEventHandler::~QButtonEventHandler()
{
    disconnect( this, nullptr, nullptr, nullptr );
}

void QButtonEventHandler::connectObjectEvent( QObject * pObj )
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
    if( nObjectType != static_cast<int>( ViewEnum::OBJECT_BUTTON_CONTROL ) )
    {
        LOGE( TAG, "This object is not a button control. objectType: %d", nObjectType );
        return;
    }

    QVariant varEventConnectFlag = pObj->property( PROP_B_CONNECT_CLICKED_EVENT );
    if( varEventConnectFlag.isNull() == false && varEventConnectFlag.isValid() && varEventConnectFlag.toBool() )
        connect( pObj, SIGNAL( controlClickedEvent() ), this, SLOT( HandleControlClickedEvent() ), Qt::QueuedConnection );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_DOUBLE_CLICKED_EVENT );
    if( varEventConnectFlag.isNull() == false && varEventConnectFlag.isValid() && varEventConnectFlag.toBool() )
        connect( pObj, SIGNAL( controlDoubleClickedEvent() ), this, SLOT( HandleControlDoubleClickedEvent() ), Qt::QueuedConnection );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_PRESS_AND_HOLD_EVENT );
    if( varEventConnectFlag.isNull() == false && varEventConnectFlag.isValid() && varEventConnectFlag.toBool() )
        connect( pObj, SIGNAL( controlPressAndHoldEvent() ), this, SLOT( HandleControlPressAndHoldEvent() ), Qt::QueuedConnection );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_PRESSED_EVENT );
    if( varEventConnectFlag.isNull() == false && varEventConnectFlag.isValid() && varEventConnectFlag.toBool() )
        connect( pObj, SIGNAL( controlPressedEvent() ), this, SLOT( HandleControlPressedEvent() ), Qt::QueuedConnection );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_RELEASED_EVENT );
    if( varEventConnectFlag.isNull() == false && varEventConnectFlag.isValid() && varEventConnectFlag.toBool() )
        connect( pObj, SIGNAL( controlReleasedEvent() ), this, SLOT( HandleControlReleasedEvent() ), Qt::QueuedConnection );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_CANCELED_EVENT );
    if( varEventConnectFlag.isNull() == false && varEventConnectFlag.isValid() && varEventConnectFlag.toBool() )
        connect( pObj, SIGNAL( controlCanceledEvent() ), this, SLOT( HandleControlCanceledEvent() ), Qt::QueuedConnection );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_TOGGLED_EVENT );
    if( varEventConnectFlag.isNull() == false && varEventConnectFlag.isValid() && varEventConnectFlag.toBool() )
        connect( pObj, SIGNAL( controlToggledEvent() ), this, SLOT( HandleControlToggledEvent() ), Qt::QueuedConnection );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_HOVERED_EVENT );
    if( varEventConnectFlag.isNull() == false && varEventConnectFlag.isValid() && varEventConnectFlag.toBool() )
        connect( pObj, SIGNAL( controlHoveredEvent(bool) ), this, SLOT( HandleControlHoveredEvent(bool) ), Qt::QueuedConnection );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_FOCUSED_EVENT );
    if( varEventConnectFlag.isNull() == false && varEventConnectFlag.isValid() && varEventConnectFlag.toBool() )
        connect( pObj, SIGNAL( controlFocusedEvent() ), this, SLOT( HandleControlFocusedEvent() ), Qt::QueuedConnection );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_FOCUS_OUT_EVENT );
    if( varEventConnectFlag.isNull() == false && varEventConnectFlag.isValid() && varEventConnectFlag.toBool() )
        connect( pObj, SIGNAL( controlFocusOutEvent() ), this, SLOT( HandleControlFocusOutEvent() ), Qt::QueuedConnection );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_ENABLED_EVENT );
    if( varEventConnectFlag.isNull() == false && varEventConnectFlag.isValid() && varEventConnectFlag.toBool() )
        connect( pObj, SIGNAL( controlEnabledEvent() ), this, SLOT( HandleControlEnabledEvent() ), Qt::QueuedConnection );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_DISABLED_EVENT );
    if( varEventConnectFlag.isNull() == false && varEventConnectFlag.isValid() && varEventConnectFlag.toBool() )
        connect( pObj, SIGNAL( controlDisabledEvent() ), this, SLOT( HandleControlDisabledEvent() ), Qt::QueuedConnection );

    pObj->setProperty( PROP_IS_EVENT_CONNECTED, true );
}

void QButtonEventHandler::disconnectObjectEvent( QObject * pObj )
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
    if( nObjectType != static_cast<int>( ViewEnum::OBJECT_BUTTON_CONTROL ) )
    {
        LOGE( TAG, "This object is not a button control. objectType: %d", nObjectType );
        return;
    }

    QVariant varEventConnectFlag = pObj->property( PROP_B_CONNECT_CLICKED_EVENT );
    if( varEventConnectFlag.isNull() == false && varEventConnectFlag.isValid() && varEventConnectFlag.toBool() )
        disconnect( pObj, SIGNAL( controlClickedEvent() ), this, SLOT( HandleControlClickedEvent() ) );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_DOUBLE_CLICKED_EVENT );
    if( varEventConnectFlag.isNull() == false && varEventConnectFlag.isValid() && varEventConnectFlag.toBool() )
        disconnect( pObj, SIGNAL( controlDoubleClickedEvent() ), this, SLOT( HandleControlDoubleClickedEvent() ) );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_PRESS_AND_HOLD_EVENT );
    if( varEventConnectFlag.isNull() == false && varEventConnectFlag.isValid() && varEventConnectFlag.toBool() )
        disconnect( pObj, SIGNAL( controlPressAndHoldEvent() ), this, SLOT( HandleControlPressAndHoldEvent() ) );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_PRESSED_EVENT );
    if( varEventConnectFlag.isNull() == false && varEventConnectFlag.isValid() && varEventConnectFlag.toBool() )
        disconnect( pObj, SIGNAL( controlPressedEvent() ), this, SLOT( HandleControlPressedEvent() ) );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_RELEASED_EVENT );
    if( varEventConnectFlag.isNull() == false && varEventConnectFlag.isValid() && varEventConnectFlag.toBool() )
        disconnect( pObj, SIGNAL( controlReleasedEvent() ), this, SLOT( HandleControlReleasedEvent() ) );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_CANCELED_EVENT );
    if( varEventConnectFlag.isNull() == false && varEventConnectFlag.isValid() && varEventConnectFlag.toBool() )
        disconnect( pObj, SIGNAL( controlCanceledEvent() ), this, SLOT( HandleControlCanceledEvent() ) );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_TOGGLED_EVENT );
    if( varEventConnectFlag.isNull() == false && varEventConnectFlag.isValid() && varEventConnectFlag.toBool() )
        disconnect( pObj, SIGNAL( controlToggledEvent() ), this, SLOT( HandleControlToggledEvent() ) );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_HOVERED_EVENT );
    if( varEventConnectFlag.isNull() == false && varEventConnectFlag.isValid() && varEventConnectFlag.toBool() )
        disconnect( pObj, SIGNAL( controlHoveredEvent(bool) ), this, SLOT( HandleControlHoveredEvent(bool) ) );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_FOCUSED_EVENT );
    if( varEventConnectFlag.isNull() == false && varEventConnectFlag.isValid() && varEventConnectFlag.toBool() )
        disconnect( pObj, SIGNAL( controlFocusedEvent() ), this, SLOT( HandleControlFocusedEvent() ) );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_FOCUS_OUT_EVENT );
    if( varEventConnectFlag.isNull() == false && varEventConnectFlag.isValid() && varEventConnectFlag.toBool() )
        disconnect( pObj, SIGNAL( controlFocusOutEvent() ), this, SLOT( HandleControlFocusOutEvent() ) );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_ENABLED_EVENT );
    if( varEventConnectFlag.isNull() == false && varEventConnectFlag.isValid() && varEventConnectFlag.toBool() )
        disconnect( pObj, SIGNAL( controlEnabledEvent() ), this, SLOT( HandleControlEnabledEvent() ) );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_DISABLED_EVENT );
    if( varEventConnectFlag.isNull() == false && varEventConnectFlag.isValid() && varEventConnectFlag.toBool() )
        disconnect( pObj, SIGNAL( controlDisabledEvent() ), this, SLOT( HandleControlDisabledEvent() ) );

    pObj->setProperty( PROP_IS_EVENT_CONNECTED, false );
}

void QButtonEventHandler::HandleControlClickedEvent()
{
    QObject* pObj = sender();

    const QString& strObjName = pObj->objectName();

    LOGD( TAG, "strObjName: %s", strObjName.toStdString().c_str() );
}

void QButtonEventHandler::HandleControlDoubleClickedEvent()
{
    QObject* pObj = sender();

    const QString& strObjName = pObj->objectName();

    LOGD( TAG, "strObjName: %s", strObjName.toStdString().c_str() );
}

void QButtonEventHandler::HandleControlPressAndHoldEvent()
{
    QObject* pObj = sender();

    const QString& strObjName = pObj->objectName();

    LOGD( TAG, "strObjName: %s", strObjName.toStdString().c_str() );
}

void QButtonEventHandler::HandleControlPressedEvent()
{
    QObject* pObj = sender();

    const QString& strObjName = pObj->objectName();

    LOGD( TAG, "strObjName: %s", strObjName.toStdString().c_str() );
}

void QButtonEventHandler::HandleControlReleasedEvent()
{
    QObject* pObj = sender();

    const QString& strObjName = pObj->objectName();

    LOGD( TAG, "strObjName: %s", strObjName.toStdString().c_str() );

    QVariant vObjectId = pObj->property( "objectId" );
    if( vObjectId.isNull() || vObjectId.isValid() == false )
    {
        LOGE( TAG, "Object id is null" );
        return;
    }
/*
    switch( vObjectId.toInt() )
    {
    case static_cast<int>(ViewEnum::ID_BTN_SOME_BUTTON):
        emit SigDoSomething();
        break;
    default:
        break;
    }
*/
}

void QButtonEventHandler::HandleControlCanceledEvent()
{
    QObject* pObj = sender();

    const QString& strObjName = pObj->objectName();

    LOGD( TAG, "strObjName: %s", strObjName.toStdString().c_str() );
}

void QButtonEventHandler::HandleControlToggledEvent()
{
    QObject* pObj = sender();

    const QString& strObjName = pObj->objectName();

    LOGD( TAG, "strObjName: %s", strObjName.toStdString().c_str() );
}

void QButtonEventHandler::HandleControlHoveredEvent(bool bHovered)
{
    QObject* pObj = sender();

    const QString& strObjName = pObj->objectName();

    LOGD( TAG, "strObjName: %s", strObjName.toStdString().c_str() );
}

void QButtonEventHandler::HandleControlFocusedEvent()
{
    QObject* pObj = sender();

    const QString& strObjName = pObj->objectName();

    LOGD( TAG, "strObjName: %s", strObjName.toStdString().c_str() );
}

void QButtonEventHandler::HandleControlFocusOutEvent()
{
    QObject* pObj = sender();

    const QString& strObjName = pObj->objectName();

    LOGD( TAG, "strObjName: %s", strObjName.toStdString().c_str() );
}

void QButtonEventHandler::HandleControlEnabledEvent()
{
    QObject* pObj = sender();

    const QString& strObjName = pObj->objectName();

    LOGD( TAG, "strObjName: %s", strObjName.toStdString().c_str() );
}

void QButtonEventHandler::HandleControlDisabledEvent()
{
    QObject* pObj = sender();

    const QString& strObjName = pObj->objectName();

    LOGD( TAG, "strObjName: %s", strObjName.toStdString().c_str() );
}

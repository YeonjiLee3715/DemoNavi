#include "QWindowEventHandler.h"

#include <QDir>

#include <cmnDef.h>

#include <CLogger.h>
#include <assert.h>

#include "viewDefs.h"

namespace nsQWindowEventHandler {
    const char* TAG = "QWindowEventHandler";
}

using namespace nsQWindowEventHandler;

QWindowEventHandler::QWindowEventHandler( QObject *parent)
    : QBaseEventHandler(parent)
{

}

QWindowEventHandler::~QWindowEventHandler()
{
    disconnect( this, nullptr, nullptr, nullptr );
}

void QWindowEventHandler::connectObjectEvent( QObject * pObj )
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
    if( nObjectType != static_cast<int>( ViewEnum::OBJECT_WINDOW ) )
    {
        LOGE( TAG, "This object is not a button control. objectType: %d", nObjectType );
        return;
    }

    QVariant varEventConnectFlag = pObj->property( PROP_B_CONNECT_SHOW_EVENT );
    if( varEventConnectFlag.isNull() == false && varEventConnectFlag.isValid() && varEventConnectFlag.toBool() )
        connect( pObj, SIGNAL( windowShowEvent() ), this, SLOT( HandleWindowShowEvent() ), Qt::QueuedConnection );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_HIDE_EVENT );
    if( varEventConnectFlag.isNull() == false && varEventConnectFlag.isValid() && varEventConnectFlag.toBool() )
        connect( pObj, SIGNAL( windowHideEvent() ), this, SLOT( HandleWindowHideEvent() ), Qt::QueuedConnection );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_OPEN_EVENT );
    if( varEventConnectFlag.isNull() == false && varEventConnectFlag.isValid() && varEventConnectFlag.toBool() )
        connect( pObj, SIGNAL( windowOpenEvent() ), this, SLOT( HandleWindowOpenEvent() ), Qt::QueuedConnection );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_CLOSED_EVENT );
    if( varEventConnectFlag.isNull() == false && varEventConnectFlag.isValid() && varEventConnectFlag.toBool() )
        connect( pObj, SIGNAL( windowClosedEvent() ), this, SLOT( HandleWindowClosedEvent() ), Qt::QueuedConnection );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_ACTIVE_EVENT );
    if( varEventConnectFlag.isNull() == false && varEventConnectFlag.isValid() && varEventConnectFlag.toBool() )
        connect( pObj, SIGNAL( windowActiveEvent() ), this, SLOT( HandleWindowActiveEvent() ), Qt::QueuedConnection );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_INACTIVE_EVENT );
    if( varEventConnectFlag.isNull() == false && varEventConnectFlag.isValid() && varEventConnectFlag.toBool() )
        connect( pObj, SIGNAL( windowInactiveEvent() ), this, SLOT( HandleWindowInactiveEvent() ), Qt::QueuedConnection );

    pObj->setProperty( PROP_IS_EVENT_CONNECTED, true );
}

void QWindowEventHandler::disconnectObjectEvent( QObject * pObj )
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
    if( nObjectType != static_cast<int>( ViewEnum::OBJECT_WINDOW ) )
    {
        LOGE( TAG, "This object is not a button control. objectType: %d", nObjectType );
        return;
    }

    QVariant varEventConnectFlag = pObj->property( PROP_B_CONNECT_SHOW_EVENT );
    if( varEventConnectFlag.isNull() == false && varEventConnectFlag.isValid() && varEventConnectFlag.toBool() )
        disconnect( pObj, SIGNAL( windowShowEvent() ), this, SLOT( HandleWindowShowEvent() ) );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_HIDE_EVENT );
    if( varEventConnectFlag.isNull() == false && varEventConnectFlag.isValid() && varEventConnectFlag.toBool() )
        disconnect( pObj, SIGNAL( windowHideEvent() ), this, SLOT( HandleWindowHideEvent() ) );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_OPEN_EVENT );
    if( varEventConnectFlag.isNull() == false && varEventConnectFlag.isValid() && varEventConnectFlag.toBool() )
        disconnect( pObj, SIGNAL( windowOpenEvent() ), this, SLOT( HandleWindowOpenEvent() ) );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_CLOSED_EVENT );
    if( varEventConnectFlag.isNull() == false && varEventConnectFlag.isValid() && varEventConnectFlag.toBool() )
        disconnect( pObj, SIGNAL( windowClosedEvent() ), this, SLOT( HandleWindowClosedEvent() ) );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_ACTIVE_EVENT );
    if( varEventConnectFlag.isNull() == false && varEventConnectFlag.isValid() && varEventConnectFlag.toBool() )
        disconnect( pObj, SIGNAL( windowActiveEvent() ), this, SLOT( HandleWindowActiveEvent() ) );

    varEventConnectFlag = pObj->property( PROP_B_CONNECT_INACTIVE_EVENT );
    if( varEventConnectFlag.isNull() == false && varEventConnectFlag.isValid() && varEventConnectFlag.toBool() )
        disconnect( pObj, SIGNAL( windowInactiveEvent() ), this, SLOT( HandleWindowInactiveEvent() ) );

    pObj->setProperty( PROP_IS_EVENT_CONNECTED, false );
}

void QWindowEventHandler::HandleWindowShowEvent()
{
    QObject* pObj = sender();

    const QString& strObjName = pObj->objectName();

    LOGD( TAG, "strObjName: %s", strObjName.toStdString().c_str() );
}

void QWindowEventHandler::HandleWindowHideEvent()
{
    QObject* pObj = sender();

    const QString& strObjName = pObj->objectName();

    LOGD( TAG, "strObjName: %s", strObjName.toStdString().c_str() );
}

void QWindowEventHandler::HandleWindowOpenEvent()
{
    QObject* pObj = sender();

    const QString& strObjName = pObj->objectName();

    LOGD( TAG, "strObjName: %s", strObjName.toStdString().c_str() );
}

void QWindowEventHandler::HandleWindowClosedEvent()
{
    QObject* pObj = sender();

    const QString& strObjName = pObj->objectName();

    LOGD( TAG, "strObjName: %s", strObjName.toStdString().c_str() );
}

void QWindowEventHandler::HandleWindowActiveEvent()
{
    QObject* pObj = sender();

    const QString& strObjName = pObj->objectName();

    LOGD( TAG, "strObjName: %s", strObjName.toStdString().c_str() );
}

void QWindowEventHandler::HandleWindowInactiveEvent()
{
    QObject* pObj = sender();

    const QString& strObjName = pObj->objectName();

    LOGD( TAG, "strObjName: %s", strObjName.toStdString().c_str() );
}

#include "QBaseView.h"

#include <baseComponentsDefs.h>
#include <QViewEventHandler.h>

#include <CLogger.h>

namespace nsQBaseView{
    const char* TAG = "QBaseView";
}

using namespace nsQBaseView;

QBaseView::QBaseView( QObject* objView, QObject* parent )
    : QObject(parent), m_pObjView(objView), m_isSet(false)
{

}

QBaseView::~QBaseView()
{
    SetControlEventDisconnections();

    destroyControlEventHandlers();

    m_isSet = false;
}

void QBaseView::SetControlEventConnections()
{
    QObject* pObjRoot = m_pObjView;
    assert( pObjRoot != nullptr );

    QVariant vEventConnected = pObjRoot->property( PROP_IS_EVENT_CONNECTED );
    if( vEventConnected.isNull() || vEventConnected.isValid() == false
            || vEventConnected.toBool() == false )
    {
        connect( pObjRoot, SIGNAL( controlLoaded(QString) ), this, SLOT( HandleControlLoadedEvent(QString) ), Qt::DirectConnection );
        connect( pObjRoot, SIGNAL( controlDestruction(QString) ), this, SLOT( HandleControlDestructionEvent(QString) ), Qt::DirectConnection );
        pObjRoot->setProperty( PROP_IS_EVENT_CONNECTED, true );
    }

    SetControlEventConnection( pObjRoot, true );
}

void QBaseView::SetControlEventConnection(QObject *pObj, bool bRecursive)
{
    if( pObj == nullptr )
    {
        LOGE( TAG, "Object is null" );
        return;
    }

    if( bRecursive )
        setControlEventConnectionRecursive( pObj );
    else
        connectObjectEvent( pObj );
}

void QBaseView::connectObjectEvent(QObject *pObj)
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

    QVariant vObjectType = pObj->property( "objectType" );
    if( vObjectType.isNull() || vObjectType.isValid() == false )
    {
        LOGE( TAG, "Object type is null" );
        return;
    }

    QBaseEventHandler* pHandler = GetEventHandler(vObjectType.toInt());
    if( pHandler != nullptr ){
        pHandler->connectObjectEvent( pObj );
    }
    else {
        LOGE( TAG, "Unknown objectType: %d", vObjectType.toInt() );
    }
}

void QBaseView::SetControlEventDisconnections()
{
    QObject* pObjRoot = m_pObjView;
    if( pObjRoot != nullptr )
    {
        QVariant vEventConnected = pObjRoot->property( PROP_IS_EVENT_CONNECTED );
        if( ( vEventConnected.isNull() == false && vEventConnected.isValid() )
                || vEventConnected.toBool() )
        {
            disconnect( pObjRoot, SIGNAL( controlLoaded(QString) ), this, SLOT( HandleControlLoadedEvent(QString) ) );
            disconnect( pObjRoot, SIGNAL( controlDestruction(QString) ), this, SLOT( HandleControlDestructionEvent(QString) ) );
            pObjRoot->setProperty( PROP_IS_EVENT_CONNECTED, false );
        }

        SetControlEventDisconnection( pObjRoot, true );
    }
}

void QBaseView::SetControlEventDisconnection(QObject *pObj, bool bRecursive)
{
    if( pObj == nullptr )
    {
        LOGE( TAG, "Object is null" );
        return;
    }

    if( bRecursive )
        setControlEventDisconnectionRecursive( pObj );
    else
        disconnectObjectEvent( pObj );
}

void QBaseView::disconnectObjectEvent(QObject *pObj)
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

    QVariant vObjectType = pObj->property( "objectType" );
    if( vObjectType.isNull() || vObjectType.isValid() == false )
    {
        LOGE( TAG, "Object type is null" );
        return;
    }

    QBaseEventHandler* pHandler = GetEventHandler(vObjectType.toInt());
    if( pHandler != nullptr ){
        pHandler->disconnectObjectEvent( pObj );
    }
    else {
        LOGE( TAG, "Unknown objectType: %d", vObjectType.toInt() );
    }
}

QObject* QBaseView::GetViewObject()
{
    return m_pObjView;
}

QObject* QBaseView::FindChildObject(const QString& objectName, QObject* pParent)
{
    if( objectName.isEmpty() )
        return nullptr;

    if( pParent == nullptr )
        pParent = m_pObjView;

    if( pParent == nullptr )
        return nullptr;

    if( objectName.compare( pParent->objectName() ) == 0 )
        return pParent;

    return pParent->findChild<QObject*>( objectName );
}

QBaseEventHandler* QBaseView::GetEventHandler(int objectType)
{
    QHash<int, QBaseEventHandler*>::iterator it = m_mapCtrHandlers.find(objectType);
    if( it != m_mapCtrHandlers.end() ){
        return it.value();
    }

    return nullptr;
}

void QBaseView::destroyControlEventHandlers()
{
    QHash<int, QBaseEventHandler*>::iterator it = m_mapCtrHandlers.begin();
    while(it != m_mapCtrHandlers.end()){
        if( (*it) != nullptr ) {
            (*it)->deleteLater();
            (*it) = nullptr;
        }
        it = m_mapCtrHandlers.erase(it);
    }
}

void QBaseView::setControlEventConnectionRecursive(QObject *pObj)
{
    if( pObj == nullptr )
    {
        LOGE( TAG, "Object is null" );
        return;
    }

    connectObjectEvent( pObj );

    QList<QObject *> lstObjChild = pObj->findChildren<QObject*>( QString(), Qt::FindDirectChildrenOnly );
    if( lstObjChild.isEmpty() )
        return;

    for( QObject* pObjChild : lstObjChild )
    {
        if( pObjChild == nullptr )
            continue;

        setControlEventConnectionRecursive( pObjChild );
    }
}

void QBaseView::setControlEventDisconnectionRecursive(QObject *pObj)
{
    if( pObj == nullptr )
    {
        LOGE( TAG, "Object is null" );
        return;
    }

    disconnectObjectEvent( pObj );

    QList<QObject *> lstObjChild = pObj->findChildren<QObject*>( QString(), Qt::FindDirectChildrenOnly );
    if( lstObjChild.isEmpty() )
        return;

    for( QObject* pObjChild : lstObjChild )
    {
        if( pObjChild == nullptr )
            continue;

        setControlEventDisconnectionRecursive( pObjChild );
    }
}

void QBaseView::Init()
{
    RegistControlEventHandlers();

    QHash<int, QBaseEventHandler*>::iterator it = m_mapCtrHandlers.find((int)ControlEnum::OBJECT_VIEW);
    if( it == m_mapCtrHandlers.end() ){
        m_mapCtrHandlers.insert( (int)ControlEnum::OBJECT_VIEW, reinterpret_cast<QBaseEventHandler*>(new QViewEventHandler()));
    }

    SetControlEventConnections();

    m_isSet = true;
}

bool QBaseView::IsSet() const
{
    return m_isSet;
}

void QBaseView::HandleControlLoadedEvent(QString objName)
{
    LOGD( TAG, "test object: %s", objName.toStdString().c_str() );
    QObject* pNewObj = FindChildObject( objName );
    if( pNewObj == nullptr )
    {
        LOGE( TAG, "Failed to get object: %s", objName.toStdString().c_str() );
        return;
    }

    SetControlEventConnection( pNewObj, true );
}

void QBaseView::HandleControlDestructionEvent(QString objName)
{
    LOGD( TAG, "test object: %s", objName.toStdString().c_str() );
    QObject* pNewObj = FindChildObject( objName );
    if( pNewObj == nullptr )
    {
        LOGE( TAG, "Failed to get object: %s", objName.toStdString().c_str() );
        return;
    }

    SetControlEventDisconnection( pNewObj, true );
}

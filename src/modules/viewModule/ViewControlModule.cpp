#include "ViewControlModule.h"

#include <QModuleManager.h>
#include <viewDefs.h>

#include <NaviHomeView.h>

#include <CLogger.h>

namespace nsViewControlModule{
    const char* TAG = "ViewControlModule";
}

using namespace nsViewControlModule;

ViewControlModule::ViewControlModule( QObject *parent )
    : QBaseModule(parent), m_pEngine(nullptr), m_pHWindowEvent(nullptr)
{
    setIndependentModule( false );
    setInitMethod( INIT_MODULE_MANAGER );
}

ViewControlModule::~ViewControlModule()
{
    SetWindowEventDisconnections();

    if( m_pHWindowEvent != nullptr ){
        m_pHWindowEvent->deleteLater();
        m_pEngine = nullptr;
    }

    QHash<int, QBaseView*>::iterator it = m_mapViews.begin();
    while( it != m_mapViews.end() ){
        if( (*it) != nullptr ){
            (*it)->deleteLater();
            (*it) = nullptr;
        }
        it = m_mapViews.erase(it);
    }

    if( m_pEngine != nullptr )
    {
        m_pEngine->exit( 0 );
        m_pEngine->deleteLater();
        m_pEngine = nullptr;
    }
}

void ViewControlModule::SetWindowEventConnections()
{
    QObject* pObjRoot = GetRootWindowObject();
    assert( pObjRoot != nullptr );

    QVariant vEventConnected = pObjRoot->property( PROP_IS_EVENT_CONNECTED );
    if( vEventConnected.isNull() || vEventConnected.isValid() == false
            || vEventConnected.toBool() == false )
    {
        connect( pObjRoot, SIGNAL( viewLoaded(QString) ), this, SLOT( HandleViewLoadedEvent(QString) ), Qt::DirectConnection );
        connect( pObjRoot, SIGNAL( viewDestruction(QString) ), this, SLOT( HandleViewDestructionEvent(QString) ), Qt::DirectConnection );
        pObjRoot->setProperty( PROP_IS_EVENT_CONNECTED, true );
    }

    SetWindowEventConnection( pObjRoot, false );
}

void ViewControlModule::SetWindowEventConnection(QObject *pObj, bool bRecursive)
{
    if( pObj == nullptr )
    {
        LOGE( TAG, "Object is null" );
        return;
    }

    if( bRecursive )
        setWindowEventConnectionRecursive( pObj );
    else
        connectObjectEvent( pObj );
}

void ViewControlModule::connectObjectEvent(QObject *pObj)
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

    if( vObjectType.toInt() == ControlEnum::OBJECT_WINDOW )
        m_pHWindowEvent->connectObjectEvent( pObj );
}

void ViewControlModule::SetWindowEventDisconnections()
{
    QObject* pObjRoot = GetRootWindowObject();
    if( pObjRoot != nullptr )
    {
        QVariant vEventConnected = pObjRoot->property( PROP_IS_EVENT_CONNECTED );
        if( (vEventConnected.isNull() == false && vEventConnected.isValid())
                || vEventConnected.toBool() )
        {
            disconnect( pObjRoot, SIGNAL( controlLoaded(QString) ), this, SLOT( HandleControlLoadedEvent(QString) ) );
            disconnect( pObjRoot, SIGNAL( controlDestruction(QString) ), this, SLOT( HandleControlDestructionEvent(QString) ) );
            pObjRoot->setProperty( PROP_IS_EVENT_CONNECTED, false );
        }

        SetWindowEventDisconnection( pObjRoot, false );
    }
}

void ViewControlModule::SetWindowEventDisconnection(QObject *pObj, bool bRecursive)
{
    if( pObj == nullptr )
    {
        LOGE( TAG, "Object is null" );
        return;
    }

    if( bRecursive )
        setWindowEventDisconnectionRecursive( pObj );
    else
        disconnectObjectEvent( pObj );
}

void ViewControlModule::disconnectObjectEvent(QObject *pObj)
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

    if( vObjectType.toInt() == ControlEnum::OBJECT_WINDOW )
        m_pHWindowEvent->disconnectObjectEvent( pObj );
}

QObject* ViewControlModule::GetRootWindowObject()
{
    QObject* pObjRoot = nullptr;

    if( m_pEngine == nullptr || m_pEngine->rootObjects().isEmpty() )
        return nullptr;

    QList<QObject*> lstRootObject = m_pEngine->rootObjects();

    for( QObject* pObj : lstRootObject ){
        if( pObj != nullptr ){
            if( pObj->objectName().compare( _idWnRoot ) == 0 ){
                pObjRoot = pObj;
                break;
            }
        }
    }

    return pObjRoot;
}

QObject* ViewControlModule::FindChildObject(const QString& objectName, QObject* pParent)
{
    if( objectName.isEmpty() )
        return nullptr;

    if( pParent == nullptr )
        pParent = GetRootWindowObject();

    if( pParent == nullptr )
        return nullptr;

    if( objectName.compare( pParent->objectName() ) == 0 )
        return pParent;

    return pParent->findChild<QObject*>( objectName );
}

QWindowEventHandler* ViewControlModule::GetWindowEventHandler()
{
    return m_pHWindowEvent;
}

void ViewControlModule::SetView(QObject* pObj)
{
    QVariant vObjectId = pObj->property( "objectId" );
    if( vObjectId.isNull() || vObjectId.isValid() == false ){
        LOGE( TAG, "Object id is null" );
        return;
    }
    QHash<int, QBaseView*>::iterator it = m_mapViews.find( vObjectId.toInt() );
    if( it != m_mapViews.end() && (*it) != nullptr ){
        if( (*it)->IsSet() == false ){
            (*it)->Init();
        }
        else {
            (*it)->SetControlEventConnections();
        }

        switch( it.key() ){
        case static_cast<int>(CustomControlEnum::ID_VW_NAVI_HOME): {
        }
        break;
        default:
            break;
        }
    }
    else {
        switch( vObjectId.toInt() ){
        case static_cast<int>(CustomControlEnum::ID_VW_NAVI_HOME): {
            NaviHomeView* pView = new NaviHomeView(pObj);
            pView->Init();
            m_mapViews.insert(vObjectId.toInt(), reinterpret_cast<QBaseView*>(pView));
        }
            break;
        default:
            break;
        }
    }
}

void ViewControlModule::UnsetView(QObject* pObj, bool bDelete)
{
    QVariant vObjectId = pObj->property( "objectId" );
    if( vObjectId.isNull() || vObjectId.isValid() == false ) {
        LOGE( TAG, "Object id is null" );
        return;
    }

    QHash<int, QBaseView*>::iterator it = m_mapViews.find( vObjectId.toInt() );
    if( it == m_mapViews.end() )
        return;

    if( (*it) != nullptr ) {
        if(it.key() == CustomControlEnum::ID_VW_NAVI_HOME)
            disconnect( this, SIGNAL( SigSetTreeModel(QObject*) ), (*it), SLOT( SetTreeModel(QObject*) ) );

        (*it)->SetControlEventDisconnections();
    }

    if( bDelete ) {
        if( (*it) != nullptr ){
            (*it)->deleteLater();
            (*it) = nullptr;
        }
        m_mapViews.erase(it);
    }
}

void ViewControlModule::setWindowEventConnectionRecursive(QObject *pObj)
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

        setWindowEventConnectionRecursive( pObjChild );
    }
}

void ViewControlModule::setWindowEventDisconnectionRecursive(QObject *pObj)
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

        setWindowEventDisconnectionRecursive( pObjChild );
    }
}

void ViewControlModule::init()
{
    if( initQmlEngine() == false )
    {
        LOGE( TAG, "Failed to init QML Engine" );
        return;
    }

    m_pHWindowEvent = new QWindowEventHandler();

    SetWindowEventConnections();
    HandleViewLoadedEvent(_idVwNaviHome);

    QBaseModule::init();
}

bool ViewControlModule::initQmlEngine()
{
    m_pEngine = new QQmlApplicationEngine();

    if( m_pEngine->rootContext() != nullptr ){
    }

    const QUrl url(u"qrc:/Main/res/qml/main.qml"_qs);

    QObject::connect(m_pEngine, &QQmlApplicationEngine::objectCreated
                     , this, [url](QObject *obj, const QUrl &objUrl) {
                            if (!obj && url == objUrl)
                                QCoreApplication::exit(-1);
                        }, Qt::QueuedConnection);

    if( m_pEngine->rootContext() != nullptr ) {
        m_pEngine->addImportPath( QStringLiteral("qrc:/Main/res") );
        m_pEngine->addImportPath( QStringLiteral("qrc:/Main/res/qml") );
        m_pEngine->addImportPath( QStringLiteral("qrc:/Main/res/img") );
        m_pEngine->addImportPath( QStringLiteral("qrc:/com/custom/basecomponents") );
    }

    qmlRegisterType<CustomControlEnum>( "CustomControlEnum", 1, 0, "CustomControlEnum" );

    m_pEngine->load(url);
    if( m_pEngine->rootObjects().isEmpty() )
        return false;

    return true;
}

QString ViewControlModule::getModuleName()
{
    return MDL_NAME( ViewControlModule );
}

void ViewControlModule::doRun()
{

}

void ViewControlModule::stopModule()
{
    QBaseModule::stopModule();

    clear();
}

void ViewControlModule::HandleViewLoadedEvent(QString objName)
{
    LOGD( TAG, "test object: %s", objName.toStdString().c_str() );
    QObject* pNewObj = FindChildObject( objName );
    if( pNewObj == nullptr )
    {
        LOGE( TAG, "Failed to get object: %s", objName.toStdString().c_str() );
        return;
    }

    SetView( pNewObj );
}

void ViewControlModule::HandleViewDestructionEvent(QString objName)
{
    LOGD( TAG, "test object: %s", objName.toStdString().c_str() );
    QObject* pObj = FindChildObject( objName );
    if( pObj == nullptr )
    {
        LOGE( TAG, "Failed to get object: %s", objName.toStdString().c_str() );
        return;
    }

    UnsetView( pObj, true );
}

void ViewControlModule::clear()
{

}

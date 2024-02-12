#ifndef VIEWCONTROLMODULE_H
#define VIEWCONTROLMODULE_H

#include <QBaseModule.h>

#include <cmnDefs.h>
#include <ModuleEnum.h>

#include <QQueue>
#include <QReadWriteLock>

#include <QBaseView.h>
#include <QBaseEventHandler.h>
#include <QWindowEventHandler.h>

#ifndef Q_MOC_RUN
#ifndef DECLARE_MODULE_REQUEST
#define DECLARE_MODULE_REQUEST( FUNCTION_NAME ) \
    void Req##FUNCTION_NAME( int sender, bool response, QVariantMap mapReq );
#endif // !DECLARE_MODULE_REQUEST
#ifndef DEFINE_MODULE_REQUEST
#define DEFINE_MODULE_REQUEST( CLASS, FUNCTION_NAME ) \
    void CLASS::Req##FUNCTION_NAME( int sender, bool response, QVariantMap mapReq )
#endif // !DEFINE_MODULE_REQUEST
#ifndef REGIST_MODULE_REQUEST
#define REGIST_MODULE_REQUEST( REQ_CODE, FUNCTION_NAME ) \
    insertFunctionToReqCode( static_cast<int>( REQ_CODE ), QString("Req")+#FUNCTION_NAME );
#endif // !REGIST_MODULE_REQUEST

#ifndef DECLARE_MODULE_RESPONSE
#define DECLARE_MODULE_RESPONSE( FUNCTION_NAME ) \
    void Res##FUNCTION_NAME( int sender, QVariantMap mapRes );
#endif // !DECLARE_MODULE_RESPONSE
#ifndef DEFINE_MODULE_RESPONSE
#define DEFINE_MODULE_RESPONSE( CLASS, FUNCTION_NAME ) \
    void CLASS::Res##FUNCTION_NAME( int sender, QVariantMap mapRes )
#endif // !DEFINE_MODULE_RESPONSE
#ifndef REGIST_MODULE_RESPONSE
#define REGIST_MODULE_RESPONSE( RES_CODE, FUNCTION_NAME ) \
    insertFunctionToResCode( static_cast<int>( RES_CODE ), QString("Res")+#FUNCTION_NAME );
#endif // !REGIST_MODULE_RESPONSE
#endif

class ViewControlModule final: public QBaseModule
{
    Q_OBJECT

public:
    explicit        ViewControlModule( QObject* parent = nullptr );
    virtual         ~ViewControlModule();

    void            SetWindowEventConnections();
    void            SetWindowEventConnection( QObject* pObj, bool bRecursive );

    void            connectObjectEvent( QObject* pObj );

    void            SetWindowEventDisconnections();
    void            SetWindowEventDisconnection( QObject* pObj, bool bRecursive );

    void            disconnectObjectEvent( QObject* pObj );

    QObject*        GetRootWindowObject();
    QObject*        FindChildObject(const QString& objectName, QObject* pParent = nullptr);

    QWindowEventHandler* GetWindowEventHandler();

private:
    void            SetView( QObject* pObj );
    void            UnsetView( QObject* pObj, bool bDelete );

private:
    void            setWindowEventConnectionRecursive( QObject* pObj );
    void            setWindowEventDisconnectionRecursive( QObject* pObj );

public:
    virtual void init() override;
    static QString getModuleName();

// module event
public slots:
    virtual void doRun() override;
    virtual void stopModule() override;

// qml event
public slots:
    void            HandleViewLoadedEvent( QString objName );
    void            HandleViewDestructionEvent( QString objName );

private:
    bool            initQmlEngine();

    void            clear();

private:
    QQmlApplicationEngine*              m_pEngine;
    QHash<int, QBaseView*>              m_mapViews;

    QWindowEventHandler*                m_pHWindowEvent;
};

#endif // ViewControlModule_H

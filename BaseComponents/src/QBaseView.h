#ifndef QBASEVIEW_H
#define QBASEVIEW_H

#include <QHash>

#include "QBaseEventHandler.h"

class QBaseView : public QObject
{
    Q_OBJECT

public:
    explicit        QBaseView(QObject* objView, QObject* parent = nullptr);
    virtual         ~QBaseView();

    void            SetControlEventConnections();
    void            SetControlEventConnection( QObject* pObj, bool bRecursive );

    void            connectObjectEvent( QObject* pObj );

    void            SetControlEventDisconnections();
    void            SetControlEventDisconnection( QObject* pObj, bool bRecursive );

    void            disconnectObjectEvent( QObject* pObj );

    QObject*        GetViewObject();
    QObject*        FindChildObject(const QString& objectName, QObject* pParent = nullptr);

    QBaseEventHandler* GetEventHandler(int objectType);

private:
    void            setControlEventConnectionRecursive( QObject* pObj );
    void            setControlEventDisconnectionRecursive( QObject* pObj );

    void            destroyControlEventHandlers();

protected:
    virtual void    RegistControlEventHandlers() = 0;

public:
    virtual void    Init();
    bool            IsSet() const;

public slots:
    void            HandleControlLoadedEvent( QString objName );
    void            HandleControlDestructionEvent( QString objName );

protected:
    QHash<int, QBaseEventHandler*> m_mapCtrHandlers;
    QObject*        m_pObjView;
    bool            m_isSet;
};

#endif // QBASEVIEW_H

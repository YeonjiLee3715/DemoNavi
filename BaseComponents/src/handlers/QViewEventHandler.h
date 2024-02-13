#ifndef QVIEWEVENTHANDLER_H
#define QVIEWEVENTHANDLER_H

#include <QObject>
#include <QBaseEventHandler.h>

class QViewEventHandler: public QBaseEventHandler
{
    Q_OBJECT

public:
    explicit            QViewEventHandler( QObject* parent );
    virtual             ~QViewEventHandler();

public:
    virtual void        connectObjectEvent( QObject* pObj ) override;
    virtual void        disconnectObjectEvent( QObject* pObj ) override;

signals:

public slots:
    virtual void        HandleViewShowEvent();
    virtual void        HandleViewHideEvent();
    virtual void        HandleViewOpenEvent();
    virtual void        HandleViewClosedEvent();
    virtual void        HandleViewActiveFocusEvent();
    virtual void        HandleViewInactiveFocusEvent();
};

#endif // QVIEWEVENTHANDLER_H

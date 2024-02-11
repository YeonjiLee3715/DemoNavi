#ifndef QWINDOWEVENTHANDLER_H
#define QWINDOWEVENTHANDLER_H

#include <QObject>
#include <QBaseEventHandler.h>

class QWindowEventHandler: public QBaseEventHandler
{
    Q_OBJECT

public:
    explicit            QWindowEventHandler( QObject* parent = nullptr );
    virtual             ~QWindowEventHandler();

public:
    virtual void        connectObjectEvent( QObject* pObj ) override;
    virtual void        disconnectObjectEvent( QObject* pObj ) override;

signals:

public slots:
    void                HandleWindowShowEvent();
    void                HandleWindowHideEvent();
    void                HandleWindowOpenEvent();
    void                HandleWindowClosedEvent();
    void                HandleWindowActiveEvent();
    void                HandleWindowInactiveEvent();

public:
private:
};

#endif // QWINDOWEVENTHANDLER_H

#ifndef QLISTEVENTHANDLER_H
#define QLISTEVENTHANDLER_H

#include <QObject>
#include <QBaseEventHandler.h>

class QListEventHandler: public QBaseEventHandler
{
    Q_OBJECT

public:
    explicit            QListEventHandler( QObject *parent = nullptr );
    virtual             ~QListEventHandler();

public:
    virtual void        connectObjectEvent( QObject* pObj ) override;
    virtual void        disconnectObjectEvent( QObject* pObj ) override;

signals:

public slots:
    virtual void        HandleControlClickedEvent( int row, int col );
    virtual void        HandleControlDoubleClickedEvent( int row, int col );
    virtual void        HandleControlEnteredEvent( int row, int col );
    virtual void        HandleControlExitedEvent( int row, int col );
    virtual void        HandleControlPressAndHoldEvent( int row, int col );
    virtual void        HandleControlPressedEvent( int row, int col );
    virtual void        HandleControlReleasedEvent( int row, int col );
    virtual void        HandleControlCanceledEvent( int row, int col );
    virtual void        HandleControlWheelEvent( int row, int col, int x, int y );

    virtual void        HandleControlHoveredEvent( int row, int col );
    virtual void        HandleControlFocusedEvent( int row, int col );
    virtual void        HandleControlFocusOutEvent( int row, int col );

    virtual void        HandleControlOpenEvent( int row, int col );
    virtual void        HandleControlClosedEvent( int row, int col );

    virtual void        HandleControlDragEvent( int row, int col, int x, int y );

    virtual void        HandleControlEnabledEvent( int row, int col );
    virtual void        HandleControlDisabledEvent( int row, int col );

    virtual void        HandleControlSelectedEvent( int row, int col );
};

#endif // QLISTEVENTHANDLER_H

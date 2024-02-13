#ifndef QBUTTONEVENTHANDLER_H
#define QBUTTONEVENTHANDLER_H

#include <QObject>
#include <QBaseEventHandler.h>

class QButtonEventHandler: public QBaseEventHandler
{
    Q_OBJECT

public:
    explicit QButtonEventHandler( QObject* parent );
    virtual ~QButtonEventHandler();

public:
    virtual void        connectObjectEvent( QObject* pObj ) override;
    virtual void        disconnectObjectEvent( QObject* pObj ) override;

public slots:
    virtual void        HandleControlClickedEvent();
    virtual void        HandleControlDoubleClickedEvent();
    virtual void        HandleControlPressAndHoldEvent();
    virtual void        HandleControlPressedEvent();
    virtual void        HandleControlReleasedEvent();
    virtual void        HandleControlCanceledEvent();
    virtual void        HandleControlToggledEvent();

    virtual void        HandleControlHoveredEvent(bool bHovered);
    virtual void        HandleControlFocusedEvent();
    virtual void        HandleControlFocusOutEvent();
    virtual void        HandleControlEnabledEvent();
    virtual void        HandleControlDisabledEvent();
public:
private:
};

#endif // QBUTTONEVENTHANDLER_H

#ifndef QBASEEVENTHANDLER_H
#define QBASEEVENTHANDLER_H

#include <QObject>

class QBaseEventHandler: public QObject
{
    Q_OBJECT

public:
    explicit            QBaseEventHandler( QObject *parent = nullptr);
    virtual             ~QBaseEventHandler();

public:
    virtual void        connectObjectEvent( QObject* pObj ) = 0;
    virtual void        disconnectObjectEvent( QObject* pObj ) = 0;
};

#endif // QBASEEVENTHANDLER_H

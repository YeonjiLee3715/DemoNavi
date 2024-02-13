#ifndef QTEXTEDITEVENTHANDLER_H
#define QTEXTEDITEVENTHANDLER_H

#include <QObject>
#include <QBaseEventHandler.h>

class QTextEditEventHandler: public QBaseEventHandler
{
    Q_OBJECT

public:
    explicit            QTextEditEventHandler( QObject* parent );
    virtual             ~QTextEditEventHandler();

public:
    virtual void        connectObjectEvent( QObject* pObj ) override;
    virtual void        disconnectObjectEvent( QObject* pObj ) override;

signals:
    //void                SigSomethingChanged( QString strPath );

public slots:
    void                HandleControlAcceptedEvent();
    void                HandleControlEditingFinishedEvent();
    void                HandleControlTextEditedEvent();
    void                HandleControlFocusedEvent();
    void                HandleControlFocusOutEvent();
    void                HandleControlEnabledEvent();
    void                HandleControlDisabledEvent();

public:
private:
};

#endif // QTEXTEDITEVENTHANDLER_H

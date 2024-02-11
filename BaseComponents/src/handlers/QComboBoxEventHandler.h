#ifndef QCOMBOBOXEVENTHANDLER_H
#define QCOMBOBOXEVENTHANDLER_H

#include <QObject>
#include <QBaseEventHandler.h>

class QComboBoxEventHandler: public QBaseEventHandler
{
    Q_OBJECT

public:
    explicit            QComboBoxEventHandler( QObject *parent = nullptr);
    virtual             ~QComboBoxEventHandler();

public:
    virtual void        connectObjectEvent( QObject* pObj ) override;
    virtual void        disconnectObjectEvent( QObject* pObj ) override;

signals:

public slots:
    virtual void        HandleControlPressedEvent(bool bPressed);
    virtual void        HandleControlHoveredEvent(bool bHovered);
    virtual void        HandleControlFocusedEvent();
    virtual void        HandleControlFocusOutEvent();

    virtual void        HandleControlEnabledEvent();
    virtual void        HandleControlDisabledEvent();
    virtual void        HandleControlOpenEvent();
    virtual void        HandleControlClosedEvent();

    /* This function only be emitted if the combo box index was changed by the user,
     * ** not when set programmatically.** */
    virtual void        HandleControlSelectedEvent( int idx );

    /* This function is emitted when the Return or Enter key is pressed on an ** editable ** combo box.
     * If the confirmed string is not currently in the model,
     * the currentIndex will be set to -1 and the currentText will be updated accordingly. */
    virtual void        HandleControlAccepted();
};

#endif // QCOMBOBOXEVENTHANDLER_H

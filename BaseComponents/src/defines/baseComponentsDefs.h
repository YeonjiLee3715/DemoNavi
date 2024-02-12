#ifndef BASECOMPONENTSDEFS_H
#define BASECOMPONENTSDEFS_H

#include <QObject>
#include <QQmlEngine>
#include <QMetaType>
#include <QMetaEnum>


#define PROP_B_CONNECT_EVENT                        "bConnectEvent"
#define PROP_IS_EVENT_CONNECTED                     "isEventConnected"

#define PROP_B_CONNECT_CLICKED_EVENT                "bConnectClickedEvent"
#define PROP_B_CONNECT_DOUBLE_CLICKED_EVENT         "bConnectDoubleClickedEvent"
#define PROP_B_CONNECT_PRESS_AND_HOLD_EVENT         "bConnectPressAndHoldEvent"
#define PROP_B_CONNECT_PRESSED_EVENT                "bConnectPressedEvent"
#define PROP_B_CONNECT_RELEASED_EVENT               "bConnectReleasedEvent"
#define PROP_B_CONNECT_CANCELED_EVENT               "bConnectCanceledEvent"
#define PROP_B_CONNECT_TOGGLED_EVENT                "bConnectToggledEvent"
#define PROP_B_CONNECT_HOVERED_EVENT                "bConnectHoveredEvent"
#define PROP_B_CONNECT_FOCUSED_EVENT                "bConnectFocusedEvent"
#define PROP_B_CONNECT_FOCUS_OUT_EVENT              "bConnectFocusOutEvent"
#define PROP_B_CONNECT_ENABLED_EVENT                "bConnectEnabledEvent"
#define PROP_B_CONNECT_DISABLED_EVENT               "bConnectDisabledEvent"
#define PROP_B_CONNECT_OPEN_EVENT                   "bConnectOpenEvent"
#define PROP_B_CONNECT_CLOSED_EVENT                 "bConnectClosedEvent"
#define PROP_B_CONNECT_SELECTED_EVENT               "bConnectSelectedEvent"
#define PROP_B_CONNECT_ACCEPTED_EVENT               "bConnectAcceptedEvent"
#define PROP_B_CONNECT_REJECTED_EVENT               "bConnectRejectedEvent"
#define PROP_B_CONNECT_ENTERED_EVENT                "bConnectEnteredEvent"
#define PROP_B_CONNECT_EXITED_EVENT                 "bConnectExitedEvent"
#define PROP_B_CONNECT_WHEEL_EVENT                  "bConnectWheelEvent"
#define PROP_B_CONNECT_DRAG_EVENT                   "bConnectDragEvent"
#define PROP_B_CONNECT_EDITING_FINISHED_EVENT       "bConnectEditingFinishedEvent"
#define PROP_B_CONNECT_TEXT_EDITED_EVENT            "bConnectTextEditedEvent"
#define PROP_B_CONNECT_SHOW_EVENT                   "bConnectShowEvent"
#define PROP_B_CONNECT_HIDE_EVENT                   "bConnectHideEvent"
#define PROP_B_CONNECT_ACTIVEFOCUS_EVENT            "bConnectActiveFocusEvent"
#define PROP_B_CONNECT_INACTIVEFOCUS_EVENT          "bConnectInactiveFocusEvent"
#define PROP_B_CONNECT_ACTIVE_EVENT                 "bConnectActiveEvent"
#define PROP_B_CONNECT_INACTIVE_EVENT               "bConnectInactiveEvent"

// Qml object names
#define _idWnRoot                                   "_idWnRoot"
// End Qml object names

class ControlEnum: public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    typedef enum eObjectType
    {
        OBJECT_NONE = 0,
        OBJECT_WINDOW,
        OBJECT_VIEW,
        OBJECT_DIALOG,
        OBJECT_BUTTON_CONTROL,
        OBJECT_COMBOBOX_CONTROL,
        OBJECT_TEXTEDIT_CONTROL,
        OBJECT_LIST_VIEW,
        OBJECT_TREE_VIEW
    }eObjectType;

    typedef enum eWindowType
    {
        WINDOW_NONE = 0,
        WINDOW_NORMAL
    }eWindowType;

    typedef enum eWindowId
    {
        ID_WN_ROOT = 100,
        ID_WN_USER_ROLE
    }eWindowId;

    typedef enum eViewType
    {
        VIEW_NONE = 0,
        VIEW_NORMAL
    }eViewType;

    typedef enum eBtnControlType
    {
        CONTROL_NONE = 0,
        CONTROL_BUTTON
    }eBtnControlType;

    typedef enum eWindowClosedCode
    {
        WINDOW_CLOSED_CODE_ACCEPTED = 0,
        WINDOW_CLOSED_CODE_REJECTED,
    }eWindowClosedCode;

    ControlEnum( QObject* parent = nullptr ): QObject( parent ) {}


    Q_ENUM( eObjectType )

    Q_ENUM( eWindowType )
    Q_ENUM( eWindowId )

    Q_ENUM( eViewType )

    Q_ENUM( eBtnControlType )

    Q_ENUM( eWindowClosedCode )
};

Q_DECLARE_METATYPE( ControlEnum::eObjectType )

Q_DECLARE_METATYPE( ControlEnum::eWindowType )
Q_DECLARE_METATYPE( ControlEnum::eWindowId )

Q_DECLARE_METATYPE( ControlEnum::eViewType )

Q_DECLARE_METATYPE( ControlEnum::eBtnControlType )

Q_DECLARE_METATYPE( ControlEnum::eWindowClosedCode )

#endif // BASECOMPONENTSDEFS_H

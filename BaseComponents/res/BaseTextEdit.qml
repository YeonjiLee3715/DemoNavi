import QtQuick 2.9
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.4
import ViewEnum 1.0

Rectangle{
    property int objectType: ViewEnum.OBJECT_TEXTEDIT_CONTROL
    property int objectId: 0
    property bool bConnectEvent: false

    property bool bConnectAcceptedEvent: false
    property bool bConnectEditingFinishedEvent: false
    property bool bConnectTextEditedEvent: false
    property bool bConnectFocusedEvent: false
    property bool bConnectFocusOutEvent: false
    property bool bConnectEnabledEvent: false
    property bool bConnectDisabledEvent: false

    signal controlAcceptedEvent()
    signal controlEditingFinishedEvent()
    signal controlTextEditedEvent()
    signal controlFocusedEvent()
    signal controlFocusOutEvent()
    signal controlEnabledEvent()
    signal controlDisabledEvent()

    property alias _idEdt: _idEdt
    property alias text: _idEdt.text

    TextInput{
        id: _idEdt
        clip: true
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        anchors.topMargin: 0
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
        anchors.fill: parent

        onAccepted: {
            if( bConnectAcceptedEvent )
                controlAcceptedEvent()
        }

        onEditingFinished: {
            if( bConnectEditingFinishedEvent )
                controlEditingFinishedEvent()
        }

        onTextEdited: {
            if( bConnectTextEditedEvent )
                controlTextEditedEvent()
        }

        onActiveFocusChanged: {
            if( activeFocus )
            {
                if(bConnectFocusedEvent)
                    controlFocusedEvent()
            }
            else
            {
                if(bConnectFocusOutEvent)
                    controlFocusOutEvent()
            }
        }

        onEnabledChanged: {
            if(enabled)
            {
                if(bConnectEnabledEvent)
                    controlEnabledEvent()
            }
            else
            {
                if(bConnectDisabledEvent)
                    controlDisabledEvent()
            }
        }
    }
}

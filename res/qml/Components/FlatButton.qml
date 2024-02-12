import QtQuick
import QtQuick.Controls
import com.custom.basecomponents

BaseButton {
    id: control

    property string bgNormalColor: "#00000000"
    property string bgHoverColor: "#00000000"
    property string bgFocusColor: "#00000000"
    property string bgPressedColor: "#00000000"
    property string bgDisableColor: "#00000000"

    property string textNormalColor: "#000000"
    property string textHoverColor: "#000000"
    property string textFocusColor: "#000000"
    property string textPressedColor: "#000000"
    property string textDisableColor: "#000000"

    property real horizontalAlignment: Text.AlignHCenter
    property real verticalAlignment: Text.AlignVCenter
    property real elide: Text.ElideRight

    font.bold: true
    font.pointSize: 10

    display: AbstractButton.TextOnly

    property int radius: 0

    property bool isIcon: false
    property bool isText: true

    background: Rectangle {
        anchors.fill: control
        border.width: 0
        color: {
            if( control.enabled )
            {
                if( control.down )
                {
                    bgPressedColor
                }
                else
                {
                    if( control.hovered )
                    {
                        bgHoverColor
                    }
                    else
                    {
                        if( control.focus )
                            bgFocusColor
                        else
                            bgNormalColor
                    }
                }
            }
            else
                bgDisableColor
        }
        radius: control.radius
    }
    text: ""

    contentItem: IconLabel {
        spacing: control.spacing
        mirrored: control.mirrored
        display: control.display

        icon: control.icon
        text: control.text
        font: control.font
        color: {
            if( control.enabled )
            {
                if( control.down )
                {
                    textPressedColor
                }
                else
                {
                    if( control.hovered )
                    {
                        textHoverColor
                    }
                    else
                    {
                        if( control.focus )
                            textFocusColor
                        else
                            textNormalColor
                    }
                }
            }
            else
            {
                textDisableColor
            }
        }
    }
    flat: true

    onDisplayChanged: {
        if( display === AbstractButton.IconOnly ){
            isIcon = true
            isText = false
        }
        else if( display === AbstractButton.TextOnly ){
            isIcon = false
            isText = true
        }
        else {
            isIcon = true
            isText = true
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

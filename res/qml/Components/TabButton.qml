import QtQuick
import QtQuick.Controls 2.15
import com.custom.basecomponents

BaseButton {
    id: control

    property string borderNormalColor: "#00000000"
    property string borderHoverColor: "#00000000"
    property string borderFocusColor: "#00000000"
    property string borderPressedColor: "#00000000"
    property string borderDisableColor: "#00000000"

    property string textNormalColor: "#ffffff"
    property string textHoverColor: "#ffffff"
    property string textFocusColor: "#ffffff"
    property string textPressedColor: "#ffffff"
    property string textDisableColor: "#ffffff"

    property real elide: Text.ElideRight

    font.bold: true
    font.pointSize: 9
    display: AbstractButton.TextOnly

    property int radius: 0

    background: Rectangle {
        anchors.fill: control
        border.width: 0
        border.color: {
            if( control.enabled )
            {
                if( control.down )
                {
                    borderPressedColor
                }
                else
                {
                    if( control.focus )
                    {
                        borderFocusColor
                    }
                    else
                    {
                        if( control.hovered )
                            borderHoverColor
                        else
                            borderNormalColor
                    }
                }
            }
            else
                borderDisableColor
        }
        gradient: Gradient{
            GradientStop{ position: 0.0; color: '#0066F0' }
            GradientStop{ position: 1.0; color: '#0043EF' }
        }
        radius: control.radius
    }
    text: ""

    contentItem: Text {
        text: control.text
        font: control.font
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignBottom
        bottomPadding: 5
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
}

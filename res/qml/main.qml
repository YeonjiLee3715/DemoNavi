/* This file is generated and only relevant for integrating the project into a Qt 6 and cmake based
C++ project. */

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import com.custom.basecomponents
import Components
import Views

BaseWindow {
    property int fixedWidth: 800
    property int fixedHeight: 450
    property int titlebarHeight: 30

    id: _idWnRoot
    objectId: ControlEnum.ID_WN_ROOT
    objectName: '_idWnRoot'

    minimumWidth: fixedWidth
    minimumHeight: fixedHeight
    maximumWidth: fixedWidth
    maximumHeight: fixedHeight
    width: fixedWidth
    height: fixedHeight

    visible: true
    flags: Qt.Window|Qt.FramelessWindowHint

    signal viewLoaded( string objName )
    signal viewDestruction( string objName )

    property string txtTitle

    Loader {
        id: _idLdrTitleBar
        sourceComponent: _idCmpTitleBar
    }

    Loader {
        id: _idLdrVw
        anchors.top: _idLdrTitleBar.bottom

        function changeView(id){
            if( item !== null )
                viewDestruction(item.objectName)

            sourceComponent = id
        }

        onLoaded: {
            txtTitle = _idLdrVw.item.viewTitle
            viewLoaded( _idLdrVw.item.objectName )
        }
    }

// components

    // title bar
    Component {
        id: _idCmpTitleBar

        Rectangle {
            id: _idTitleBar
            z: 1
            height: titlebarHeight
            width: fixedWidth
            color: 'lightsteelblue'
            layer.enabled: true
            anchors.top: _idWnRoot.top

            Text {
                anchors.fill: parent
                verticalAlignment: Qt.AlignVCenter
                horizontalAlignment: Qt.AlignHCenter
                text: txtTitle
                font.pointSize: 12
            }

            MouseArea {
                id: _idMaTitleBar
                anchors.fill: parent
                property variant clickPos: "1,1"

                function setClickPose(mouse) {
                    clickPos  = Qt.point(mouse.x,mouse.y)
                }

                function moveWindow(mouse) {
                    var delta = Qt.point(mouse.x-clickPos.x, mouse.y-clickPos.y)
                    _idWnRoot.x += delta.x;
                    _idWnRoot.y += delta.y;
                }

                Connections {
                    function onPressed(mouse){ _idMaTitleBar.setClickPose(mouse) }
                    function onPositionChanged(mouse){ _idMaTitleBar.moveWindow(mouse) }
                }
            }

            FlatButton {
                anchors.verticalCenter: _idTitleBar.verticalCenter
                x: fixedWidth-30
                width: 30
                height: _idTitleBar.hight
                text: "X"
                font.bold: true
                font.pointSize: 12
                textNormalColor: 'black'
                bgHoverColor: "#ff5555"
                bgPressedColor: "#ff2222"

                onClicked: Qt.quit()
            }
        }
    }

    // NaviHomeView
    Component {
        id: _idCmpVwNaviHome
        NaviHomeView {
            width: fixedWidth
            height: fixedHeight-titlebarHeight
        }
    }

    Component.onCompleted: {
        _idLdrVw.sourceComponent = _idCmpVwNaviHome
    }
}

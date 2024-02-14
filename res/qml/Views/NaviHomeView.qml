import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtPositioning
import QtLocation

import com.custom.basecomponents
import Components
import CustomControlEnum 1.0

BaseView {
    id: _idVwNaviHome
    objectId: CustomControlEnum.ID_VW_NAVI_HOME
    objectName: '_idVwNaviHome'

    readonly property string viewTitle: ''
    property alias mapview: mapview

    visible: true

    FlatButton {
        id: _idBtnGoToCurPos
        x: 10
        y: 10
        z: 1
        width: 50
        height: 50
        icon.source: "qrc:/Main/res/img/aim.png"
        display: AbstractButton.IconOnly

        bgNormalColor: "#8888ff"
        bgHoverColor: "#5555ff"
        bgFocusColor: "#8888ff"
        bgPressedColor: "#2222ff"
        opacity: 0.5

        onClicked: {
            mapview.map.center = _idMkCur.coordinate
        }
    }

    FlatButton {
        id: _idBtnSearchView
        anchors.top: _idBtnGoToCurPos.bottom
        anchors.topMargin: 10
        x: 10
        z: 1
        width: 50
        height: 50
        icon.source: "qrc:/Main/res/img/search.png"
        display: AbstractButton.IconOnly

        bgNormalColor: "#8888ff"
        bgHoverColor: "#5555ff"
        bgFocusColor: "#8888ff"
        bgPressedColor: "#2222ff"
        opacity: 0.5

        onClicked: {
            _idWnRoot.showSearchView()
        }
    }

    MapView{
        id: mapview

        anchors.fill: parent
        map.zoomLevel: map.maximumZoomLevel
        map.center {
            // GangNam station
            latitude: 37.497952
            longitude: 127.027619
        }
        focus: true
        map.onCopyrightLinkActivated: Qt.openUrlExternally(link)
        map.plugin: Plugin {
                        name: "osm"
                        PluginParameter { name: "osm.useragent"; value: "Qt osm test" }
                        PluginParameter { name: "osm.mapping.host"; value: "http://osm.tile.server.address/" }
                        PluginParameter { name: "osm.mapping.copyright"; value: "All mine" }
                        PluginParameter { name: "osm.routing.host"; value: "http://osrm.server.address/viaroute" }
                        PluginParameter { name: "osm.geocoding.host"; value: "https://nominatim.openstreetmap.org/search" }
                    }

        Component.onCompleted: {
            _idMkCur.coordinate = map.center
        }
    }

    MapQuickItem {
        id: _idMkCur
        parent: mapview.map
        sourceItem: Image {
                        id: image
                        source: "qrc:/Main/res/img/marker.png"
                    }
        opacity: 1.0
        anchorPoint: Qt.point(sourceItem.width/2, sourceItem.height/2)
    }
}

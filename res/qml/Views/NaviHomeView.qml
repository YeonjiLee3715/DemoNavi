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

    MapView{
        id: mapview

        anchors.fill: parent
        map.zoomLevel: map.maximumZoomLevel
        map.center {
            // The GangNam station
            latitude: 37.497952
            longitude: 127.027619
        }
        focus: true
        map.onCopyrightLinkActivated: Qt.openUrlExternally(link)
        map.plugin:     Plugin {
            name: "osm"
            PluginParameter { name: "osm.useragent"; value: "My great Qt OSM application" }
            PluginParameter { name: "osm.mapping.host"; value: "http://osm.tile.server.address/" }
            PluginParameter { name: "osm.mapping.copyright"; value: "All mine" }
            PluginParameter { name: "osm.routing.host"; value: "http://osrm.server.address/viaroute" }
            PluginParameter { name: "osm.geocoding.host"; value: "http://geocoding.server.address" }
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

        Component.onCompleted: {
            _idMkCur.coordinate = map.center
        }
    }
}

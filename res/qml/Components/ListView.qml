import QtQuick
import QtQuick.Controls 2.15
import QtQuick.Layouts
import com.custom.basecomponents

BaseTreeView {
    _idTree.boundsBehavior: Flickable.DragOverBounds
    _idTree.flickableDirection: Flickable.VerticalFlick
    _idTree.delegate: Item {
        id: _idDelTreeView

        implicitWidth: _idTree.width
        implicitHeight: 40

        readonly property real indent: 32
        readonly property real padding: 5

        // Assigned to by TreeView:
        required property TreeView treeView
        required property bool isTreeNode
        required property bool expanded
        required property int hasChildren
        required property int depth

        TapHandler {
            onTapped: {
                treeView.toggleExpanded(row)
                if( _idDelTreeView.isTreeNode && _idDelTreeView.hasChildren )
                    isExpanded = !isExpanded
            }
        }

        RowLayout {
            anchors.fill: parent
            spacing: 5

            Item{
                id: _idSpacer
                property real fixedWidth: (_idDelTreeView.depth * _idDelTreeView.indent)

                Layout.minimumWidth: fixedWidth
                Layout.maximumWidth: fixedWidth
                Layout.fillHeight: true
            }

            Item {
                Layout.minimumWidth: 32
                Layout.maximumWidth: 32
                Layout.minimumHeight: 32
                Layout.maximumHeight: 32
                Layout.alignment: Qt.AlignVCenter
                clip: true

                Image {
                    id: _idImgIndicator
                    width: 25
                    height: 25
                    anchors.centerIn: parent
                    visible: _idDelTreeView.isTreeNode && _idDelTreeView.hasChildren
                    source: _idDelTreeView.expanded ? 'qrc:/img/ico_collapse.png' : 'qrc:/img/ico_expand.png'
                }
            }

            Image {
                id: _idImgIcon
                visible: isIcon
                width: 36
                height: 36
                Layout.minimumWidth: 36
                Layout.maximumWidth: 36
                Layout.minimumHeight: 36
                Layout.maximumHeight: 36
                Layout.alignment: Qt.AlignVCenter
                source: (isIcon ? iconSrc : '')
            }

            Text {
                id: label
                Layout.alignment: Qt.AlignVCenter
                Layout.fillHeight: true
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
                clip: true
                text: name
                font.pointSize: 12
            }
        }
    }
}

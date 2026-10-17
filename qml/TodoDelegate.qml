import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

RowLayout {
    id: root

    required property int index
    required property string title
    required property bool done

    signal toggled()
    signal removed()

    CheckBox {
        checked: root.done
        onToggled: root.toggled()
    }

    Label {
        Layout.fillWidth: true
        text: root.title
        font.strikeout: root.done
        elide: Text.ElideRight
    }

    Button {
        text: qsTr("Delete")
        flat: true
        onClicked: root.removed()
    }
}

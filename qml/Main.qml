import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import TodoApp

ApplicationWindow {
    id: window

    width: 400
    height: 600
    visible: true
    title: qsTr("Todo App")

    TodoModel {
        id: todoModel
    }

    function addTodo() {
        if (todoModel.add(input.text))
            input.clear()
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 12
        spacing: 8

        RowLayout {
            Layout.fillWidth: true

            TextField {
                id: input

                Layout.fillWidth: true
                placeholderText: qsTr("What needs doing?")
                onAccepted: window.addTodo()
            }

            Button {
                text: qsTr("Add")
                enabled: input.text.trim().length > 0
                onClicked: window.addTodo()
            }
        }

        ListView {
            id: list

            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            model: todoModel
            delegate: TodoDelegate {
                width: list.width
                onToggled: todoModel.toggle(index)
                onRemoved: todoModel.remove(index)
            }
        }
    }
}

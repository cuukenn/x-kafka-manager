import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls

Window {
    width: 320
    height: 500
    visible: true
    title: qsTr("XKafkaManager")
    Text {
        color: 'red'
        text: context.text
    }
}

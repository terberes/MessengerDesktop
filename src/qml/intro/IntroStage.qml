import QtQuick 2.0
import QtQuick.Controls 2.12

Item {
    signal stageComplete
    signal setSpin(bool t)
    signal setNumber(var number)
    signal openErrorDialog(var content, var header, var footer)
}

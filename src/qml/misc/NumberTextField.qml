import QtQuick 2.0
import QtQuick.Controls 2.12
import Misc.Numbers 1.0

TextField {
    readOnly: true
    text: "+"
    horizontalAlignment: Text.AlignLeft
    property bool isError: false
    property bool isChecked: false
    //        color: isError ? "#c00000" : (isChecked ? "#00c000" : "#000000")
    signal submit
    color: isError ? "#c00000" : "#000000"
    function check() {
        isError = !numberService.verify()
        isChecked = !isError
        if (isChecked)
            submit()
        return isChecked
    }
    Keys.onPressed: {
        switch (event.key) {
        case Qt.Key_Return:
        case Qt.Key_Enter:
            check()
            break
        case Qt.Key_Backspace:
            numberService.remove_digit()
            text = numberService.number
            break
        default:
            if (numberService.add_digit(event.text)) {
                text = numberService.number
                isError = false
            } else
                isError = true
            break
        }
    }

    PhoneNumberService {
        id: numberService
    }
}

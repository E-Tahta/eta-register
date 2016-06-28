import QtQuick 2.3
import QtQuick.Controls 1.2
import eta.bridge 1.0

ApplicationWindow {
    id:test
    visible: false
    width: 300
    height: 300


    Column {
        id:mainColumn
        anchors.fill: parent

        TextField {
            id:city
            width: 200
            antialiasing: true
            anchors.horizontalCenter: parent.horizontalCenter
        }
        TextField {
            id:town
            width: 200
            antialiasing: true
            anchors.horizontalCenter: parent.horizontalCenter
        }
        TextField {
            id:school
            width: 200
            placeholderText: "Input School name ..."
            antialiasing: true
            anchors.horizontalCenter: parent.horizontalCenter
        }
        TextField {
            id:code
            width: 200
            placeholderText: "Input Facility code ..."
            antialiasing: true
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
    Button{
        id: sendButton
        x: 123
        y: 147
        width: 75
        text: "Send"
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        tooltip: "Sends Data"
        isDefault: true

        onClicked: {
            sendButton.text = "Processing";
            bridge.sendData(city.text,town.text,school.text,code.text);
        }

    }

    Bridge {
        id:bridge
        onShowGui: {            
            test.visible = true;
        }
        onClose: {
            Qt.quit();
        }
        onResultRecieved: {

            var res = result.split(" ");
            var done = res[3];
            console.log(""+done);
            if (done == "SUCCESFULL") {
              sendButton.text = "Succesfull";
            } else if(done == "UNSUCCESFULL") {
              sendButton.text = "Unsuccesfull";
            }
        }
    }
    Component.onCompleted: {
        bridge.isOnline();
    }
}

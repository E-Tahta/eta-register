/*****************************************************************************
 *   Copyright (C) 2016 by Hikmet Bas                                        *
 *   <hikmet.bas@pardus.org.tr>                                              *
 *                                                                           *
 *   This program is free software; you can redistribute it and/or modify    *
 *   it under the terms of the GNU General Public License as published by    *
 *   the Free Software Foundation; either version 2 of the License, or       *
 *   (at your option) any later version.                                     *
 *                                                                           *
 *   This program is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 *   GNU General Public License for more details.                            *
 *                                                                           *
 *   You should have received a copy of the GNU General Public License       *
 *   along with this program; if not, write to the                           *
 *   Free Software Foundation, Inc.,                                         *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA .          *
 *****************************************************************************/

import QtQuick 2.0
import QtQuick.Controls 1.2
import eta.bridge 1.0
import "../js/functions.js" as Func

Item {

    function gotInfo(errorType) {
        switch (errorType) {
        case 0:
            txtError.text = main.errorDatabase
            break
        case 1:
            txtError.text = main.codeNotFound
            manuelEntry.visible = true
            break
        case 2:
            txtError.text = main.errorDatabase // city not found
        }
    }

    Column {
        width: parent.width / 2
        height: parent.height  / 2
        anchors.centerIn: parent
        spacing: main.spacing

        Text {
            id:txtRegisterMessage
            width: parent.width
            height: 40
            font.pointSize: main.messageTextSize
            font.bold: true
            text: registerMessage
            color: main.textColor
        }


        TextField {
            id:code
            width: parent.width
            height: 60
            placeholderText: "Kurum/Tesis kodunuzu giriniz"
            maximumLength: 8
            onFocusChanged: {
                if(code.focus) {
                    bridge.showKeyboard()
                }
            }
        }

        Row {
            spacing: main.spacing
            width: parent.width

            Rectangle {
                id: btnCancel
                height: 60
                width: parent.width / 2 - main.spacing / 2
                color: main.btnNoColor
                radius: main.rad

                Text {
                    id: txtLater
                    text: "Vazgeç"
                    font.bold: true
                    font.pointSize: main.buttonTextSize
                    anchors.centerIn: parent
                    color: "white"
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: Qt.quit()
                }
            }

            Rectangle {
                id: btnSend
                height: 60
                width: parent.width / 2 - main.spacing / 2
                color: main.btnYesColor
                radius: main.rad
                Text {
                    id: txtContinue
                    text: "Gönder"
                    font.bold: true
                    font.pointSize: main.buttonTextSize
                    anchors.centerIn: parent
                    color: "white"
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        main.code = code.text.trim()
                        if (Func.checkCode(main.code)) {
                            bridge.getData(main.code);
                        } else {
                            txtError.text = main.errorCode
                        }
                    }
                }
            }
        }

        Item {
            id: container
            width: parent.width
            height: 40

            Text {
                id: txtError
                color: "red"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                opacity: 0
                anchors.centerIn: parent
                onTextChanged: {
                    txtError.opacity = txtError.text != "" ? 1 : 0
                }
            }
        }

        Item {
            id: manuelEntry
            width: parent.width
            height: 80
            visible: false
            Rectangle {
                id: btnManuelEntry
                height: 60
                width: parent.width / 2
                color: main.btnEditColor
                radius: main.rad

                anchors.centerIn: parent

                Text {
                    id: txtManuelEntry
                    text: "Bilgileri el ile gir"
                    font.bold: true
                    font.pointSize: main.buttonTextSize
                    anchors.centerIn: parent
                    color: "white"
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        stackView.push(register)
                    }
                }
            }
        }
    }
    Component.onCompleted: {
        bridge.onDbError.connect(gotInfo)
    }
}




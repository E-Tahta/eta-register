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

import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Window 2.0
import QtQuick.XmlListModel 2.0
import eta.bridge 1.0


ApplicationWindow {
    id: main
    visible: false
    width: Screen.width / 2
    height: Screen.height / 2
    title: "Eta Kayıt"

    color: "#383838"

    x: Screen.width - (main.width + Screen.desktopAvailableWidth) / 2
    y: Screen.height - (main.height + Screen.desktopAvailableHeight) / 2

    flags: Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint

    property int buttonSize: 30
    property int buttonTextSize: 12
    property int messageTextSize: 15
    property int textSize: 12
    property int spacing: 10
    property int rad : 5
    property bool busy: true
    property string message: "Pardus Etkileşimli Tahta Arayüzü'ne Hoş Geldiniz"
    property string subMessage: "Etkileşimli tahta envanter kaydı"
    property string confirmMessage: "Lütfen gönderilecek bilgileri onaylayın"

    property string registerMessage: "Lütfen gerekli bilgileri doldurun"
    property string errorCode: "Hatalı kurum/tesis kodu girdiniz"
    property string errorEmptyFields : "Tüm alanların eksiksiz "+
                                       "doldurulması zorunludur"
    property string codeNotFound: "Bu tesis koduna ait bilgi bulunamadı.\n"+
                                  "Bilgileri girmek ister misiniz?"
    property string errorDatabase: "Veritabanı hatası!!!"

    property string cityID
    property string city
    property string town
    property string school
    property string code

    property string cityCode : "01"

    property string textColor: "white"
    property string statusMessage
    property string imageSource

    property int currIndex: 0

    property bool success: false
    property bool citiesReady: false

    property string btnYesColor : "#5294E2"
    property string btnNoColor: "#FF6C00"
    property string btnEditColor: "#4CAF50"

    function fillCities(){
        cityModel.clear()
        for (var i = 0; i<xmlCities.count; i++){
            cityModel.append({"name":xmlCities.get(i).name})
        }

        main.citiesReady = true
    }

    function fillTowns(){
        townsModel.clear()
        for (var i = 0; i<xmlTowns.count; i++){
            if (xmlTowns.get(i).city_id == (currIndex + 1)){
                townsModel.append({"name":xmlTowns.get(i).name})
            }
        }
    }

    XmlListModel {
        id: xmlCities
        source: "../xml/cities.xml"
        query: "/cities/city"
        XmlRole { name: "name"; query: "name/string()" }
        XmlRole { name: "id"; query: "id/string()" }
        onStatusChanged: {
            if (xmlCities.status == XmlListModel.Ready){
                fillCities()
            }
        }
    }

    XmlListModel {
        id: xmlTowns
        source: "../xml/towns.xml"
        query: "/towns/town"
        XmlRole { name: "name"; query: "name/string()" }
        XmlRole { name: "city_id"; query: "city_id/string()" }
        onStatusChanged: {
            if (xmlTowns.status == XmlListModel.Ready){
                fillTowns()
            }
        }

    }

    ListModel {
        id: cityModel
    }

    ListModel {
        id: townsModel
    }

    Welcome {
        id: welcome
        visible: false
    }

    Code {
        id: code
        visible: false
    }

    Register {
        id: register
        visible: false
    }

    Confirm {
        id: confirm
        visible: false
    }

    Status {
        id: status
        visible: false
    }

    StackView {
        id: stackView
        anchors.fill: parent
    }

    onCitiesReadyChanged: {
        if (main.citiesReady) {
            fillTowns()
        } else {
            fillCities()
        }
    }

    Component.onCompleted: {
        stackView.push(welcome)
        bridge.isOnline();
    }

    Bridge {
        id:bridge

        onOnline: {
            keepAlive.stop()
            bridge.doesExist()
        }

        onOffline: {
            keepAlive.start()
        }

        onShowGui: {
            main.visible = true;
        }
        onClose: {
            Qt.quit();
        }

        onResultRecieved: {

            var res = result.split(" ");
            var done = res[3];

            if (done == "SUCCESSFUL") {
                main.busy = false
                timer.stop()
                main.imageSource = "Images/success.svg"
                statusMessage = "Tahta başarıyla kaydedildi";
                main.success = true
            } else if(done == "UNSUCCESSFUL") {
                main.busy = false
                timer.stop()
                main.imageSource = "Images/failed.svg"
                main.statusMessage = "Sunucularımız kısa bir süreliğine meşgul\n"+
                        "Bir süre sonra tekrar deneyiniz "
            } else {
                console.log(result)
            }
        }


        onDbError: {

        }

        onInfoCollected: {
            main.code = datas[0]
            main.city = datas[1]
            main.cityCode = datas[2]
            main.town = datas[3]
            main.school = datas[4]

            stackView.push(confirm)
        }
    }

    Timer {
        id: keepAlive
        running: false
        interval: 10000
        onTriggered: {
            bridge.isOnline()
        }
    }

    Timer {
        id: timer
        running: false
        interval: 10000
        onTriggered: {
            if (main.visible) {
                main.busy = false
                timer.stop()
                main.imageSource = "Images/failed.svg"
                main.statusMessage = "Kayıt sırasında hata oluştu\n"+
                        "Ağ ayarlarınızı kontrol edin"
            }
        }
    }
}

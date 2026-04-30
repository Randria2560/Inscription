import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12


ApplicationWindow{
    visible: true
    title: qsTr("MyBD sur l'inscription")
    width: 700
    height: 700
    Material.theme: Material.Light
    menuBar:MenuBar{
        Menu{
            title: qsTr("Raccourcis")
            MenuItem{
                text:qsTr("Copy")
            }
            MenuItem{
                text:qsTr("Cut")
            }
            MenuItem{
                text:qsTr("Paste")
            }
            MenuItem{
                text:qsTr("Select All")
            }
        }
        Menu{
            title:qsTr("File")
            MenuItem{
                text:qsTr("Open")
            }
            MenuItem{
                text:qsTr("Save as")
            }
            MenuItem{
                text:qsTr("Save")
            }
            MenuItem{
                text:qsTr("Ouvrir")
            }
        }
    }
    //srollbar et fromulaire ajouter et supprimer:

    Column {
        anchors.fill: parent
        spacing: 5
        Row {
            width: parent.width
            height: parent.height / 2
            spacing: 10
            Rectangle{
                width: parent.width /2-5
                height: parent.height
                color: "#e3f2fd"
                Column
                {
                    anchors.fill:parent
                    spacing: 5
                    Text{
                        text:"Ajouter";
                        font.bold: true
                    }
                    TextField {
                        id: input_nom
                        placeholderText: "Nom" }
                    TextField {
                        id: input_password
                        placeholderText: "password" }

                    Button {
                        text: "S'Inscrire"   /*ajouter à la fin*/
                        onClicked: {
                            Backend.ajouter(input_nom.text, input_password.text)
                        }
                    }
               }
            }
            Dialog{
                id: dialog
                modal: true
                standardButtons: Dialog.Ok
                property string message: ""  //on peut modifier
                contentItem: Text{
                    text: dialog.message
                }
            }

            Rectangle{
                /*Créer des boutons rechercher, supprimer , ajouter à une position->demander une position*/
                width: parent.width / 2 - 5
                height: parent.height
                color: "#ffebee"
                ScrollView{
                    anchors.fill : parent
                    contentWidth: parent.width

                Column {
                    anchors.fill: parent
                    width: parent.width
                    anchors.margins: 10
                    spacing: 10
                    //non encore une classe mais QString
                    /*=================Supprimer==========================================*/
                    Text { text: "Supprimer inscript"; font.bold: true }

                        TextField {
                            id: delete_nom
                            width: parent.width - 20
                            placeholderText: "Nom à supprimer"
                        }
                        RowLayout{
                            CheckBox{
                                id: supp_un
                                text: "Supprimer un"
                                checked: false
                            }
                            CheckBox{
                                id: supp_all
                                text: "supprimer all"
                                checked: false
                            }
                        }

                        Button {
                            text: "Supprimer"

                            onClicked: {
                                if (delete_nom.text === "") {
                                    dialog.message = "Entrer un nom"
                                    dialog.open()
                                    return
                                }

                                if (!supp_un.checked && !supp_all.checked) {
                                    dialog.message = "Choisissez une option"
                                    dialog.open()
                                    return
                                }
                                if (supp_un.checked) {
                                    Backend.supprimer(delete_nom.text)
                                    dialog.message = "Suppression d’un élément"
                                    dialog.open()
                                }
                                else if (supp_all.checked) {
                                    console.log("supprimer tout")  /*devrai: apres confirmation -> suppression et non simultanément */
                                    Backend.supprimer_all(delete_nom.text)
                                    dialog.message = "Tout supprimé"
                                    dialog.open()
                                }
                            }
                        }


                    /*=================Ajouter à une position===========================================*/
                    Text { text: "Ajouter à une position"; font.bold: true }
                    TextField{
                        id: pos_nom
                        width: parent.width - 20
                        placeholderText: "Nom à entrer"
                    }
                    TextField{
                        id: pos_password
                        width:parent.width - 20
                        placeholderText: "password"
                        echoMode: TextInput.Password
                    }
                    TextField{
                        /*Vérifier que ce soit un digit*/
                        id:pos_index
                        width: parent.width - 20
                        placeholderText: "pos_index"
                        /*Ajouter le validator*/
                    }

                    Button {
                        text: "Ajouter à la position"
                        onClicked:{
                            if (pos_nom.text !== "" && pos_index.text !== "")
                                Backend.ajouter_position(
                                    pos_nom.text,
                                    pos_password.text,
                                    parseInt(pos_index.text)
                                )
                            pos_nom.text = ""
                            pos_index.text = ""
                        }
                    }


                    /*=================Rechercher =========================================*/
                    Text { text: "Rechercher"; font.bold: true }

                    TextField {
                        id: search_nom
                        width: parent.width - 20
                        placeholderText: "Nom à rechercher"
                    }

                    Button {
                        text: "Rechercher"
                        onClicked: {
                            if (search_nom.text !== "")
                                Backend.rechercher(search_nom.text)
                        }
                    }
                    /*==========================*/

                }

                }
            }
        }


        /*2 eme partie: afficher les choses dans le fichier*/
        Rectangle {
            width: parent.width
            height: parent.height / 2
            color: "#f5f5f5"

            Column {
                anchors.fill: parent
                anchors.margins: 8
                spacing: 6

                Text {
                    text: "Liste des inscrits :"
                    font.bold: true
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                ScrollView {
                    width: parent.width          // ← doit avoir width explicite
                    height: parent.height - 30   // ← doit avoir height explicite
                    clip: true

                    ListView {
                        id: liste_view
                        width: parent.width      // ← ajouter width ici
                        height: parent.height    // ← ajouter height ici
                        model: Backend.listeModel
                        spacing: 4

                        delegate: Rectangle {
                            width: liste_view.width
                            height: 36
                            radius: 4
                            color: liste_view.currentIndex === index
                                   ? "#bbdefb"
                                   : (index % 2 === 0 ? "#ffffff" : "#eeeeee")

                            Text {
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 12
                                text: modelData   // ← affiche "[0]  Alice  —  pass1"
                                font.pixelSize: 13
                            }

                            MouseArea {
                                anchors.fill: parent
                                onClicked: liste_view.currentIndex = index
                            }
                        }
                    }
                }
            }
        }
    }
}

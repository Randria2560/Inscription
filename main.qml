import QtQuick
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
    property int page:0


    Dialog{
        id: dialog
        modal: true
        standardButtons: Dialog.Ok
        property string message: ""  //on peut modifier
        contentItem: Text{
            text: dialog.message
        }
    }

    Dialog{
        id: dialog1
        title: "Voulez-vous Quitter?"
        standardButtons: Dialog.Yes | Dialog.No
        property string message: ""
        contentItem: Text{
            text: dialog1.message
        }

        onAccepted: {
            //affiche un message de Dialog et quitter
            Backend.enregistrement()
            dialog1.message="Enregistrement OK"
            Qt.quit()
        }
        onRejected:{
            dialog1.message="Non enregistrement "
            Qt.quit()
        }
    }

    onClosing:
            function(close){
                close.accepted = true
                dialog1.open()
            }




    menuBar:MenuBar{
        Menu{
            title: qsTr("Raccourcis")
            MenuItem{
                text:qsTr("Copy     <<CTRL-C>>")
                onTriggered: zoneTexte.copy()
            }
            MenuItem{
                text:qsTr("Cut      <<CTRL-X>>")
                onTriggered: zoneTexte.cut()
            }
            MenuItem{
                text:qsTr("Paste    <<CTRL-V>>")
                onTriggered: zoneTexte.paste()
            }
            MenuItem{
                text:qsTr("Select All   <<CTRL-A>>")
                onTriggered: zoneTexte.selectAll()
            }
        }
        Menu{
            title:qsTr("File")
            MenuItem{
                text:qsTr("Open   <<Ctrl+O>>")
                Backend.ouvrir()

            }
            MenuItem{
                text:qsTr("Save as <<Ctrl+S>>")
                Backend.save_as()
            }
            MenuItem{
                text:qsTr("Save <<Ctrl+P>>")
                Backend.save()
            }

        }

    }
    header: ToolBar{
        RowLayout{
            anchors.fill: parent
            spacing: 10
            ToolButton{
                text: "🏠 Accueil"

                onClicked: page = 0

            }
            ToolButton{
                text: "📝 TextArea"

                onClicked:  page = 1

            }
        }
    }

    //Les raccourcis clavier:


    //page de textarea:
    Rectangle {
        visible: page === 1
        anchors.fill: parent
        color: "#f1f1f1"

        TextArea {
            id: zoneTexte
            anchors.fill: parent
            wrapMode: TextArea.Wrap
            placeholderText: "Écrire ici..."
            textFormat: TextEdit.PlainText
        }
    }

    //les raccourcis clavier si on ne passe pas par le menu:
    Shortcut{
        sequence: "Ctrl+C"
        onActivated: zoneTexte.copy()
    }
    Shortcut{
        sequence: "Ctrl+X"
        onActivated: zoneTexte.cut()
    }
    Shortcut{
        sequence: "Ctrl+V"
        onActivated: zoneTexte.paste()
    }
    Shortcut{
        sequence: "Ctrl+A"
        onActivated: zoneTexte.selectAll()
    }



    //srollbar et fromulaire ajouter et supprimer:
    Column {
        visible: page == 0
        anchors.fill: parent
        spacing: 10
        id: mainColumn
        property string sexe: ""
        property string dateN: ""
        property string niveau: ""
        property string choix: ""

        Row {
            width: parent.width
            height: parent.height / 2
            spacing: 10

            Rectangle{
                width: parent.width /2-5
                height: parent.height
                color: "#e3f2fd"
                ScrollView{
                    anchors.fill : parent
                    contentWidth: parent.width
                Column
                {
                    anchors.fill:parent
                    spacing: 5
                    Text{
                        text:"Inscription";
                        anchors.horizontalCenter: parent.horizontalCenter;
                        font.bold: true
                    }

                    RowLayout{
                        Text{
                            text: "Nom: "
                        }
                        TextField {
                            id: input_nom
                            placeholderText: "Nom" }
                    }
                    RowLayout{
                        Text{
                            text: "Prenoms: "
                        }
                        TextField {
                            id: input_prenom
                            placeholderText: "Prenom" }
                    }


                    RowLayout{
                        Text {
                            text: "Sexe :"
                        }
                        ButtonGroup {
                            id: groupeSexe

                            onCheckedButtonChanged: {
                                if (checkedButton !== null)
                                {
                                    mainColumn.sexe = checkedButton.text

                                }
                            }
                        }


                        RadioButton {
                            text: "Homme"
                            ButtonGroup.group: groupeSexe
                        }
                        RadioButton {
                            text: "Femme"
                            ButtonGroup.group: groupeSexe
                        }
                    }




                    RowLayout{

                        Text {
                            text: "Date de naissance : "
                        }

                        TextField {
                            id: dateField
                            placeholderText: "JJ/MM/AAAA"

                            onTextChanged: {
                                mainColumn.dateN = text  // Capture directement comme string
                            }
                        }
                    }

                    RowLayout{
                        Text{
                            text: "Lieu Naissance"
                        }
                        TextField {
                            id: input_lieu
                            placeholderText: "Lieu_Naissance" }
                    }
                    RowLayout{
                        Text{
                            text: "Adresse: "
                        }
                        TextField {
                            id: input_adresse
                            placeholderText: "Adresse" }
                    }



                    //et le selecte:choix multiple
                   RowLayout{

                       Text {
                           text: "Niveau : "
                       }

                       ComboBox {
                           id: comboNiveau

                           model: ["L1", "L2", "L3", "M1", "M2"]

                           onCurrentTextChanged: {
                               mainColumn.niveau = currentText
                           }
                       }
                   }


                   RowLayout{
                       Text{
                           text: "Filière:  "
                       }
                       TextField {
                           id: input_filiere
                           placeholderText: "Filière" }
                    }

                    Button {
                        text: "S'Inscrire"   /*ajouter à la fin*/
                        onClicked: {
                            Backend.ajouter(input_nom.text, input_prenom.text, mainColumn.sexe , mainColumn.dateN , input_lieu.text, input_adresse.text, mainColumn.niveau , input_filiere.text)
                        }
                    }
                }

            }



            //Colonne à gauche===================================================================================================
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
                            pos_password= ""
                        }
                    }


                    /*=================Rechercher avec beaucoup d'options:=========================================*/

                    RowLayout{

                        Text{
                            text: "Rechercher selon: ";
                            font.bold: true
                        }
                        ComboBox{
                            id: recherche
                            model: ["Nom", "Prenom", "Sexe" , "Date_Naissance", "Lieu_Naissance", "Adresse" , "Niveau" , "Filiere"]
                            onCurrentTextChanged: {
                                mainColumn.choix = currentText
                            }
                        }
                    }

                    TextField {
                        id: search_nom
                        width: parent.width - 20
                        placeholderText: "Rechercher: "
                    }

                    Button {
                        text: "Rechercher"
                        onClicked: {
                            if (search_nom.text !== "")
                                /*recherche depuis le début et qu'on on appuie sur tab: suivant*/
                                Backend.rechercher(search_nom.text , mainColumn.choix)
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
                    width: parent.width
                    height: parent.height - 30
                    clip: true

                    ListView {
                        id: liste_view
                        width: parent.width
                        height: parent.height
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
                    /*ListView pour la recherche: */
                }
            }
        }
    }
}

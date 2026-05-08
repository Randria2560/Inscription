#include <iostream>
#include "Backend.h"
#include <QFile>

#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>

#include <QTextStream>
#include <QDebug>

using namespace std;
QString fichier = "/home/natacha/monprojet/temporaire.csv";
QString fichier2 = "/home/natacha/monprojet/data_2.csv";

Backend::Backend(QObject *parent) : QObject(parent)
{
    // ✅ Au démarrage : copier fichier → fichier2 si fichier2 n'existe pas
    if (!QFile::exists(fichier2) && QFile::exists(fichier)) {
        QFile::copy(fichier, fichier2);
        qDebug() << "✅ Copie initiale : fichier → fichier2";
    }

    chargerFichier();
    emit listeChanged();
}

void Backend::chargerFichier()
{
    QFile file(fichier2);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Impossible d'ouvrir le fichier";
        return;
    }

    QTextStream in(&file);
    liste_personne.clear();

    while (!in.atEnd()) {
        QString ligne = in.readLine();
        QStringList parts = ligne.split(",");

        if (parts.size() == 8) {
            QString nom     = parts[0].trimmed();
            QString prenom  = parts[1].trimmed();
            QString sexe    = parts[2].trimmed();
            QString date    = parts[3].trimmed();
            QString lieu    = parts[4].trimmed();
            QString adresse = parts[5].trimmed();
            QString niveau  = parts[6].trimmed();
            QString filiere = parts[7].trimmed();

            Personne p(nom, prenom, sexe, date, lieu, adresse, niveau, filiere);
            liste_personne.append(p);
        }
    }

    file.close();
    qDebug() << "Chargement terminé. Total :" << liste_personne.size();
}

// ── Getters ───────────────────────────────────────────────────────
QStringList Backend::listeModel() const
{
    QStringList result;
    QVector<Personne> source;

    if (liste_personne_recherche.isEmpty()) {
        source = liste_personne;
    } else {
        source = liste_personne_recherche;
    }

    for (int i = 0; i < source.size(); ++i)
        result << QString("[%1]  %2  —  %3 - %4 - %5 - %6 - %7 - %8 - %9")
                      .arg(i)
                      .arg(source[i].getNom())
                      .arg(source[i].getPrenom())
                      .arg(source[i].getSexe())
                      .arg(source[i].getDateNaissance())
                      .arg(source[i].getLieuNaissance())
                      .arg(source[i].getAdresse())
                      .arg(source[i].getNiveau())
                      .arg(source[i].getFiliere());

    return result;
}

// ✅ CORRECTION : Sauvegarder dans fichier2 (travail temporaire)
void Backend::sauvegarderFichier()
{
    QFile f(fichier2);  // ✅ Sauvegarde dans fichier2
    if (!f.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Impossible d'écrire dans fichier2.";
        return;
    }

    QTextStream out(&f);
    // ✅ CORRECTION : Une seule boucle (pas de duplication)
    for (const Personne &p : liste_personne) {
        out << p.getNom() << "," << p.getPrenom() << "," << p.getSexe() << ","
            << p.getDateNaissance() << "," << p.getLieuNaissance() << ","
            << p.getAdresse() << "," << p.getNiveau() << ","
            << p.getFiliere() << "\n";
    }

    f.close();
    qDebug() << "✅ Fichier2 (travail temporaire) sauvegardé.";
}

// ── Ajouter à la fin ─────────────────────────────────────────────
void Backend::ajouter(const QString &nom, const QString &prenom, const QString &sexe,
                      const QString &date, const QString &lieu, const QString &adresse,
                      const QString &niveau, const QString &filiere)
{
    Personne p1 = Personne(nom, prenom, sexe, date, lieu, adresse, niveau, filiere);
    liste_personne.append(p1);
    cout << liste_personne.last().getNom().toStdString() << endl;


    sauvegarderFichier();
    emit listeChanged();
}

// ── Supprimer ─────────────────────────────────────────────────────
void Backend::supprimer(const QString &nom)
{
    for (int i = 0; i < liste_personne.size(); ++i) {
        if (liste_personne[i].getNom().toLower() == nom.toLower()) {
            liste_personne.removeAt(i);
            sauvegarderFichier();
            emit listeChanged();
            return;
        }
    }
}

void Backend::supprimer_all(const QString &nom)
{
    // ✅ Parcourir en sens inverse pour éviter les problèmes d'index
    for (int i = liste_personne.size() - 1; i >= 0; --i) {
        if (liste_personne[i].getNom().toLower() == nom.toLower()) {
            liste_personne.removeAt(i);
        }
    }
    sauvegarderFichier();
    emit listeChanged();
}

// ── Ajouter à une position ────────────────────────────────────────
void Backend::ajouter_position(const QString &nom, const QString &prenom, int pos)
{


    Personne p1 = Personne(nom, prenom);
    liste_personne.insert(liste_personne.begin() + pos, p1);

    sauvegarderFichier();
    emit listeChanged();


}

// ── Rechercher ────────────────────────────────────────────────────
void Backend::rechercher(const QString &val, const QString &choix)
{
    liste_personne_recherche.clear();

    for (int i = 0; i < liste_personne.size(); ++i) {
        if (choix == "Nom" && liste_personne[i].getNom() == val) {
            liste_personne_recherche.append(liste_personne[i]);
        }
        else if (choix == "Prenom" && liste_personne[i].getPrenom() == val) {
            liste_personne_recherche.append(liste_personne[i]);
        }
        else if (choix == "Sexe" && liste_personne[i].getSexe() == val) {
            liste_personne_recherche.append(liste_personne[i]);
        }
        else if (choix == "Date_Naissance" && liste_personne[i].getDateNaissance() == val) {
            liste_personne_recherche.append(liste_personne[i]);
        }
        else if (choix == "Lieu_Naissance" && liste_personne[i].getLieuNaissance() == val) {
            liste_personne_recherche.append(liste_personne[i]);
        }
        else if (choix == "Adresse" && liste_personne[i].getAdresse() == val) {
            liste_personne_recherche.append(liste_personne[i]);
        }
        else if (choix == "Niveau" && liste_personne[i].getNiveau() == val) {
            liste_personne_recherche.append(liste_personne[i]);
        }
        else if (choix == "Filiere" && liste_personne[i].getFiliere() == val) {
            liste_personne_recherche.append(liste_personne[i]);
        }
    }

    emit listeChanged();
}

// ✅ CORRECTION : À la fermeture, copier fichier2 → fichier
void Backend::enregistrement()
{
    // 1. Supprimer l'ancien fichier d'abord
    if (QFile::exists(fichier)) {
        QFile::remove(fichier);
        qDebug() << "Ancien fichier supprimé";
    }

    // 2. Copier fichier2 → fichier (sauvegarde finale)
    if (QFile::copy(fichier2, fichier)) {
        qDebug() << " Enregistrement final réussi : fichier2 → fichier";
    } else {
        qDebug() << " Erreur lors de la copie finale !";
    }
}

void Backend::ouvrir()
{
    QString filename = QFileDialog::getOpenFileName(
        nullptr,
        "Ouvrir le fichier",
        "/home/natacha/monprojet",
        "Fichier csv(*.csv);;Fichier txt(*.txt)"
        );

    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream flu(&file);
        QString contenu = flu.readAll();
        file.close();

       emit chargerPage(1);   // ← Changer vers page TextArea
       emit ajoutTexte(contenu);
    }

}




void Backend::save(const QString &text)
{
    QString filename= "/home/natacha/default.txt" ;
    QFile file(filename);

    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        out << text ;
        file.close();
        qDebug() << "Ok sauvegardé" << filename;
    }
    else{
        qDebug() <<  "Non svg" ;
    }

}

void Backend::save_as(const QString &text)
{
    QString filename = QFileDialog::getSaveFileName(
        nullptr,
        "Save as",
        "/home/natacha.monprojet",
        "Fichier csv(*.csv);;Fichier txt(*.txt)"
        );

    QFile file(filename);

    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        out << text ;
        file.close();
        qDebug() << "Ok sauvegardé" << filename;
    }
    else{
        qDebug() <<  "Non svg" ;
    }
}

void Backend::afficher(const QString &choix)
{
    QString texte= "Entrer votre " + choix;
    bool ok=true;
    if(choix == "nom" || choix== "prenom" || choix=="date" || choix == "lieu" || choix =="sexe" || choix=="adresse" || choix == "niveau" || choix=="filiere")
    {
        QString text = QInputDialog::getText(
            nullptr,
            "Modification:",
            texte,
            QLineEdit::Normal,
            "",
            &ok
        );
        if( ok && !text.isEmpty())
        {
            QMessageBox::information(nullptr,"Confirmation", "Valeur modifiée");
        }
        else{
            QMessageBox::warning(nullptr, "Alerte", "Champ Vide");
        }

        //modifier le texte et l'afficher dans le modalData et
    }

}

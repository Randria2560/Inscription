#include <iostream>
#include "Backend.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QDebug>

using namespace std;
QString fichier = "/home/natacha/monprojet/data.csv";
QString fichier2 = "/home/natacha/monproject/data_2.csv";

Backend::Backend(QObject *parent) : QObject(parent)
{
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

    liste_personne.clear(); // QVector<Personne> liste;

    while (!in.atEnd()) {
        QString ligne = in.readLine();
        QStringList parts = ligne.split(";");

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
    QVector <Personne> source;
    if (liste_personne_recherche.isEmpty())
    {
        source = liste_personne;
    }
    else
    {
        source = liste_personne_recherche ;
    }

    for (int i = 0; i < source.size(); ++i)
        result << QString("[%1]  %2  —  %3 - %4 - %5 -%6 - %7 -%8 -%9")
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


void Backend::sauvegarderFichier()
{
    QFile f(fichier);
    if (!f.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Impossible d'écrire dans le fichier.";
        return;
    }

    QTextStream out(&f);
    for (const Personne &p : liste_personne)
        out << p.getNom() << "," << p.getPrenom() << "," << p.getSexe() << "," << p.getDateNaissance() << "," << p.getLieuNaissance() << "," << p.getAdresse() << "," << p.getNiveau() << "," << p.getFiliere()<< "\n";

    f.close();
    qDebug() << "Fichier sauvegardé.";
}


// ── Ajouter à la fin ─────────────────────────────────────────────
void Backend::ajouter(const QString &nom, const QString &prenom, const QString &sexe , const QString &date, const QString &lieu, const QString &adresse, const QString &niveau, const QString &filiere )
{
    // 1. Vérifier D'ABORD
    /*if (nom.trimmed().isEmpty()) {
        setMessage("Erreur : nom vide.");
        return;
    }

    // 2. Vérifier les doublons
    for (const Personne &p : liste_personne) {
        if (p.getNom() == nom && p.getPassword() == password) {
            setMessage("Erreur : \"" + nom + "\" existe déjà.");
            return;
        }
    }*/

    // 3. Ajouter SEULEMENT si tout est bon
    Personne p1= Personne(nom,prenom, sexe ,date, lieu,adresse, niveau,filiere );

    liste_personne.append(p1);
    cout << liste_personne.last().getNom().toStdString() << endl;

    sauvegarderFichier();
    emit listeChanged();   /*ListView se rafraichit*/

}


// ── Supprimer ─────────────────────────────────────────────────────
void Backend::supprimer(const QString &nom)
{
    /*Ajouter une option si select all ou bien un seule à la fois*/

        for (int i = 0; i < liste_personne.size(); ++i) {
            if (liste_personne[i].getNom().toLower() == nom .toLower()) {
                liste_personne.removeAt(i);

                sauvegarderFichier();
                emit listeChanged();
                return;
            }
        }

}
void Backend::supprimer_all(const QString &nom)
{
    for (int i = 0; i < liste_personne.size(); ++i) {
        if (liste_personne[i].getNom().toLower() == nom.toLower()) {
            liste_personne.removeAt(i);
        }
    }
    sauvegarderFichier();
    emit listeChanged();

}

// ── Ajouter à une position ────────────────────────────────────────
void Backend::ajouter_position(const QString &nom,
                               const QString &prenom,
                               int pos)
{
    //trimmed() supprimer les espaces au début et à la fin:
    /*if (nom.trimmed().isEmpty()) {
        setMessage("Erreur : nom vide.");
        return;
    }*/

    /*for (const Personne &p : liste_personne) {
        if (p.getNom() == nom) {
            setMessage("Erreur : \"" + nom + "\" existe déjà.");
            return;
        }
    }*/
    Personne p1= Personne(nom,prenom );
    liste_personne.insert(liste_personne.begin()+pos, p1);

    //insertion
    emit listeChanged();

}

// ── Rechercher :
void Backend::rechercher(const QString &val, const QString &choix)
{
    liste_personne_recherche.clear();

    for (int i = 0; i < liste_personne.size(); ++i)
    {
        if (choix == "Nom")
        {
            if (liste_personne[i].getNom() == val)
                liste_personne_recherche.append(liste_personne[i]);
        }

        if (choix == "Prenom")
        {
            if (liste_personne[i].getPrenom() == val)
                liste_personne_recherche.append(liste_personne[i]);
        }

        if (choix == "Sexe")
        {
            if (liste_personne[i].getSexe() == val)
                liste_personne_recherche.append(liste_personne[i]);
        }

        if (choix == "Date_Naissance")
        {
            if (liste_personne[i].getDateNaissance() == val)
                liste_personne_recherche.append(liste_personne[i]);
        }

        if (choix == "Lieu_Naissance")
        {
            if (liste_personne[i].getLieuNaissance() == val)
                liste_personne_recherche.append(liste_personne[i]);
        }

        if (choix == "Adresse")
        {
            if (liste_personne[i].getAdresse() == val)
                liste_personne_recherche.append(liste_personne[i]);
        }

        if (choix == "Niveau")
        {
            if (liste_personne[i].getNiveau() == val)
                liste_personne_recherche.append(liste_personne[i]);
        }

        if (choix == "Filiere")
        {
            if (liste_personne[i].getFiliere() == val)
                liste_personne_recherche.append(liste_personne[i]);
        }
    }

    emit listeChanged();
}
void Backend::enregistrement()
{
    QFile f(fichier2);
    if (!f.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Impossible d'écrire dans le fichier2.";

    }

    //on remplace le fichier2 par fichier
    QFile::rename(fichier2, fichier);


    qDebug() << "Fichier2 sauvegardé.";

}

void Backend::ouvrir()
{

}
void Backend::save()
{

}
void Backend::save_as()
{

}

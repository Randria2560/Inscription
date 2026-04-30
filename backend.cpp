#include <iostream>
#include "backend.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

using namespace std;
QString fichier = "/home/natacha/monprojet/data.csv";

Backend::Backend(QObject *parent) : QObject(parent)
{
    chargerFichier();
    emit listeChanged();
}
void Backend::chargerFichier()
{
    QFile f(fichier);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Fichier introuvable, on repart de zéro.";
        return;
    }

    QTextStream in(&f);
    while (!in.atEnd()) {
        QString ligne = in.readLine().trimmed();
        //reconstruire le modèle
        if (ligne.isEmpty()) continue;

        QStringList parts = ligne.split(",");
        if (parts.size() >= 2) {
            QString nom      = parts[0].trimmed();
            QString password = parts[1].trimmed();
            liste_personne.append(Personne(nom, password));
        }
    }
    f.close();
    qDebug() << "Fichier chargé :" << liste_personne.size() << "personnes.";
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
        result << QString("[%1]  %2  —  %3")
                      .arg(i)
                      .arg(source[i].getNom())
                      .arg(source[i].getPassword());
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
        out << p.getNom() << "," << p.getPassword() << "\n";

    f.close();
    qDebug() << "Fichier sauvegardé.";
}


// ── Ajouter à la fin ──────────────────────────────────────────────
void Backend::ajouter(const QString &nom, const QString &password)
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
    liste_personne.append(Personne(nom, password));
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
        if (liste_personne[i].getNom().toLower() == nom .toLower()) {
            liste_personne.removeAt(i);
        }
    }
    sauvegarderFichier();
    emit listeChanged();

}

// ── Ajouter à une position ────────────────────────────────────────
void Backend::ajouter_position(const QString &nom,
                               const QString &password,
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
    Personne p = Personne (nom, password);
    liste_personne.insert(liste_personne.begin()+pos, p);

    //insertion
    emit listeChanged();

}

// ── Rechercher :
void Backend::rechercher(const QString &nom)
{
    /*nouveau fichier*/
    /*quand on clique sur suivant: tab*/

    liste_personne_recherche.clear();
    //sauvegarde dans un autre  fichier
    for (int i = 0; i < liste_personne.size(); ++i) {
        if (liste_personne[i].getNom() == nom) {
            liste_personne_recherche.append(liste_personne[i]);
        }
    }
    emit listeChanged();
    liste_personne_recherche.clear();

}

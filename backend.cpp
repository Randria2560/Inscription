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
    for (int i = 0; i < liste_personne.size(); ++i)
        result << QString("[%1]  %2  —  %3")
                      .arg(i)
                      .arg(liste_personne[i].getNom())
                      .arg(liste_personne[i].getPassword()); // ← ajouter le password
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

QString Backend::message() const
{
    return m_message;
}

// ── Ajouter à la fin ──────────────────────────────────────────────
void Backend::ajouter(const QString &nom, const QString &password)
{
    // 1. Vérifier D'ABORD
    if (nom.trimmed().isEmpty()) {
        setMessage("Erreur : nom vide.");
        return;
    }

    // 2. Vérifier les doublons
    for (const Personne &p : liste_personne) {
        if (p.getNom() == nom && p.getPassword() == password) {
            setMessage("Erreur : \"" + nom + "\" existe déjà.");
            return;
        }
    }

    // 3. Ajouter SEULEMENT si tout est bon
    liste_personne.append(Personne(nom, password));
    cout << liste_personne.last().getNom().toStdString() << endl;


    sauvegarderFichier();
    emit listeChanged();   /*ListView se rafraichit*/
    /* et affichage dans liste_scroll_bar*/
    setMessage("OK : \"" + nom + "\" ajouté.");
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

                setMessage("OK : \"" + nom + "\" supprimé.");
                return;
            }
        }
    setMessage("Erreur : \"" + nom + "\" introuvable.");
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
    setMessage("Erreur : \"" + nom + "\" introuvable.");
}

// ── Ajouter à une position ────────────────────────────────────────
void Backend::ajouter_position(const QString &nom,
                               const QString &password,
                               int pos)
{
    //trimmed() supprimer les espaces au début et à la fin:
    if (nom.trimmed().isEmpty()) {
        setMessage("Erreur : nom vide.");
        return;
    }

    for (const Personne &p : liste_personne) {
        if (p.getNom() == nom) {
            setMessage("Erreur : \"" + nom + "\" existe déjà.");
            return;
        }
    }
    Personne p = Personne (nom, password);
    liste_personne.insert(liste_personne.begin()+pos, p);

    //insertion
    emit listeChanged();


   /* setMessage("OK : \"" + nom + "\" inséré à la position "
               + QString::number(index) + ".");*/
}

// ── Rechercher ────────────────────────────────────────────────────
void Backend::rechercher(const QString &nom)
{
    for (int i = 0; i < liste_personne.size(); ++i) {
        if (liste_personne[i].getNom() == nom) {
            setMessage("OK : \"" + nom + "\" trouvé à la position "
                       + QString::number(i) + ".");
            return;
        }
    }
    setMessage("Erreur : \"" + nom + "\" introuvable.");
}

// ── Utilitaire privé ──────────────────────────────────────────────
void Backend::setMessage(const QString &msg)
{
    m_message = msg;
    emit messageChanged();
}

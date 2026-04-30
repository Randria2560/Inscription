#include "backend.h"
#include <iostream>
using namespace std;

Backend::Backend(QObject *parent) : QObject(parent)
{
}

// ── Getters ───────────────────────────────────────────────────────
QStringList Backend::listeModel() const
{
    QStringList result;
    for (int i = 0; i < liste_personne.size(); ++i)
        result << QString("[%1]  %2").arg(i).arg(liste_personne[i].getNom());
    return result;
}

QString Backend::message() const
{
    return m_message;
}

// ── Ajouter à la fin ──────────────────────────────────────────────
void Backend::ajouter(const QString &nom, const QString &password)
{
        cout << nom.toStdString() << endl;
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

    liste_personne.append(Personne(nom, password));

    emit listeChanged();

    setMessage("OK : \"" + nom + "\" ajouté.");
}

// ── Supprimer ─────────────────────────────────────────────────────
void Backend::supprimer(const QString &nom)
{
    for (int i = 0; i < liste_personne.size(); ++i) {
        if (liste_personne[i].getNom() == nom) {
            liste_personne.removeAt(i);
            emit listeChanged();
            setMessage("OK : \"" + nom + "\" supprimé.");
            return;
        }
    }
    setMessage("Erreur : \"" + nom + "\" introuvable.");
}

// ── Ajouter à une position ────────────────────────────────────────
void Backend::ajouter_position(const QString &nom,
                               const QString &password,
                               int pos)
{
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

    int index = qBound(0, pos, liste_personne.size());
    liste_personne.insert(index, Personne(nom, password));
    emit listeChanged();
    setMessage("OK : \"" + nom + "\" inséré à la position "
               + QString::number(index) + ".");
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

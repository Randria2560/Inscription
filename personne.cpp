#include "personne.h"

Personne::Personne(const QString &nom, const QString &password)
    : m_nom(nom), m_password(password)
{}

QString Personne::getNom()      const { return m_nom; }
QString Personne::getPassword() const { return m_password; }
void Personne::setNom(const QString &nom)           { m_nom = nom; }
void Personne::setPassword(const QString &password) { m_password = password; }

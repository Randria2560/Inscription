#include "Personne.h"

Personne::Personne(const QString &nom, const QString &prenom, const QString &sexe , const QString &date, const QString &lieu, const QString &adresse, const QString &niveau, const QString &filiere )
    : m_nom(nom), m_prenom(prenom), m_sexe(sexe), m_date(date), m_lieu(lieu), m_adresse(adresse), m_niveau(niveau), m_filiere(filiere)
{

}

Personne::Personne(const QString &nom, const QString &prenom)
{

}
QString Personne:: getNom()      const
{
    return m_nom;
}
QString Personne:: getPrenom() const
{
    return m_prenom;
}
QString Personne:: getSexe()      const
{
    return m_sexe;
}
QString Personne:: getDateNaissance() const
{
    return m_date;
}
QString Personne:: getLieuNaissance()      const
{
    return m_lieu;
}
QString Personne:: getAdresse() const
{
    return m_adresse;
}
QString Personne:: getNiveau() const
{
    return m_niveau;
}
QString Personne:: getFiliere() const
{
    return m_filiere;
}



void Personne:: setNom(const QString &nom)
{
    m_nom=nom;
}
void Personne:: setPrenom(const QString &prenom)
{
    m_prenom=prenom;
}
void Personne:: setSexe(const QString &sexe)
{
    m_sexe=sexe;
}
void Personne:: setDateNaissance(const QString &date)
{
    m_date=date;
}
void Personne:: setLieuNaissance(const QString &lieu)
{
    m_lieu=lieu;
}
void Personne:: setAdresse(const QString &adresse)
{
    m_adresse=adresse;
}
void Personne:: setNiveau(const QString &niveau)
{
    m_niveau=niveau;
}
void Personne:: setFiliere(const QString &filiere)
{
    m_filiere=filiere;
}

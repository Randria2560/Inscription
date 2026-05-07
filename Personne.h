#ifndef PERSONNE_H
#define PERSONNE_H

#include <QString>

class Personne
{
public:
    Personne(const QString &nom, const QString &prenom, const QString &sexe , const QString &date, const QString &lieu, const QString &adresse, const QString &niveau, const QString &filiere );
    Personne(const QString &nom, const QString &prenom);
    QString getNom()      const;
    QString getPrenom() const;
    QString getSexe()      const;
    QString getDateNaissance() const;
    QString getLieuNaissance()      const;
    QString getAdresse() const;
    QString getNiveau() const;
    QString getFiliere() const;



    void setNom(const QString &nom);
    void setPrenom(const QString &prenom);
    void setSexe(const QString &sexe);
    void setDateNaissance(const QString &date);
    void setLieuNaissance(const QString &lieu);
    void setAdresse(const QString &adresse);
    void setNiveau(const QString &niveau);
    void setFiliere(const QString &filiere);


private:
    QString m_nom;
    QString m_prenom;
    QString m_sexe;
    QString m_date;
    QString m_lieu;
    QString m_adresse;
    QString m_niveau;
    QString m_filiere;

};

#endif

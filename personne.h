#ifndef PERSONNE_H
#define PERSONNE_H

#include <QString>

class Personne
{
public:
    Personne(const QString &nom, const QString &password);

    QString getNom()      const;
    QString getPassword() const;
    void setNom(const QString &nom);
    void setPassword(const QString &password);

private:
    QString m_nom;
    QString m_password;
};

#endif

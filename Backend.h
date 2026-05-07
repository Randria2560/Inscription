#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QVector>
#include "Personne.h"

class Backend : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QStringList listeModel
                   READ listeModel
                       NOTIFY listeChanged)

public:
    explicit Backend(QObject *parent = nullptr);

    /*si supprimer, message de confirmation et enregistrer dans le fichier:*/

    void sauvegarderFichier();
    void chargerFichier();
    QStringList listeModel() const;
    void enregistrement();


public slots:
    //recharger d'abord le fichier dans la liste

    Q_INVOKABLE void ajouter(const QString &nom, const QString &prenom, const QString &sexe , const QString &date, const QString &lieu, const QString &adresse, const QString &niveau, const QString &filiere );
    Q_INVOKABLE void supprimer(const QString &nom);
     Q_INVOKABLE void supprimer_all(const QString &nom);

    Q_INVOKABLE void ajouter_position(const QString &nom,
                                      const QString &personne,
                                      int pos);

    Q_INVOKABLE void rechercher(const QString &val, const QString &choix);


    /*File==================*/
    Q_INVOKABLE void ouvrir();
    Q_INVOKABLE void save_as();
    Q_INVOKABLE void save();


signals:
    void listeChanged();

private:
    QVector<Personne> liste_personne;
    QString           m_message;
    QVector<Personne> liste_personne_recherche;

};

#endif

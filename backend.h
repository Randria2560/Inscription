#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QVector>
#include "personne.h"

class Backend : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QStringList listeModel
                   READ listeModel
                       NOTIFY listeChanged)

public:
    explicit Backend(QObject *parent = nullptr);

    void sauvegarderFichier();
    void chargerFichier();
    QStringList listeModel() const;


public slots:
    //recharger d'abord le fichier dans la liste

    Q_INVOKABLE void ajouter(const QString &nom, const QString &password);
    Q_INVOKABLE void supprimer(const QString &nom);
     Q_INVOKABLE void supprimer_all(const QString &nom);

    Q_INVOKABLE void ajouter_position(const QString &nom,
                                      const QString &password,
                                      int pos);
    Q_INVOKABLE void rechercher(const QString &nom);

signals:
    void listeChanged();

private:
    QVector<Personne> liste_personne;
    QString           m_message;
    QVector<Personne> liste_personne_recherche;

};

#endif

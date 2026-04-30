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

    Q_PROPERTY(QString message
                   READ message
                       NOTIFY messageChanged)

public:
    explicit Backend(QObject *parent = nullptr);

    QStringList listeModel() const;
    QString     message()    const;

public slots:
    Q_INVOKABLE void ajouter(const QString &nom, const QString &password);
    Q_INVOKABLE void supprimer(const QString &nom);
    Q_INVOKABLE void ajouter_position(const QString &nom,
                                      const QString &password,
                                      int pos);
    Q_INVOKABLE void rechercher(const QString &nom);

signals:
    void listeChanged();
    void messageChanged();

private:
    QVector<Personne> liste_personne;
    QString           m_message;

    void setMessage(const QString &msg);
};

#endif

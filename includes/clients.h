#ifndef CLIENTS_H
#define CLIENTS_H

#include <QSqlTableModel>
#include <QSqlRecord>
#include "basededonnees.h"

class Clients
{
public:
    Clients();
    QSqlTableModel *model(QWidget *parent, BaseDeDonnees *bdd);
    QSqlRecord modelRecord();
    bool ajouter();
    QModelIndex selDernier();
    bool sauvegarder(const QSqlRecord record, const int rowId);
    int nbr();
    QString getDonnees(const int rowId, const int valueId);
    bool supprimer(const int rowId);
    bool filtreCat(const int catId);

private:
    BaseDeDonnees *baseDeDonnees;
    QSqlTableModel *tableModel;
};

#endif // CLIENTS_H

#ifndef PRESTATIONS_H
#define PRESTATIONS_H

#include <QSqlTableModel>
#include <QSqlRecord>
#include "basededonnees.h"

class Prestations
{
public:
    Prestations();
    QSqlTableModel *model(QWidget *parent, BaseDeDonnees *bdd);
    QSqlRecord modelRecord();
    bool ajouter();
    QModelIndex selDernier();
    bool sauvegarder(const QSqlRecord record, const int rowId);
    int nbr();
    QString getDonnees(const int rowId, const int valueId);
    bool supprimer(const int rowId);

private:
    BaseDeDonnees *baseDeDonnees;
    QSqlTableModel *tableModel;
};

#endif // PRESTATIONS_H

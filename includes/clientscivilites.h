#ifndef CLIENTSCIVILITES_H
#define CLIENTSCIVILITES_H

#include <QSqlTableModel>
#include "includes/basededonnees.h"

class ClientsCivilites
{
    public:
        ClientsCivilites();
        QSqlTableModel *model(QWidget *parent, BaseDeDonnees *baseDeDonnees);
        QSqlRecord modelRecord();
        QString getDonnee(const int rowId, const int valueId);

    private:
        BaseDeDonnees *baseDeDonnees;
        QSqlTableModel *tableModel;
};

#endif // CLIENTSCIVILITES_H

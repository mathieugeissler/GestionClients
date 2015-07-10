#ifndef PROJETS_H
#define PROJETS_H

#include <QSqlTableModel>
#include <QSqlRecord>
#include "basededonnees.h"

class Projets
{

public:
    Projets();
    QSqlTableModel *model(QWidget *parent, BaseDeDonnees *bdd);

private:
    BaseDeDonnees *baseDeDonnees;
    QSqlTableModel *tableModel;
};

#endif // PROJETS_H

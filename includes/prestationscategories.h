#ifndef PRESTATIONSCATEGORIES_H
#define PRESTATIONSCATEGORIES_H

#include <QSqlTableModel>
#include "includes/basededonnees.h"

class PrestationsCategories
{
public:
    PrestationsCategories();
    QSqlTableModel *model(QWidget *parent, BaseDeDonnees *baseDeDonnees);
    QSqlRecord modelRecord();

private:
    BaseDeDonnees *baseDeDonnees;
    QSqlTableModel *tableModel;
};

#endif // PRESTATIONSCATEGORIES_H

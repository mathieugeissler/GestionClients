#include "prestationscategories.h"

PrestationsCategories::PrestationsCategories()
{

}

QSqlTableModel * PrestationsCategories::model(QWidget *parent, BaseDeDonnees *baseDeDonnees)
{
    tableModel = new QSqlTableModel(parent, baseDeDonnees->getBase());
    tableModel->setTable("presta_categorie");
    tableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tableModel->select();
    tableModel->setHeaderData(0, Qt::Horizontal, "id");
    tableModel->setHeaderData(1, Qt::Horizontal, "Catégorie");
    tableModel->setHeaderData(2, Qt::Horizontal, "Déscription");
    return tableModel;
}

QString PrestationsCategories::getDonnee(const int rowId, const int valueId)
{
    return tableModel->record(rowId).value(valueId).toString();
}

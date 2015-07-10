#include "projets.h"

Projets::Projets()
{

}

QSqlTableModel * Projets::model(QWidget *parent, BaseDeDonnees *baseDeDonnees)
{
    tableModel = new QSqlTableModel(parent, baseDeDonnees->getBase());
    tableModel->setTable("projets");
    tableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tableModel->select();
    tableModel->setHeaderData(0, Qt::Horizontal, "Numéro projet");
    tableModel->setHeaderData(1, Qt::Horizontal, "Nom projet");
    tableModel->setHeaderData(2, Qt::Horizontal, "Numéro client");
    tableModel->setHeaderData(3, Qt::Horizontal, "Numéros prestations");
    tableModel->setHeaderData(4, Qt::Horizontal, "Total ht");
    tableModel->setHeaderData(5, Qt::Horizontal, "Date de création");
    tableModel->setHeaderData(6, Qt::Horizontal, "Date limite");
    tableModel->setHeaderData(7, Qt::Horizontal, "Projet validé");
    return tableModel;
}

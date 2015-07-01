#include "prestations.h"

Prestations::Prestations()
{

}

QSqlTableModel * Prestations::model(QWidget *parent, BaseDeDonnees *baseDeDonnees)
{
    tableModel = new QSqlTableModel(parent, baseDeDonnees->getBase());
    tableModel->setTable("presta");
    tableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tableModel->select();
    tableModel->setHeaderData(0, Qt::Horizontal, "Numéro");
    tableModel->setHeaderData(1, Qt::Horizontal, "Nom");
    tableModel->setHeaderData(2, Qt::Horizontal, "Catégorie");
    tableModel->setHeaderData(3, Qt::Horizontal, "Description");
    tableModel->setHeaderData(4, Qt::Horizontal, "Prix unitaire");
    return tableModel;

}

int Prestations::nbr()
{
        QSqlQuery query("SELECT MAX(presta_id) FROM presta");
        if(!query.exec())
        {
            qDebug() << "EREUR recup nbr presta";
        }
        else
        {
        while (query.next())
        {
            return query.value(0).toInt();
        }
        }
        return 0;
}

bool Prestations::ajouter()
{
    if(tableModel->insertRow(tableModel->rowCount()))
    {
        return true;
    }
return false;
}

QModelIndex Prestations::selDernier()
{
    return tableModel->index(tableModel->rowCount()-1, 4);
}

QSqlRecord Prestations::modelRecord()
{
    return tableModel->record();
}

bool Prestations::sauvegarder(const QSqlRecord record, const int rowId)
{
    bool insert = tableModel->setRecord(rowId, record);
    bool submit = tableModel->submitAll();

    if(!insert || !submit)
    {
        qDebug() << tableModel->lastError().text();
        return false;
    }
    else
    {
        return true;
    }
}

QString Prestations::getDonnees(const int rowId, const int valueId)
{
    return tableModel->record(rowId).value(valueId).toString();
}

bool Prestations::supprimer(const int rowId)
{
    tableModel->removeRow(rowId);

    if(tableModel->submitAll())
    {
        tableModel->database().commit();
        return true;
    }
    else
    {
       tableModel->database().rollback();
        return false;
    }
}

bool Prestations::filtreCat(const int catId)
{
    if(catId == 0)
    {
        tableModel->setFilter("presta_cat != -1");
    }
    else
    {
      tableModel->setFilter(QString("presta_cat = %0").arg(catId));
    }
    if(tableModel->submitAll())
    {
        return true;
    }
    return false;
}

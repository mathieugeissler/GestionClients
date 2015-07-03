#include "clients.h"

Clients::Clients()
{
}

QSqlTableModel * Clients::model(QWidget *parent, BaseDeDonnees *baseDeDonnees)
{
    tableModel = new QSqlTableModel(parent, baseDeDonnees->getBase());
    tableModel->setTable("clients");
    tableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tableModel->select();
    tableModel->setHeaderData(0, Qt::Horizontal, "Numéro");
    tableModel->setHeaderData(1, Qt::Horizontal, "Entité");
    tableModel->setHeaderData(2, Qt::Horizontal, "Civilité");
    tableModel->setHeaderData(3, Qt::Horizontal, "Nom");
    tableModel->setHeaderData(4, Qt::Horizontal, "Prénom");
    tableModel->setHeaderData(5, Qt::Horizontal, "Adresse");
    tableModel->setHeaderData(6, Qt::Horizontal, "CP");
    tableModel->setHeaderData(7, Qt::Horizontal, "Ville");
    tableModel->setHeaderData(8, Qt::Horizontal, "Mail");
    tableModel->setHeaderData(9, Qt::Horizontal, "Téléphone 1");
    tableModel->setHeaderData(10, Qt::Horizontal, "Téléphone 2");
    tableModel->setHeaderData(11, Qt::Horizontal, "Site web");
    tableModel->setHeaderData(12, Qt::Horizontal, "Description");
    tableModel->setHeaderData(13, Qt::Horizontal, "Numéro Siret");
    return tableModel;
}

int Clients::nbr()
{
        QSqlQuery query("SELECT MAX(clients_id) FROM clients");
        if(!query.exec())
        {
            qDebug() << "ERREUR recup nbr clients";
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

bool Clients::ajouter()
{
    if(tableModel->insertRow(tableModel->rowCount()))
    {
        return true;
    }
return false;
}

QModelIndex Clients::selDernier()
{
    return tableModel->index(tableModel->rowCount()-1, 0);
}

QSqlRecord Clients::modelRecord()
{
    return tableModel->record();
}

bool Clients::sauvegarder(const QSqlRecord record, const int rowId)
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

QString Clients::getDonnees(const int rowId, const int valueId)
{
    return tableModel->record(rowId).value(valueId).toString();
}

bool Clients::supprimer(const int rowId)
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

bool Clients::filtreCat(const int catId)
{
    if(catId == 0)
    {
        tableModel->setFilter("clients_civilite != -1");
    }
    else
    {
      tableModel->setFilter(QString("clients_civilite = %0").arg(catId));
    }
    if(tableModel->submitAll())
    {
        return true;
    }
    return false;
}

#include "basededonnees.h"

BaseDeDonnees::BaseDeDonnees()
{

}

void BaseDeDonnees::coBDD()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setPort(3306);
    db.setUserName("root");
    db.setPassword("root");
    db.setDatabaseName("gestionclients");

    if(!db.open())
    {
        qDebug() << "pas de connection à la bdd : " << db.lastError().text();
    }
}

QSqlDatabase BaseDeDonnees::getBase()
{
    return QSqlDatabase::database();
}

bool BaseDeDonnees::estConnecte()
{
    if(db.isOpen())
    {
        return true;
    }
    return false;
}

int BaseDeDonnees::nbrClients()
{
        QSqlQuery query("SELECT MAX(clients_id) FROM clients");
        if(!query.exec())
        {
            qDebug() << "EREUR recup nbr clients";
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

QSqlTableModel * BaseDeDonnees::tableModelClients(QWidget *parent)
{
    modelClients = new QSqlTableModel(parent, QSqlDatabase::database());
    modelClients->setTable("clients");
    modelClients->setEditStrategy(QSqlTableModel::OnManualSubmit);
    modelClients->select();
    modelClients->setHeaderData(0, Qt::Horizontal, "Numéro");
    modelClients->setHeaderData(1, Qt::Horizontal, "Entité");
    modelClients->setHeaderData(2, Qt::Horizontal, "Civilité");
    modelClients->setHeaderData(3, Qt::Horizontal, "Nom");
    modelClients->setHeaderData(4, Qt::Horizontal, "Prénom");
    modelClients->setHeaderData(5, Qt::Horizontal, "Adresse");
    modelClients->setHeaderData(6, Qt::Horizontal, "CP");
    modelClients->setHeaderData(7, Qt::Horizontal, "Ville");
    modelClients->setHeaderData(8, Qt::Horizontal, "Mail");
    modelClients->setHeaderData(9, Qt::Horizontal, "Téléphone 1");
    modelClients->setHeaderData(10, Qt::Horizontal, "Téléphone 2");
    modelClients->setHeaderData(11, Qt::Horizontal, "Site web");
    modelClients->setHeaderData(12, Qt::Horizontal, "Description");
    modelClients->setHeaderData(13, Qt::Horizontal, "Numéro Siret");
    return modelClients;
}

QString BaseDeDonnees::getDonneesClient(int rowId, int valueId)
{
    return modelClients->record(rowId).value(valueId).toString();
}

bool BaseDeDonnees::supprClient(int rowId)
{
    modelClients->removeRow(rowId);

    if(modelClients->submitAll())
    {
        modelClients->database().commit();
        return true;
    }
    else
    {
        modelClients->database().rollback();
        return false;
    }
}

bool BaseDeDonnees::ajouterClient(const QSqlRecord record)
{
    modelClients->insertRow(modelClients->rowCount());

   bool insert = modelClients->setRecord(modelClients->rowCount()-1, record);
   bool submit = modelClients->submitAll();

    if(!insert || !submit)
    {
        qDebug() << modelClients->lastError().text();
        return false;
    }
    else
    {
        return true;
    }
}

bool BaseDeDonnees::modifierClient(const QSqlRecord record, const int rowId)
{
    bool insert = modelClients->setRecord(rowId, record);
    bool submit = modelClients->submitAll();

    if(!insert || !submit)
    {
        qDebug() << modelClients->lastError().text();
        return false;
    }
    else
    {
        return true;
    }
}

QSqlRecord BaseDeDonnees::modelRecordClient()
{
    return modelClients->record();
}

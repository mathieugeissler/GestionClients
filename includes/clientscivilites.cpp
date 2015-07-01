#include "clientscivilites.h"

ClientsCivilites::ClientsCivilites()
{

}

QSqlTableModel * ClientsCivilites::model(QWidget *parent, BaseDeDonnees *baseDeDonnees)
{
    tableModel = new QSqlTableModel(parent, baseDeDonnees->getBase());
    tableModel->setTable("clients_civilite");
    tableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tableModel->select();
    tableModel->setHeaderData(0, Qt::Horizontal, "id");
    tableModel->setHeaderData(1, Qt::Horizontal, "Civilité");
    return tableModel;
}

QString ClientsCivilites::getDonnee(const int rowId, const int valueId)
{
    return tableModel->record(rowId).value(valueId).toString();
}

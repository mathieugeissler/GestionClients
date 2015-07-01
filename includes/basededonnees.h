#ifndef BASEDEDONNEES_H
#define BASEDEDONNEES_H

#include <QtSql>
#include <QSqlDatabase>
#include <QDebug>

class BaseDeDonnees
{

public:
   BaseDeDonnees();
   void coBDD();
   bool estConnecte();
   int nbrClients();
   QSqlTableModel *tableModelClients(QWidget *parent);
   QString getDonneesClient(int rowId, int valueId);
   bool supprClient(int rowId);
   bool ajouterClient(const QSqlRecord record);
   bool modifierClient(const QSqlRecord record, const int rowId);
   QSqlRecord modelRecordClient();
   QSqlDatabase getBase();

private:
   QSqlDatabase db;
   QSqlTableModel *modelClients;

};

#endif // BASEDEDONNEES_H

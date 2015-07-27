#ifndef ONGLETS_H
#define ONGLETS_H

#include <QtWidgets>
#include "includes/basededonnees.h"
#include "includes/clientscivilites.h"
#include "includes/clients.h"
#include "includes/prestations.h"
#include "includes/prestationscategories.h"
#include "includes/projets.h"
#include "includes/projettablemodel.h"
#include "includes/spinboxdelegate.h"

class Onglets : QWidget
{
    Q_OBJECT

public:
    Onglets(BaseDeDonnees *bdd, bool nvProjet, int id);
    QWidget *ouvrir();

private:
    void creerSelClient();
    void creerSelPresta();
    void creerTotal();
    void creerLayout();

private slots:
    void clientsCivChange(int indexId);
    void prestaCatChange(int indexId);
    void ajouterPresta();
    void quantiteChange(QWidget *widget);
    void prestaSuppr();

private:
    QWidget *parent;
    BaseDeDonnees *baseDeDonnees;
    int idProjet;
    ProjetTableModel *tableModel;
    ClientsCivilites *clientsCivilites;
    Clients *clients;
    PrestationsCategories *prestaCategories;
    Prestations *prestations;
    Projets *projets;
    QVBoxLayout *layoutPrincipal;
    QComboBox *clientCbbCiv;
    QComboBox *clientCbbNom;
    QComboBox *prestaCbbCat;
    QComboBox *prestaCbbNom;
    QGroupBox *clientGroupBox;
    QGroupBox *prestaGroupBox;
    QGroupBox *totalGroupBox;
    QTableWidget *prestaTableau;
    int rowSelect;
    int colSelect;
};

#endif // ONGLETS_H

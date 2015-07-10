#ifndef ONGLETS_H
#define ONGLETS_H

#include <QtWidgets>
#include "includes/basededonnees.h"
#include "includes/clientscivilites.h"
#include "includes/clients.h"
#include "includes/prestations.h"
#include "includes/prestationscategories.h"
#include "includes/projets.h"

class Onglets : QWidget
{
    Q_OBJECT

public:
    Onglets(BaseDeDonnees *bdd, bool nvProjet, int idProjet);
    QWidget *ouvrir();

private:
    void creerSelClient();
    void creerSelPresta();
    void creerTotal();
    void creerLayout();

private slots:
    void clientsCivChange(int indexId);
    void prestaCatChange(int indexId);

private:
    QWidget *parent;
    BaseDeDonnees *baseDeDonnees;
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
};

#endif // ONGLETS_H

#ifndef WIDGETCLIENTS_H
#define WIDGETCLIENTS_H

#include <QtWidgets>
#include "includes/basededonnees.h"
#include "includes/clientscivilites.h"
#include "includes/clients.h"

class WidgetClients : QWidget
{   
    Q_OBJECT

public:
    WidgetClients(QMainWindow *parent, BaseDeDonnees *bdd);
    void ouvrir();

private:
    void creerTableau();
    void creerActions();
    void creerToolBar();
    void creerCivilites();
    void creerLayout();
    void viderFormulaire();
    bool ligneEstSelectionnee();
    void desactiverForm(const bool ok);
    void nvIdClient();
    bool verifForm();
    void chargerForm();

private slots:
    void sauvClient();
    void ajouterClient();
    void supprClient();
    void clientsCivChange(int indexId);
    void idChange(QItemSelection nvId, QItemSelection ancienId);
    void entiteChange(int);

private:
    QMainWindow *parent;
    BaseDeDonnees *baseDeDonnees;
    QWidget *widget;
    QToolBar *toolBar;
    Clients *clients;
    ClientsCivilites *clientsCivilites;
    QComboBox *cbbCivilites;
    QTreeView *tableau;
    QAction *actionSauvClient;
    QAction *actionAjouterClient;
    QAction *actionSupprClient;
    QGroupBox *groupBox;
    QCheckBox *editEntite;
    QLineEdit *editNom;
    QComboBox *editCiv;
    QLineEdit *editPrenom;
    QLineEdit *editAdresse;
    QLineEdit *editCP;
    QLineEdit *editVille;
    QLineEdit *editTel1;
    QLineEdit *editTel2;
    QLineEdit *editMail;
    QLineEdit *editSiteWeb;
    QTextEdit *editDesc;
    QLineEdit *editSiret;
    int rowId;
    int idClient;
};

#endif // WIDGETCLIENTS_H

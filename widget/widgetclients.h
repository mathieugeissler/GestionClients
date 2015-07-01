#ifndef WIDGETCLIENTS_H
#define WIDGETCLIENTS_H

#include <QtWidgets>
#include "includes/basededonnees.h"
#include "includes/clientscivilites.h"
#include "fenetreeditionclient.h"

class WidgetClients : QWidget
{   
    Q_OBJECT

public:
    WidgetClients(QMainWindow *parent, BaseDeDonnees *bdd);
    void ouvrir();
    void fermer();

private:
    void creerTableau();
    void creerActions();
    void creerToolBar();
    void creerCivilites();

private slots:
    void editerClient();
    void ajouterClient();
    void supprClient();
    void clientsCivChange(int indexId);

private:
    QMainWindow *parent;
    BaseDeDonnees *baseDeDonnees;
    QWidget *widget;
    QToolBar *toolBar;
    ClientsCivilites *clientsCivilites;
    QComboBox *cbbCivilites;
    QTreeView *tableau;
    QAction *actionEditerClient;
    QAction *actionAjouterClient;
    QAction *actionSupprClient;
};

#endif // WIDGETCLIENTS_H

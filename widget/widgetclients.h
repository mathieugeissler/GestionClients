#ifndef WIDGETCLIENTS_H
#define WIDGETCLIENTS_H

#include <QtWidgets>
#include "includes/basededonnees.h"
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

private slots:
    void editerClient();
    void ajouterClient();
    void supprClient();

private:
    QMainWindow *parent;
    BaseDeDonnees *baseDeDonnees;
    QWidget *widget;
    QToolBar *toolBar;
    QTreeView *tableau;
    QAction *actionEditerClient;
    QAction *actionAjouterClient;
    QAction *actionSupprClient;
};

#endif // WIDGETCLIENTS_H

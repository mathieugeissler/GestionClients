#ifndef WIDGETPROJETS_H
#define WIDGETPROJETS_H

#include <QtWidgets>
#include "includes/basededonnees.h"

class WidgetProjets : public QWidget
{
public:
    WidgetProjets(QMainWindow *parent, BaseDeDonnees *bdd);
    void ouvrir();
private :
    void creerToolBar();
    void creerAction();
    void creerOnglets();
    void creerTableau();

private:
    QMainWindow *parent;
    BaseDeDonnees *baseDeDonnees;
    QWidget *widget;
    QAction *actionOuvrirProjet;
    QAction *actionFermerTous;
    QAction *actionAjouterProjet;
    QAction *actionSauvTous;
    QAction *actionSupprProjet;
    QToolBar *toolBar;
    QTabWidget *onglets;
    QWidget *ongletPrincipal;
    QTreeView *tableau;
};

#endif // WIDGETPROJETS_H

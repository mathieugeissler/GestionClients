#ifndef WIDGETPROJETS_H
#define WIDGETPROJETS_H

#include <QtWidgets>
#include "includes/basededonnees.h"
#include "includes/projets.h"
#include "widget/onglets.h"


class WidgetProjets : public QWidget
{
    Q_OBJECT

public:
    WidgetProjets(QMainWindow *parent, BaseDeDonnees *bdd);
    QWidget *ouvrir();

private :
    void creerToolBar();
    void creerAction();
    void creerOnglets();
    void creerTableau();

private slots :
    void ajouterProjet();

private:
    QMainWindow *parent;
    BaseDeDonnees *baseDeDonnees;
    QWidget *widgetProjets;
    QAction *actionOuvrirProjet;
    QAction *actionFermerTous;
    QAction *actionAjouterProjet;
    QAction *actionSauvTous;
    QAction *actionSupprProjet;
    QToolBar *toolBar;
    QTabWidget *onglets;
    QWidget *ongletPrincipal;
    QTreeView *tableau;
    Projets *projets;
};

#endif // WIDGETPROJETS_H

#ifndef WIDGETPROJETS_H
#define WIDGETPROJETS_H

#include <QtWidgets>
#include "includes/basededonnees.h"

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

    QWidget *ajouterNvlOnglet(const bool nvProjet, const int idProjet = 0);

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
};

#endif // WIDGETPROJETS_H

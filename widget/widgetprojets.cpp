#include "widgetprojets.h"

WidgetProjets::WidgetProjets(QMainWindow *parent, BaseDeDonnees *bdd) : parent(parent), baseDeDonnees(bdd)
{
    QVBoxLayout *layoutVer = new QVBoxLayout;

    creerAction();
    creerToolBar();
    creerOnglets();

    widgetProjets = new QWidget();
    widgetProjets->setLayout(layoutVer);

    layoutVer->addWidget(onglets);
}

QWidget *WidgetProjets::ouvrir()
{
    return widgetProjets;
}

void WidgetProjets::creerAction()
{
    actionOuvrirProjet = new QAction("Ouvrir le projet", this);
    actionOuvrirProjet->setIcon(QIcon(QPixmap(":/ressources/dossier-icone.png")));

    actionFermerTous = new QAction("Enregistrer et fermer tous les projets ouverts", this);
    actionFermerTous->setIcon(QIcon(QPixmap(":/ressources/supprimer-dossier-icone.png")));

    actionAjouterProjet = new QAction("Créer un nouveau projet", this);
    actionAjouterProjet->setIcon(QIcon(QPixmap(":/ressources/ajouter-un-dossier-icone.png")));
    connect(actionAjouterProjet, SIGNAL(triggered(bool)), this, SLOT(ajouterProjet()));

    actionSauvTous = new QAction("Sauvegarder tous les projets ouverts", this);
    actionSauvTous->setIcon(QIcon(QPixmap(":/ressources/dossier-verifie-icone.png")));

    actionSupprProjet = new QAction("Supprimer le projet", this);
    actionSupprProjet->setIcon(QIcon(QPixmap(":/ressources/dossier-supprimer-icone.png")));
}

void WidgetProjets::creerToolBar()
{
    toolBar = new QToolBar;
    toolBar->addAction(actionOuvrirProjet);
    toolBar->addAction(actionAjouterProjet);
    toolBar->addAction(actionSupprProjet);
    toolBar->addSeparator();
    toolBar->addAction(actionSauvTous);
    toolBar->addAction(actionFermerTous);
    toolBar->setIconSize(QSize(32,32));
}

void WidgetProjets::creerOnglets()
{
    onglets = new QTabWidget;

    //Onglet principal
    ongletPrincipal = new QWidget;
    onglets->addTab(ongletPrincipal, "Gestion des projets");
    QVBoxLayout *layoutVer = new QVBoxLayout;
    //toolbar
    creerToolBar();
    layoutVer->addWidget(toolBar);
    //tableau
    creerTableau();
    layoutVer->addWidget(tableau);
    ongletPrincipal->setLayout(layoutVer);
}

void WidgetProjets::creerTableau()
{
    tableau = new QTreeView;
    projets = new Projets;
    tableau->setModel(projets->model(this, baseDeDonnees));
    tableau->setRootIsDecorated(false);
    tableau->setAlternatingRowColors(true);
    tableau->setSortingEnabled(true);
    tableau->sortByColumn(0, Qt::AscendingOrder);
    tableau->setSelectionMode(QAbstractItemView::SingleSelection);
    tableau->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableau->setEditTriggers(false);
}

void WidgetProjets::ajouterProjet()
{
    Onglets *nvOnglet = new Onglets(baseDeDonnees, true, 0);
    onglets->addTab(nvOnglet->ouvrir(), "Nouveau Projet");
    onglets->setCurrentIndex(onglets->count()-1);
}



#include "widgetclients.h"

WidgetClients::WidgetClients(QMainWindow *parent, BaseDeDonnees *bdd) : parent(parent), baseDeDonnees(bdd)
{
    QVBoxLayout *layoutVer = new QVBoxLayout;

    creerActions();
    creerToolBar();
    creerTableau();

    layoutVer->addWidget(toolBar);
    layoutVer->addWidget(tableau);

    widget = new QWidget();
    widget->setLayout(layoutVer);
}

void WidgetClients::ouvrir()
{
    parent->setCentralWidget(widget);
}

void WidgetClients::creerActions()
{
    //Edition Client
    actionEditerClient = new QAction(tr("Editer le client"), this);
    actionEditerClient->setIcon(QIcon(QPixmap(":ressources/utilisateur-dediter.ico")));
    connect(actionEditerClient, SIGNAL(triggered(bool)), this, SLOT(editerClient()));

    //Ajout Client
    actionAjouterClient = new QAction(tr("Ajouter un client"), this);
    actionAjouterClient->setIcon(QIcon(QPixmap(":/ressources/utilisateur-dajouter.ico")));
    connect(actionAjouterClient, SIGNAL(triggered(bool)), this, SLOT(ajouterClient()));

    //Suppr Client
    actionSupprClient = new QAction(tr("Supprimer le client"), this);
    actionSupprClient->setIcon(QIcon(QPixmap(":/ressources/supprimer-un-utilisateur.ico")));
    connect(actionSupprClient, SIGNAL(triggered(bool)), this, SLOT(supprClient()));

}

void WidgetClients::creerToolBar()
{
    toolBar = new QToolBar;
    toolBar->addAction(actionAjouterClient);
    toolBar->addAction(actionEditerClient);
    toolBar->addAction(actionSupprClient);
}
void WidgetClients::creerTableau()
{
    tableau = new QTreeView;
    tableau->setModel(baseDeDonnees->tableModelClients(this));
    tableau->setRootIsDecorated(false);
    tableau->setAlternatingRowColors(true);
    tableau->setSortingEnabled(true);
    tableau->sortByColumn(0, Qt::AscendingOrder);
    tableau->setSelectionMode(QAbstractItemView::SingleSelection);
    tableau->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableau->setEditTriggers(false);
}

void WidgetClients::editerClient()
{
    int row = tableau->selectionModel()->currentIndex().row(); //recup la ligne

    FenetreEditionClient *editionClient = new FenetreEditionClient(this, baseDeDonnees, false, row);
    editionClient->show();
}

void WidgetClients::ajouterClient()
{
    FenetreEditionClient *editionClient = new FenetreEditionClient(this, baseDeDonnees, true);
    editionClient->show();
}

void WidgetClients::supprClient()
{
    QString nomClient = baseDeDonnees->getDonneesClient(tableau->selectionModel()->currentIndex().row(), 3);
    int rep = QMessageBox::warning(this, "Suppression d'un client", "Supprimer le client : " + nomClient +" ?", QMessageBox::Yes, QMessageBox::No);

    if(rep == QMessageBox::Yes)
    {
        baseDeDonnees->supprClient(tableau->selectionModel()->currentIndex().row());
    }
    else
    {
        return;
    }
}


#include "fenetreprincipale.h"

FenetrePrincipale::FenetrePrincipale()
{
    //Connection à la base de données
    bdd = new BaseDeDonnees;
    bdd->coBDD();

    creerActions();
    creerMenus();
    creerToolBar();
    creerListWidget();

    //Options de la fenêtre
    setMinimumSize(1000,700);
    setWindowTitle(tr("Gestion Clients"));
}

void FenetrePrincipale::creerActions()
{
    //Quitter
    actionQuitter = new QAction(tr("Quitter"), this);
    actionQuitter->setIcon(QIcon(QPixmap(":/ressources/exit.ico")));
    connect(actionQuitter, SIGNAL(triggered(bool)), qApp, SLOT(quit()));

    //Test Bdd
    actionTestCoBdd = new QAction("Tester la Co à la Bdd", this);
    connect(actionTestCoBdd, SIGNAL(triggered(bool)), this, SLOT(verifCoBdd()));
}

void FenetrePrincipale::creerMenus()
{
    QMenu *menuFichier = menuBar()->addMenu(tr("Fichier"));

    //Menu : Fichier
    menuFichier->addAction(actionQuitter);
    menuFichier->addAction(actionTestCoBdd);
}

void FenetrePrincipale::creerToolBar()
{

}

void FenetrePrincipale::creerListWidget()
{
    listWidget = new QListWidget;
    listWidget->setEditTriggers(false);
    listWidget->setDragDropMode(QAbstractItemView::NoDragDrop);
    listWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    listWidget->setMaximumWidth(107);
    listWidget->setMinimumWidth(107);
    listWidget->setIconSize(QSize(96,96));
    listWidget->setTextElideMode(Qt::ElideNone);
    listWidget->setMovement(QListView::Static);
    listWidget->setFlow(QListView::TopToBottom);
    listWidget->setResizeMode(QListView::Adjust);
    listWidget->setGridSize(QSize(107,150));
    listWidget->setViewMode(QListView::IconMode);
    listWidget->setCurrentRow(0);

    QListWidgetItem *listWidgetClient = new QListWidgetItem("Clients", listWidget);
    listWidgetClient->setIcon(QIcon(QPixmap(":/ressources/utilisateurs-icone.png")));
    listWidgetClient->setData(Qt::UserRole, QVariant(1));
    listWidget->addItem(listWidgetClient);

    QListWidgetItem *listWidgetPrestations = new QListWidgetItem("Préstations", listWidget);
    listWidgetPrestations->setIcon((QIcon(QPixmap(":/ressources/notes-icone.png"))));
    listWidgetPrestations->setData(Qt::UserRole, QVariant(2));
    listWidget->addItem(listWidgetPrestations);

    QListWidgetItem *listWidgetProjets = new QListWidgetItem("Projets", listWidget);
    listWidgetProjets->setIcon((QIcon(QPixmap(":/ressources/outils-icone.png"))));
    listWidgetProjets->setData(Qt::UserRole, QVariant(3));
    listWidget->addItem(listWidgetProjets);

    QListWidgetItem *listWidgetParametres = new QListWidgetItem("Paramètres", listWidget);
    listWidgetParametres->setIcon((QIcon(QPixmap(":/ressources/parametres-icone.png"))));
    listWidgetParametres->setData(Qt::UserRole, QVariant(3));
    listWidget->addItem(listWidgetParametres);


    dockWidget = new QDockWidget("Menu Principale", this);
    dockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
    dockWidget->setWidget(listWidget);
    addDockWidget(Qt::LeftDockWidgetArea, dockWidget);

    connect(listWidget, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)), this, SLOT(changerWidget(QListWidgetItem*, QListWidgetItem*)));
}

void FenetrePrincipale::changerWidget(QListWidgetItem *nvItem, QListWidgetItem *ancienItem)
{
    if(nvItem != ancienItem)
    {
        qDebug() << nvItem;
        qDebug() << listWidget->currentItem()->text();

        if(nvItem->text() == "Clients")
        {
            affWidgetClients = new WidgetClients(this, bdd);
            affWidgetClients->ouvrir();
        }
        if(nvItem->text() == "Préstations")
        {
            affWidgetPrestations = new WidgetPrestations(this, bdd);
            affWidgetPrestations->ouvrir();
        }
        if(nvItem->text() == "Projets")
        {
            affWidgetProjets = new WidgetProjets(this, bdd);
            affWidgetProjets->ouvrir();
        }
    }
}

void FenetrePrincipale::verifCoBdd()
{
    if(bdd->estConnecte())
    {
        QMessageBox::information(this, "coBDD", "la connexion est ok");
    }
    else
    {
        QMessageBox::warning(this, "CoBDD", "la connexion na pas reussi");
    }
}

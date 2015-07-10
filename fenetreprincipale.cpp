#include "fenetreprincipale.h"

FenetrePrincipale::FenetrePrincipale()
{
    //Connection à la base de données
    bdd = new BaseDeDonnees;
    bdd->coBDD();

    creerActions();
    creerMenus();
    creerToolBar();
    creerStackedLayout();
    creerListWidget();

    //Options de la fenêtre
    setMinimumSize(1000,700);
    setWindowTitle(tr("Gestion Clients"));

    //Widget central
    widgetCentral = new QWidget;
    setCentralWidget(widgetCentral);
    QVBoxLayout *layoutCentral = new QVBoxLayout;
    layoutCentral->addLayout(stackedLayout);
    widgetCentral->setLayout(layoutCentral);
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

void FenetrePrincipale::creerStackedLayout()
{
    stackedLayout = new QStackedLayout;

    affWidgetClients = new WidgetClients(this, bdd);
    stackedLayout->addWidget(affWidgetClients->ouvrir());

    affWidgetPrestations = new WidgetPrestations(this, bdd);
    stackedLayout->addWidget(affWidgetPrestations->ouvrir());

    affWidgetProjets = new WidgetProjets(this, bdd);
    stackedLayout->addWidget(affWidgetProjets->ouvrir());
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


    dockWidget = new QDockWidget("Menu Principal", this);
    dockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
    dockWidget->setWidget(listWidget);
    addDockWidget(Qt::LeftDockWidgetArea, dockWidget);

    connect(listWidget, SIGNAL(currentRowChanged(int)), stackedLayout, SLOT(setCurrentIndex(int)));
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

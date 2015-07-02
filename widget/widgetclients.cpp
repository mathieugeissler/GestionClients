#include "widgetclients.h"

WidgetClients::WidgetClients(QMainWindow *parent, BaseDeDonnees *bdd) : parent(parent), baseDeDonnees(bdd)
{
    QVBoxLayout *layoutVer = new QVBoxLayout;

    creerActions();
    creerToolBar();
    creerCivilites();
    creerLayout();
    creerTableau();  

    widget = new QWidget();
    widget->setLayout(layoutVer);

    layoutVer->addWidget(toolBar);
    layoutVer->addWidget(groupBox);
    layoutVer->addWidget(tableau);
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

    QLabel *civilite = new QLabel("Civilité : ");
    cbbCivilites = new QComboBox;

    toolBar->addWidget(civilite);
    toolBar->addWidget(cbbCivilites);
    toolBar->addSeparator();
    toolBar->addAction(actionAjouterClient);
    toolBar->addAction(actionEditerClient);
    toolBar->addAction(actionSupprClient);
}

void WidgetClients::creerCivilites()
{
    clientsCivilites = new ClientsCivilites;
    cbbCivilites->setModel(clientsCivilites->model(this, baseDeDonnees));
    cbbCivilites->setModelColumn(1);
    cbbCivilites->setCurrentIndex(0);

    connect(cbbCivilites, SIGNAL(currentIndexChanged(int)), this, SLOT(clientsCivChange(int)));
}

void WidgetClients::creerLayout()
{
    QGridLayout *layoutGrid = new QGridLayout;
    groupBox = new QGroupBox;

    QLabel *lblNom = new QLabel("Nom : ");
    QLabel *lblPrenom = new QLabel("Prénom : ");
    QLabel *lblAdresse = new QLabel("Adresse : ");
    QLabel *lblCP = new QLabel("Code Postal : ");
    QLabel *lblVille = new QLabel("Ville : ");
    QLabel *lblTel1 = new QLabel("Tel. 1 : ");
    QLabel *lblTel2 = new QLabel("Tel. 2 : ");
    QLabel *lblMail = new QLabel("Mail : ");
    QLabel *lblSiteWeb = new QLabel("Site-Web : ");
    QLabel *lblDesc = new QLabel("Déscription : ");

    editNom = new QLineEdit;
    editCiv = new QComboBox;
    editPrenom = new QLineEdit;
    editAdresse = new QLineEdit;
    editCP = new QLineEdit;
    editVille = new QLineEdit;
    editTel1 = new QLineEdit;
    editTel2 = new QLineEdit;
    editMail = new QLineEdit;
    editSiteWeb = new QLineEdit;
    editDesc = new QTextEdit;

    //Nom Prenom
    layoutGrid->addWidget(editCiv, 0,0);
    layoutGrid->addWidget(lblNom, 0,1);
    layoutGrid->addWidget(editNom, 0,2);
    layoutGrid->addWidget(lblPrenom, 0,3);
    layoutGrid->addWidget(editPrenom, 0,4);
    //Adresse
    layoutGrid->addWidget(lblAdresse, 1,0);
    layoutGrid->addWidget(editAdresse, 1,1, 1, 4);
    //CP Ville
    layoutGrid->addWidget(lblCP, 2,0);
    layoutGrid->addWidget(editCP, 2,1, 1, 2);
    layoutGrid->addWidget(lblVille, 2,3);
    layoutGrid->addWidget(editVille, 2,4);
    //Tel
    layoutGrid->addWidget(lblTel1, 3,0);
    layoutGrid->addWidget(editTel1, 3,1, 1,2 );
    layoutGrid->addWidget(lblTel2, 3,3);
    layoutGrid->addWidget(editTel2, 3,4);
    //Mail Web
    layoutGrid->addWidget(lblMail, 4,0);
    layoutGrid->addWidget(editMail, 4,1, 1,2);
    layoutGrid->addWidget(lblSiteWeb, 4,3);
    layoutGrid->addWidget(editSiteWeb, 4,4);
    //Desc
    layoutGrid->addWidget(lblDesc, 5,0);
    layoutGrid->addWidget(editDesc, 5,1, 1,4);

    editCiv->setModel(clientsCivilites->model(this, baseDeDonnees));
    editCiv->setModelColumn(1);
    editCiv->setCurrentIndex(0);

    groupBox->setFixedHeight(200);
    groupBox->setLayout(layoutGrid);
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

void WidgetClients::clientsCivChange(int indexId)
{
    //clients->filtreCat(prestaCategories->getDonnee(indexId, 0).toInt());
    //viderFormulaire();
    //desactiverForm(true);
}


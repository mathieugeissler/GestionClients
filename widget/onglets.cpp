#include "onglets.h"

Onglets::Onglets(BaseDeDonnees *bdd, bool nvProjet, int idProjet = 0) : baseDeDonnees(bdd)
{
    layoutPrincipal = new QVBoxLayout;
    this->setLayout(layoutPrincipal);

    creerSelClient();
    creerSelPresta();
    creerTotal();
    creerLayout();
}

QWidget *Onglets::ouvrir()
{
    return this;
}

void Onglets::creerSelClient()
{
    clientGroupBox = new QGroupBox("Sélection du client");
    clientGroupBox->setFixedHeight(50);
    QHBoxLayout *clientLayout = new QHBoxLayout;
    QLabel *clientLblCiv = new QLabel("Civilité : ");

    //civilités
    clientCbbCiv = new QComboBox;
    clientsCivilites = new ClientsCivilites;
    clientCbbCiv->setModel(clientsCivilites->model(this, baseDeDonnees));
    clientCbbCiv->setModelColumn(1);
    clientCbbCiv->setCurrentIndex(0);

    connect(clientCbbCiv, SIGNAL(currentIndexChanged(int)), this, SLOT(clientsCivChange(int)));

    //nom
    QLabel *clientLblNom = new QLabel("Nom : ");
    clientCbbNom = new QComboBox;
    clients = new Clients;
    clientCbbNom->setModel(clients->model(this, baseDeDonnees));
    clientCbbNom->setModelColumn(3);
    clientCbbNom->setCurrentIndex(0);

    clientLayout->addWidget(clientLblCiv);
    clientLayout->addWidget(clientCbbCiv);
    clientLayout->addWidget(clientLblNom);
    clientLayout->addWidget(clientCbbNom);
    clientGroupBox->setLayout(clientLayout);
}

void Onglets::clientsCivChange(int indexId)
{
   clients->filtreCat(clientsCivilites->getDonnee(indexId, 0).toInt());
}

void Onglets::creerSelPresta()
{
    prestaGroupBox = new QGroupBox("Préstations :");
    QVBoxLayout *prestaLayoutVer = new QVBoxLayout;
    QHBoxLayout *prestaLayoutHor = new QHBoxLayout;

    //catégories
    QLabel *prestaLblCat = new QLabel("Catégories : ");
    prestaCbbCat = new QComboBox;
    prestaCategories = new PrestationsCategories;
    prestaCbbCat->setModel(prestaCategories->model(this, baseDeDonnees));
    prestaCbbCat->setModelColumn(1);
    prestaCbbCat->setCurrentIndex(0);

    //nom
    QLabel *prestaLblNom = new QLabel("Nom : ");
    prestaCbbNom = new QComboBox;
    prestations = new Prestations;
    prestaCbbNom->setModel(prestations->model(this, baseDeDonnees));
    prestaCbbNom->setModelColumn(1);

    connect(prestaCbbCat, SIGNAL(currentIndexChanged(int)), this, SLOT(prestaCatChange(int)));

    //Ajouter
    QPushButton *prestaPbAjouter = new QPushButton("Ajouter");

    prestaLayoutHor->addWidget(prestaLblCat);
    prestaLayoutHor->addWidget(prestaCbbCat);
    prestaLayoutHor->addWidget(prestaLblNom);
    prestaLayoutHor->addWidget(prestaCbbNom);
    prestaLayoutHor->addWidget(prestaPbAjouter);

    //tableau
    QTableView *prestaTableau = new QTableView;
    QSqlTableModel *tableModel = new QSqlTableModel;
    tableModel->setHeaderData(0, Qt::Horizontal, "Numéro");
    tableModel->setHeaderData(1, Qt::Horizontal, "Préstation");
    tableModel->setHeaderData(2, Qt::Horizontal, "Prix unit. HT");
    tableModel->setHeaderData(3, Qt::Horizontal, "Quantitée");
    tableModel->setHeaderData(4, Qt::Horizontal, "Prix Total");
    tableModel->setHeaderData(5, Qt::Horizontal, "Suppr");
    prestaTableau->setModel(tableModel);

    prestaLayoutVer->addLayout(prestaLayoutHor);
    prestaLayoutVer->addWidget(prestaTableau);
    prestaGroupBox->setLayout(prestaLayoutVer);
}

void Onglets::prestaCatChange(int indexId)
{
    prestations->filtreCat(prestaCategories->getDonnee(indexId, 0).toInt());
}

void Onglets::creerTotal()
{
    totalGroupBox = new QGroupBox("Total :");
}

void Onglets::creerLayout()
{
    layoutPrincipal->addWidget(clientGroupBox);
    layoutPrincipal->addWidget(prestaGroupBox);
    layoutPrincipal->addWidget(totalGroupBox);
}

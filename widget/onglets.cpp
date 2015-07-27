#include "onglets.h"

Onglets::Onglets(BaseDeDonnees *bdd, bool nvProjet, int id = 0) : baseDeDonnees(bdd), idProjet(id)
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
    connect(prestaPbAjouter, SIGNAL(clicked(bool)), this, SLOT(ajouterPresta()));

    prestaLayoutHor->addWidget(prestaLblCat);
    prestaLayoutHor->addWidget(prestaCbbCat);
    prestaLayoutHor->addWidget(prestaLblNom);
    prestaLayoutHor->addWidget(prestaCbbNom);
    prestaLayoutHor->addWidget(prestaPbAjouter);

    //tableau
    prestaTableau = new QTableWidget;
    prestaTableau->setAlternatingRowColors(true);
    prestaTableau->verticalHeader()->hide();
    prestaTableau->setSelectionMode(QAbstractItemView::SingleSelection);
    prestaTableau->setSelectionBehavior(QAbstractItemView::SelectRows);
    for(int i = 0; i < 6; i++)
    {
        prestaTableau->insertColumn(i);
    }
    prestaTableau->setHorizontalHeaderItem(0, new QTableWidgetItem("Id"));
    prestaTableau->setHorizontalHeaderItem(1, new QTableWidgetItem("Nom"));
    prestaTableau->setHorizontalHeaderItem(2, new QTableWidgetItem("Prix unitaire"));
    prestaTableau->setHorizontalHeaderItem(3, new QTableWidgetItem("Quantité"));
    prestaTableau->setHorizontalHeaderItem(4, new QTableWidgetItem("Prix total"));
    prestaTableau->setHorizontalHeaderItem(5, new QTableWidgetItem("Supprimer"));

    prestaTableau->setItemDelegateForColumn(3, new SpinBoxDelegate(prestaTableau));
    connect(prestaTableau->itemDelegateForColumn(3), SIGNAL(commitData(QWidget*)), this, SLOT(quantiteChange(QWidget *)));

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

void Onglets::ajouterPresta()
{
    int idPresta = prestaCbbNom->currentIndex();

    prestaTableau->insertRow(prestaTableau->rowCount());
    int row = prestaTableau->rowCount()-1;

    QTableWidgetItem *itemIdPresta = new QTableWidgetItem(QString("%1").arg(idPresta));
    prestaTableau->setItem(row, 0, itemIdPresta);

    QTableWidgetItem *itemNom = new QTableWidgetItem(tr("%1").arg(prestations->getDonnees(idPresta, 1)));
    prestaTableau->setItem(row, 1, itemNom);

    QTableWidgetItem *itemPrixUnit = new QTableWidgetItem(tr("%1").arg(prestations->getDonnees(idPresta, 4)));
    prestaTableau->setItem(row, 2, itemPrixUnit);

    QTableWidgetItem *itemPrixTotal = new QTableWidgetItem(tr("%1").arg(prestations->getDonnees(idPresta, 4)));
    prestaTableau->setItem(row, 4, itemPrixTotal);

    QPushButton *supprimer = new QPushButton("Supprimer", prestaTableau);
    prestaTableau->setCellWidget(row, 5, supprimer);
    connect(supprimer, SIGNAL(clicked(bool)), this, SLOT(prestaSuppr()));
}

void Onglets::quantiteChange(QWidget *widget)
{
    int value = prestaTableau->itemAt(widget->pos())->data(Qt::DisplayRole).toInt();
    int row = widget->pos().y();
    if(row != 0)
    {
        row = row / 30;
    }
    double prix = prestaTableau->item(row, 2)->data(Qt::DisplayRole).toDouble();

    prestaTableau->item(row, 4)->setData(Qt::DisplayRole, QVariant(value * prix));
}

void Onglets::prestaSuppr()
{
    int row = prestaTableau->currentRow();

    if(row < 0)
    {
        QMessageBox::warning(this, "Erreur", "Selectionner la ligne à supprimer");
    }
    else
    {
        int rep = QMessageBox::warning(this, "Suppression d'une prestation", "Supprimer la préstation ?", QMessageBox::Yes, QMessageBox::No);
        if (rep == QMessageBox::Yes)
        {
            prestaTableau->removeRow(row);
        }
    }
}

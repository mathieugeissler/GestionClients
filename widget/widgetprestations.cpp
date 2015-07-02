#include "widgetPrestations.h"

WidgetPrestations::WidgetPrestations(QMainWindow *parent, BaseDeDonnees *bdd) : parent(parent), baseDeDonnees(bdd)
{
    QVBoxLayout *layoutVer = new QVBoxLayout;

    creerActions();
    creerToolBar();
    creerLayoutPresta();
    creerCategories();
    creerTableau();

    widget = new QWidget();
    widget->setLayout(layoutVer);

    layoutVer->addWidget(toolBar);
    layoutVer->addWidget(groupBox);
    layoutVer->addWidget(tableau);

    //défini une ligne négative = aucune ligne selectionnée
    rowId = -1;
}

void WidgetPrestations::ouvrir()
{
    parent->setCentralWidget(widget);
}

void WidgetPrestations::creerActions()
{
    actionAjouterPrestation = new QAction(tr("Ajouter une préstation"), this);
    actionAjouterPrestation->setIcon(QIcon(QPixmap(":/ressources/page-ajouter-icone.png")));
    connect(actionAjouterPrestation, SIGNAL(triggered(bool)), this, SLOT(ajouterPrestation()));

    actionSauvPrestation = new QAction(tr("Sauvegarder la préstation"), this);
    actionSauvPrestation->setIcon(QIcon(QPixmap(":/ressources/enregistrer-page-icone.png")));
    connect(actionSauvPrestation, SIGNAL(triggered(bool)), this, SLOT(sauvPrestation()));

    actionSupprPrestation = new QAction(tr("Supprimer la préstation"), this);
    actionSupprPrestation->setIcon(QIcon(QPixmap(":/ressources/supprimer-la-page-icone.png")));
    connect(actionSupprPrestation, SIGNAL(triggered(bool)), this, SLOT(supprPrestation()));
}

void WidgetPrestations::creerToolBar()
{
    toolBar = new QToolBar;

    QLabel *categorie = new QLabel("Catégorie : ");
    cbbPrestaCategories = new QComboBox;

    toolBar->addWidget(categorie);
    toolBar->addWidget(cbbPrestaCategories);

    toolBar->addSeparator();
    toolBar->addAction(actionAjouterPrestation);
    toolBar->addAction(actionSauvPrestation);
    toolBar->addAction(actionSupprPrestation);
}

void WidgetPrestations::creerLayoutPresta()
{
    QGridLayout *layoutGrid = new QGridLayout;
    groupBox = new QGroupBox;

    QLabel *lblNom = new QLabel("Nom :");
    QLabel *lblPrix = new QLabel("Prix :");
    QLabel *lblDesc = new QLabel("Déscription :");
    editPrix = new QDoubleSpinBox;
    editNom = new QLineEdit;
    editDesc = new QTextEdit;

    editNom->setFixedWidth(400);
    groupBox->setFixedHeight(120);
    editPrix->setFixedWidth(100);
    editPrix->setRange(0.0,9999.99);

    layoutGrid->addWidget(lblNom, 0, 0);
    layoutGrid->addWidget(editNom, 0, 1);
    layoutGrid->addWidget(lblPrix, 0, 2, Qt::AlignRight);
    layoutGrid->addWidget(editPrix, 0, 3);
    layoutGrid->addWidget(lblDesc, 1, 0);
    layoutGrid->addWidget(editDesc, 2, 0, 1, 4);

    groupBox->setLayout(layoutGrid);

    desactiverForm(true);
}

void WidgetPrestations::creerCategories()
{
    prestaCategories = new PrestationsCategories;
    cbbPrestaCategories->setModel(prestaCategories->model(this, baseDeDonnees));
    cbbPrestaCategories->setModelColumn(1);
    cbbPrestaCategories->setCurrentIndex(0);

    connect(cbbPrestaCategories, SIGNAL(currentIndexChanged(int)), this, SLOT(prestaCatChange(int)));
}

void WidgetPrestations::creerTableau()
{
    prestations = new Prestations;
    tableau = new QTreeView;
    tableau->setModel(prestations->model(this, baseDeDonnees));
    tableau->setRootIsDecorated(false);
    tableau->setAlternatingRowColors(true);
    tableau->setSortingEnabled(true);
    tableau->sortByColumn(0, Qt::AscendingOrder);
    tableau->setSelectionMode(QAbstractItemView::SingleSelection);
    tableau->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableau->setColumnHidden(2, true);
    tableau->setEditTriggers(false);

    connect(tableau->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(idPrestaChange(QItemSelection, QItemSelection)));
}

void WidgetPrestations::idPrestaChange(QItemSelection nvId, QItemSelection ancienId)
{
    if(nvId != ancienId)
    {
        rowId = tableau->selectionModel()->currentIndex().row();
        chargerForm();
    }

    if(!ligneEstSelectionnee())
    {
        desactiverForm(true);
    }
}

void WidgetPrestations::ajouterPrestation()
{

    if(prestations->ajouter())
    {
        tableau->selectionModel()->setCurrentIndex(prestations->selDernier(), QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows);
        nvIdPresta();
    }
    else
    {
        qDebug() << "Erreur ajout row";
    }
}

void WidgetPrestations::viderFormulaire()
{
    editNom->setText("");
    editPrix->setValue(0);
    editDesc->setText("");
}

void WidgetPrestations::sauvPrestation()
{
   if(rowId < 0)
   {
        QMessageBox::warning(this, "Erreur", "Aucune ligne selectionné, pour ajouter une nouvelle préstation cliquer sur \"Ajouter une préstation\"");
        return;
   }
   if(verifForm() && ligneEstSelectionnee())
    {
        QSqlRecord record = prestations->modelRecord();


        record.setValue(0, QVariant(idPresta));

        record.setValue(1, QVariant(editNom->displayText()));
        record.setValue(2, QVariant(prestaCategories->getDonnee(cbbPrestaCategories->currentIndex(), 0).toInt()));
        record.setValue(3, QVariant(editDesc->toPlainText()));
        record.setValue(4, QVariant(editPrix->value()));

        if(prestations->sauvegarder(record, rowId))
        {
            QMessageBox::information(this, "Sauvegarde de la préstation", "la préstation " + editNom->displayText() + " est sauvegardée");
            viderFormulaire();
            desactiverForm(true);
        }
        else
        {
            QMessageBox::warning(this, "Sauvegarde de la préstation", "Erreur lors de la sauvegarde de la préstation " + editNom->displayText());
        }
   }
}

bool WidgetPrestations::verifForm()
{
    if(editNom->displayText().isEmpty())
    {
        QMessageBox::warning(this, "Erreur", "Vous n'avez pas entré le nom");
        return false;
    }
    if(editPrix->value() <= 0)
    {
        QMessageBox::warning(this, "Erreur", "Le prix de la prestation ne peut être égale à 0");
        return false;
    }
    return true;
}

bool WidgetPrestations::ligneEstSelectionnee()
{
    if(tableau->currentIndex().row() < 0)
    {
        return false;
    }
    return true;
}

void WidgetPrestations::nvIdPresta()
{
   int num = 1;
   idPresta = num + prestations->nbr();
}

void WidgetPrestations::chargerForm()
{
    desactiverForm(false);
    idPresta = prestations->getDonnees(rowId, 0).toInt();
    editNom->setText(prestations->getDonnees(rowId, 1));
    editPrix->setValue(prestations->getDonnees(rowId, 4).toDouble());
    editDesc->setPlainText(prestations->getDonnees(rowId, 3));
}

void WidgetPrestations::supprPrestation()
{
    if(rowId < 0)
    {
         QMessageBox::warning(this, "Erreur", "Aucune ligne selectionné");
         return;
    }
    if(ligneEstSelectionnee())
    {
        int rep = QMessageBox::warning(this, "Suppression d'une préstation", "Supprimer la préstation : " + editNom->displayText() +" ?", QMessageBox::Yes, QMessageBox::No);

        if(rep == QMessageBox::Yes)
        {
            if(prestations->supprimer(rowId))
            {
                viderFormulaire();
                desactiverForm(true);
            }
        }
        else
        {
            return;
        }
    }
}

void WidgetPrestations::desactiverForm(const bool ok)
{
    if(ok)
    {
        editNom->setDisabled(true);
        editPrix->setDisabled(true);
        editDesc->setDisabled(true);
    }
    else
    {
        editNom->setDisabled(false);
        editPrix->setDisabled(false);
        editDesc->setDisabled(false);
    }

}

void WidgetPrestations::prestaCatChange(int indexId)
{
    prestations->filtreCat(prestaCategories->getDonnee(indexId, 0).toInt());
    viderFormulaire();
    desactiverForm(true);
}

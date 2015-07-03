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

    rowId = -1;
}

void WidgetClients::ouvrir()
{
    parent->setCentralWidget(widget);
}

void WidgetClients::creerActions()
{
    //Sauvegarde Client
    actionSauvClient = new QAction(tr("Sauvegarder le client"), this);
    actionSauvClient->setIcon(QIcon(QPixmap(":ressources/utilisateur-dediter.ico")));
    connect(actionSauvClient, SIGNAL(triggered(bool)), this, SLOT(sauvClient()));

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
    toolBar->addAction(actionSauvClient);
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
    QLabel *lblSiret = new QLabel("Siret : ");

    editEntite = new QCheckBox;
    connect(editEntite, SIGNAL(stateChanged(int)), this, SLOT(entiteChange(int)));

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
    editSiret = new QLineEdit;

    editEntite->setText("Entreprise");

    //Entite
    layoutGrid->addWidget(editEntite, 0,0);
    //Siret
    layoutGrid->addWidget(lblSiret, 0,1);
    layoutGrid->addWidget(editSiret, 0,2);
    //Nom Prenom
    layoutGrid->addWidget(editCiv, 1,0);
    layoutGrid->addWidget(lblNom, 1,1);
    layoutGrid->addWidget(editNom, 1,2);
    layoutGrid->addWidget(lblPrenom, 1,3);
    layoutGrid->addWidget(editPrenom, 1,4);
    //Adresse
    layoutGrid->addWidget(lblAdresse, 2,0);
    layoutGrid->addWidget(editAdresse, 2,1, 1, 4);
    //CP Ville
    layoutGrid->addWidget(lblCP, 3,0);
    layoutGrid->addWidget(editCP, 3,1, 1, 2);
    layoutGrid->addWidget(lblVille, 3,3);
    layoutGrid->addWidget(editVille, 3,4);
    //Tel
    layoutGrid->addWidget(lblTel1, 4,0);
    layoutGrid->addWidget(editTel1, 4,1, 1,2 );
    layoutGrid->addWidget(lblTel2, 4,3);
    layoutGrid->addWidget(editTel2, 4,4);
    //Mail Web
    layoutGrid->addWidget(lblMail, 5,0);
    layoutGrid->addWidget(editMail, 5,1, 1,2);
    layoutGrid->addWidget(lblSiteWeb, 5,3);
    layoutGrid->addWidget(editSiteWeb, 5,4);
    //Desc
    layoutGrid->addWidget(lblDesc, 6,0);
    layoutGrid->addWidget(editDesc, 6,1, 1,4);


    editCiv->setModel(clientsCivilites->model(this, baseDeDonnees));
    editCiv->setModelColumn(1);
    editCiv->setCurrentIndex(0);

    groupBox->setFixedHeight(220);
    groupBox->setLayout(layoutGrid);

    desactiverForm(true);
}

void WidgetClients::creerTableau()
{
    clients = new Clients;
    tableau = new QTreeView;
    tableau->setModel(clients->model(this, baseDeDonnees));
    tableau->setRootIsDecorated(false);
    tableau->setAlternatingRowColors(true);
    tableau->setSortingEnabled(true);
    tableau->sortByColumn(0, Qt::AscendingOrder);
    tableau->setSelectionMode(QAbstractItemView::SingleSelection);
    tableau->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableau->setEditTriggers(false);
    tableau->setColumnHidden(2, true);

    for(int i = 0; i < 13; i++)
    {
        tableau->resizeColumnToContents(i);
    }


    connect(tableau->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(idChange(QItemSelection, QItemSelection)));
}

void WidgetClients::idChange(QItemSelection nvId, QItemSelection ancienId)
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

void WidgetClients::ajouterClient()
{

    if(clients->ajouter())
    {
        tableau->selectionModel()->setCurrentIndex(clients->selDernier(), QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows);
        nvIdClient();
    }
    else
    {
        qDebug() << "Erreur ajout row";
    }
}

void WidgetClients::viderFormulaire()
{
    editNom->setText("");
    editPrenom->setText("");
    editAdresse->setText("");
    editCP->setText("");
    editVille->setText("");
    editTel1->setText("");
    editTel2->setText("");
    editMail->setText("");
    editSiteWeb->setText("");
    editDesc->setText("");
    editSiret->setText("");
}

void WidgetClients::sauvClient()
{
   if(rowId < 0)
   {
        QMessageBox::warning(this, "Erreur", "Aucune ligne selectionné, pour ajouter un nouveau client cliquer sur \"Ajouter un client\"");
        return;
   }
   if(verifForm() && ligneEstSelectionnee())
    {
        QSqlRecord record = clients->modelRecord();

        record.setValue(0, QVariant(idClient));
        if(editEntite->isChecked())
        {
            record.setValue(1, QVariant("E"));
            record.setValue(13, QVariant(editSiret->displayText()));
        }
        else
        {
            record.setValue(1, QVariant("P"));
        }
        record.setValue(2, QVariant(clientsCivilites->getDonnee(editCiv->currentIndex(), 0).toInt()));
        record.setValue(3, QVariant(editNom->displayText()));
        record.setValue(4, QVariant(editPrenom->displayText()));
        record.setValue(5, QVariant(editAdresse->displayText()));
        record.setValue(6, QVariant(editCP->displayText()));
        record.setValue(7, QVariant(editVille->displayText()));
        record.setValue(8, QVariant(editMail->displayText()));
        record.setValue(9, QVariant(editTel1->displayText()));
        record.setValue(10, QVariant(editTel2->displayText()));
        record.setValue(11, QVariant(editSiteWeb->displayText()));
        record.setValue(12, QVariant(editDesc->toPlainText()));

        if(clients->sauvegarder(record, rowId))
        {
            QMessageBox::information(this, "Sauvegarde de la préstation", "la préstation " + editNom->displayText() + " est sauvegardée");
            viderFormulaire();
            desactiverForm(true);
            for(int i = 0; i < 13; i++)
            {
                tableau->resizeColumnToContents(i);
            }
        }
        else
        {
            QMessageBox::warning(this, "Sauvegarde de la préstation", "Erreur lors de la sauvegarde de la préstation " + editNom->displayText());
        }
   }
}

bool WidgetClients::verifForm()
{
    if(editNom->text().isEmpty())
    {
        QMessageBox::warning(this, "Erreur", "Vous n'avez pas saisi le nom");
        return false;
    }
    if(!editEntite->isChecked() && editPrenom->text().isEmpty())
    {
        QMessageBox::warning(this, "Erreur", "Vous n'avez pas saisi le prénom");
        return false;
    }
    if(editAdresse->text().isEmpty())
    {
        QMessageBox::warning(this, "Erreur", "Vous n'avez pas saisi l'adresse");
        return false;
    }
    if(editCP->text().isEmpty())
    {
        QMessageBox::warning(this, "Erreur", "Vous n'avez pas saisi le code postal");
        return false;
    }
    if(editVille->text().isEmpty())
    {
        QMessageBox::warning(this, "Erreur", "Vous n'avez pas saisi la ville");
        return false;
    }
    if(editMail->text().isEmpty())
     {
         QMessageBox::warning(this, "Erreur", "Vous n'avez pas saisi l'adresse mail");
         return false;
     }
    return true;
}

bool WidgetClients::ligneEstSelectionnee()
{
    if(tableau->currentIndex().row() < 0)
    {
        return false;
    }
    return true;
}

void WidgetClients::nvIdClient()
{
   int num = 1;
   idClient = num + clients->nbr();
}

void WidgetClients::chargerForm()
{
    desactiverForm(false);
    idClient = clients->getDonnees(rowId, 0).toInt();
    if(clients->getDonnees(rowId, 1) == "E")
    {
        editEntite->setChecked(true);
        editSiret->setText(clients->getDonnees(rowId, 13));
    }
    editCiv->setCurrentIndex(clients->getDonnees(rowId, 2).toInt());
    editNom->setText(clients->getDonnees(rowId, 3));
    editPrenom->setText(clients->getDonnees(rowId, 4));
    editAdresse->setText(clients->getDonnees(rowId, 5));
    editCP->setText(clients->getDonnees(rowId, 6));
    editVille->setText(clients->getDonnees(rowId, 7));
    editTel1->setText(clients->getDonnees(rowId, 9));
    editTel2->setText(clients->getDonnees(rowId, 10));
    editMail->setText(clients->getDonnees(rowId, 8));
    editSiteWeb->setText(clients->getDonnees(rowId, 11));
    editDesc->setPlainText(clients->getDonnees(rowId, 12));
}

void WidgetClients::supprClient()
{
    if(rowId < 0)
    {
         QMessageBox::warning(this, "Erreur", "Aucune ligne selectionné");
         return;
    }
    if(ligneEstSelectionnee())
    {
        int rep = QMessageBox::warning(this, "Suppression d'un client", "Supprimer le client : " + editNom->displayText() +" ?", QMessageBox::Yes, QMessageBox::No);

        if(rep == QMessageBox::Yes)
        {
            if(clients->supprimer(rowId))
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

void WidgetClients::desactiverForm(const bool ok)
{
    if(ok)
    {
        editCiv->setDisabled(true);
        editEntite->setDisabled(true);
        editNom->setDisabled(true);
        editPrenom->setDisabled(true);
        editAdresse->setDisabled(true);
        editCP->setDisabled(true);
        editVille->setDisabled(true);
        editTel1->setDisabled(true);
        editTel2->setDisabled(true);
        editMail->setDisabled(true);
        editSiteWeb->setDisabled(true);
        editDesc->setDisabled(true);
        editSiret->setDisabled(true);
    }
    else
    {
       editCiv->setDisabled(false);
       editEntite->setDisabled(false);
       editNom->setDisabled(false);
       editPrenom->setDisabled(false);
       editAdresse->setDisabled(false);
       editCP->setDisabled(false);
       editVille->setDisabled(false);
       editTel1->setDisabled(false);
       editTel2->setDisabled(false);
       editMail->setDisabled(false);
       editSiteWeb->setDisabled(false);
       editDesc->setDisabled(false);
    }

}

void WidgetClients::clientsCivChange(int indexId)
{
    clients->filtreCat(clientsCivilites->getDonnee(indexId, 0).toInt());
    viderFormulaire();
    desactiverForm(true);
}

void WidgetClients::entiteChange(int check)
{
    qDebug() << check;
    if(check == 2)
    {
        editPrenom->setDisabled(true);
        editSiret->setDisabled(false);
    }
    else
    {
        editPrenom->setDisabled(false);
        editSiret->setDisabled(true);
    }
}

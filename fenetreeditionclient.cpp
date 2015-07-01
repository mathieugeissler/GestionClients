#include "fenetreeditionclient.h"

FenetreEditionClient::FenetreEditionClient(QWidget *parent, BaseDeDonnees *bdd, bool nvClient, int rowId) : QDialog(parent), baseDeDonnees(bdd), nvClient(nvClient), rowId(rowId)
{
    creerFormulaire();
    creerConnection();
    chargerComboBox();
}

void FenetreEditionClient::creerFormulaire()
{
    entitePersonne = new QRadioButton;
    entiteEntreprise = new QRadioButton;
    civilite = new QComboBox;
    nom = new QLineEdit;
    prenom = new QLineEdit;
    adresse = new QLineEdit;
    codepostal = new QLineEdit;
    ville = new QLineEdit;
    mail = new QLineEdit;
    siteweb = new QLineEdit;
    tel1 = new QLineEdit;
    tel2 = new QLineEdit;
    siret = new QLineEdit;
    description = new QTextEdit;
    sauvegarder = new QPushButton;
    annuler = new QPushButton;

    //Num client et entité
    QHBoxLayout *entiteLayout = new QHBoxLayout;

    numClientLabel = new QLabel;

    if (nvClient)
    {
        numNvClient();
    }
    else
    {
        chargerDonneesClient();
    }
    entiteEntreprise->setText("Entreprise");
    entitePersonne->setText("Personne");
    entiteGroup = new QButtonGroup(this);
    entiteGroup->addButton(entitePersonne, 1);
    entiteGroup->addButton(entiteEntreprise, 2);

    entiteLayout->addWidget(numClientLabel);
    entiteLayout->addWidget(entitePersonne);
    entiteLayout->addWidget(entiteEntreprise);

    //Formulaire
    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow("Civilité :", civilite);
    formLayout->addRow("Nom :", nom);
    formLayout->addRow("Prénom :", prenom);
    formLayout->addRow("Adresse :", adresse);
    formLayout->addRow("Code Postal :", codepostal);
    formLayout->addRow("Ville :", ville);
    formLayout->addRow("Adresse email :", mail);
    formLayout->addRow("Site web :", siteweb);
    formLayout->addRow("Téléphone 1", tel1);
    formLayout->addRow("Téléphone 2", tel2);
    formLayout->addRow("Siret :", siret);
    formLayout->addRow(description);

    siret->setDisabled(true);

    // Boutton
    sauvegarder->setText("Sauvegarder");
    annuler->setText("Annuler");
    QHBoxLayout *bouttonLayout = new QHBoxLayout;
    bouttonLayout->addWidget(sauvegarder);
    bouttonLayout->addWidget(annuler);

    //Fenetre
    QVBoxLayout *layoutPrincipal = new QVBoxLayout;
    layoutPrincipal->addLayout(entiteLayout);
    layoutPrincipal->addLayout(formLayout);
    layoutPrincipal->addLayout(bouttonLayout);
    setLayout(layoutPrincipal);

}

void FenetreEditionClient::creerConnection()
{
    connect(sauvegarder, SIGNAL(clicked(bool)), this, SLOT(sauvClient()));
    connect(annuler, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(entiteGroup, SIGNAL(buttonClicked(int)), this, SLOT(entiteChange(int)));
}

void FenetreEditionClient::chargerComboBox()
{
    QStringList civiliteList;
    civiliteList << "Monsieur" << "Madame";

    civilite->addItems(civiliteList);

}

void FenetreEditionClient::sauvClient()
{
    if(verifForm())
    {
        QSqlRecord record = baseDeDonnees->modelRecordClient();
        record.setValue(0, QVariant(numClient));
        if(entitePersonne->isChecked())
        {
            record.setValue(1, QVariant("P"));
        }
        else
        {
            record.setValue(1, QVariant("E"));
            record.setValue(13, QVariant(siret->displayText()));
        }
        record.setValue(2, QVariant(civilite->currentText()));
        record.setValue(3, QVariant(nom->displayText()));
        record.setValue(4, QVariant(prenom->displayText()));
        record.setValue(5, QVariant(adresse->displayText()));
        record.setValue(6, QVariant(codepostal->displayText()));
        record.setValue(7, QVariant(ville->displayText()));
        record.setValue(8, QVariant(mail->displayText()));
        record.setValue(9, QVariant(tel1->displayText()));
        record.setValue(10, QVariant(tel2->displayText()));
        record.setValue(11, QVariant(siteweb->displayText()));
        record.setValue(12, QVariant(description->toPlainText()));

        if(nvClient)
        {
            if(baseDeDonnees->ajouterClient(record))
            {
                QMessageBox::information(this, "Ajout d'un nouveau client", "Le client " + nom->displayText() + " à été ajouté");
                this->close();
            }
            else
            {
                QMessageBox::warning(this, "Erreur ajout d'un nouveau client", "le client " + nom->displayText() + " n'a pas été ajouté");
            }
        }
        else
        {
            if(baseDeDonnees->modifierClient(record, rowId))
            {
                QMessageBox::information(this, "Modification d'un client", "Le client " + nom->displayText() + " à été modifié");
                this->close();
            }
            else
            {
                QMessageBox::warning(this, "Erreur modfication du client", "le client " + nom->displayText() + " n'a pas été modifié");
            }
        }
    }
}

void FenetreEditionClient::entiteChange(const int numButton)
{
    if(numButton == 1)
    {
        civilite->setDisabled(false);
        prenom->setDisabled(false);
        siret->setDisabled(true);
    }
    else
    {
        civilite->setDisabled(true);
        prenom->setDisabled(true);
        siret->setDisabled(false);
   }
}

bool FenetreEditionClient::verifForm()
{
    if(nom->text().isEmpty())
    {
        QMessageBox::warning(this, "Erreur", "Vous n'avez pas rempli le nom");
        return false;
    }
    if(entitePersonne->isChecked() && prenom->text().isEmpty())
    {
        QMessageBox::warning(this, "Erreur", "Vous n'avez pas rempli le prénom");
        return false;
    }
    if(adresse->text().isEmpty())
    {
        QMessageBox::warning(this, "Erreur", "Vous n'avez pas rempli l'adresse");
        return false;
    }
    if(codepostal->text().isEmpty())
    {
        QMessageBox::warning(this, "Erreur", "Vous n'avez pas rempli le code postal");
        return false;
    }
    if(ville->text().isEmpty())
    {
        QMessageBox::warning(this, "Erreur", "Vous n'avez pas rempli la ville");
        return false;
    }
    if(mail->text().isEmpty())
     {
         QMessageBox::warning(this, "Erreur", "Vous n'avez pas rempli l'adresse mail");
         return false;
     }
    return true;
}

void FenetreEditionClient::numNvClient()
{
    int num = 1 ;
    num += baseDeDonnees->nbrClients();
    numClient = numClient.setNum(num);
    numClientLabel->setText("Numéro client : " + numClient);
}

void FenetreEditionClient::chargerDonneesClient()
{
    numClient = baseDeDonnees->getDonneesClient(rowId, 0);
    numClientLabel->setText("Numéro client : " + numClient);
    qDebug() << baseDeDonnees->getDonneesClient(rowId, 1);
    if(baseDeDonnees->getDonneesClient(rowId, 1) == "E")
    {
        entiteEntreprise->setChecked(true);
        entiteChange(2);
    }
    else
    {
        entitePersonne->setChecked(true);
    }
    civilite->setCurrentText(baseDeDonnees->getDonneesClient(rowId, 2));
    nom->setText(baseDeDonnees->getDonneesClient(rowId, 3));
    prenom->setText(baseDeDonnees->getDonneesClient(rowId, 4));
    adresse->setText(baseDeDonnees->getDonneesClient(rowId, 5));
    codepostal->setText(baseDeDonnees->getDonneesClient(rowId, 6));
    ville->setText(baseDeDonnees->getDonneesClient(rowId, 7));
    mail->setText(baseDeDonnees->getDonneesClient(rowId, 8));
    tel1->setText(baseDeDonnees->getDonneesClient(rowId, 9));
    tel2->setText(baseDeDonnees->getDonneesClient(rowId, 10));
    siteweb->setText(baseDeDonnees->getDonneesClient(rowId, 11));
    description->setText(baseDeDonnees->getDonneesClient(rowId, 12));
    siret->setText(baseDeDonnees->getDonneesClient(rowId, 13));
}

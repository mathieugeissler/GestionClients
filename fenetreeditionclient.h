#ifndef FENETREEDITIONCLIENT
#define FENETREEDITIONCLIENT

#include <QtWidgets>
#include "includes/basededonnees.h"

class FenetreEditionClient : public QDialog
{
    Q_OBJECT

public:
    FenetreEditionClient(QWidget *parent, BaseDeDonnees *bdd, bool nvClient, int rowId = 0);
private:
    void creerFormulaire();
    void creerConnection();
    bool verifForm();
    void chargerComboBox();
    void numNvClient();
    void chargerDonneesClient();

private slots:
    void sauvClient();
    void entiteChange(int numBoutton);

private:
    BaseDeDonnees *baseDeDonnees;
    bool nvClient;
    int rowId;
    QString numClient;
    QRadioButton *entitePersonne;
    QRadioButton *entiteEntreprise;
    QComboBox *civilite;
    QLineEdit *nom;
    QLineEdit *prenom;
    QLineEdit *adresse;
    QLineEdit *codepostal;
    QLineEdit *ville;
    QLineEdit *mail;
    QLineEdit *siteweb;
    QLineEdit *tel1;
    QLineEdit *tel2;
    QLineEdit *siret;
    QTextEdit *description;
    QPushButton *sauvegarder;
    QPushButton *annuler;
    QButtonGroup *entiteGroup;
    QLabel *numClientLabel;
};

#endif // FENETREEDITIONCLIENT


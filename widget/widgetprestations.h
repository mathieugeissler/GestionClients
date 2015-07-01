#ifndef WIDGETPRESTATIONS_H
#define WIDGETPRESTATIONS_H

#include <QtWidgets>
#include "includes/basededonnees.h"
#include "includes/prestations.h"
#include "includes/prestationscategories.h"


class WidgetPrestations : public QWidget
{
    Q_OBJECT

public:
    WidgetPrestations(QMainWindow *parent, BaseDeDonnees *baseDeDonnees);
    void ouvrir();

private:
    void creerTableau();
    void creerActions();
    void creerToolBar();
    void creerLayoutPresta();
    void creerCategories();
    void viderFormulaire();
    bool verifForm();
    void nvIdPresta();
    void chargerForm();
    bool ligneEstSelectionnee();
    void desactiverForm(const bool ok);

private slots:
    void idPrestaChange(QItemSelection nvId, QItemSelection ancienId);
    void ajouterPrestation();
    void sauvPrestation();
    void supprPrestation();

private:
    QMainWindow *parent;
    BaseDeDonnees *baseDeDonnees;
    Prestations *prestations;
    PrestationsCategories *prestaCategories;
    int idPresta;
    int rowId;
    QWidget *widget;
    QToolBar *toolBar;
    QTreeView *tableau;
    QAction *actionAjouterPrestation;
    QAction *actionSauvPrestation;
    QAction *actionSupprPrestation;
    QGroupBox *groupBox;
    QComboBox *cbbPrestaCategories;
    QLineEdit *editNom;
    QDoubleSpinBox *editPrix;
    QTextEdit *editDesc;
};

#endif // WIDGETPRESTATIONS_H

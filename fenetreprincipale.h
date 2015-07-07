#ifndef FENETREPRINCIPALE
#define FENETREPRINCIPALE

#include "includes/basededonnees.h"
#include "widget/widgetclients.h"
#include "widget/widgetprestations.h"
#include "widget/widgetprojets.h"
#include <QtWidgets>
#include <QString>

class FenetrePrincipale : public QMainWindow
{
    Q_OBJECT

public:
    FenetrePrincipale();

private:
    void creerActions();
    void creerMenus();
    void creerToolBar();
    void creerListWidget();
    void fermerWidget(QListWidgetItem *ancienItem);

private slots:
    void verifCoBdd();
    void changerWidget(QListWidgetItem *nvItem, QListWidgetItem *ancienItem);

private:
    QDockWidget *dockWidget;
    QListWidget *listWidget;
    QAction *actionQuitter;
    QAction *actionTestCoBdd;
    BaseDeDonnees *bdd;
    WidgetClients *affWidgetClients;
    WidgetPrestations *affWidgetPrestations;
    WidgetProjets *affWidgetProjets;
};

#endif // FENETREPRINCIPALE


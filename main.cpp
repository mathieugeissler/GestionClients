#include <QApplication>
#include "fenetreprincipale.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    FenetrePrincipale FenetrePrincipale;
    FenetrePrincipale.show();
    return app.exec();
}


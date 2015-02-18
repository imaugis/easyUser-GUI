#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QFont>
#include <QIcon>
#include <QtGui>
#include "fenetreprincipale.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setStyle("GTK");
    fenetrePrincipale fenetre;
    fenetre.show();


    return app.exec();
}

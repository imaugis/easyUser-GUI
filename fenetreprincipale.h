#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H

#include <QApplication>
#include <QtGui>
#include <QByteArray>
#include <QGtkStyle>
#include <QIODevice>
#include <string>
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

class fenetrePrincipale : public QWidget
{
    Q_OBJECT

    public:
    fenetrePrincipale();

    public slots:
    void ajouter();

    private:

    // Titre
    QLabel *m_labelTitre;

    // Formulaire Utilisateur
    QLineEdit *m_lineEditNom;
    QLineEdit *m_lineEditPrenom;
    QFormLayout *m_formLayoutUser;
    QGroupBox *m_groupBoxUser;

    // Formulaire de connection
    QLineEdit *m_lineEditLogin;
    QLineEdit *m_lineEditPass1;
    QLineEdit *m_lineEditPass2;
    QLabel *m_labelPassBoot;
    QRadioButton *m_radioButtonPassBootYes;
    QRadioButton *m_radioButtonPassBootNo;
    QFormLayout *m_formLayoutLogin;
    QGridLayout *m_layoutPassBoot;
    QGroupBox *m_groupBoxPassBoot;
    QGroupBox *m_groupBoxLogin;

    // Formulaire d'environnement
    QLabel *m_labelProfil;
    QRadioButton *m_radioButtonEleve;
    QRadioButton *m_radioButtonEnseignant;
    QGridLayout *m_layoutEnvironnement;
    QGroupBox *m_groupBoxEnvironnement;

    // Frame contenant le logo ENPT 2.0
    QLabel *m_labelLogo;

    // Boutons "Valider" et "Quitter"
    QPushButton *m_boutonValider;
    QPushButton *m_boutonQuitter;

};

#endif // FENETREPRINCIPALE_H

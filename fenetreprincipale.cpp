#include "fenetreprincipale.h"

fenetrePrincipale::fenetrePrincipale() : QWidget()
{
    // On calcul les dimensions de l'écran pour placer notre fenêtre principale
    QDesktopWidget *widget = QApplication::desktop();
    int desktop_width = widget->width();
    int desktop_height = widget->height();
    int x = desktop_width / 2 - width() / 2;
    int y = desktop_height / 2 - height() / 2 - 25;

    // Paramétrage de la fenêtre principale
    setFixedSize(600, 450);
    move(QPoint(x, y));
    setWindowIcon(QIcon("/usr/share/easyuser/icone.png"));
    setWindowTitle("ENPT 2.0 - Ajouter un utilisateur");

    // Titre
    m_labelTitre = new QLabel("Ajouter Un Utilisateur", this);
    m_labelTitre->setStyleSheet("font-size: 22px; color: #444444; font-weight: bold;");
    m_labelTitre->setGeometry(0, 0, 600, 40);
    m_labelTitre->setAlignment(Qt::AlignCenter);

    // Formulaire Utilisateur
    m_lineEditNom = new QLineEdit;
    m_lineEditPrenom = new QLineEdit;

    m_formLayoutUser = new QFormLayout(this);
    m_formLayoutUser->addRow("&Nom : ", m_lineEditNom);
    m_formLayoutUser->addRow(trUtf8("&Prénom : "), m_lineEditPrenom);

    m_groupBoxUser = new QGroupBox("Informations Utilisateur", this);
    m_groupBoxUser->setGeometry(10, 60, 350, 100);
    m_groupBoxUser->setLayout(m_formLayoutUser);

    // Formulaire Identification
    m_lineEditLogin = new QLineEdit;
    m_lineEditPass1 = new QLineEdit;
    m_lineEditPass1->setEchoMode(QLineEdit::Password);
    m_lineEditPass2 = new QLineEdit;
    m_lineEditPass2->setEchoMode(QLineEdit::Password);

    m_formLayoutLogin = new QFormLayout(this);
    m_formLayoutLogin->addRow("&Identifiant : ", m_lineEditLogin);
    m_formLayoutLogin->addRow("Mot de &passe : ", m_lineEditPass1);
    m_formLayoutLogin->addRow("Confirmez mot de p&asse : ", m_lineEditPass2);

    m_groupBoxLogin = new QGroupBox("Informations de connection", this);
    m_groupBoxLogin->setGeometry(10, 170, 350, 150);
    m_groupBoxLogin->setLayout(m_formLayoutLogin);

    //m_labelPassBoot = new QLabel(trUtf8("Mot de passe au démarrage : "));
    //m_radioButtonPassBootYes = new QRadioButton("Oui");
    //m_radioButtonPassBootYes->setChecked(true);
    //m_radioButtonPassBootNo = new QRadioButton("Non");

    //m_layoutPassBoot = new QGridLayout;
    //m_layoutPassBoot->addWidget(m_labelPassBoot, 0, 0);
    //m_layoutPassBoot->addWidget(m_radioButtonPassBootYes, 0, 1);
    //m_layoutPassBoot->addWidget(m_radioButtonPassBootNo, 0, 2);

    //m_groupBoxPassBoot = new QGroupBox(this);
    //m_groupBoxPassBoot->setGeometry(10, 260, 350, 60);
    //m_groupBoxPassBoot->setLayout(m_layoutPassBoot);

    // Formulaire d'environnement
    m_labelProfil = new QLabel("Profil de l'utilisateur : ");
    m_radioButtonEleve = new QRadioButton(trUtf8("Élève"));
    m_radioButtonEleve->setChecked(true);
    m_radioButtonEnseignant = new QRadioButton("Enseignant");

    m_layoutEnvironnement = new QGridLayout;
    m_layoutEnvironnement->addWidget(m_labelProfil, 0, 0);
    m_layoutEnvironnement->addWidget(m_radioButtonEleve, 0, 1);
    m_layoutEnvironnement->addWidget(m_radioButtonEnseignant, 0, 2);

    m_groupBoxEnvironnement = new QGroupBox("Choix de l'environnement", this);
    m_groupBoxEnvironnement->setGeometry(10, 320, 350, 60);
    m_groupBoxEnvironnement->setLayout(m_layoutEnvironnement);

    // Frame contenant le logo ENPT 2.0
    m_labelLogo = new QLabel(this);
    m_labelLogo->setPixmap(QPixmap("/usr/share/easyuser/logo.png"));
    m_labelLogo->setAlignment(Qt::AlignCenter);
    m_labelLogo->setGeometry(380, 50, 210, 350);

    // Bouton "Valider"
    m_boutonValider = new QPushButton("Valider", this);
    m_boutonValider->setGeometry(320, 400, 120, 30);
    m_boutonValider->setToolTip("Enregistrer un nouvel utilisateur");

    // Bouton "Quitter"
    m_boutonQuitter = new QPushButton("Quitter", this);
    m_boutonQuitter->setGeometry(450, 400, 120, 30);
    m_boutonQuitter->setToolTip("Quitter l'application");

    // Connexion aux slots
    QObject::connect(m_boutonValider, SIGNAL(clicked()), this, SLOT(ajouter()));
    QObject::connect(m_boutonQuitter, SIGNAL(clicked()), qApp, SLOT(quit()));

}

// Traitement des données saisies dans le formulaire
void fenetrePrincipale::ajouter()
{
        // Initialisation des variables
        QString userLastName = m_lineEditNom->text();
        QString userFirstName = m_lineEditPrenom->text();
        QString userLogin = m_lineEditLogin->text();
        QString userPass1 = m_lineEditPass1->text();
        QString userPass2 = m_lineEditPass2->text();
        QString userGroup = "nogroup";

        // Initialisation des RegEx pour vérifier le login et le mot de passe
        QRegExp regLogin("^[A-Za-z0-9]{4,}$");
        QRegExp regPasswd("^[A-Za-z0-9]{6,}$");

        // On vérifie que les champs ne sont pas vides
        if (userLastName.isEmpty() || userFirstName.isEmpty() || userLogin.isEmpty() || userPass1.isEmpty() || userPass2.isEmpty())
        {
            QMessageBox::warning(this, "Attention !", trUtf8("Tous les champs doivent être renseigné !"));
        }
        else
        {
            if(userLogin.contains(regLogin))
            {
                if(userPass1.contains(regPasswd))
                {
                    // Vérification du groupe (ce qui va déterminer l'environnement)
                    if(m_radioButtonEleve->isChecked())
                    {
                        userGroup = "eleve";
                    }
                    else if(m_radioButtonEnseignant->isChecked())
                    {
                        userGroup = "enseignant";
                    }

                    // On vérifie que les mots de passe sont identiques
                    if (userPass1 != userPass2)
                    {
                        QMessageBox::warning(this, "Attention !", "Les mots de passe ne sont pas identiques !");
                    }
                    else
                    {
                        // On chiffre le mot de passe avec "mkpasswd"
                        QProcess *processPasswd = new QProcess;
                        processPasswd->start("mkpasswd " + userPass1);
                        if(!processPasswd->waitForFinished())
                        {
                            return;
                        }
                        QByteArray resultPasswd = processPasswd->readAll();
                        QString passwdCrypt(resultPasswd);

                        // On génère la commande "adduser" pour créer le nouvel utilisateur
                        int valeurRetour;
                        // S'il est enseignant on l'ajoute aussi aux groupes leterrier et sudo
                        if(userGroup == "enseignant"){
                            QString cmdAddUser("/usr/sbin/useradd -m " + userLogin + " -G " + userGroup + ",leterrier,sudo -p " + passwdCrypt + " -c \"" + userLastName + " " + userFirstName + "\" -d /home/" + userLogin + " -s /bin/bash -b /home/" + userLogin);
                            valeurRetour = QProcess::execute(cmdAddUser);
                        }
                        // S'il est élève on ne l'ajoute pas au groupe sudo
                        else if(userGroup == "eleve"){
                            QString cmdAddUser("/usr/sbin/useradd -m " + userLogin + " -G " + userGroup + " -p " + passwdCrypt + " -c \"" + userLastName + " " + userFirstName + "\" -d /home/" + userLogin + " -s /bin/bash -b /home/" + userLogin);
                            valeurRetour = QProcess::execute(cmdAddUser);
                        }

                        //QString cmdAddUser("/usr/sbin/useradd -m " + userLogin + " -G " + userGroup + ",sudo -p " + passwdCrypt + " -c \"" + userLastName + " " + userFirstName + "\" -d /home/" + userLogin + " -s /bin/bash -b /home/" + userLogin);
                        //valeurRetour = QProcess::execute(cmdAddUser);

                        if(valeurRetour == 1)
                        {
                            QMessageBox::critical(this, "Erreur !", trUtf8("<strong>Erreur n° 1</strong><br />Impossible de mettre à jour le fichier des mots de passe !"));
                        }
                        else if(valeurRetour == 2)
                        {
                            QMessageBox::critical(this, "Erreur !", trUtf8("<strong>Erreur n° 2</strong><br />Erreur de syntaxe !"));
                        }
                        else if(valeurRetour == 3)
                        {
                            QMessageBox::critical(this, "Erreur !", trUtf8("<strong>Erreur n° 3</strong><br />Paramètre non valable !"));
                        }
                        else if(valeurRetour == 4)
                        {
                            QMessageBox::critical(this, "Erreur !", trUtf8("<strong>Erreur n° 4</strong><br />Cet UID est déjà utilisé !"));
                        }
                        else if(valeurRetour == 6)
                        {
                            QMessageBox::critical(this, "Erreur !", trUtf8("<strong>Erreur n° 6</strong><br />Le groupe spécifié n'existe pas !"));
                        }
                        else if(valeurRetour == 9)
                        {
                            QMessageBox::critical(this, "Erreur !", trUtf8("<strong>Erreur n° 9</strong><br />Ce nom d'utilisateur est déjà utilisé !"));
                            m_lineEditLogin->clear();
                        }
                        else if(valeurRetour == 10)
                        {
                            QMessageBox::critical(this, "Erreur !", trUtf8("<strong>Erreur n° 10</strong><br />Impossible de mettre à jour le fichier des groupes !"));
                        }
                        else if(valeurRetour == 12)
                        {
                            QMessageBox::critical(this, "Erreur !", trUtf8("<strong>Erreur n° 12</strong><br />Impossible de créer le répertoire personnel !"));
                        }
                        else if(valeurRetour == 13)
                        {
                            QMessageBox::critical(this, "Erreur !", trUtf8("<strong>Erreur n° 13</strong><br />Impossible de créer le répertoire d'attente des courriels !"));
                        }
                        else // Si aucunes erreurs, l'utilisateur est bien crée
                        {
                            QMessageBox::information(this, "Notification", trUtf8("Le nouvel utilisateur a été ajouté avec succès !"));

                            // On vide les champs
                            m_lineEditNom->clear();
                            m_lineEditPrenom->clear();
                            m_lineEditLogin->clear();
                            m_lineEditPass1->clear();
                            m_lineEditPass2->clear();
                            m_radioButtonEleve->setChecked(true);
                        }

                    }

                }
                else
                {
                    QMessageBox::warning(this, "Attention !", trUtf8("<strong>Mot de passe non valide !</strong><br /><br />- Le mot de passe doit contenir au moins 6 caractères;<br />- Le mot de passe ne doit pas contenir d'espaces;<br />- Le mot de passe ne doit pas contenir de caractères spéciaux;<br />- Le mot de passe ne doit pas contenir de caractères accentués;"));
                }

            }
            else
            {
                QMessageBox::warning(this, "Attention !", trUtf8("<strong>Identifiant non valide !</strong><br /><br />- L'identifiant doit contenir au moins 4 caractères;<br />- L'identifiant ne doit pas contenir d'espaces;<br />- L'identifiant ne doit pas contenir de caractères spéciaux;<br />- L'identifiant ne doit pas contenir de caractères accentués;"));
            }
        }

}

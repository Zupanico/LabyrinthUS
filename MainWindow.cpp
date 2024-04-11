#include "MainWindow.h"
#include "Authentification.h"
#include "LoadGame.h"
#include "Info.h"
#include "Play.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    MenuPrincipale();
}

void MainWindow::paintEvent(QPaintEvent* event)
{
    // Ajout d'image en arriere plan
    QPainter painter(this);
    QPixmap background(":/images/imgInterface.jpg");

    if (background.isNull())
    {
        qDebug() << "L'image n'a pas pu être chargée ! Vérifiez le chemin.";
    }
    else
    {
        painter.drawPixmap(rect(), background);
    }
}

void MainWindow::MenuPrincipale()
{
    // Nettoyage du Menu precedent
    listButton.clear();

    // Création du layout principal de la fenêtre
    QVBoxLayout* mainLayout = new QVBoxLayout();

    // Création du grid layout pour l'icône et les boutons
    QGridLayout* gridLayout = new QGridLayout();

    // Création du QPushButton pour afficher l'icône Menu bar
    iconButton = new QPushButton(this);
    QPixmap originalIcon(":/images/barreMenu.png");
    QPixmap resizedIcon = originalIcon.scaled(QSize(60, 60), Qt::KeepAspectRatio); // Redimensionner l'icône
    iconButton->setIcon(QIcon(resizedIcon));
    iconButton->setIconSize(resizedIcon.size());
    iconButton->setFixedSize(resizedIcon.size()); // Taille fixe pour s'adapter à l'icône
    iconButton->setFlat(true); // Rendre le bouton sans bordure

    // Ajouter l'icône dans le grid layout
    gridLayout->addWidget(iconButton, 0, 0, Qt::AlignTop | Qt::AlignLeft); // Utiliser pour placer l'icône en haut à gauche

    connect(iconButton, &QPushButton::clicked, this, bind(&MainWindow::playClickSound, this, 0));

    // Création du QPushButton pour afficher l'icône settings
    iconButton1 = new QPushButton(this); // Utiliser iconButton1 pour l'icône des paramètres
    QPixmap originalIcon1(":/images/parametres.png");
    QPixmap resizedIcon1 = originalIcon1.scaled(QSize(60, 60), Qt::KeepAspectRatio); // Redimensionner l'icône
    iconButton1->setIcon(QIcon(resizedIcon1));
    iconButton1->setIconSize(resizedIcon1.size());
    iconButton1->setFixedSize(resizedIcon1.size()); // Taille fixe pour s'adapter à l'icône
    iconButton1->setFlat(true); // Rendre le bouton sans bordure

    // Ajouter l'icône dans le grid layout en bas à droite
    gridLayout->addWidget(iconButton1, 0, 2, Qt::AlignBottom | Qt::AlignRight); // Utiliser iconButton1 ici
    connect(iconButton1, &QPushButton::clicked, this, bind(&MainWindow::playClickSound, this, 0));

    // Création du QPushButton pour afficher l'icône information
    iconButton2 = new QPushButton(this); // Utiliser iconButton1 pour l'icône des paramètres
    QPixmap originalIcon2(":/images/information.png");
    QPixmap resizedIcon2 = originalIcon2.scaled(QSize(60, 60), Qt::KeepAspectRatio); // Redimensionner l'icône
    iconButton2->setIcon(QIcon(resizedIcon2));
    iconButton2->setIconSize(resizedIcon1.size());
    iconButton2->setFixedSize(resizedIcon1.size()); // Taille fixe pour s'adapter à l'icône
    iconButton2->setFlat(true); // Rendre le bouton sans bordure

    // Ajouter l'icône dans le grid layout en bas à droite
    gridLayout->addWidget(iconButton2, 0, 1, Qt::AlignBottom | Qt::AlignCenter); // Utiliser iconButton1 ici
    connect(iconButton2, &QPushButton::clicked, this, bind(&MainWindow::playClickSound, this, 0));

    // Ajouter des espacements entre les éléments de la grille
    gridLayout->setHorizontalSpacing(20);
    gridLayout->setVerticalSpacing(150);

    // Creation de mes Boutons
    listButton.push_back(new QPushButton(tr("&NEW GAME")));
    listButton.push_back(new QPushButton(tr("&LOAD GAME")));
    QPushButton* quitButton = new QPushButton(tr("&QUIT PLAY"));
    connect(quitButton, &QPushButton::clicked, &QCoreApplication::quit);
    listButton.push_back(quitButton);

    // Charger les polices et les appliquer aux boutons
    int fontPolice = QFontDatabase::addApplicationFont(":/fonts/BadBoys.ttf");

    QFont font; // Déclaration de la police ici

    if (fontPolice != -1)
    {
        QString fontFamillePolice = QFontDatabase::applicationFontFamilies(fontPolice).at(0);
        font = QFont(fontFamillePolice, 60, QFont::Bold);
    }
    else
    {
        qDebug() << "Échec du chargement de la police Aligator.";
        // Appliquer une police par défaut si la police personnalisée n'est pas chargée
        font = QFont("Arial", 60, QFont::Bold);
    }

    for (size_t i = 0; i < listButton.size(); i++)
    {
        // Configuration des connexions signal-slot
        connect(listButton.at(i), &QPushButton::clicked, this, bind(&MainWindow::playClickSound, this, 0));

        // Ajout des boutons dans le grid layout
        gridLayout->addWidget(listButton.at(i), i + 1, 0, 1, 3, Qt::AlignCenter); // Aligner les boutons verticalement au centre

        // Application de la police sur les Buttons
        listButton.at(i)->setFont(font);

        // Appliquer le style CSS pour aligner le texte au centre verticalement
        listButton.at(i)->setStyleSheet("QPushButton { padding-top: 15px; padding-bottom: 15px; }");
    }

    // Ajouter le grid layout au layout principal
    mainLayout->addLayout(gridLayout);

    // Affichage de la des boutons
    centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout); // Affecter le layout principal à la fenêtre
    setCentralWidget(centralWidget);

    // Personnaliser le style des boutons
    foreach(QPushButton * button, centralWidget->findChildren<QPushButton*>())
    {
        button->setMinimumHeight(70);
        button->setStyleSheet("QPushButton { color: red; background-color: transparent; border: none; }"
            "QPushButton:pressed { color: yellow; background-color: transparent; }");
    }
    setFixedSize(1525, 785);
    setWindowTitle(tr("LABYRINTHUS GROUPE P6 : : PROJET DE FIN DE SESSION S2 -->> BAKAYOKO KANVALI"));
}


void MainWindow::MenuPause()
{
    // Nettoyage du Menu precedent
    listButton.clear();

    // Création du layout principal de la fenêtre
    QVBoxLayout* mainLayout = new QVBoxLayout();

    // Création du grid layout pour les boutons
    QGridLayout* gridLayout = new QGridLayout();

    // Creation de mes Boutons
    listButton.push_back(new QPushButton(tr("&CONTINUER")));
    listButton.push_back(new QPushButton(tr("&RECOMMENCER")));
    listButton.push_back(new QPushButton(tr("&QUITTER PARTIE")));

    // Charger les polices et les appliquer aux boutons
    int fontPolice = QFontDatabase::addApplicationFont(":/fonts/BadBoys.ttf");

    QFont font; // Déclaration de la police ici

    if (fontPolice != -1)
    {
        QString fontFamillePolice = QFontDatabase::applicationFontFamilies(fontPolice).at(0);
        font = QFont(fontFamillePolice, 60, QFont::Bold);
    }
    else
    {
        qDebug() << "Échec du chargement de la police Aligator.";
        // Appliquer une police par défaut si la police personnalisée n'est pas chargée
        font = QFont("Arial", 60, QFont::Bold);
    }

    for (size_t i = 0; i < listButton.size(); i++)
    {
        // Configuration des connexions signal-slot
        connect(listButton.at(i), &QPushButton::clicked, this, bind(&MainWindow::playClickSound, this, 1));

        // Ajout des boutons dans le grid layout
        gridLayout->addWidget(listButton.at(i), i + 1, 0, 1, 1, Qt::AlignCenter); // Aligner les boutons verticalement au centre

        // Application de la police sur les Buttons
        listButton.at(i)->setFont(font);

        // Appliquer le style CSS pour aligner le texte au centre verticalement
        listButton.at(i)->setStyleSheet("QPushButton { padding-top: 15px; padding-bottom: 15px; }");
    }

    // Ajouter le grid layout au layout principal
    mainLayout->addLayout(gridLayout);

    // Affichage de la des boutons
    centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout); // Affecter le layout principal à la fenêtre
    setCentralWidget(centralWidget);

    // Personnaliser le style des boutons
    foreach(QPushButton * button, centralWidget->findChildren<QPushButton*>())
    {
        button->setMinimumHeight(70);
        button->setStyleSheet("QPushButton { color: red; background-color: transparent; border: none; }"
            "QPushButton:pressed { color: yellow; background-color: transparent; }");
    }
    setFixedSize(1525, 785);
    setWindowTitle(tr("LABYRINTHUS GROUPE P6 : : PROJET DE FIN DE SESSION S2 -->> BAKAYOKO KANVALI"));
}


void MainWindow::MenuAuthentification()
{
    if (authentificationWindow != nullptr)
    {
        delete authentificationWindow;
    }
    authentificationWindow = new Authentification(this);
    authentificationWindow->show(); // Affiche la fenêtre d'authentification
}

void MainWindow::MenuLoadGame()
{
    // Applle la class pour MenuLoadGame
    if (LoadGameWindow != nullptr)
    {
        delete LoadGameWindow;
    }
    LoadGameWindow = new LoadGame(this);
    LoadGameWindow->show(); // Affiche la fenêtre d'authentification
}

void MainWindow::MenuInfo()
{
    // Applle la class pour MenuInfo
    if (infoWinow != nullptr)
    {
        delete infoWinow;
    }
    infoWinow = new Info(this);
    infoWinow->show(); // Affiche la fenêtre d'authentification
}

void MainWindow::MenuQuitPlay()
{
    // Applle la class pour MenuQuitPlay
    connect(listButton.at(3), &QPushButton::clicked, &QCoreApplication::quit);
}

void MainWindow::Continuer()
{
    // Applle la class pour Continuer
    authentificationWindow->continueGame();
}

void MainWindow::Redemarrer()
{
    authentificationWindow->restartGame();
}

void MainWindow::RetourMenuPrincipale()
{
    // Applle la class pour RetourMenuPrincipale
    MenuPrincipale();
}

void MainWindow::Settings()
{
    // reglage 
}

void MainWindow::playClickSound(int menu_index)
{
    SonClick.setSource(QUrl::fromLocalFile("clickSound.wav"));
    SonClick.setLoopCount(1);
    SonClick.setVolume(1.0f);

    // Déterminer le bouton cliqué
    QObject* obj = sender();
    QPushButton* button = qobject_cast<QPushButton*>(obj);

    if (button != nullptr)
    {
        SonClick.play();

        if (button == iconButton)
        {
            // active la methode de l'icone
        }

        if (button == iconButton1)
        {
            // active la methode de l'icone
            Settings();
        }

        if (button == iconButton2)
        {
            // active la methode de l'icone
            MenuInfo();
        }

        for (size_t i = 0; i < listButton.size(); i++)
        {
            // vérifier l'identité du bouton
            if (button == listButton.at(i))
            {
                if (menu_index == 0)
                {
                    Cas1(i);
                }

                if (menu_index == 1)
                {
                    Cas2(i);
                }
            }
        }
    }
}

void MainWindow::Cas1(int i)
{
    switch (i)
    {
    case 0:
        MenuAuthentification();
        break;

    case 1:
        MenuLoadGame();
        break;

    case 2:
        MenuQuitPlay();
        break;

    default:
        break;
    }
}

void MainWindow::Cas2(int i)
{
    switch (i)
    {
    case 0:
        Continuer();
        break;

    case 1:
        Redemarrer();
        break;

    case 2:
        RetourMenuPrincipale();
        break;

    default:
        break;
    }
}
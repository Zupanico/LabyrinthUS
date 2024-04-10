#include "LoadGame.h"

LoadGame::LoadGame(QWidget* parent) :QMainWindow(parent)
{
    MenuLoadGame();
}

void LoadGame::paintEvent(QPaintEvent* event)
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

void LoadGame::MenuLoadGame()
{
    // Supprime tous les enfants de ce widget
    qDeleteAll(this->findChildren<QWidget*>("", Qt::FindDirectChildrenOnly));

    centralWidget = new QWidget(this);

    // Configuration des groupes score en Classement
    QGroupBox* ClassementGroupBox = new QGroupBox(tr(""), this);
    ClassementGroupBox->setStyleSheet("QGroupBox { border: 0; }"); // Masquer les contours

    QHBoxLayout* ClassementLayout = new QHBoxLayout(ClassementGroupBox);
    QLabel* LabelLaodGameClassement = new QLabel(tr("CLASSEMENT"), ClassementGroupBox);

    LabelLaodGameClassement->setAlignment(Qt::AlignCenter);
    LabelLaodGameClassement->setStyleSheet("QLabel { color: red; }");

    // Configuration des groupes Joueur Label
    QGroupBox* playerGroupBox = new QGroupBox(tr(""), this);
    playerGroupBox->setStyleSheet("QGroupBox { border: 0; }"); // Masquer les contours

    QHBoxLayout* playerLayout = new QHBoxLayout(playerGroupBox);
    QLabel* LabelLaodGamePlayer = new QLabel(tr("JOUEURS"), playerGroupBox);

    LabelLaodGamePlayer->setAlignment(Qt::AlignCenter);
    LabelLaodGamePlayer->setStyleSheet("QLabel { color: red; }");

    // Configuration des groupes score en Label
    QGroupBox* scoreGroupBox = new QGroupBox(tr(""), this);
    scoreGroupBox->setStyleSheet("QGroupBox { border: 0; }"); // Masquer les contours

    QHBoxLayout* scoreLayout = new QHBoxLayout(scoreGroupBox);
    QLabel* LabelLaodGamePScore = new QLabel(tr("SCORES"), scoreGroupBox);

    LabelLaodGamePScore->setAlignment(Qt::AlignCenter);
    LabelLaodGamePScore->setStyleSheet("QLabel { color: red; }");

    playerLayout->addWidget(LabelLaodGamePlayer);
    scoreLayout->addWidget(LabelLaodGamePScore);
    ClassementLayout->addWidget(LabelLaodGameClassement);

    playerGroupBox->setLayout(playerLayout);
    scoreGroupBox->setLayout(scoreLayout);
    ClassementGroupBox->setLayout(ClassementLayout);

    // Chargement et application des polices sur les titres (Classement, joueur, Scores)
    QFont font1;
    int fontId1 = QFontDatabase::addApplicationFont(":/fonts/BadBoys.ttf");
    if (fontId1 != -1) {
        QString fontFamily = QFontDatabase::applicationFontFamilies(fontId1).at(0);
        font1 = QFont(fontFamily, 50, QFont::Bold);
    }
    else {
        qDebug() << "Échec du chargement de la police BadBoys.";
        font1 = QFont("Arial", 50, QFont::Bold);
    }
    LabelLaodGamePlayer->setFont(font1);
    LabelLaodGamePScore->setFont(font1);
    LabelLaodGameClassement->setFont(font1);

    // Chargement et application des polices
    QFont font;
    int fontId = QFontDatabase::addApplicationFont(":/fonts/BadBoys.ttf");
    if (fontId != -1) {
        QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
        font = QFont(fontFamily, 40, QFont::Bold);
    }
    else {
        qDebug() << "Échec du chargement de la police BadBoys.";
        font = QFont("Arial", 40, QFont::Bold);
    }

    // Création du QPushButton pour afficher l'icône Suivant
    boutonDemarrer = new QPushButton(this);
    QPixmap originalNextIcon(":/images/aller.png"); // Chemin de l'icône suivant
    QPixmap resizedNextIcon = originalNextIcon.scaled(QSize(60, 60), Qt::KeepAspectRatio); // Redimensionner l'icône
    boutonDemarrer->setIcon(QIcon(resizedNextIcon));
    boutonDemarrer->setIconSize(resizedNextIcon.size());
    boutonDemarrer->setFixedSize(resizedNextIcon.size()); // Taille fixe pour s'adapter à l'icône
    boutonDemarrer->setFlat(true); // Rendre le bouton sans bordure
    boutonDemarrer->setProperty("role", "demarrer");

    // Ajouter l'icône Suivant dans le grid layout
    connect(boutonDemarrer, &QPushButton::clicked, this, &LoadGame::playClickSound);

    // Création du QPushButton pour afficher l'icône Précédent
    boutonPrecedent = new QPushButton(this);
    QPixmap originalPrevIcon(":/images/retour.png"); // Chemin de l'icône précédente
    QPixmap resizedPrevIcon = originalPrevIcon.scaled(QSize(60, 60), Qt::KeepAspectRatio); // Redimensionner l'icône
    boutonPrecedent->setIcon(QIcon(resizedPrevIcon));
    boutonPrecedent->setIconSize(resizedPrevIcon.size());
    boutonPrecedent->setFixedSize(resizedPrevIcon.size()); // Taille fixe pour s'adapter à l'icône
    boutonPrecedent->setFlat(true); // Rendre le bouton sans bordure
    boutonPrecedent->setProperty("role", "precedent");

    // Ajouter l'icône Précédent dans le grid layout
    connect(boutonPrecedent, &QPushButton::clicked, this, &LoadGame::playClickSound);



    // Layout principal
    QGridLayout* mainLayout = new QGridLayout(centralWidget);

    for (size_t i = 0; i < 8; i++)
    {
        mainLayout->setRowStretch(i, 1);
        mainLayout->setColumnStretch(i, 1);
    }

    mainLayout->addWidget(playerGroupBox, 0, 0, Qt::AlignTop | Qt::AlignRight);
    mainLayout->addWidget(scoreGroupBox, 0, 4, Qt::AlignTop | Qt::AlignCenter);
    mainLayout->addWidget(ClassementGroupBox, 0, 8, Qt::AlignTop | Qt::AlignLeft);

    mainLayout->addWidget(boutonPrecedent, 8, 0, 1, 1, Qt::AlignLeft | Qt::AlignBottom); // Précédent en bas à gauche
    mainLayout->addWidget(boutonDemarrer, 8, 8, 1, 1, Qt::AlignRight | Qt::AlignBottom); // Suivant en bas à droite

    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    // Connexions
    connect(boutonDemarrer, &QPushButton::clicked, this, &LoadGame::playClickSound);
    connect(boutonPrecedent, &QPushButton::clicked, this, &LoadGame::playClickSound);

    setFixedSize(1525, 785);
    setWindowTitle(tr("LABYRINTHUS GROUPE P6 : : PROJET DE FIN DE SESSION S2 -->> BAKAYOKO KANVALI"));
}

void LoadGame::playClickSound()
{
    // Déterminer le bouton cliqué
    QObject* obj = sender();
    QPushButton* button = qobject_cast<QPushButton*>(obj);

    if (button != nullptr)
    {
        SonClick.setSource(QUrl::fromLocalFile("clickSound.wav"));
        SonClick.setLoopCount(1);
        SonClick.setVolume(1.0f);
        SonClick.play();

        // vérifier l'identité du bouton en utilisant sa propriété
        QString role = button->property("role").toString();

        if (role == "demarrer")
        {
            // Faire quelque chose pour le bouton "Démarrer" Comme lancement du jeu
        }
        else if (role == "precedent")
        {
            if (mainWindow == nullptr)
            {
                mainWindow = new MainWindow(this);
                mainWindow->show();
                mainWindow->MenuPrincipale();
            }
            else
            {
                mainWindow->show();
                mainWindow->MenuPrincipale();
            }
            this->hide(); // Cachez la fenêtre d'authentification actuelle
        }
    }
}

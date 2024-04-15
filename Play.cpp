#include "Play.h"

Play::Play(QWidget* parent) :QMainWindow(parent)
{
    mainWindow = (MainWindow*)parent;
    MenuPlay();
}

void Play::paintEvent(QPaintEvent* event)
{
    // Ajout d'image en arriere plan
    QPainter painter(this);
    QPixmap background(":/images/play.jpg");

    if (background.isNull())
    {
        qDebug() << "L'image n'a pas pu être chargée ! Vérifiez le chemin.";
    }
    else
    {
        painter.drawPixmap(rect(), background);
    }
}

void Play::MenuPlay()
{
    // Configuration du widget central
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Création et configuration du groupe pour le bouton "Play"
    QGroupBox* playGroupBox = new QGroupBox("", this);
    playGroupBox->setStyleSheet("QGroupBox { border: 0; }");

    QVBoxLayout* playLayout = new QVBoxLayout(playGroupBox);

    // Création et configuration du bouton "Play"
    QPushButton* boutonPlay = new QPushButton(tr("JOUER"), playGroupBox);
    boutonPlay->setProperty("role", "play");
    boutonPlay->setFixedSize(300, 150);

    // Chargement de la police
    QFont font;
    int fontId = QFontDatabase::addApplicationFont(":/fonts/BadBoys.ttf");
    if (fontId != -1) {
        QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
        font = QFont(fontFamily, 105, QFont::Bold);
    }
    else {
        qDebug() << "Échec du chargement de la police BadBoys.";
        font = QFont("Arial", 105, QFont::Bold);
    }
    boutonPlay->setFont(font);

    // Style du bouton
    boutonPlay->setStyleSheet("QPushButton { color: green; background-color: transparent; border: none; }"
        "QPushButton:pressed { color: yellow; background-color: transparent; }");

    // Ajout du bouton au layout
    playLayout->addWidget(boutonPlay);
    playGroupBox->setLayout(playLayout);

    // Configuration du layout principal
    QGridLayout* mainLayout = new QGridLayout(centralWidget);
    mainLayout->setRowStretch(0, 1);
    mainLayout->setRowStretch(2, 1);
    mainLayout->setColumnStretch(0, 1);
    mainLayout->setColumnStretch(2, 1);
    mainLayout->addWidget(playGroupBox, 1, 1, Qt::AlignCenter); // Centre le groupe de boutons

    // Connecter le signal du bouton au slot approprié
    connect(boutonPlay, &QPushButton::clicked, this, &Play::playClickSound);

    // Configuration de la fenêtre
    setWindowState(Qt::WindowMaximized);
    setWindowTitle(tr("LABYRINTHUS GROUPE P6 : : PROJET DE FIN DE SESSION S2 -->> OLYMPUS"));
}


void Play::playClickSound()
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

        // Vérifier l'identité du bouton en utilisant sa propriété
        QString role = button->property("role").toString();

        if (role == "play")
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
        }
    }
}

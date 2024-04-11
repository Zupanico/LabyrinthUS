#include "Authentification.h"
#include "MainWindow.h"
#include "game.h"

Authentification::Authentification(QWidget* parent):QMainWindow(parent)
{
    mainWindow = qobject_cast<MainWindow*>(parent);
    MenuAuthentification();
}

void Authentification::paintEvent(QPaintEvent* event)
{
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

void Authentification::updateDemarrerButtonState()
{
    boutonDemarrer->setEnabled(!EditNomJoueur->text().isEmpty());
}

void Authentification::MenuAuthentification()
{
    qDeleteAll(this->findChildren<QWidget*>("", Qt::FindDirectChildrenOnly));
    centralWidget = new QWidget(this);

    QGridLayout* mainLayout = new QGridLayout(centralWidget);

    LabelAuthentification = new QLabel(tr("Veuillez entrer vos Noms"), centralWidget);
    LabelAuthentification->setAlignment(Qt::AlignCenter);
    LabelAuthentification->setStyleSheet("QLabel { color: red; }");

    EditNomJoueur = new QLineEdit(centralWidget);
    EditNomJoueur->setPlaceholderText(tr(""));
    EditNomJoueur->setMaxLength(25);
    EditNomJoueur->setStyleSheet("QLineEdit { color: white; }");
    EditNomJoueur->setAlignment(Qt::AlignCenter);

    boutonDemarrer = new QPushButton(centralWidget);
    boutonDemarrer->setIcon(QIcon(":/images/aller.png"));
    boutonDemarrer->setIconSize(QSize(60, 60));
    boutonDemarrer->setFixedSize(QSize(60, 60));
    boutonDemarrer->setFlat(true);
    boutonDemarrer->setProperty("role", "demarrer");

    boutonPrecedent = new QPushButton(centralWidget);
    boutonPrecedent->setIcon(QIcon(":/images/retour.png"));
    boutonPrecedent->setIconSize(QSize(60, 60));
    boutonPrecedent->setFixedSize(QSize(60, 60));
    boutonPrecedent->setFlat(true);
    boutonPrecedent->setProperty("role", "precedent");

    iconLabel = new QLabel(centralWidget);
    QPixmap originalIcon(":/images/profil.png");
    QPixmap resizedIcon = originalIcon.scaled(QSize(250, 250), Qt::KeepAspectRatio);
    iconLabel->setPixmap(resizedIcon);
    iconLabel->setAlignment(Qt::AlignCenter);

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

    LabelAuthentification->setFont(font);
    boutonDemarrer->setFont(font);
    boutonPrecedent->setFont(font);

    QFont font2;
    int fontId2 = QFontDatabase::addApplicationFont(":/fonts/BadBoys1.ttf");
    if (fontId2 != -1) {
        QString fontFamily2 = QFontDatabase::applicationFontFamilies(fontId2).at(0);
        font2 = QFont(fontFamily2, 25, QFont::Bold);
    }
    else {
        qDebug() << "Échec du chargement de la police BadBoys1.";
        font2 = QFont("Arial", 25, QFont::Bold);
    }
    EditNomJoueur->setFont(font2);

    mainLayout->addWidget(iconLabel, 0, 0, 2, 8, Qt::AlignCenter);
    mainLayout->addWidget(LabelAuthentification, 1, 1, 2, 6, Qt::AlignCenter);
    mainLayout->addWidget(EditNomJoueur, 2, 1, 1, 6, Qt::AlignCenter);
    mainLayout->addWidget(boutonPrecedent, 3, 0, 1, 2, Qt::AlignLeft | Qt::AlignBottom);
    mainLayout->addWidget(boutonDemarrer, 3, 6, 1, 2, Qt::AlignRight | Qt::AlignBottom);

    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    connect(boutonDemarrer, &QPushButton::clicked, this, &Authentification::playClickSound);
    connect(boutonPrecedent, &QPushButton::clicked, this, &Authentification::playClickSound);
    connect(EditNomJoueur, &QLineEdit::textChanged, this, &Authentification::updateDemarrerButtonState);

    setFixedSize(1525, 785);
    setWindowTitle(tr("LABYRINTHUS GROUPE P6 : : PROJET DE FIN DE SESSION S2 -->> BAKAYOKO KANVALI"));
}

void Authentification::startGame()
{
    // Créer une nouvelle instance du jeu
    g = new game(this);

    // Créer un timer pour mettre à jour le jeu à intervalles réguliers
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, g, &game::updateGame);
    timer->start(1000 / 30);

    // Connecter le signal GameOver au slot pour arrêter le timer
    connect(g, &game::GameOver, [&]() {
        timer->stop();
        });

    // Actualiser la map pour commencer le jeu
    g->actualiserMap("map1.txt");
}

void Authentification::restartGame()
{

}

void Authentification::continueGame()
{
}

void Authentification::playClickSound()
{
    QObject* obj = sender();
    QPushButton* button = qobject_cast<QPushButton*>(obj);

    if (button != nullptr)
    {
        SonClick.setSource(QUrl::fromLocalFile("clickSound.wav"));
        SonClick.setLoopCount(1);
        SonClick.setVolume(1.0f);
        SonClick.play();

        QString role = button->property("role").toString();

        if (role == "demarrer")
        {
            startGame();
        }
        else if (role == "precedent")
        {
            if (mainWindow == nullptr)
            {
                mainWindow = new MainWindow(this);
            }
            mainWindow->show();
            mainWindow->MenuPrincipale();
            this->hide();
        }
    }
}

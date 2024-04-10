#include "Authentification.h"

Authentification::Authentification(QWidget* parent):QMainWindow(parent)
{
    MenuAuthentification();
}

void Authentification::paintEvent(QPaintEvent* event)
{
    // Ajout d'image en arriere plan
    QPainter painter(this);
    QPixmap background(":/images/imgInterface.jpg");

    if (background.isNull())
    {
        qDebug() << "L'image n'a pas pu �tre charg�e ! V�rifiez le chemin.";
    }
    else
    {
        painter.drawPixmap(rect(), background);
    }
}

void Authentification::updateDemarrerButtonState()
{
    // Slot pour mettre � jour l'�tat du bouton "D�marrer"
    boutonDemarrer->setEnabled(!EditNomJoueur->text().isEmpty());

    // Appelle le debut du jeux
}

void Authentification::MenuAuthentification()
{
    // Supprime tous les enfants de ce widget
    qDeleteAll(this->findChildren<QWidget*>("", Qt::FindDirectChildrenOnly));

    centralWidget = new QWidget(this);

    QGridLayout* mainLayout = new QGridLayout(centralWidget);

    // Configuration des groupes et layouts
    QGroupBox* infoGroupBox = new QGroupBox(tr(""), this);
    infoGroupBox->setStyleSheet("QGroupBox { border: 0; }"); // Masquer les contours

    QVBoxLayout* infoLayout = new QVBoxLayout(infoGroupBox);
    QLabel* LabelAuthentification = new QLabel(tr("Veuillez entrer vos Noms"), infoGroupBox);

    LabelAuthentification->setAlignment(Qt::AlignCenter);
    LabelAuthentification->setStyleSheet("QLabel { color: red; }");

    QLineEdit* EditNomJoueur = new QLineEdit(infoGroupBox);
    EditNomJoueur->setPlaceholderText(tr(""));
    EditNomJoueur->setMaxLength(25);
    EditNomJoueur->setStyleSheet("QLineEdit { color: white; }");
    EditNomJoueur->setAlignment(Qt::AlignCenter);

    infoLayout->addWidget(LabelAuthentification);
    infoLayout->addWidget(EditNomJoueur);
    infoGroupBox->setLayout(infoLayout);

    // Ajouter un QLabel pour afficher l'ic�ne
    QGroupBox* iconeGroupBox = new QGroupBox(tr(""), this);
    iconeGroupBox->setStyleSheet("QGroupBox { border: 0; }"); // Masquer les contours

    QVBoxLayout* infoLayout1 = new QVBoxLayout(iconeGroupBox);
    QLabel* iconLabel = new QLabel(this);

    QPixmap originalIcon(":/images/profil.png");
    QPixmap resizedIcon = originalIcon.scaled(QSize(2500, 250), Qt::KeepAspectRatio); // Redimensionner l'ic�ne

    iconLabel->setPixmap(resizedIcon);
    iconLabel->setAlignment(Qt::AlignCenter);

    infoLayout1->addWidget(iconLabel);
    iconeGroupBox->setLayout(infoLayout1);

    // Chargement et application des polices pour Authentification
    QFont font1;
    int fontId1 = QFontDatabase::addApplicationFont(":/fonts/BadBoys.ttf");
    if (fontId1 != -1) {
        QString fontFamily = QFontDatabase::applicationFontFamilies(fontId1).at(0);
        font1 = QFont(fontFamily, 45, QFont::Bold);
    }
    else {
        qDebug() << "�chec du chargement de la police BadBoys.";
        font1 = QFont("Arial", 45, QFont::Bold);
    }
    LabelAuthentification->setFont(font1);

    // Chargement et application des polices pour EditNomJoueur
    QFont font2;
    int fontId2 = QFontDatabase::addApplicationFont(":/fonts/BadBoys1.ttf");
    if (fontId2 != -1) {
        QString fontFamily = QFontDatabase::applicationFontFamilies(fontId2).at(0);
        font2 = QFont(fontFamily, 25, QFont::Bold);
    }
    else {
        qDebug() << "�chec du chargement de la police BadBoys1.";
        font2 = QFont("Arial", 25, QFont::Bold);
    }
    EditNomJoueur->setFont(font2);

    // Chargement et application des polices pour tous le reste
    QFont font;
    int fontId = QFontDatabase::addApplicationFont(":/fonts/BadBoys.ttf");
    if (fontId != -1) {
        QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
        font = QFont(fontFamily, 40, QFont::Bold);
    }
    else {
        qDebug() << "�chec du chargement de la police BadBoys.";
        font = QFont("Arial", 40, QFont::Bold);
    }

    // Cr�ation du QPushButton pour afficher l'ic�ne Suivant
    boutonDemarrer = new QPushButton(this);
    QPixmap originalNextIcon(":/images/aller.png"); // Chemin de l'ic�ne suivant
    QPixmap resizedNextIcon = originalNextIcon.scaled(QSize(60, 60), Qt::KeepAspectRatio); // Redimensionner l'ic�ne
    boutonDemarrer->setIcon(QIcon(resizedNextIcon));
    boutonDemarrer->setIconSize(resizedNextIcon.size());
    boutonDemarrer->setFixedSize(resizedNextIcon.size()); // Taille fixe pour s'adapter � l'ic�ne
    boutonDemarrer->setFlat(true); // Rendre le bouton sans bordure
    boutonDemarrer->setProperty("role", "demarrer");

    // Ajouter l'ic�ne Suivant dans le grid layout
    connect(boutonDemarrer, &QPushButton::clicked, this, &Authentification::playClickSound);

    // Cr�ation du QPushButton pour afficher l'ic�ne Pr�c�dent
    boutonPrecedent = new QPushButton(this);
    QPixmap originalPrevIcon(":/images/retour.png"); // Chemin de l'ic�ne pr�c�dente
    QPixmap resizedPrevIcon = originalPrevIcon.scaled(QSize(60, 60), Qt::KeepAspectRatio); // Redimensionner l'ic�ne
    boutonPrecedent->setIcon(QIcon(resizedPrevIcon));
    boutonPrecedent->setIconSize(resizedPrevIcon.size());
    boutonPrecedent->setFixedSize(resizedPrevIcon.size()); // Taille fixe pour s'adapter � l'ic�ne
    boutonPrecedent->setFlat(true); // Rendre le bouton sans bordure
    boutonPrecedent->setProperty("role", "precedent");

    // Ajouter l'ic�ne Pr�c�dent dans le grid layout
    connect(boutonPrecedent, &QPushButton::clicked, this, &Authentification::playClickSound);

    mainLayout->setRowStretch(0, 1);  // Espacement en haut
    mainLayout->setRowStretch(2, 1);  // Espacement en bas
    mainLayout->setColumnStretch(0, 1);  // Espacement � gauche
    mainLayout->setColumnStretch(2, 1);  // Espacement � droite

    mainLayout->addWidget(infoGroupBox, 1, 1, 1, 1, Qt::AlignCenter); // Ajouter infoGroupBox dans la premi�re ligne
    mainLayout->addWidget(iconeGroupBox, 0, 0, 1, 3, Qt::AlignCenter); // Ajouter iconeGroupBox au milieu

    // Ajouter les boutons Suivant et Pr�c�dent en bas de la grille
    mainLayout->addWidget(boutonPrecedent, 2, 0, 1, 1, Qt::AlignLeft | Qt::AlignBottom); // Pr�c�dent en bas � gauche
    mainLayout->addWidget(boutonDemarrer, 2, 2, 1, 1, Qt::AlignRight | Qt::AlignBottom); // Suivant en bas � droite

    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    // Connexions
    connect(boutonDemarrer, &QPushButton::clicked, this, &Authentification::playClickSound);
    connect(boutonPrecedent, &QPushButton::clicked, this, &Authentification::playClickSound);
/*    connect(EditNomJoueur, &QLineEdit::textChanged, this, [boutonDemarrer](const QString& text) 
        { 
                boutonDemarrer->setEnabled(!text.isEmpty());
        }
    )*/;


    setFixedSize(1525, 785);
    setWindowTitle(tr("LABYRINTHUS GROUPE P6 : : PROJET DE FIN DE SESSION S2 -->> BAKAYOKO KANVALI"));
}

void Authentification::playClickSound()
{
    // D�terminer le bouton cliqu�
    QObject* obj = sender();
    QPushButton* button = qobject_cast<QPushButton*>(obj);

    if (button != nullptr)
    {
        SonClick.setSource(QUrl::fromLocalFile("clickSound.wav"));
        SonClick.setLoopCount(1);
        SonClick.setVolume(1.0f);
        SonClick.play();

        // v�rifier l'identit� du bouton en utilisant sa propri�t�
        QString role = button->property("role").toString();

        if (role == "demarrer")
        {
            // Faire quelque chose pour le bouton "D�marrer" Comme lancement du jeu
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
            this->hide(); // Cachez la fen�tre d'authentification actuelle
        }
    }
}

